//#include "multiboot.h"
#include "monitor.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
//int kernel_main(multiboot_info_t * mboot_ptr)
int kernel_main()
{
    monitor_clear();
    monitor_write( "Hello World!\n" );

    init_gdt();
    init_idt();


    init_timer(20);
    asm volatile ( "int $0x3" );
    asm volatile ( "int $0x4" );
    asm volatile ( "int $0x20" );
    asm volatile ( "int $0x28" );
    return 0xDEADCAFE;
}
