#include "timer.h"
#include "isr.h"
#include "monitor.h"
#include "idt.h"
uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
    tick++;
    monitor_write( "Tick: ");
    monitor_write_hex( tick );
    monitor_write( "/" );
    monitor_write_hex( regs.int_no );
    monitor_write( "\n");
}

void init_timer(uint32_t frequency)
{
    register_interrupt_handler(IRQ0, &timer_callback);

    uint32_t divisor = 1193180 / frequency;

    uint8_t l = (uint8_t) (divisor & 0xFF); 
    uint8_t h = (uint8_t) ((divisor >> 8) & 0xFF);
    outb(0x43, 0x36); // command byte
    outb(0x40, l);
    outb(0x40, h);
}
