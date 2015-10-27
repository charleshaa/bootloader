global entrypoint  ; the entry point symbol defined in kernel.ld

; Values for the multiboot header
MULTIBOOT_HEADER_MAGIC     equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS     equ 0x0
; magic + checksum + flags must equal 0
MULTIBOOT_HEADER_CHECKSUM  equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

;---------------------------------------------------------------------------------------------------
; bootloader section
; This section must be located at the very beginning of the kernel image.


section .bootloader
align 4    ; section aligned to a 4 bytes boundary

; Minimum multiboot header
dd MULTIBOOT_HEADER_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd MULTIBOOT_HEADER_CHECKSUM


entrypoint:
	; Bootloader code starts executing here
	cli  ; disable hardware interrupts

	; TODO : initialiser le pointeur de pile ainsi qu'EBP (à la même valeur)
    ; Rappel : la pile "grandi" en descendant !
	; ...
	push EBP
	mov EBP, ESP


	; TODO : appeler la fonction principale du kernel (code C)
	; Celle-ci doit etre visible par le linker
	; ...

	;affiche un smile
	mov EAX, 0xB8000
	mov word [eax], 0x0E01

	;il faudra faire un call sur une fonction en C

	mov ESP, EBP
	pop EBP
	mov EAX,0
	ret	

	

	

	; infinite loop (should never get here)
.forever:
	hlt
	jmp .forever

;---------------------------------------------------------------------------------------------------
; stack section

; TODO : ajouter une section pour la pile kernel dans laquelle
; reserver au moins 256KB grace a la directive "resb".
; Cette section devra etre alignee sur 4 bytes.
; ...

;section .stack

;stack:
	stack_size resb 256;reserver de la memoire pour la pile ??????


;---------------------------------------------------------------------------------------
; rempli le code avec des "nop" (opcode 0x90) jusqu'à l'adresse 510
times 510-($-$$) db 0x90

; les 2 bytes de signature d'un boot secteur
dw 0xAA55