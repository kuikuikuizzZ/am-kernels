#include "trap.h"
#include <klib.h>

#define SDRAM_BASE 0xa0000000

void sdram_test(){ 
    for(int i=0;i<16;i++){
        *(volatile char *)(SDRAM_BASE + i)= '0'+i;
    }
    for(int i=0;i<16;i++){
        char s = *(volatile char *)(SDRAM_BASE + i);
        check(s==('0'+i));
    }
    for(int i=0;i<8;i++){
        *((volatile short *)(SDRAM_BASE)+i) = '0'+i;
    }
    for(int i=0;i<8;i++){
        short s=*((volatile short *)(SDRAM_BASE)+i) ;
        check(s==('0'+i));
    }

    for(int i=0;i<8;i++){
        *((volatile unsigned *)(SDRAM_BASE)+i) = '0'+i;
    }
    for(int i=0;i<8;i++){
        unsigned s = *((volatile unsigned *)(SDRAM_BASE)+i) ;
        // printf("s: %x",s);
        check(s==('0'+i));
    }
}


void temp_test(){
    uint32_t offset = 0;
    *(volatile char *)(SDRAM_BASE + offset)= 0x12;
    offset = 1;
	short s = *(volatile short *)(SDRAM_BASE + offset);
    printf("%x\n",s);
}


int main (){
	// temp_test();
    sdram_test();
    return 0;
}