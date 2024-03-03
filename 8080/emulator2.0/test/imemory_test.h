#ifndef IMEMORY_TEST_H
#define IMEMORY_TEST_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "imemory.h"

iMem iMem_init_test();

int load_file_into_Mem_test(const char * filename, uint16_t addr);

uint8_t iMem_read_byte_test(uint16_t addr);

void iMem_write_byte_test(uint16_t addr, uint8_t byte);

void iMem_free_test(void);

#endif