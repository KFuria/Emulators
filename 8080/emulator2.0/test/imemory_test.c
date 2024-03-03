#include "imemory_test.h"

iMem iMem_init_test(){
    //test iMem_init
    iMem mem_test = iMem_init();
    if (mem_test == NULL){
        fprintf(stderr, "Memory not created\n");
    }
    int count = 0;
    for(int i = 0; i< MEM_SIZE; i++){
        if(mem_test[i] != 0){
            count+=1;
        }
    }
}

int load_file_into_Mem_test(const char * filename, uint16_t addr);