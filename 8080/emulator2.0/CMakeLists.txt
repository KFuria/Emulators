cmake_minimum_required(VERSION 3.1)

project(emu8080
  LANGUAGES C
  DESCRIPTION "8080 Emulator"
)


set(SOURCES
  src/i8080.c
  src/i8080dis.c
  test/i8080_hal.c
  test/i8080_test.c
)

add_executable(emu8080 ${SOURCES})
set_target_properties(emu8080 PROPERTIES C_STANDARD 99)
if (MSVC)
  target_compile_options(emu8080 PRIVATE /W4)
else()
  target_compile_options(emu8080 PRIVATE -Wall -Wextra -pedantic -Wno-gnu-binary-literal)
endif()

target_include_directories(emu8080 PRIVATE
  inc/
  test/
)

set(ROMS_DIR "${CMAKE_SOURCE_DIR}/ROMs/" CACHE STRING "Path to directory containing rom files")
file(COPY "${CMAKE_SOURCE_DIR}/ROMs" DESTINATION "${CMAKE_BINARY_DIR}")