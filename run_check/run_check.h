#ifndef EXT2FS_CHECK_RUN_CHECK_H
#define EXT2FS_CHECK_RUN_CHECK_H

#include "options_parser.h"
#include "file_entry.h"
#include "../check_super/check_super.h"
#include "../check_group/check_group.h"
#include "../iterate_fs/iterate_filesystem_tree.h"

constexpr size_t base_offset = 1024;
int check_filesystem (file_entry* filesystem);

#endif //EXT2FS_CHECK_RUN_CHECK_H
