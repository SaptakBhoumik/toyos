all:
	mkdir -p build
	python3 build.py
	qemu-system-x86_64 -boot d  -cdrom toy.iso -m 200

clear:
	rm *.iso
	rm ./build/*
