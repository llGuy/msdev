MBOOT_PAGE_ALIGN equ 1<<0 		;Load kernel and modules on a page boundary
MBOOT_MEM_INFO equ 1<<1 		;Provide your kernel with memory info
MBOOT_HEADER_MAGIC equ 0x1BADB002 	;Multiboot Magic value
					;NOTE : we do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not 
					;pass us a symbol table
MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

bits 32 				; All instructions should be 32-bit
section .text

global mboot 				;make mboot accessible from C
extern code 				; start of the .text section
extern bss				;start of the .bss section
extern end 				;end of the last loadable section

mboot: 
	dd MBOOT_HEADER_MAGIC 			;GRUB will search for this value on each 
					;4-byte boundary in your kernel file\
	dd MBOOT_HEADER_FLAGS 			;How GRUB should load your file / settings
	dd MBOOT_CHECKSUM 			;To ensure that the above values are correct
	dd mboot 				;location of this descriptor
		dd code 				;start of the kernel .text (code) section
		dd bss 					;start of the last loadable section
		dd end					;end of kernel
		dd start 				;kernel entry point (initial EIP)

global start:function start.end-start 				;kernel entry point
extern kernel_main 				;this is the entry point of our C Code

start:
	cli
	mov esp,stack
	push ebx				;load multiboot header location
	mov ebp,0

	call kernel_main				;call our main() function
	jmp $ 					;executing whatever rubbish is in the memory 
.end

section .bss
	resb 32768
stack:
