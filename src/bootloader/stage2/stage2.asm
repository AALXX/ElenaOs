jmp EnterProtectedMode

%include "src/bootloader/stage2/gdt.asm"

EnterProtectedMode:
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
%include "src/bootloader/stage2/CPUID.asm"
%include "src/bootloader/stage2/SimplePaging.asm"
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
[extern _start]

Start64Bit:
    mov edi, 0xb8000
	mov rax, 0x1f201f201f201f20
	mov ecx, 500
	rep stosq

    ; expect boot drive in dl, send it as argument to cstart function
    xor rdx, rdx
    mov dl, [g_BootDrive]
    push rdx
    call _start
    
    jmp $
g_BootDrive: db 0

times 2048-($-$$) db 0
