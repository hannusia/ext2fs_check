# ext2fs_check

# OS course project
Authors: [Olha Liuba](https://github.com/oliuba), [Hanna Yershova](https://github.com/hannusia), [Ihor Ramskyi](https://github.com/botanich)

# Prerequisites:
- CMake (3.23 minimum version)
- Unix-like OS
- ext2 partition or image
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
