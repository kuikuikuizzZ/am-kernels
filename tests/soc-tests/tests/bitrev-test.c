#include "trap.h"
#include <klib.h>
#define SPI_BASE      0x10001000
#define SPI_SS        0x18
#define SPI_CTRL      0x10
#define SPI_DIVIDER   0x14

#define SPI_TX0         0x0
#define SPI_TX1         0x4
#define SPI_RX0         0x0

#define FLASH_BASE      0x30000000L
#define FLASH_TX0        0x0



void bitrev_char_test() {
  // set SPI char len 16 bits 
  *(volatile unsigned *)(SPI_BASE + SPI_DIVIDER) = 0x1;
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x40;
  // tx the reverse of 'a' 
  *(volatile unsigned *)(SPI_BASE + SPI_SS)=0x80;
  *(volatile short *)(SPI_BASE + SPI_TX0)=0x8600;
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
  while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));

  //  rx 'a' 
  char s = *(volatile char *)(SPI_BASE + SPI_RX0);
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
  while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));
  printf("%x",s);
  check((char)s == 'a');
}

uint32_t flash_read(uint32_t addr) {
  // char len 64 bit
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x2040;
  *(volatile unsigned *)(SPI_BASE + SPI_SS)=0x01;

  // ss port 0
  *(volatile unsigned *)(SPI_BASE + SPI_TX1)=0x03000000+addr;
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
  while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));

  uint32_t s = *(volatile unsigned *)(SPI_BASE + SPI_RX0);
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
  while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));
  return s;
}

int main() {
  *(volatile unsigned *)(SPI_BASE + SPI_DIVIDER) = 0x1;
  // bitrev_char_test();
  uint32_t s ;
  s = flash_read(0);
  check(s==0x58020000);
  s = flash_read(4);
  printf("%x\n",s);
  check(s==0x04030000);

  return 0;
}
