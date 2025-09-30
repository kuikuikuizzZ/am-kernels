#include "trap.h"
#include <klib.h>

#define NVBOARD_BASE 0x10002000
#define LED 0x0
#define SWITCH 0x4
#define SEG_ADDR 0x8


void simple_test(){
    uint32_t i = 1;
    uint16_t* led_addr = (uint16_t*) NVBOARD_BASE + LED;
    uint16_t* switch_addr = (uint16_t*) (NVBOARD_BASE + SWITCH);
    uint32_t* seg_addr = (uint32_t*) (NVBOARD_BASE + SEG_ADDR);

    uint16_t led = 1;
    *led_addr = 2;
    uint32_t seg = 00000001; 
    while (1)
    {       
        
        while (i % 1000 != 0) i++; 
        
        led = led << 1 ;
        *led_addr = led;
        *seg_addr = seg;
        seg ++;
        printf("i = %d *led %x\n", i,led); 
        printf("seg %d\n", seg);  
 
        i = 1;      
        if (led == 0) {
            led = 1;
        }
        printf("led = %d\n", led);
        printf("switch  = %d\n", *switch_addr);
    }
}

int main () { 

    while(1){
        // printf("Try to read (uart)...\n");
        char ch = io_read(AM_UART_RX).data;
        if (ch == (char)-1) continue;
        printf("Got (uart): %c (%d)\n", ch, ch & 0xff);
    }

    
    
   
    return 0;
}