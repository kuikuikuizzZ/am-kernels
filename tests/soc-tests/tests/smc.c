#define UART_TX 0x10000000

int main() {
  asm volatile("li a0, 0;"
               "li a1, 0x10000000;"     // change UART_TX to the correct address
               "li t1, 0x41;"        // 0x41 = 'A'
               "la a2, again;"
               "li t2, 0x00008067;"  // 0x00008067 = ret
               "again:"
               "sb t1, (a1);"
               "sw t2, (a2);"
               "li t1, 0x42;"
               ".word 0x0000100f;"
               "sb t1, (a1);"
               "sb t1, (a1);"
               "sb t1, (a1);"
               "sb t1, (a1);"
               "j again;"
              );
  return 0;
}