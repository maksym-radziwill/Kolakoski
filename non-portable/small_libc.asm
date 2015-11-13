        .intel_syntax noprefix
	.globl quit
	.globl print_str
	.globl _start

_start:	call start
	ret
	
quit:	push ebp
	mov ebp, esp
	push ebx
	
	mov eax, 1
	mov ebx, [ebp + 8]
	int 0x80

	pop ebx
	pop ebp
	ret


print_str:
	push ebp
	mov ebp, esp
	push ebx
	
	/* Compute length of string */
	
	mov edx, [ebp + 8]
	dec edx

	xor ecx, ecx
	
loop:	inc edx
	inc ecx
	cmp byte ptr [edx], 0
	jne loop

	/* Call the write syscall */
	
	mov edx, ecx
	mov ecx, [ebp + 8]
	mov ebx, 1
	mov eax, 4
	int 0x80

	pop ebx
	pop ebp
	ret


