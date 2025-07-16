[BITS 32]

; Rutinas de servicio exportadas
EXTERN isr_default_int, isr_GP_exc, isr_PF_exc, isr_clock_int, isr_kbd_int

; Rutinas de ensamblador exportadas
GLOBAL _asm_default_int, _asm_exc_GP, _asm_exc_PF, _asm_irq_0, _asm_irq_1

; Rutina por defecto
_asm_default_int:
    pusha
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call isr_default_int
    
    pop gs
    pop fs
    pop es
    pop ds
    popa
    
    iret

; Excepción General Protection
_asm_exc_GP:
    pusha
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call isr_GP_exc
    
    pop gs
    pop fs
    pop es
    pop ds
    popa
    
    add esp, 4  ; remover código de error
    iret

; Excepción Page Fault
_asm_exc_PF:
    pusha
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call isr_PF_exc
    
    pop gs
    pop fs
    pop es
    pop ds
    popa
    
    add esp, 4  ; remover código de error
    iret

; IRQ0 - Timer
_asm_irq_0:
    pusha
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call isr_clock_int
    
    pop gs
    pop fs
    pop es
    pop ds
    popa
    
    iret

; IRQ1 - Teclado
_asm_irq_1:
    pusha
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call isr_kbd_int
    
    pop gs
    pop fs
    pop es
    pop ds
    popa
    
    iret
