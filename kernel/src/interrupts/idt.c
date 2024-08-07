#include <stdint.h>

#include "../include/idt.h"
#include "../include/util.h"
#include "../include/printf.h"

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
    idtr.base = (uint64_t)&idt;
    idtr.limit = sizeof(idt)-1;
    load_traps();
    __asm__("lidt %0"::"m"(idtr));
    __asm__("sti");
}

void handle_interrupt(tf *frame) {
    kprintf(KRED "[error] interrupt occured, halting\n");
    kprintf(KRED "vector = 0x%x\n", frame->vector);
    kprintf(KRED "rip = 0x%llx\n", frame->rip);
    hcf();
}
