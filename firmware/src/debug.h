#ifndef __debug_h
#define __debug_h

/* Debug interface implementation, based on SWO */

/*
Technical notes:

- ST-LINK only starts displaying the trace after reconnecting to the target!
- Modding ST-LINK v2 for SWO:
  https://research.kudelskisecurity.com/2020/04/15/swd-part-3-swo-and-nrst/
*/

#ifdef _DEBUG

void DEBUG_Init(void);

void DEBUG_PrintChar_(char x);
void DEBUG_PrintString_(const char *s);
void DEBUG_PrintHex_(const void *p, unsigned n);
void DEBUG_PrintU8_(uint8_t value);
void DEBUG_PrintU16_(uint16_t value);
void DEBUG_PrintU32_(uint32_t value);

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
