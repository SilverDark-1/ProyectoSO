#include "screen.h"
#include "types.h"

/* Rutina por defecto para interrupciones no implementadas */
void isr_default_int(void)
{
    print("Interrupcion no implementada\n");
    return;
}

/* Rutina para excepción General Protection (#GP) */
void isr_GP_exc(void)
{
    kattr = 0x4F;  /* texto blanco sobre fondo rojo */
    print("EXCEPTION: General Protection Fault\n");
    kattr = 0x07;  /* restaurar atributos normales */
    asm("hlt");    /* detener el sistema */
}

/* Rutina para excepción Page Fault (#PF) */
void isr_PF_exc(void)
{
    kattr = 0x4F;  /* texto blanco sobre fondo rojo */
    print("EXCEPTION: Page Fault\n");
    kattr = 0x07;  /* restaurar atributos normales */
    asm("hlt");    /* detener el sistema */
}

/* Rutina para IRQ0 (Timer) */
void isr_clock_int(void)
{
    print(".");
    
    /* Enviar EOI al PIC */
    asm("mov $0x20, %al; out %al, $0x20");
    return;
}

/* Rutina para IRQ1 (Teclado) */
void isr_kbd_int(void)
{
    u8 scancode;
    
    /* Leer el scancode del teclado */
    asm volatile("inb $0x60, %0" : "=a" (scancode));
    
    /* Mostrar información del teclado */
    print("Tecla presionada: ");
    putcar('0' + (scancode / 100));
    putcar('0' + ((scancode / 10) % 10));
    putcar('0' + (scancode % 10));
    print("\n");
    
    /* Enviar EOI al PIC */
    asm volatile("movb $0x20, %al; outb %al, $0x20");
    return;
}
