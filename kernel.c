#include "types.h"
#include "gdt.h"
#include "idt.h"
#include "screen.h"

/* Prototipo de funciones */
void init_pic(void);
int main(void);

void _start(void)
{
    kY = 18;
    kattr = 0x5E;
    print("kernel: cargando nueva GDT...\n");

    /* inicialización de la GDT y los segmentos */
    init_gdt();

    /* Inicialización del puntero de pila %esp */
    asm("   movw $0x18, %ax \n \
            movw %ax, %ss \n \
            movl $0x20000, %esp");

    kattr = 0x4E;
    print("kernel: nueva GDT cargada!\n");
    
    kattr = 0x5E;
    print("kernel: inicializando IDT...\n");
    
    /* inicialización de la IDT */
    init_idt();
    
    kattr = 0x4E;
    print("kernel: IDT inicializada!\n");
    
    kattr = 0x5E;
    print("kernel: inicializando PIC...\n");
    
    /* inicialización del PIC */
    init_pic();
    
    kattr = 0x4E;
    print("kernel: PIC inicializado!\n");

    main();
}

int main(void)
{
    kattr = 0x0A;
    print("Sistema operativo con manejo de interrupciones!\n");
    print("Presiona cualquier tecla para probar...\n");
    
    /* Habilitar interrupciones */
    asm("sti");
    
    while (1) {
        /* Loop infinito - las interrupciones manejan los eventos */
        asm("hlt");
    }
}
