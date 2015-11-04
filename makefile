iso/kernel.iso:
	clear
	rm -f kernel/kernel.o
	make -C kernel
	grub-mkrescue -o iso/kernel.iso iso

iso/kernel_debug.iso:
	clear
	rm -f kernel/kernel.o
	make DFLAGS="-D_DEBUG" -C kernel
	grub-mkrescue -o iso/kernel_debug.iso iso

debug: iso/kernel_debug.iso
	qemu-system-i386 -hda iso/kernel_debug.iso

run: iso/kernel.iso
	qemu-system-i386 -hda iso/kernel.iso

clean:
	clear
	make clean -C kernel