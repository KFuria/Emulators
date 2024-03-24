#include "i8080_hal.h"

static iMem imem = NULL;

iMem iMem_init(void){
    imem = malloc(MEM_SIZE);
    memset(imem, 0, MEM_SIZE);
    if(imem == NULL){
        fprintf(stderr, "Memory not created\n");
    }
    printf("Memory assigned at: %p\n", imem);
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

    if(fsize + addr >= MEM_SIZE){
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

iMem iMem_free(void){
    free(imem); 
    imem = NULL;
    return NULL;
}


uint8_t iMem_read_byte(uint16_t addr){
    return imem[addr];

}

void iMem_write_byte(uint16_t addr, uint8_t byte){
    imem[addr] = byte;
}


uint8_t i8080_hal_io_input(void * cpu_pointer, uint8_t port) {
    return 0;
}

void i8080_hal_io_output(void * cpu_pointer, uint8_t port, uint8_t value) {
    i8080 * const cpu = (i8080*) cpu_pointer;
    if (port == 1) {
        if (cpu->c == 2) { // print a character stored in register E
            printf("%c", cpu->e);
        } else if (cpu->c == 9) {
            // print from memory at DE until '$' char 
            uint16_t addr = (cpu->d << 8) | cpu->e;
            do {
                printf("%c", iMem_read_byte(addr++));
            } while (iMem_read_byte(addr) != '$');
        }
    }
}