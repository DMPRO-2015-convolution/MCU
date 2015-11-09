#include "ff.h"
#include "microsd.h"
#include "diskio.h"
#include "filesystem.h"
#include <string.h>


#define BUFFER_SIZE 1024
#define FILENAME "test.bit"




FIL fsrc;			// File object
FATFS fatfs;		// File system specific
FRESULT fres;		// FAT common result
DSTATUS resCard;	// SD card status



DWORD get_fattime(void)
{
  return (28 << 25) | (2 << 21) | (1 << 16);
}



extern void init_filesystem() {

	while (1) {
		// Initialize SD card and setup USART0
		MICROSD_Init();

		resCard = disk_initialize(0);
		if (!resCard) break;
	}

	// Mount filesystem
	if (f_mount(0, &fatfs) != FR_OK)
	{
		/* Could not mount filesystem due to MicroSD missing or no FAT32 */
		while(1);
	}

}




extern void open_file(FIL *file, char *filename) {
	if (f_open(file, filename, FA_READ) != FR_OK)	{
		/* Could not find file*/
		while (1);
	}

	/*Set the file write pointer to first location */
	if (f_lseek(file, 0) != FR_OK) {
		/* Error. Cannot set the file write pointer */
		while(1);
	}
}


extern void read_file(FIL *file, void *buffer, UINT bytesToRead, UINT *bytesRead) {
	if (f_read(file, buffer, bytesToRead, bytesRead) != FR_OK) {
		/* Could not read file */
		while (1);
	}
}

extern void close_file(FIL *file) {
	if (f_close(file) != FR_OK) {
		/* Could not close file */
		while(1);
	}
}

extern void seek_file(FIL *file, DWORD offset) {
	if (f_lseek(file, offset) != FR_OK) {
		/* Could not seek file */
		while(1);
	}
}



extern void get_filenames(char *path, char strings[FILE_COUNT][FILENAME_LENGTH], int* num_files) {
	FRESULT res;
	FILINFO fno;
	DIR dir;
	int i = 0;
	char *fn;

	res = f_opendir(&dir, path);
	if (res == FR_OK) {
		while(i < FILE_COUNT) {
			res = f_readdir(&dir, &fno);
			if (res != FR_OK || fno.fname[0] == 0) {
				//while(1);
				break;
			}
			if (fno.fname[0] == '.') continue;

			char *a = fno.fname;
			//while(1);

			strcpy(strings[i], fno.fname);

			i++;
		}
	} else {
		// Not ok
		while(1);
	}

	*num_files = i;
}





extern void load_kernel(char *filename, kernel_type *kernel) {
	FIL file;
	UINT bytesRead;
	open_file(&file, filename);
	read_file(&file, kernel, sizeof(uint16_t)*(MAX_KERNEL_SIZE+1), &bytesRead);
	close_file(&file);
}

