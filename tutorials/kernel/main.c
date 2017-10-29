//#include "multiboot.h"
#include "monitor.h"
#include "gdt.h"

//int kernel_main(multiboot_info_t * mboot_ptr)
int kernel_main()
{
    monitor_clear();
    monitor_write( "Hello World!" );

    init_gdt();
    return 0xDEADCAFE;
}
