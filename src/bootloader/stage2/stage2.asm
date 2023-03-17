bits 16

section .entry

extern __bss_start
extern __end
extern _init

global entry


entry:
    cli
    ; save boot drive
    mov [g_BootDrive], dl

    ;setupStack
    mov ax, ds
    mov ss, ax
    mov sp, 0xFFF0
    mov bp, sp

    call EnableA20
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp codeseg:StartProtectedMode


EnableA20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret


[bits 32]
%include "CPUID.asm"
%include "SimplePaging.asm"
StartProtectedMode:
	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
    
    call DetectCPUID
    call DetectLongMode
    call SetUpIdentityPaging 
    call EditGDT
    jmp codeseg:Start64Bit

[bits 64]
[extern start]

Start64Bit:
    mov edi, 0xb8000
	mov rax, 0x1f201f201f201f20
	mov ecx, 500
	rep stosq

    ; expect boot drive in dl, send it as argument to cstart function
    xor rdx, rdx
    mov dl, [g_BootDrive]
    push rdx
    call start
    
    cli
    hlt
g_BootDrive: db 0


[bits 16]

gdt_nulldesc:
	dd 0
	dd 0	
gdt_codedesc:
	dw 0xFFFF			; Limit
	dw 0x0000			; Base (low)
	db 0x00				; Base (medium)
	db 10011010b		; Flags
	db 11001111b		; Flags + Upper Limit
	db 0x00				; Base (high)
gdt_datadesc:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

gdt_end:

gdt_descriptor:
	gdt_size: 
		dw gdt_end - gdt_nulldesc - 1
		dq gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc
[bits 32]

EditGDT:
	mov [gdt_codedesc + 6], byte 10101111b

	mov [gdt_datadesc + 6], byte 10101111b
	ret

[bits 16]
 
