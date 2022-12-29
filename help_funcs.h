#ifndef EXT2FS_CHECK_HELP_FUNCS_H
#define EXT2FS_CHECK_HELP_FUNCS_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <ext2fs/ext2_fs.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <filesystem>
#include "options_parser/options_parser.h"

struct file_entry {
    FILE* file_ptr;
    const char *filename;
};

constexpr size_t base_offset = 1024;
int check_filesystem_size (file_entry* filesystem, ext2_super_block* super_block);
int check_group_size (ext2_super_block* super_block);
int check_num_blocks (ext2_super_block* super_block);
int check_total_num_inodes (ext2_super_block* super_block);
int check_total_num_blocks (ext2_super_block* super_block);
int check_reserved_num_blocks (ext2_super_block* super_block);
int check_num_blocks_per_group(ext2_super_block* super_block);
int check_num_inodes_per_group(ext2_super_block* super_block);
int check_num_fragments_per_group(ext2_super_block* super_block);
int check_free_num (std::vector<char> &bitmap, uint16_t expected_free);
int check_free_blocks_num (FILE* fp, ext2_group_desc* group, size_t block_size);
int check_free_inodes_num (FILE* fp, ext2_group_desc* group, size_t block_size);
int check_filesystem (file_entry* filesystem);

#endif //EXT2FS_CHECK_HELP_FUNCS_H
