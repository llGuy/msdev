#include "common.h"
#include "isr.h"
#include "monitor.h"


isr_t interrupt_handlers[256];

void init_isr()
{
    memset((uint8_t*)&interrupt_handlers, 0, sizeof(isr_t)*256);
}

void isr_handler(registers_t * regs)
{
    monitor_write( "isr ");
    monitor_write_hex( regs->int_no );
    monitor_put( '\n');

    if( interrupt_handlers[regs->int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(*regs);
    }
}


void irq_handler(registers_t * regs)
{
    monitor_write( "irq ");
    monitor_write_hex( regs->int_no );
    monitor_put( '\n');
    if( regs->int_no >= 40)
    {
        outb(0xA0, 0x20); // send reset signal to slave
    }
    outb(0x20, 0x20); // send reset signal to master

    if( interrupt_handlers[regs->int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(*regs);
    }
}

void register_interrupt_handler(uint8_t irq, isr_t handler)
{
    interrupt_handlers[irq] = handler;
}
