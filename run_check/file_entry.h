#ifndef EXT2FS_CHECK_FILE_ENTRY_H
#define EXT2FS_CHECK_FILE_ENTRY_H

#include <cstdio>

struct file_entry {
    FILE* file_ptr;
    const char *filename;
};

#endif //EXT2FS_CHECK_FILE_ENTRY_H
