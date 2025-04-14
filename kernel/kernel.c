#include <stdint.h>
#include "../lib/memory.h"
#include "vbe.h"
#include "gui.h"
#include "wine.h"

/* Толкиновские цвета */
#define COLOR_MITHRIL  0x00A8C8FF  // Серебристо-голубой
#define COLOR_ELVEN    0x00FFD700  // Золотой Лориэна
#define COLOR_MORDOR   0x008B0000  // Тёмно-красный

/* Глобальные переменные */
uint32_t* framebuffer;
uint32_t screen_width;
uint32_t screen_height;

void panic(const char* msg) {
    draw_error_screen(msg, COLOR_MORDOR);
    while(1);
}

void kernel_main() {
    // 1. Инициализация памяти
    if (!memory_init()) {
        panic("Moria mines collapsed! (Memory fail)");
    }

    // 2. Настройка графики
    if (!vbe_set_mode(1024, 768, 32)) {
        panic("Palantir broken! (VBE fail)");
    }
    framebuffer = (uint32_t*)vbe_get_framebuffer();
    screen_width = vbe_get_width();
    screen_height = vbe_get_height();

    // 3. Загрузка GUI
    if (!gui_init()) {
        panic("Elven magic failed! (GUI error)");
    }

    // 4. Инициализация Wine
    wine_init();

    // 5. Основной цикл
    while (1) {
        gui_update();
        
        // Пример: запуск .exe по "горячей клавише"
        if (key_pressed(KEY_F1)) {
            wine_execute("/apps/legolas.exe");
        }
    }
}
