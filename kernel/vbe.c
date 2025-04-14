void init_vbe(uint16_t mode) {
    struct vbe_mode_info* mode_info = (struct vbe_mode_info*)0x2000;
    
    // Получаем информацию о режиме
    if (!vbe_get_mode_info(mode, mode_info)) {
        return 0;
    }
    
    // Устанавливаем режим
    __asm__ volatile (
        "movw $0x4F02, %%ax\n"
        "movw %0, %%bx\n"
        "int $0x10"
        : : "r" (mode | 0x4000) : "eax", "ebx"
    );
    
    framebuffer = (uint32_t*)mode_info->framebuffer;
    return 1;
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x < 0 || y < 0 || x >= SCREEN_W || y >= SCREEN_H) return;
    framebuffer[y * SCREEN_W + x] = color;
}