#include <stddef.h>
#include <stdint.h>
#include "../kernel/kernel.hpp"
#include "../utils/utils.hpp"

//credit https://wiki.osdev.org/Bare_Bones

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = 0;
uint16_t* terminal_buffer;
namespace terminal{
	void terminal_initialize(void)
	{
		terminal_row = 0;
		terminal_column = 0;
		terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		terminal_buffer = (uint16_t*) 0xB8000;
		for (size_t y = 0; y < VGA_HEIGHT; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = vga_entry(' ', terminal_color);
			}
		}
	}

	void terminal_setcolor(uint8_t color)
	{
		terminal_color = color;
	}

	void print_newline() {
	    terminal_column = -1;

	    if (terminal_row < VGA_HEIGHT - 1) {
	        terminal_row++;
	        return;
	    }

	    for (size_t row = 0; row < VGA_HEIGHT; row++) {
	        for (size_t col = 0; col < VGA_WIDTH; col++) {
	            auto character = terminal_buffer[col + VGA_WIDTH * row];
	            terminal_buffer[col + VGA_WIDTH * (row - 1)] = character;
	        }
	    }

	}

	void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
	{
	  if (c=='\n'){
	    print_newline();
	    return;
	  }
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(c, color);
	}



	void terminal_putchar(char c)
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}

	void terminal_write(const char* data, size_t size)
	{
		for (size_t i = 0; i < size; i++)
			terminal_putchar(data[i]);
	}

	void terminal_writestring(const char* data)
	{
		terminal_write(data, strlen(data));
	}
}
extern "C" void main()
{
	/* Initialize terminal interface */
	terminal::terminal_initialize();
  terminal::terminal_setcolor(VGA_COLOR_LIGHT_RED);
	terminal::terminal_writestring("Hello, World!\nHello NewLine");
}
