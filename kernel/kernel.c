#include <stdint.h>

#define VBE_MODE 0x4115  // 1024x768x32bpp

void main() {
    // Инициализация оборудования
    init_gdt();
    init_idt();
    init_memory();
    
    // Графический режим
    if (!init_vbe(VBE_MODE)) {
        panic("Failed to set VBE mode!");
    }
    
    // Инициализация GUI
    init_gui();
    
    // Запуск оболочки
    start_shell();
    
    // Вечный цикл
    while(1);
}

void panic(const char* msg) {
    draw_error_screen(msg);
    while(1);
}