#include "trap.h"
#include <klib.h>

#define PSRAM_BASE 0x80000000


int main (){
    char bytes[16] = "0123456789abcdef";
    char bytes_ans[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x61,0x62,0x63,0x64,0x65,0x66};
    unsigned short shorts_ans[] =  {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37};
    unsigned int_ans[] =  {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37};
    unsigned long long_ans[] =  {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37};

    for (int i=0; i<16;i++){
        char *addr = (char*)(PSRAM_BASE + i);
        *addr = bytes[i];
    }

    for (int i = 0; i < 16; i++){
        check(bytes[i]==bytes_ans[i]);
        
    }
    for (int i = 0; i < 8; i++){
        check(bytes[i]==shorts_ans[i]);
    }
    for (int i = 0; i < 8; i++){
        check(bytes[i]==int_ans[i]);
    }
    for (int i = 0; i < 8; i++){
        check(bytes[i]==long_ans[i]);
    }

    
}