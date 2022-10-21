#ifndef __MEM_DRIVER_H
#define __MEM_DRIVER_H

#include <stdint.h>

typedef enum {
    MEM_OK,
    MEM_FAIL,
    MEM_PARAMS,
    MEM_TIMEOUT,
} MD_Status_t;

typedef uint8_t (*MD_CmdHandler_t)(void);

typedef struct MD_CmdHanderEntry {
    uint8_t CommandID;
    uint8_t ParamsLength;
    MD_CmdHandler_t Handler;
} MD_CmdHanderEntry_t;

#define PAGE_BUFFER_SIZE 8192

extern uint8_t PageBuffer[PAGE_BUFFER_SIZE];

#endif /* __MEM_DRIVER_H */
