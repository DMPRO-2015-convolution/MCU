#include "ff.h"
#include "microsd.h"
#include "diskio.h"
#include "filesystem.h"



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


extern void read_file(FIL *file, uint8_t *buffer, UINT bufferSize, UINT *bytesRead) {
	if (f_read(file, buffer, bufferSize, bytesRead) != FR_OK) {
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
