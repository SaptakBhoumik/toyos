all:
	mkdir -p build
	nasm -f elf asm/kernal/boot.asm -o build/boot.o
	g++ -c kernel/kernel.cpp -o build/kernel.o -m32 -ffreestanding -fno-exceptions -fno-rtti
	gcc build/boot.o build/kernel.o -T linker.ld -o iso/boot/toyos -nostdlib -nodefaultlibs -lgcc -m32
	grub-mkrescue iso --output=toy.iso
	qemu-system-x86_64 -boot d  -cdrom toy.iso -m 200
