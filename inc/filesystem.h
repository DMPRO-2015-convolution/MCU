#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "ff.h"

extern void init_filesystem();
extern void open_file(FIL *file, char *filename);
extern void read_file(FIL *file, void *buffer, UINT bytesToRead, UINT *bytesRead);
extern void close_file(FIL *file);
extern void seek_file(FIL *file, DWORD offset);

#endif
