all: run

bootloader.o: bootloader.s
	nasm -f bin $< -o $@

disk.img: bootloader.o
	dd if=/dev/zero of=$@ bs=512 count=64
	dd if=$< of=$@ conv=notrunc

kernel.o: kernel.c
	gcc kernel.c -o kernel.o -std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c

gdt_asm.o: gdt_asm.s
	nasm -f elf32 gdt_asm.s 

kernel.elf: kernel.o gdt_asm.o
	ld -Tkernel.ld -melf_i386 kernel.o gdt_asm.o -o kernel.elf
	cp kernel.elf ../boot

boot:
	mkdir ../boot/
grub:
	mkdir ../boot/grub
	cp ../grub/grub.cfg ../boot/grub


run: boot grub kernel.elf disk.img
	qemu-system-i386 -hda disk.img

clean:
	rm -f *.o
	rm -f *.img
	rm -f *.elf
	rm -rf ../boot

