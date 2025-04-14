ENTRY(kernel_main)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS {
    . = 0x100000; /* Загрузка по 1MB */

    .text : {
        *(.text*)
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(COMMON)
        *(.bss*)
    }

    /DISCARD/ : {
        *(.comment)
    }
}
