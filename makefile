all: clean
	cd kernel && $(MAKE) run
	grub-mkrescue -o iso/kernel.iso iso
	qemu-system-i386 -hda iso/kernel.iso
clean:
	cd kernel && $(MAKE) clean