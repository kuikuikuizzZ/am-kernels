#include "trap.h"
#include <klib.h>

#define PSRAM_BASE 0x80010000

void temp_test(){
    uint32_t offset = 1;
    *(volatile char *)(PSRAM_BASE + offset)= '0';
    offset = 1;
	char s = *(volatile char *)(PSRAM_BASE + offset);
    // printf("%x\n",s);
    check(s=='a');
}

void psram_mem_test(){ 
 for(int i=0;i<16;i++){
        *(volatile char *)(PSRAM_BASE + i)= '0'+i;
    }
    for(int i=0;i<16;i++){
        char s = *(volatile char *)(PSRAM_BASE + i);
        check(s==('0'+i));
    }
    for(int i=0;i<8;i++){
        *((volatile short *)(PSRAM_BASE)+i) = '0'+i;
    }
    for(int i=0;i<8;i++){
        short s=*((volatile short *)(PSRAM_BASE)+i) ;
        check(s==('0'+i));
    }

    for(int i=0;i<8;i++){
        *((volatile unsigned *)(PSRAM_BASE)+i) = '0'+i;
    }
    for(int i=0;i<8;i++){
        unsigned s = *((volatile unsigned *)(PSRAM_BASE)+i) ;
        printf("s: %x",s);
        check(s==('0'+i));
    }
}
int main (){
	temp_test();
    return 0;
}