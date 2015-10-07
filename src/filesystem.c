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



int8_t readBuffer[BUFFER_SIZE];


// File read state






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


	if (f_mount(0, &fatfs) != FR_OK)
	{
		while(1);
	}

}


