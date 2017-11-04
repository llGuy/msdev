SRC=main.c common.c monitor.c gdt.c idt.c isr.c timer.c
ASM=loader.s gdt_asm.s idt_asm.s common_asm.s
OBJECTS = $(ASM:.s=.o) $(SRC:.c=.o)

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

depend: $(SRC)
	makedepend $(SRC)

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R \
			-b boot/grub/stage2_eltorito \
			-no-emul-boot \
			-boot-load-size 4 \
			-A os \
			-input-charset utf8 \
			-quiet \
			-boot-info-table \
			-o os.iso \
			iso

run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso


# DO NOT DELETE

main.o: monitor.h common.h gdt.h idt.h timer.h
common.o: common.h
monitor.o: monitor.h common.h
gdt.o: common.h gdt.h
idt.o: idt.h common.h isr.h
isr.o: common.h isr.h monitor.h
timer.o: timer.h common.h isr.h monitor.h idt.h
