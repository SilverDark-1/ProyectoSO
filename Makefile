CC = gcc
CFLAGS = -m32 -c -ffreestanding -fno-pic -fno-stack-protector -nostdlib
LD = ld
LDFLAGS = -m elf_i386 --oformat binary -Ttext 1000
NASM = nasm
NASMFLAGS = -f elf32

OBJECTS = kernel.o screen.o gdt.o lib.o idt.o isr.o pic.o interrupt.o

all: floppy.img

bootsect:
	nasm -f bin -o bootsect bootsect.asm

kernel: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel

kernel.o: kernel.c
	$(CC) $(CFLAGS) kernel.c

screen.o: screen.c
	$(CC) $(CFLAGS) screen.c

gdt.o: gdt.c
	$(CC) $(CFLAGS) gdt.c

lib.o: lib.c
	$(CC) $(CFLAGS) lib.c

idt.o: idt.c
	$(CC) $(CFLAGS) idt.c

isr.o: isr.c
	$(CC) $(CFLAGS) isr.c

pic.o: pic.c
	$(CC) $(CFLAGS) pic.c

interrupt.o: interrupt.asm
	$(NASM) $(NASMFLAGS) interrupt.asm

floppy.img: bootsect kernel
	cat bootsect kernel /dev/zero | dd of=floppy.img bs=512 count=2880

clean:
	rm -f *.o kernel bootsect floppy.img

run: floppy.img
	qemu-system-i386 -fda floppy.img

debug: floppy.img
	qemu-system-i386 -fda floppy.img -s -S

.PHONY: all clean run debug
