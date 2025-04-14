# Компиляторы и утилиты
CC = gcc
LD = ld
NASM = nasm
GRUB = grub-mkrescue

# Флаги
NASMFLAGS = -f elf64
CFLAGS = -ffreestanding -nostdlib -Ikernel/ -Ilib/ -Wall -Wextra
LDFLAGS = -T lib/linker.ld -nostdlib

# Исходные файлы
BOOT_SRC = boot/boot.asm
KERNEL_SRCS = $(wildcard kernel/*.c)
DRIVER_SRCS = $(wildcard drivers/*.c)
LIB_SRCS = lib/memory.c
OBJS = $(KERNEL_SRCS:.c=.o) $(DRIVER_SRCS:.c=.o) $(LIB_SRCS:.c=.o)

# Цели сборки
all: aranore_os.iso

boot.bin: $(BOOT_SRC)
	$(NASM) -f bin $< -o $@

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	@echo "Kernel built with Elven precision!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

aranore_os.iso: boot.bin kernel.elf
	@mkdir -p iso/boot/grub
	@cp boot.bin iso/
	@cp kernel.elf iso/boot/
	@echo 'menuentry "Aranore OS" { multiboot /boot/kernel.elf }' > iso/boot/grub/grub.cfg
	@$(GRUB) -o $@ iso/
	@echo "ISO forged in the fires of Mount Doom!"

clean:
	@rm -f *.bin *.elf *.o *.iso
	@rm -rf iso/
	@echo "Cleaned like the Shire after Bilbo's party"

run: aranore_os.iso
	qemu-system-x86_64 -cdrom $< -m 2G -vga virtio -serial stdio

.PHONY: all clean run
