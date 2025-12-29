#include <stddef.h>
#include <stdint.h>

/* --- Safety Checks --- */
#if defined(__linux__)
#error "You are not using a cross-compiler! Use i686-elf-gcc instead."
#endif

/* --- VGA Constants & Types --- */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | (bg << 4);
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

/* --- The Terminal Class --- */
class Terminal {
private:
    size_t row;
    size_t col;
    uint8_t color;
    uint16_t* buffer;
    static const size_t WIDTH = 80;
    static const size_t HEIGHT = 25;

public:
    Terminal() {
        row = 0;
        col = 0;
        color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        buffer = (uint16_t*) 0xB8000;
        clear();
    }

    void clear() {
        for (size_t y = 0; y < HEIGHT; y++) {
            for (size_t x = 0; x < WIDTH; x++) {
                const size_t index = y * WIDTH + x;
                buffer[index] = vga_entry(' ', color);
            }
        }
    }

    void set_color(uint8_t new_color) {
        color = new_color;
    }

    void put_char(char c) {
        if (c == '\n') {
            col = 0;
            if (++row == HEIGHT) row = 0;
            return;
        }

        const size_t index = row * WIDTH + col;
        buffer[index] = vga_entry(c, color);

        if (++col == WIDTH) {
            col = 0;
            if (++row == HEIGHT) row = 0;
        }
    }

    void write(const char* data) {
        for (size_t i = 0; data[i] != '\0'; i++) {
            put_char(data[i]);
        }
    }
};

/* --- Global Instances --- */
// Because we updated boot.s and linker.ld, this constructor WILL run.
Terminal tty;

/* --- Kernel Entry Point --- */
extern "C" void kernel_main(void) {
    // We don't need to call terminal_initialize()! 
    // The global constructor already did it.
    
    tty.write("C++ Global Constructor Test: SUCCESS\n");
    tty.set_color(vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
    tty.write("Hello from the Terminal Class!\n");
    
    tty.set_color(vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
    tty.write("Newline support is active.\n");
}