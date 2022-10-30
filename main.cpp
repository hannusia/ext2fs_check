#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <ext2fs/ext2_fs.h>
#include <iostream>
#include "options_parser/options_parser.h"

int check_filesystem(const std::string & filesystem) {
    FILE *fp;
    fp = fopen(filesystem.data(), "rb");

    if (!fp) {
        std::cerr << "Failed to open file" << std::endl;
        return -1;
    }

    return 0;
};

int main(int argc, char* argv[]) {
    struct ext2_super_block super;
    struct ext2_group_desc group;
    int fd;

    command_line_options_t command_line_options{argc, argv};
    std::vector<std::string> filesystems = command_line_options.get_filesystems();

    for (auto filesystem:filesystems) {

    }
    return 0;
}