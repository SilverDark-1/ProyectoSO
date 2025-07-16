#ifndef _LIB_H_
#define _LIB_H_

#include "types.h"

/* Funciones básicas de librería */
void *memcpy(void *dest, const void *src, u32 count);
void *memset(void *dest, u8 val, u32 count);
u32 strlen(const char *s);

#endif