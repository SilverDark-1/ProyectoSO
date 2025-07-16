#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "types.h"

/* Variables globales para la pantalla */
extern char kX, kY, kattr;

/* Funciones de pantalla */
void scrollup(unsigned int n);
void putcar(uchar c);
void print(char *string);

#endif