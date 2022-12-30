#include "run_check.h"

int check_filesystem (file_entry* filesystem) {
    int fseek_res;
    int exit_code = 0;
    size_t read_res;
    FILE* fp = filesystem->file_ptr;

    //--------------------------------------------------------------------------
    //  Get super block info
    //--------------------------------------------------------------------------
    struct ext2_super_block super = {};

    if ((fseek_res = fseek(fp, base_offset, SEEK_SET)) != 0) {
        std::cerr << "Fseek super block error (no slay)" << std::endl;
        return -2;
    }

    if ((read_res = fread(&super, 1, sizeof(super), fp)) != sizeof(super)) {
        std::cerr << "Reading super block error (no slay)" << std::endl;
        return -3;
    }

    if (super.s_magic != EXT2_SUPER_MAGIC) {
        std::cerr << "Filesystem is not ext2 (anti slay)" << std::endl;
        return -4;
    }

    //--------------------------------------------------------------------------
    //  Get group block info
    //--------------------------------------------------------------------------
    struct ext2_group_desc group = {};
    size_t block_size = 1024 << super.s_log_block_size;

    if ((fseek_res = fseek(fp, base_offset + block_size, SEEK_SET)) != 0) {
        std::cerr << "Fseek group block error (no slay)" << std::endl;
        return -2;
    }

    if ((read_res = fread(&group, 1, sizeof(group), fp)) != sizeof(group)) {
        std::cerr << "Reading group block error (no slay)" << std::endl;
        return -3;
    }

    exit_code += check_filesystem_size(filesystem, &super);
    exit_code += check_group_size(&super);
    exit_code += check_num_blocks(&super);
    exit_code += check_total_num_inodes(&super);
    exit_code += check_total_num_blocks(&super);
    exit_code += check_reserved_num_blocks(&super);
    exit_code += check_num_blocks_per_group(&super);
    exit_code += check_num_inodes_per_group(&super);
    exit_code += check_num_fragments_per_group(&super);
    exit_code += check_free_blocks_num(fp, &group, block_size);
    exit_code += check_free_inodes_num(fp, &group, block_size);
    exit_code += iterate_tree(fp, &group, block_size);

    // state contains information about errors: 1 means no errors, 2 means errors in filesystem
    if (exit_code == 0) {
        super.s_state = 1;
    } else {
        super.s_state = 2;
    }
    return exit_code;
}