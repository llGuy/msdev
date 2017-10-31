#ifndef ISR_H
#define ISR_H
#include "common.h"

typedef struct 
{
    uint32_t ds, edi, esi, ebp, esp, ebx, edx, ecs, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

#endif
