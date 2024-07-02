#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct idt_entry_t {
    uint64_t isr_low  : 16;
    uint64_t cs : 16;
    uint64_t ist : 3;
    uint64_t reserved_0 : 5;
    uint64_t gate_type : 4;
    uint64_t reserved_1 : 1;
    uint64_t dpl : 2;
    uint64_t present : 1;
    uint64_t isr_high : 48;
    uint64_t reserved_2 : 32;
} __attribute__((__packed__)) idt_entry_t;

typedef struct {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
} __attribute__((__packed__)) cpu_state;

typedef struct {
    uint64_t error_code;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((__packed__)) stack_state;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((__packed__)) idtr_t;


void handle_interrupt(cpu_state *cpu, stack_state *stack);
void init_idt();
void set_idt_gate(uintptr_t handler, uint8_t idx);
void load_traps();
#endif
