#ifndef EXT2FS_CHECK_CHECK_GROUP_H
#define EXT2FS_CHECK_CHECK_GROUP_H

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
#include <vector>

int check_free_num (std::vector<char> &bitmap, uint16_t expected_free);
int check_free_blocks_num (FILE* fp, ext2_group_desc* group, size_t block_size);
int check_free_inodes_num (FILE* fp, ext2_group_desc* group, size_t block_size);


#endif //EXT2FS_CHECK_CHECK_GROUP_H
