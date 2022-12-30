#include "iterate_filesystem_tree.h"

int slay_dir (FILE* fp, ext2_super_block* super, ext2_group_desc* group, size_t inode_num, std::vector<int>& checked, int inode_check) {
    struct ext2_inode inode;
    struct ext2_dir_entry_2 dir_entry;
    int fseek_res;
    size_t read_res;
    size_t block_size = 1024 << super->s_log_cluster_size;

    if ((fseek_res = fseek(fp, group->bg_inode_table * block_size + (inode_num - 1) * sizeof(struct ext2_inode), SEEK_SET)) != 0) {
        std::cerr << "Fseek " << inode_num << " inode error (no slay)" << std::endl;
        return -2;
    }

    if ((read_res = fread(&inode, 1, sizeof(inode), fp)) != sizeof(inode)) {
        std::cerr << "Reading " << inode_num << " inode error (no slay)" << std::endl;
        return -3;
    }

    if ((fseek_res = fseek(fp, inode.i_block[0] * block_size, SEEK_SET)) != 0) {
        std::cerr << "Fseek dir entry error (no slay)" << std::endl;
        return -2;
    }

    if ((read_res = fread(&dir_entry, 1, sizeof(dir_entry), fp)) != sizeof(dir_entry)) {
        std::cerr << "Reading root entry error (no slay)" << std::endl;
        return -3;
    }

    size_t next_entry = inode.i_block[0] * block_size;
    struct ext2_inode next_inode;

    while (next_entry < inode.i_block[0] * block_size + inode.i_size) {
        if (dir_entry.inode == 0) {
            return 0;
        }

        if ((fseek_res = fseek(fp, group->bg_inode_table * block_size + (dir_entry.inode - 1) * sizeof(struct ext2_inode), SEEK_SET)) != 0) {
            std::cerr << "Fseek root inode error (no slay)" << std::endl;
            return -2;
        }

        if ((read_res = fread(&next_inode, 1, sizeof(next_inode), fp)) != sizeof(next_inode)) {
            std::cerr << "Reading " << dir_entry.inode << " inode error (no slay)" << std::endl;
            return -3;
        }

        if (next_inode.i_block[0] < super->s_first_data_block) {
            std::cerr << "Error with " << dir_entry.inode << " inode data block";
            inode_check--;
        }

        if ((dir_entry.file_type == 2) and (is_untracked(checked, dir_entry.inode))) {
            checked.push_back(dir_entry.inode);
            slay_dir(fp, super, group, dir_entry.inode, checked, inode_check);
        }

        next_entry += dir_entry.rec_len;

        // set file offset to next directory entry
        if ((fseek_res = fseek(fp, next_entry, SEEK_SET)) != 0) {
            std::cerr << "Fseek next root entry error (no slay)" << std::endl;
            return -2;
        }

        if ((read_res = fread(&dir_entry, 1, sizeof(dir_entry), fp)) != sizeof(dir_entry)) {
            std::cerr << "Reading next root entry error (no slay)" << std::endl;
            return -3;
        }
    }
    return 0;
}

int is_untracked (const std::vector<int>& checked, int inode_num) {
    for (int i : checked) {
        if (i == inode_num) {
            return 0;
        }
    }
    return 1;
}

int iterate_tree (FILE* fp, ext2_super_block* super, ext2_group_desc* group) {
    int inode_check = 0;
    std::vector<int> checked;
    size_t block_size = 1024 << super->s_log_cluster_size;
    slay_dir(fp, super, group, 2, checked, inode_check);
    if (group->bg_used_dirs_count != checked.size()) {
        std::cerr << "Number of directories is wrong!" << std::endl;
        return -1;
    }
    std::cout << "Correct number of directories" << std::endl;
    if (inode_check != 0) {
        return -1;
    }
    std::cout << "Correct inodes data blocks" << std::endl;
    return 0;
}