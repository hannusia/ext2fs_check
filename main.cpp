#include "help_funcs.h"

int main(int argc, char* argv[]) {
    struct ext2_super_block super;
    struct ext2_group_desc group;
    std::string filesystem_name;
    int fd;
    FILE *fp;
    file_entry filesystem;

    command_line_options_t command_line_options{argc, argv};
    std::vector<std::string> filesystems = command_line_options.get_filesystems();

    if (filesystems.size() != 1) {
        std::cerr << "Wrong number of arguments (no slay)" << std::endl;
    }

    filesystem_name = filesystems[0];

    fp = fopen(filesystem_name.data(), "rb");

    if (!fp) {
        std::cerr << "Failed to open file (no slay)" << std::endl;
        return -1;
    }

    filesystem.file_ptr = fp;
    filesystem.filename = filesystem_name.c_str();

    check_filesystem(&filesystem);

    return 0;
}