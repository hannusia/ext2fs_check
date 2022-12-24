#include "help_funcs.h"

std::string seconds_to_datetime(uint32_t seconds) {
    std::time_t temp = seconds;
    std::tm* t = std::gmtime(&temp);
    std::stringstream ss; // or if you're going to print, just input directly into the output stream
    ss << std::put_time(t, "%Y-%m-%d %I:%M:%S %p");
    return ss.str();
}

int check_filesystem_size (file_entry* filesystem, ext2_super_block* super_block) {
    std::uintmax_t filesystem_size = std::filesystem::file_size(filesystem->filename);
    size_t block_size = 1024 << super_block->s_log_block_size;
    size_t actual_size = super_block->s_blocks_count * block_size;
    if (filesystem_size < actual_size) {
        return -1;
    }
    return 0;
}


int check_filesystem (file_entry* filesystem) {
    int fseek_res;
    size_t read_res;
    size_t block_size = 0;
    FILE* fp = filesystem->file_ptr;

    //--------------------------------------------------------------------------
    //  Get super block info
    //--------------------------------------------------------------------------
    struct ext2_super_block super;

    if ((fseek_res = fseek(fp, base_offset, SEEK_SET)) != 0) {
        std::cerr << "Fseek super block error (no slay)" << std::endl;
        return -2;
    }

    if ((read_res = fread(&super, 1, sizeof(super), fp)) != sizeof(super)) {
        std::cerr << "Reading super block error (no slay)" << std::endl;
        return -3;
    }

    if (super.s_magic != EXT2_SUPER_MAGIC) {
        std::cerr << "Filesystem is not ext2 (anti slay)" << std::endl;
        return -4;
    }

    //--------------------------------------------------------------------------
    //  Get group block info
    //--------------------------------------------------------------------------
    struct ext2_group_desc group;

    block_size = 1024 << super.s_log_block_size;

    if ((fseek_res = fseek(fp, block_size, SEEK_SET)) != 0) {
        std::cerr << "Fseek group block error (no slay)" << std::endl;
        return -2;
    }

    if ((read_res = fread(&group, 1, sizeof(group), fp)) != sizeof(group)) {
        std::cerr << "Reading group block error (no slay)" << std::endl;
        return -3;
    }

    std::cout << check_filesystem_size(filesystem, &super) << std::endl;
}
