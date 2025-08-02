#define UART_BASE      0x10000000
#define UART_TX        0x0



void _start() {
  asm volatile ("mv a0, x0");
  *(volatile char *)(UART_BASE + UART_TX) = 'A';
  *(volatile char *)(UART_BASE + UART_TX) = '\n';
  asm volatile ("ebreak");
}