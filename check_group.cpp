#include "check_group.h"

int check_free_num (std::vector<char> &bitmap, uint16_t expected_free) {
    size_t free = 0;
    for (auto c: bitmap) {
        for (int i = 7; i >= 0; --i) {
            if (!(c & (1 << i))) {
                free++; // block is free if 0
            }
        }
    }
    if (free == expected_free) {
        return 0;
    }
    return -1;
}

int check_free_blocks_num (FILE* fp, ext2_group_desc* group, size_t block_size) {
    auto block_bitmap_addr = group->bg_block_bitmap * block_size;
    std::vector<char> block_bitmap(block_size);
    if (fseek(fp, block_bitmap_addr, SEEK_SET) != 0) {
        std::cerr << "Fseek block bitmap error (no slay)" << std::endl;
        return -2;
    }

    if (fread(&block_bitmap[0], 1, block_bitmap.size(), fp) != block_bitmap.size()) {
        std::cerr << "Reading block bitmap error (no slay)" << std::endl;
        return -3;
    }

    if (check_free_num(block_bitmap, group->bg_free_blocks_count) == 0) {
        std::cout << "Correct free blocks count" << std::endl;
        return 0;
    }
    std::cerr << "Wrong free blocks count" << std::endl;
    return -1;
}

int check_free_inodes_num (FILE* fp, ext2_group_desc* group, size_t block_size) {
    auto inode_bitmap_addr = group->bg_inode_bitmap * block_size;
    std::vector<char> inode_bitmap(block_size);

    if (fseek(fp, inode_bitmap_addr, SEEK_SET) != 0) {
        std::cerr << "Fseek block bitmap error (no slay)" << std::endl;
        return -2;
    }

    if (fread(&inode_bitmap[0], 1, inode_bitmap.size(), fp) != inode_bitmap.size()) {
        std::cerr << "Reading inode bitmap error (no slay)" << std::endl;
        return -3;
    }

    if (check_free_num(inode_bitmap, group->bg_free_inodes_count) == 0) {
        std::cout << "Correct free inodes count" << std::endl;
        return 0;
    }
    std::cerr << "Wrong free inodes count" << std::endl;
    return -1;
}