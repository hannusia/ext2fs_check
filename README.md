# ext2fs_check

# OS course project
Authors: [Olha Liuba](https://github.com/oliuba), [Hanna Yershova](https://github.com/hannusia), [Ihor Ramskyi](https://github.com/botanich)

# Prerequisites:
- CMake (3.23 minimum version)
- Unix-like OS
- ext2 image
- g++ compiler (C++20)

# What it does:
Checks if there are corruptions/troubles with ext2 partition or image

# Installation and build:
```
$ git clone https://github.com/hannusia/ext2fs_check/
$ cd ext2fs_check
$ ./compile.sh -O
```

after installation and build executable `ext2fs_check` will be in `bin` folder

# Usage
```
$ ext2fs_check [-h|--help] <filesystem>
```

# To create an ext2fs image you can use following commands
```
# create file
mkfs.ext2 file 1000

# mount it
sudo mkdir /mnt/file
sudo mount -t ext2 -o loop file /mnt/file

# check if mounted
mount -t ext2

# unmount
# save the filesystem to file
sudo umount /mnt/file
```

# Documentation

Functions that check filesystem are divided into four groups:
## check_super
functions that check super block consistency

- `int check_filesystem_size (file_entry* filesystem, ext2_super_block* super_block)` -- check that filesystem size is bigger than number of blocks multiplied by block size;

- `int check_group_size (ext2_super_block* super_block)` -- check that group size counted from blocks (multiply block size by number of blocks per group) is equal to group size counted from fragments (multiply fragment size by number of fragments per group);

- `int check_num_block_groups (ext2_super_block* super_block)` -- check that number of block grups counted from dividing all blocks by blocks per group is equal to number of block grups counted from dividing all inodes by inodes per group;

- `int check_total_num_inodes (ext2_super_block* super_block)` -- check that total number of inodes is greater or equal to number of free inodes;

- `int check_total_num_blocks (ext2_super_block* super_block)` -- check that total number of blocks is greater or equal to number of free blocks;

- `int check_reserved_num_blocks (ext2_super_block* super_block)` -- check that total number of blocks is greater or equal to number of reserved blocks;

- `int check_num_blocks_per_group(ext2_super_block* super_block)` -- check that number of blocks per group is less than or equal to number of bits in a block (for blocks to fit into block bitmap);

- `int check_num_inodes_per_group(ext2_super_block* super_block)` -- check that number of inodes per group is less than or equal to number of bits in a block (for inodes to fit into inode bitmap);

- `int check_num_fragments_per_group(ext2_super_block* super_block)` -- check that number of fragments per group is less or equal to number of bits in a block (for fragments to fit into bitmap);

## check_group
functions that check group descriptor block consistency

- `int check_free_num (std::vector<char> &bitmap, uint16_t expected_free)` -- auxilary function to check bitmaps for zero bits and compare the number of such bits to an expected number of zero bits; used for checking free blocks/inodes;

- `int check_free_blocks_num (FILE* fp, ext2_group_desc* group, size_t block_size)` -- checks that number of free blocks stated in block group descriptor table is equal to number of free blocks that appear in the block bitmap as zero bits;

- `int check_free_inodes_num (FILE* fp, ext2_group_desc* group, size_t block_size)` -- checks that number of free inodes stated in block group descriptor table is equal to number of free inodes that appear in the inode bitmap as zero bits;

## iterate_fs
contains function that recursively iterates through filesystem tree

- `int slay_dir (FILE* fp, ext2_group_desc* group, size_t block_size, size_t inode_num, std::vector<int>& checked)` -- checks directory entries in one directory, if entry is another directory then recursively calls itself;

- `int is_untracked (const std::vector<int>& checked, int inode_num)` -- check if we already checked inode;

- `int iterate_tree (FILE* fp, ext2_group_desc* group, size_t block_size)` -- main function for filesystem iteration also checks if number of directories if correct and checks data bloks for each inode;

## run_check
- `int check_filesystem (file_entry* filesystem)` -- main function with all checks;


