#ifndef EXT2FS_CHECK_CHECK_SUPER_H
#define EXT2FS_CHECK_CHECK_SUPER_H

#include "../run_check/file_entry.h"
#include <linux/fs.h>
#include <ext2fs/ext2_fs.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <filesystem>
#include <cmath>

int check_filesystem_size (file_entry* filesystem, ext2_super_block* super_block);
int check_group_size (ext2_super_block* super_block);
int check_num_blocks (ext2_super_block* super_block);
int check_total_num_inodes (ext2_super_block* super_block);
int check_total_num_blocks (ext2_super_block* super_block);
int check_reserved_num_blocks (ext2_super_block* super_block);
int check_num_blocks_per_group(ext2_super_block* super_block);
int check_num_inodes_per_group(ext2_super_block* super_block);
int check_num_fragments_per_group(ext2_super_block* super_block);


#endif //EXT2FS_CHECK_CHECK_SUPER_H
