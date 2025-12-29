cmake_minimum_required(VERSION 3.10)
project(MyOS C CXX ASM)

# Disable standard libraries
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ffreestanding -O2 -nostdlib -lgcc")

# Define the kernel executable
add_executable(myos.bin 
    kernel/boot.s 
    kernel/kernel.cpp
)

# Set the linker script
target_link_options(myos.bin PRIVATE -T ${CMAKE_CURRENT_SOURCE_DIR}/kernel/linker.ld)