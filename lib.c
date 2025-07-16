#include "lib.h"

/*
 * memcpy: copia 'count' bytes de 'src' a 'dest'
 */
void *memcpy(void *dest, const void *src, u32 count)
{
    char *d = (char*)dest;
    const char *s = (const char*)src;
    
    while (count--)
        *d++ = *s++;
    
    return dest;
}

/*
 * memset: llena 'count' bytes de 'dest' con 'val'
 */
void *memset(void *dest, u8 val, u32 count)
{
    char *d = (char*)dest;
    
    while (count--)
        *d++ = val;
    
    return dest;
}

/*
 * strlen: calcula la longitud de una cadena
 */
u32 strlen(const char *s)
{
    u32 len = 0;
    
    while (*s++)
        len++;
    
    return len;
}
