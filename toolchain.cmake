set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i386)

set(TARGET i686-elf)
set(CMAKE_C_COMPILER ${TARGET}-gcc)
set(CMAKE_CXX_COMPILER ${TARGET}-g++)
set(CMAKE_ASM_COMPILER ${TARGET}-as)

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# For libraries and headers listed in find_library and find_path
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Optional: Force CMake to bypass the compiler check entirely
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)