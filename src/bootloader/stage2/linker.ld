ENTRY(entry)
OUTPUT_FORMAT("binary")
phys = 0x00000500;

SECTIONS
{
    . = phys;

    .entry              : ALIGN(0x1000) { __entry_start = .;      *(.entry)   }
    .text               : ALIGN(0x1000) { __text_start = .;       *(.text)    }
    .data               : ALIGN(0x1000) { __data_start = .;       *(.data)    }
    .rodata             : ALIGN(0x1000) { __rodata_start = .;     *(.rodata)  }
    .bss                : ALIGN(0x1000) { __bss_start = .;        *(.bss)     }
    
    __end = .;
}