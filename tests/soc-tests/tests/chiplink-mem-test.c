#include "trap.h"
#include <klib.h>

#define CHIPLINK_BASE 0xcffffff0
#define SIZE 0x10
void chiplink_test(){ 
    for(int j=0;j<SIZE;j++){
        int i = j%16;
        *(volatile char *)(CHIPLINK_BASE + j)= '0'+i;
    }
    for(int j=0;j<SIZE;j++){
        int i = j%16;
        char s = *(volatile char *)(CHIPLINK_BASE + j);
        printf("s: %x",s);
        check(s==('0'+i));
    }
    for(int j=0;j<SIZE;j++){
        *((volatile short *)(CHIPLINK_BASE)+j) = 0x1234;
    }
    for(int j=0;j<SIZE;j++){
        short s=*((volatile short *)(CHIPLINK_BASE)+j) ;
        check(s==(0x1234));
    }

    for(int j=0;j<SIZE;j++){
        *((volatile unsigned *)(CHIPLINK_BASE)+j) = 0x12345678;
    }
    for(int j=0;j<SIZE;j++){
        unsigned s = *((volatile unsigned *)(CHIPLINK_BASE)+j) ;
        // printf("s: %x",s);
        check(s==0x12345678);
    }
}


void temp_test(){
    uint32_t offset = 0;
    *(volatile unsigned *)(CHIPLINK_BASE + offset)= 0x12345678;
	unsigned s = *(volatile unsigned *)(CHIPLINK_BASE + offset);
    printf("%x\n",s);
    check(s==0x12345678);

    // *(volatile short *)(CHIPLINK_BASE + offset)= 0x1234;
	// unsigned s = *(volatile short *)(CHIPLINK_BASE + offset);
    // printf("%x\n",s);
    // check(s==0x1234);

    *(volatile char *)(CHIPLINK_BASE + offset)= 0x12;
	char ss = *(volatile char *)(CHIPLINK_BASE + offset);
    // printf("%x\n",ss);
    check(ss==0x12);
}


int main (){
	temp_test();
    chiplink_test();
    return 0;
}