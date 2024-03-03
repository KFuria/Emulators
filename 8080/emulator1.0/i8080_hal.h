#ifndef I8080_HAL_H
#define I8080_HAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

extern uint8_t i8080_hal_memory_read_byte(uint16_t addr);
extern void i8080_hal_memory_write_byte(uint16_t addr, uint8_t byte);
extern uint8_t i8080_hal_io_input(void * cpu_pointer, uint8_t port);
extern void i8080_hal_io_output(void * cpu_pointer, uint8_t port, uint8_t value);
extern uint8_t* i8080_hal_memory_init(void);
extern void i8080_hal_memory_free(void);

extern int load_file_into_memory(const char *name, uint16_t addr);

#endif