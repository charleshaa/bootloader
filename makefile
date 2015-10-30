all: clean
	clear
	make -C kernel
	grub-mkrescue -o iso/kernel.iso iso
	qemu-system-i386 -hda iso/kernel.iso
clean:
	make clean -C kernel