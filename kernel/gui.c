void init_gui() {
    // Создаем основные элементы
    create_window(100, 100, 400, 300, "Palantír Terminal");
    create_button(120, 200, 80, 30, "Execute", execute_callback);
    
    // Загружаем шрифты
    load_font("/sys/fonts/elven.ttf");
    
    // Устанавливаем тему
    set_theme(THEME_RIVENDELL);
}

void draw_window(int x, int y, int w, int h, const char* title) {
    // Рисуем окно в стиле Ривенделла
    draw_rounded_rect(x, y, w, h, 10, COLOR_ELVEN_GOLD);
    draw_text(x+10, y+5, title, COLOR_WHITE);
}

void execute_callback() {
    // Запуск .exe файла через Wine
    wine_execute("/apps/legolas.exe");
}