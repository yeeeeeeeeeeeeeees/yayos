#ifndef PHYSICAL_H
#define PHYSICAL_H

#include "../limine.h"

// #define HHDM_OFFSET 0xffffffff80002620

typedef struct pmm_entry_t {
    struct pmm_entry_t *next;
} pmm_entry_t;

void *palloc();
void pfree(void *ptr);
void init_pmm();

#endif
