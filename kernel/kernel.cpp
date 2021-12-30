#include <stdio.h>
#include "../kernel/arch/i386/tty.hpp"


extern "C" void __kernal__main()
{
	/* Initialize terminal interface */
	terminal::terminal_initialize();
  terminal::terminal_setcolor(VGA_COLOR_LIGHT_RED);
	terminal::terminal_writestring("Hello, World!\nHello NewLine\n");
	terminal::terminal_setcolor(VGA_COLOR_LIGHT_BLUE,VGA_COLOR_LIGHT_GREEN);
	terminal::terminal_writestring("Hello, World!\nHello NewLine");
}
