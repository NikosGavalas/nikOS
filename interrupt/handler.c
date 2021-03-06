#include <interrupt/handler.h>
#include <lib/asm.h>

#include <drivers/pic.h>
#include <lib/logger.h>

#include "drivers/keyb.h"

/* Causes a software interrupt */
void sw_interrupt() { asm_sw_interrupt(); }

struct cpu_state {
    unsigned int edi;
    unsigned int esi;
    unsigned int ebp;
    unsigned int esp;
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;
    unsigned int eax;
} __attribute__((packed));

/* The interrupt handler */
void interrupt_handler(struct cpu_state cpu, unsigned int int_num,
                       unsigned int err) {
    switch (int_num) {
        case 0x21:
            keyb_handle_scan_code(inb(0x60));
            pic_ack();
            break;
        default:
            log(CONSOLE, PANIC, "unknown interrupt occured.");
    }
}
