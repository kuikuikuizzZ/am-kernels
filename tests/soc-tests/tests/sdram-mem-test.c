#include "trap.h"
#include <klib.h>

#define SDRAM_BASE 0xa1000069
#define SIZE 0x2
void sdram_test(){ 
    for(int j=0;j<SIZE;j++){
        int i = j%16;
        *(volatile char *)(SDRAM_BASE + j)= '0'+i;
    }
    for(int j=0;j<SIZE;j++){
        int i = j%16;
        char s = *(volatile char *)(SDRAM_BASE + j);
        printf("s: %x",s);
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
    uint32_t offset = 1;
    // *(volatile unsigned *)(SDRAM_BASE + offset)= 0x12345678;
    // offset = 1;
	// unsigned s = *(volatile unsigned *)(SDRAM_BASE + offset);
    // printf("%x\n",s);
    // check(s==0x12345678);
    *(volatile char *)(SDRAM_BASE + offset)= 0x12;
	char ss = *(volatile char *)(SDRAM_BASE + offset);
    // printf("%x\n",ss);
    check(ss==0x12);
}


int main (){
	temp_test();
    // sdram_test();
    return 0;
}