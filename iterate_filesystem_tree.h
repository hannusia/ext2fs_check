#ifndef EXT2FS_CHECK_ITERATE_FILESYSTEM_TREE_H
#define EXT2FS_CHECK_ITERATE_FILESYSTEM_TREE_H

#include <linux/fs.h>
#include <ext2fs/ext2_fs.h>
#include <cstdio>
#include <iostream>
#include <vector>

int slay_dir (FILE* fp, ext2_group_desc* group, size_t block_size, size_t inode_num, std::vector<int>& checked);
int is_untracked (const std::vector<int>& checked, int inode_num);
int iterate_tree (FILE* fp, ext2_group_desc* group, size_t block_size);

#endif //EXT2FS_CHECK_ITERATE_FILESYSTEM_TREE_H
