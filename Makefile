# Use your cross-compiler
CC = i686-elf-gcc
CXX = i686-elf-g++
AS = i686-elf-as

# Compiler flags
CFLAGS = -ffreestanding -O2 -Wall -Wextra
CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS = -ffreestanding -O2 -nostdlib -T kernel/linker.ld -lgcc

# Files
OBJS = kernel/boot.o kernel/kernel.o

all: myos.bin

kernel/boot.o: kernel/boot.s
	$(AS) kernel/boot.s -o kernel/boot.o

kernel/kernel.o: kernel/kernel.cpp
	$(CXX) -c kernel/kernel.cpp -o kernel/kernel.o $(CXXFLAGS)

myos.bin: $(OBJS)
	$(CC) -o myos.bin $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) myos.bin myos.iso