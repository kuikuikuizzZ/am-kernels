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

uint32_t a = 0;

uint32_t flash_read(uint32_t addr) {
  // char len 64 bit
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x40;
  *(volatile unsigned *)(SPI_BASE + SPI_DIVIDER) = 0x1;
  *(volatile unsigned *)(SPI_BASE + SPI_SS)=0x01;

  // ss port 0
  *(volatile unsigned *)(SPI_BASE + SPI_TX1)=0x03000000;
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
  while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));

  uint32_t s = *(volatile unsigned *)(SPI_BASE + SPI_RX0);
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
  while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));
  printf("%x\n",s);
  check(s==0x5802);
  return s;
}

void _start(){
    // char len 64 bit
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x40;
  *(volatile unsigned *)(SPI_BASE + SPI_DIVIDER) = 0x1;
  *(volatile unsigned *)(SPI_BASE + SPI_SS)=0x01;

  // ss port 0
  *(volatile unsigned *)(SPI_BASE + SPI_TX1)=0x03000000;
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
  while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));

  short s = *(volatile char *)(SPI_BASE + SPI_RX0);
  *(volatile unsigned *)(SPI_BASE + SPI_CTRL) = 0x100;
  while((*(volatile unsigned *)(SPI_BASE + SPI_CTRL)& 0x100));
  *(volatile char *)(UART_BASE + UART_TX) = s;
  if (s ==0x0) {
    asm volatile ("addi a0, x0, 1");
  }  
    halt(1);
   asm volatile ("ebreak");
}