#include "memory.h"

static iMem imem = NULL;
static size_t mem_size = 0;

iMem iMem_init(size_t size_in_bytes){
    mem_size = size_in_bytes;
    imem = malloc(size_in_bytes);
    memset(imem, 0, size_in_bytes);
    if(imem == NULL){
        fprintf(stderr, "Memory not created\n");
    }
    return imem;
}

int load_file_into_Mem(const char * filename, uint16_t addr){
    FILE * f = fopen(filename, "rb");
    if(f==NULL){
        fprintf(stderr, "error: can't open file '%s'.\n", filename);
        return 1;
    }

    //get file size
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    rewind(f);
    printf("File size: %ld\n", fsize);

    if(fsize + addr >= mem_size){
        fprintf(stderr, "error: file %s can't fit in memory.\n", filename);
        return 1;
    }

    //read  file into memory
    uint8_t * load_to = imem + addr;
    printf("File located at: 0x%p\n", load_to);
    size_t result = fread(&imem[addr], sizeof(uint8_t), fsize, f);
    if (result != fsize){
        fprintf(stderr, "error: while reading file '%s'\n", filename);
        return 1;
    }

    fclose(f);
    return 0;
}

uint8_t iMem_read_byte(uint16_t addr){
    return imem[addr];

}

void iMem_write_byte(uint16_t addr, uint8_t byte){
    imem[addr] = byte;
}

void iMem_free(void){
    free(imem); 
    imem = NULL;
}