#include "trap.h"
#include <klib.h>
#define SPI_BASE      0x10001000
#define SPI_SS        0x18
#define SPI_CTRL      0x10
#define SPI_DIVIDER   0x14

#define SPI_TX0         0x0
#define SPI_TX1         0x4
#define SPI_RX0         0x0

#define FLASH_BASE      0x30000000
#define FLASH_TX0        0x0

#define UART_BASE      0x10000000
#define UART_TX      0x0

#define SRAM_CODE_BASE      0x0f000200

uint32_t a = 0;

uint32_t flash_read(uint32_t addr) {
	*(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x2040;
	*(volatile unsigned *)(SPI_BASE + SPI_DIVIDER) = 0x1;
	*(volatile unsigned *)(SPI_BASE + SPI_SS)=0x01;
	// ss port 0
	// should be FLASH 
	*(volatile unsigned *)(SPI_BASE + SPI_TX1)=0x03000000+addr;
	*(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
	while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));

	uint32_t s = *(volatile uint32_t *)(SPI_BASE + SPI_RX0);
	*(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
	while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));
	return s;
}

typedef void (*func)(void);
int main() {
	// char len 64 bit

   	uint32_t* sram_pointer = (void*) SRAM_CODE_BASE;
   	uint32_t  offset =  0;
	uint32_t flash_data = 0;
   	for (int i = 0; i < 8; i++) {
		flash_data = flash_read(offset);
		uint32_t temp[4] = {flash_data & 0xff, (flash_data >> 8) & 0xff, (flash_data >> 16) & 0xff, (flash_data >> 24) & 0xff};
		*sram_pointer =  (temp[0] << 24) | (temp[1] << 16) | (temp[2] << 8) | temp[3];
		sram_pointer++;
		offset+=4;
	}
    func pc = (void*) SRAM_CODE_BASE;
    pc();
  return 0;
}