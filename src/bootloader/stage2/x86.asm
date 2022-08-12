bits 16

section _TEXT class=CODE

;void _cdecl x86_div64_32(uint64_t divident, uint32_t divizor, uint64_t *quotientOut, uint64_t *remainderOut);
global _x86_div64_32
_x86_div64_32:
    ;make new call frame
    push bp         ;save old call frame
    mov bp, sp      ;init a new call frame

    push bx

    ;divident upper 32 bits
    mov eax, [bp + 8]   ;eax <- upper 32 bits of divident
    mov ecx, [bp + 12]  ;ecx <-divizor
    xor edx, edx
    div ecx             ;eax -quot, edx -reminder

    ;store pper 32 bits of quotient
    mov bx, [bp + 16]
    mov [bx + 4],   eax

    ;divide lower 32 bits
    mov eax, [bp + 4]   ;eax <- lower 32 bits of divident
                        ;edx <- old reminder
    div ecx


    ;restore results
    mov [bx], eax
    mov bx, [bp +18]
    mov [bx], edx

    pop bx

    ;restore old frame
    mov sp, bp
    pop bp
    ret

;int 10h ah=0EH
;argparams: character, page
global _x86_Video_WriteCharTeletype
_x86_Video_WriteCharTeletype:  
    ;make new call frame
    push bp         ;save old call frame
    mov bp, sp      ;init a new call frame

    ;save bx
    push bx

    ; [bp + 0] - old call frame 
    ; [bp + 2] - return address (small memmory table model => 2 bytes) 
    ; [bp + 4] - (character) bytes converted to words
    ; [bp + 6] - (page)
    mov ah, 0Eh
    mov al, [bp + 4]
    mov bh, [bp + 6] 

    int 10h

    ;retore bx
    pop bx

    ;restore old frame
    mov sp, bp
    pop bp
    ret