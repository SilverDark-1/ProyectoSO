#include "types.h"
#define RAMSCREEN 0xB8000       /* inicio de la memoria de video */
#define SIZESCREEN 0xFA0        /* 4000, número de bytes de una página texto */
#define SCREENLIM 0xB8FA0
char kX = 0;                    /* posición actual del cursor en pantalla */
char kY = 17;
char kattr = 0x0E;              /* atributos de video de los caracteres a mostrar */
/* 
 * 'scrollup' desplaza la pantalla (la consola mapeada en RAM) hacia arriba
 * n líneas (de 0 a 25).
 */
void scrollup(unsigned int n)
{
    unsigned char *video, *tmp;
    for (video = (unsigned char *) RAMSCREEN;
         video < (unsigned char *) SCREENLIM; video += 2) {
        tmp = (unsigned char *) (video + n * 160);
        if (tmp < (unsigned char *) SCREENLIM) {
            *video = *tmp;
            *(video + 1) = *(tmp + 1);
        } else {
            *video = 0;
            *(video + 1) = 0x07;
        }
    }
    kY -= n;
    if (kY < 0)
        kY = 0;
}
void putcar(uchar c)
{
    unsigned char *video;
    int i;
    if (c == 10) {          /* CR-NL */
        kX = 0;
        kY++;
    } else if (c == 9) {    /* TAB */
        kX = kX + 8 - (kX % 8);
    } else if (c == 13) {   /* CR */
        kX = 0;
    } else {                /* otros caracteres */
        video = (unsigned char *) (RAMSCREEN + 2 * kX + 160 * kY);
        *video = c;
        *(video + 1) = kattr;

        kX++;
        if (kX > 79) {
            kX = 0;
            kY++;
        }
    }
    if (kY > 24)
        scrollup(kY - 24);
}
/*
 * 'print' muestra en pantalla, en la posición actual del cursor, una cadena
 * de caracteres terminada en \0.
 */
void print(char *string)
{
    while (*string != 0) {  /* mientras el carácter sea diferente de 0x0 */
        putcar(*string);
        string++;
    }
}
