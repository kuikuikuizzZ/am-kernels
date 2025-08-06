#include "trap.h"
#include <klib.h>

#define SDRAM_BASE 0xa0000069
#define SIZE 0x10
void sdram_test(){ 
    for(int j=0;j<SIZE;j++){
        int i = j%16;
        *(volatile char *)(SDRAM_BASE + j)= '0'+i;
    }
    for(int j=0;j<SIZE;j++){
        int i = j%16;
        char s = *(volatile char *)(SDRAM_BASE + j);
        check(s==('0'+i));
    }
    for(int j=0;j<SIZE;j++){
        *((volatile short *)(SDRAM_BASE)+j) = 0x1234;
    }
    for(int j=0;j<SIZE;j++){
        short s=*((volatile short *)(SDRAM_BASE)+j) ;
        check(s==(0x1234));
    }

    for(int j=0;j<SIZE;j++){
        *((volatile unsigned *)(SDRAM_BASE)+j) = 0x12345678;
    }
    for(int j=0;j<SIZE;j++){
        unsigned s = *((volatile unsigned *)(SDRAM_BASE)+j) ;
        // printf("s: %x",s);
        check(s==0x12345678);
    }
}


void temp_test(){
    uint32_t offset = 0;
    *(volatile unsigned *)(SDRAM_BASE + offset)= 0x12345678;
    offset = 0;
	unsigned s = *(volatile unsigned *)(SDRAM_BASE + offset);
    printf("%x\n",s);
}


int main (){
	// temp_test();
    sdram_test();
    return 0;
}