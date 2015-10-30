global outb
global outw
global inb
global inw

section .text

	outb:
		push	ebp
		mov		ebp,esp

		mov		eax,[ebp+8]
		mov		ecx,[ebp+12]
		add		eax,ecx

		mov		esp,ebp
		pop		ebp
		ret

	outw:
		push	ebp
		mov		ebp,esp

		mov		eax,[ebp+8]
		mov		ecx,[ebp+12]
		add		eax,ecx

		mov		esp,ebp
		pop		ebp
		ret

	inb:
		push	ebp
		mov		ebp,esp

		mov		eax,[ebp+8]
		mov		ecx,[ebp+12]
		add		eax,ecx

		mov		esp,ebp
		pop		ebp
		ret

	inW: 
		push	ebp
		mov		ebp,esp

		mov		eax,[ebp+8]
		mov		ecx,[ebp+12]
		add		eax,ecx

		mov		esp,ebp
		pop		ebp
		ret