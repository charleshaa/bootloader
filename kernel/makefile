DFLAGS=

all: run

bootloader.o: bootloader.s
	nasm -f elf32 $< -o $@

kernel.o: kernel.c kernel.h
	gcc $(DFLAGS) kernel.c -o kernel.o -std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c

gdt_asm.o: gdt_asm.s
	nasm -f elf32 gdt_asm.s

fonction_asm.o: fonction_asm.s
	nasm -f elf32 fonction_asm.s 

gdt.o: gdt.c gdt.c fonction.h ../common/types.h x86.h
	gcc -std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c gdt.c

fonction.o: fonction.c fonction.h
	gcc -std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c fonction.c

math.o: math.c math.h
	gcc -std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c math.c

fonction_affichage.o: fonction_affichage.c fonction_affichage.h
	gcc -std=gnu99 -m32 -fno-builtin -ffreestanding -Wall -Wextra -c fonction_affichage.c

kernel.elf: kernel.o gdt_asm.o bootloader.o gdt.o fonction.o fonction_asm.o fonction_affichage.o math.o
	ld -Tkernel.ld -melf_i386 $^ -o kernel.elf 
	cp kernel.elf ../iso/boot

../iso:
	mkdir -p ../iso
../iso/boot: ../iso
	mkdir -p ../iso/boot/
../iso/boot/grub: ../iso/boot 
	mkdir -p ../iso/boot/grub
	cp ../grub/grub.cfg ../iso/boot/grub

run: ../iso/boot/grub kernel.elf 

clean:
	rm -f *.o
	rm -f *.img
	rm -f *.elf
	rm -rf ../iso