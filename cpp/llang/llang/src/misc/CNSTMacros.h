#ifndef _CNST_MACROS
#define _CNST_MACROS

#define _NULL 0
#define _STR_NULL "NULL"
#define _SIZE_OF_LLIST 4
#define _DEF_SIZE_HTABLE 4
#define _XOR(p1,p2) p1 ^ p2
#define _LSHIFT(valToShift,shifter) valToShift << shifter
#define _ROTL(p1,p2,shifter) _XOR(p1,_LSHIFT(p2,shifter)) 

#endif
