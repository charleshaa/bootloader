global entrypoint  ; the entry point symbol defined in kernel.ld
; Values for the multiboot header
MULTIBOOT_HEADER_MAGIC     equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS     equ 0x0
; magic + checksum + flags must equal 0
MULTIBOOT_HEADER_CHECKSUM  equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

;---------------------------------------------------------------------------------------------------
; bootloader section
; This section must be located at the very beginning of the kernel image.

;fonction externe
extern kernel

section .bootloader
align 4    ; section aligned to a 4 bytes boundary

; Minimum multiboot header
dd MULTIBOOT_HEADER_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd MULTIBOOT_HEADER_CHECKSUM


entrypoint:
	; Bootloader code starts executing here
	cli  ; disable hardware interrupts

	
	;initialisation du pointeur de pile
	push EBP 
	mov EBP, ESP

	;appel du kernel (code C)
	call kernel 

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

section .stack
align 4    ; section aligned to a 4 bytes boundary


	resb 2^20;reserver de la memoire pour la pile


;---------------------------------------------------------------------------------------