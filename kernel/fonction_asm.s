global outb
global outw
global inb
global inw

section .text

	outb:
		push	ebp
		mov		ebp,esp

		;PORT
		mov		dx,[ebp+8]
		;DATA
		mov		al,[ebp+12]

		out		dx,al

		mov		esp,ebp
		pop		ebp
		ret

	outw:
		push	ebp
		mov		ebp,esp

		mov		dx,[ebp+8]
		mov		ax,[ebp+12]

		out		dx,ax

		mov		esp,ebp
		pop		ebp
		ret

	inb:
		push	ebp
		mov		ebp,esp

		mov		dx,[ebp+8]
		in		al,dx

		mov		esp,ebp
		pop		ebp
		ret

	inw:
		push	ebp
		mov		ebp,esp

		mov		dx,[ebp+8]
		in		ax,dx

		mov		esp,ebp
		pop		ebp
		ret