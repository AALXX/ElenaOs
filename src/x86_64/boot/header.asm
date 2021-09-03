;;This is a multiboot header
section .multiboot_header
header_start:

    dd 0xe85250d6 ;multiboot2 magic number
    
    ;architecture
    dd 0 ;protected mode
    
    dd header_end - header_start ;calculates bootloader cheader lenght

    dd 0x100000000  - (0xe85250d6 + 0 + (header_end - header_start)) ;checksum: we sum up some numbers, and then use that number to check that they’re all what we expected things to be

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size

header_end:
