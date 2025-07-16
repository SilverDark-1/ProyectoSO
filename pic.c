#include "types.h"

/*
 * Inicialización del controlador de interrupciones PIC 8259A
 */
void init_pic(void)
{
    /* Inicialización del PIC maestro */
    asm("mov $0x11, %al; out %al, $0x20");      /* ICW1 */
    asm("mov $0x20, %al; out %al, $0x21");      /* ICW2 */
    asm("mov $0x04, %al; out %al, $0x21");      /* ICW3 */
    asm("mov $0x01, %al; out %al, $0x21");      /* ICW4 */
    
    /* Inicialización del PIC esclavo */
    asm("mov $0x11, %al; out %al, $0xA0");      /* ICW1 */
    asm("mov $0x70, %al; out %al, $0xA1");      /* ICW2 */
    asm("mov $0x02, %al; out %al, $0xA1");      /* ICW3 */
    asm("mov $0x01, %al; out %al, $0xA1");      /* ICW4 */
    
    /* Habilitar todas las interrupciones */
    asm("mov $0x0, %al; out %al, $0x21");       /* maestro */
    asm("mov $0x0, %al; out %al, $0xA1");       /* esclavo */
}
