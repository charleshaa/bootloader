global outb
global outw
global inb
global inw

section .text

	outb:
		push  ebp
		mov	ebp,esp

		mov	dx,[ebp+8]	;port
		mov	al,[ebp+12]	;data
		out	dx,al       ;ecrit "data" sur le port "port"

		mov	esp,ebp
		pop	ebp
		ret

	outw:
		push	ebp
		mov	ebp,esp

		mov	dx,[ebp+8]	;port
		mov	ax,[ebp+12] ;data
		out	dx,ax       ;ecrit "data" sur le port "port"

		mov	esp,ebp
		pop	ebp
		ret

	inb:
		push	ebp
		mov	ebp,esp

		mov	dx,[ebp+8] ;port
		in		al,dx		  ;lit "data" sur le port "port"
							  ;retourne "data"
		mov	esp,ebp
		pop	ebp
		ret

	inw:
		push	ebp
		mov	ebp,esp

		mov	dx,[ebp+8] ;port
		in		ax,dx		  ;lit "data" sur le port "port"
							  ;retourne "data"
		mov	esp,ebp
		pop	ebp
		ret