#ifndef ISR_H
#define ISR_H
#include "common.h"

typedef struct 
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecs, eax; // pusha
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss; // pushed by processor
} __attribute__((packed)) registers_t;

#endif
