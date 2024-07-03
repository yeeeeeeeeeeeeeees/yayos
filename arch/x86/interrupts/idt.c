#include "idt.h"
#include "../klib/printf.h"
#include <stdint.h>

idt_entry_t idt[256] __attribute__((aligned(0x10)));
extern uint64_t trap_stubs[256];

void load_traps() {
    for (int k=0;k<256;k++) {
        set_idt_gate(trap_stubs[k], k);
    }
}

void set_idt_gate(uintptr_t handler, uint8_t idx) {
    idt_entry_t* entry = &idt[idx];

    entry->isr_low = handler & 0xFFFF;
    entry->isr_high = handler >> 16;
    entry->gate_type = 0xE;
    entry->dpl = 0;
    entry->ist = 0;
    entry->present = 1;
    entry->cs = 0x28;
}

void init_idt() {
    idtr_t idtr;
    idtr.base = (uint64_t)&idtr;
    idtr.limit = sizeof(idt_entry_t) * 255;
    load_traps();
    __asm__("lidt %0"::"m"(idtr));
    __asm__("sti");
    kprintf("%s[yayos] idt set up", KCYN);
}

void handle_interrupt(cpu_state *cpu, stack_state *stack) {
    switch(stack->error_code) {
        case 0x06:
            kprintf("%s[yayos] invalid opcode, maybe division by 0?", KRED);
            __asm__("cli; hlt");
    }
}
