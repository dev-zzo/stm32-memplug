#ifndef __debug_h
#define __debug_h

void DEBUG_Init(void);

void DEBUG_PrintChar_(char x);
void DEBUG_PrintString_(const char *s);
void DEBUG_PrintHex_(const void *p, unsigned n);
void DEBUG_PrintU8_(uint8_t value);
void DEBUG_PrintU16_(uint16_t value);
void DEBUG_PrintU32_(uint32_t value);

#if 1

#define DEBUG_PrintChar(c) DEBUG_PrintChar_(c)
#define DEBUG_PrintString(s) DEBUG_PrintString_(s)
#define DEBUG_PrintHex(p,n) DEBUG_PrintHex_((const void *)(p), (n))
#define DEBUG_PrintU8(v) DEBUG_PrintU8_(v)
#define DEBUG_PrintU16(v) DEBUG_PrintU16_(v)
#define DEBUG_PrintU32(v) DEBUG_PrintU32_(v)

#else

#define DEBUG_PrintChar(c)
#define DEBUG_PrintString(s)
#define DEBUG_PrintHex(p,n)
#define DEBUG_PrintU8(v)
#define DEBUG_PrintU16(v)
#define DEBUG_PrintU32(v)

#endif

#endif /* __debug_h */
