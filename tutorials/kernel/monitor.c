#include "monitor.h"

uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint16_t * video_memory = (uint16_t*)0xB8000;
uint8_t color_fg = 15;
uint8_t color_bg = 0; // black

static void move_cursor()
{
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursorLocation >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorLocation);
}

static void scroll()
{
    uint8_t attributeByte = (0 << 4) | (15 & 0xF);//black(0) bg, white fg
    uint16_t blank = 0x20 | (attributeByte << 8);

    if( cursor_y >= 25)
    {
        int i;
        for( i=0; i < 24*80;i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        for( i=24*80; i < 25*80; i++)
        {
            video_memory[i] = blank;
        }
        cursor_y = 24;
    }
}

void monitor_put(char c)
{
    
    uint8_t attributeByte = (color_bg << 4) | (color_fg & 0x0F);
    uint16_t attribute = attributeByte << 8;

    uint16_t * location;

    if( c == 0x08 && cursor_x) //backspace
    {
        cursor_x--;
    }
    else if( c==0x09 ) //tab
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }
    else if( c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }else if( c >= ' ') // printable
    {
        location = video_memory + (cursor_y*80+cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    if( cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    scroll();
    move_cursor();
}

void monitor_clear()
{
    uint8_t attributeByte = (color_bg << 4) | (color_fg & 0x0F);
    uint16_t blank = 0x20 | (attributeByte << 9);

    int i;
    for( i=0; i < 80*25; i++)
    {
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void monitor_write( char * c )
{
    int i=0;
    while( c[i] )
    {
        monitor_put(c[i++]);
    }
}
