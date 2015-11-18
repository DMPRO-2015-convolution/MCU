#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "ff.h"

// Read buffer size

extern void init_filesystem();

//
// File operations
//
#define READ_BUFFER_SIZE 64
extern void open_file(FIL *file, char *filename);
extern void read_file(FIL *file, void *buffer, UINT bytesToRead, UINT *bytesRead);
extern void close_file(FIL *file);
extern void seek_file(FIL *file, DWORD offset);


// Directory
#define FILE_COUNT 5
#define FILENAME_LENGTH 32
extern void get_filenames(char *path, char strings[FILE_COUNT][FILENAME_LENGTH], int* num_files);



//
// Kernel
//
#define MAX_KERNEL_SIZE 49

typedef struct {
	uint16_t size;
	int16_t elements[MAX_KERNEL_SIZE];
} kernel_t;

extern void load_kernel(char *filename, kernel_t *kernel);


//
// BMP
//
#define BMP_HEADER_SIZE 14
#define BMP_INFO_HEADER_SIZE 40

typedef struct {
	uint16_t signature;
	uint32_t size;
	uint32_t reserved;
	uint32_t image_data_offset;
} BMP_HEADER ;

typedef struct {
	uint32_t size;
	uint32_t width;
	uint32_t height;
	uint16_t num_planes;
	uint16_t bitcount;
	uint32_t compression;
	uint32_t compressedImageSize;
	uint32_t xPixelsPerM;
	uint32_t yPixelsPerM;
	uint32_t colorsUsed;
	uint32_t colorsImportant;
} BMP_INFO_HEADER;



#endif
