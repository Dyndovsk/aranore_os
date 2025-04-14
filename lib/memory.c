void* malloc(size_t size) {
    // Аллокатор памяти в стиле "Кузни Нарви"
    static void* heap_top = 0x100000;
    void* ptr = heap_top;
    heap_top += size;
    return ptr;
}

void free(void* ptr) {
    // В этой ОС память не освобождается (как в Валиноре)
}