#include "check_super.h"

int check_filesystem_size (file_entry* filesystem, ext2_super_block* super_block) {
    std::uintmax_t filesystem_size = std::filesystem::file_size(filesystem->filename);
    size_t block_size = 1024 << super_block->s_log_block_size;
    size_t actual_size = super_block->s_blocks_count * block_size;
    if (filesystem_size < actual_size) {
        std::cerr << "Wrong filesystem size" << std::endl;
        return -1;
    }
    std::cout << "Correct filesystem size" << std::endl;
    return 0;
}

int check_group_size (ext2_super_block* super_block) {
    size_t block_size = 1024 << super_block->s_log_block_size;
    size_t fragment_size = 1024 << super_block->s_log_cluster_size;
    auto group_size_blocks = block_size * super_block->s_blocks_per_group;
    auto group_size_fragments = fragment_size * super_block->s_clusters_per_group;
    if (group_size_blocks != group_size_fragments) {
        std::cerr << "Wrong group size" << std::endl;
        return -1;
    }
    std::cout << "Correct group size" << std::endl;
    return 0;
}

int check_num_blocks (ext2_super_block* super_block) {
    auto block_num_blocks = std::ceil(static_cast<double>(super_block->s_blocks_count) /
                                      static_cast<double>(super_block->s_blocks_per_group));
    auto block_num_inodes = std::ceil(static_cast<double>(super_block->s_inodes_count) /
                                      static_cast<double>(super_block->s_inodes_per_group));
    if (block_num_blocks == block_num_inodes) {
        std::cout << "Correct number of blocks" << std::endl;
        return 0;
    }
    std::cerr << "Wrong number of blocks" << std::endl;
    return -1;
}

int check_total_num_inodes (ext2_super_block* super_block) {
    if (super_block->s_inodes_count >= super_block->s_free_inodes_count) {
        std::cout << "Correct total & free number of inodes" << std::endl;
        return 0;
    }
    std::cerr << "Total number of inodes is smaller than number of free inodes" << std::endl;
    return -1;
}

int check_total_num_blocks (ext2_super_block* super_block) {
    if (super_block->s_blocks_count >= super_block->s_free_blocks_count) {
        std::cout << "Correct total & free number of blocks" << std::endl;
        return 0;
    }
    std::cerr << "Total number of blocks is smaller than number of free blocks" << std::endl;
    return -1;
}

int check_reserved_num_blocks (ext2_super_block* super_block) {
    if (super_block->s_blocks_count >= super_block->s_r_blocks_count) {
        std::cout << "Correct total & reserved number of blocks" << std::endl;
        return 0;
    }
    std::cerr << "Total number of blocks is smaller than number of reserved blocks" << std::endl;
    return -1;
}

int check_num_blocks_per_group(ext2_super_block* super_block) {
    unsigned int block_size = 1024 << super_block->s_log_block_size;
    unsigned int calc_num_blocks_per_group = 8 * block_size;  // because block group block bitmap takes exactly one block
    if (super_block->s_blocks_per_group <= calc_num_blocks_per_group) {
        std::cout << "Correct count of blocks per group" << std::endl;
        return 0;
    }
    std::cerr << "Number of blocks per group is bigger than possible" << std::endl;
    return -1;
}

int check_num_inodes_per_group(ext2_super_block* super_block) {
    unsigned int block_size = 1024 << super_block->s_log_block_size;
    unsigned int calc_num_inodes_per_group = 8 * block_size;  // because block group inode bitmap takes exactly one block
    if (super_block->s_inodes_per_group <= calc_num_inodes_per_group) {
        std::cout << "Correct count of inodes per group" << std::endl;
        return 0;
    }
    std::cerr << "Number of inodes per group is bigger than possible" << std::endl;
    return -1;
}

int check_num_fragments_per_group(ext2_super_block* super_block) {
    unsigned int fragment_size = 1024 << super_block->s_log_cluster_size;
    unsigned int calc_num_fragments_per_group = 8 * fragment_size;
    if (super_block->s_clusters_per_group <= calc_num_fragments_per_group) {
        std::cout << "Correct count of fragments per group" << std::endl;
        return 0;
    }
    std::cerr << "Number of fragments per group is bigger than possible" << std::endl;
    return -1;
}