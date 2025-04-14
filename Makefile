CC = gcc
LD = ld
NASM = nasm

CFLAGS = -ffreestanding -nostdlib -Ikernel/
LDFLAGS = -T lib/linker.ld -nostdlib

SRCS = kernel/kernel.c kernel/gui.c kernel/vbe.c kernel/wine.c
OBJS = $(SRCS:.c=.o)

all: aranore_os.iso

boot.bin: boot/boot.asm
	$(NASM) -f bin $< -o $@

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o kernel/$@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

aranore_os.iso: boot.bin kernel.elf
	mkdir -p iso/boot/grub
	cp boot.bin iso/
	cp kernel/kernel.elf iso/boot/
	echo 'menuentry "Aranore OS" { multiboot /boot/kernel.elf }' > iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso/

clean:
	rm -f *.bin *.elf *.o *.iso
	rm -rf iso/

run: aranore_os.iso
	qemu-system-x86_64 -cdrom $< -m 2G -vga std
