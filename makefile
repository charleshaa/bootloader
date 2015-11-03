iso/kernel.iso:
	clear
	make -C kernel
	grub-mkrescue -o iso/kernel.iso iso

debug:clean
	clear
	make DFLAGS="-D_DEBUG" -C kernel
	grub-mkrescue -o iso/kernel_debug.iso iso
	qemu-system-i386 -hda iso/kernel_debug.iso

run: iso/kernel.iso
	qemu-system-i386 -hda iso/kernel.iso

clean:
	clear
	make clean -C kernel