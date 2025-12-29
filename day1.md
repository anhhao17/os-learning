https://wiki.osdev.org/Bare_Bones

## make
make

## cmake
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake && cmake --build build

## run qemu
qemu-system-i386 -kernel myos.bin
