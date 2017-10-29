//#include "multiboot.h"
#include "monitor.h"

//int kernel_main(multiboot_info_t * mboot_ptr)
int kernel_main()
{
    monitor_clear();
    monitor_write( "Hello World!" );
    return 0xDEADCAFE;
}
