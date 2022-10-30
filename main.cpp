#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <ext2fs/ext2_fs.h>
#include <iostream>
#include "options_parser/options_parser.h"

int check_filesystem(const std::string & filesystem) {
    constexpr size_t base_offset = 1024;
    struct ext2_super_block super;
    struct ext2_group_desc group;
    size_t block_size = 0;
    size_t read_res;
    int fseek_res;

    FILE *fp;

    fp = fopen(filesystem.data(), "rb");

    if (!fp) {
        std::cerr << "Failed to open file (no slay)" << std::endl;
        return -1;
    }

    if ((fseek_res = fseek(fp, base_offset, SEEK_SET)) != 0) {
//        std::cout << fseek_res << std::endl;
        std::cerr << "Fseek super block error (no slay)" << std::endl;
        return -2;
    }

    if ((read_res = fread(&super, 1, sizeof(super), fp)) != sizeof(super)) {
//        std::cout << read_res << " " << sizeof(super) << std::endl;
        std::cerr << "Reading super block error (no slay)" << std::endl;
        return -3;
    }

    if (super.s_magic != EXT2_SUPER_MAGIC) {
        std::cerr << "Filesystem is not ext2 (anti slay)" << std::endl;
        return -4;
    }

    block_size = 1024 << super.s_log_block_size;

    if ((fseek_res = fseek(fp, base_offset + block_size, SEEK_SET)) != 0) {
//        std::cout << fseek_res << std::endl;
        std::cerr << "Fseek group block error (no slay)" << std::endl;
        return -2;
    }
    if ((read_res = fread(&group, 1, sizeof(group), fp)) != sizeof(group)) {
//        std::cout << read_res << " " << sizeof(group) << std::endl;
        std::cerr << "Reading group block error (no slay)" << std::endl;
        return -3;
    }
    fclose(fp);
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