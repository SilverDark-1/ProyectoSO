extern void scrollup(unsigned int);
extern void print(char *);

extern kY;
extern kattr;

void _start(void)
{
    kY = 18;
    kattr = 0x5E;
    print("Kernel en C iniciado!\n");

    kattr = 0x4E;
    print("Sistema operativo basico funcionando\n");

    scrollup(2);

    while (1);
}
