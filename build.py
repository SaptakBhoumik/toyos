from os import system
system("mkdir -p build")
system("peregrine.elf compile kernel/kernel.pe -emit_cpp -o temp.cc")
system("nasm -f elf asm/kernal/boot.asm -o build/boot.o")
system("g++ -c temp.cc -o build/kernel.o -m32 -ffreestanding -fno-exceptions -fno-rtti")
system("gcc build/boot.o build/kernel.o -T linker.ld -o iso/boot/toyos -nostdlib -nodefaultlibs -lgcc -m32")
system("grub-mkrescue iso --output=toy.iso")
system("qemu-system-x86_64 -boot d  -cdrom toy.iso -m 200")
system("rm build/*")
