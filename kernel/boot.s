# Multiboot constants
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve stack space
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function

_start:
    # Setup Stack
    mov $stack_top, %esp

    # Call Global Constructors
    # We don't use 'extern', just load the symbols directly
    mov $__init_array_start, %ebx

next_ctor:
    cmp $__init_array_end, %ebx
    je done_ctors
    call *(%ebx)
    add $4, %ebx
    jmp next_ctor

done_ctors:
    # Enter Kernel
    call kernel_main

    # Halt if kernel returns
    cli
1:  hlt
    jmp 1b

.size _start, . - _start
