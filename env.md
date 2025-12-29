# Cross-Compiler Build Guide (i686-elf)

This document provides a step-by-step guide to setting up a cross-compiler environment for OS development.

## 1. Environment Setup

Run these commands to set the installation path and target architecture.

```bash
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p $HOME/src
cd $HOME/src

# Get Binutils (Handles assembly and linking)
wget [https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.gz](https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.gz)

# Get GCC (The compiler)
wget [https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz](https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz)

# Extract archives
tar -xf binutils-2.41.tar.gz
tar -xf gcc-13.2.0.tar.gz

mkdir build-binutils
cd build-binutils

../binutils-2.41/configure --target=$TARGET \
                           --prefix="$PREFIX" \
                           --with-sysroot \
                           --disable-nls \
                           --disable-werror

make -j$(nproc)
make install
cd ..

mkdir build-gcc
cd build-gcc

../gcc-13.2.0/configure --target=$TARGET \
                        --prefix="$PREFIX" \
                        --disable-nls \
                        --enable-languages=c,c++ \
                        --without-headers

# Build GCC and the supporting runtime library (libgcc)
make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)

# Install files to $PREFIX
make install-gcc
make install-target-libgcc
cd ..

```