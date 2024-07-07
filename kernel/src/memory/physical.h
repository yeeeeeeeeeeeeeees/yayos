#ifndef PHYSICAL_H
#define PHYSICAL_H

typedef struct pmm_entry_t {
    struct pmm_entry_t *next;
} pmm_entry_t;

void *palloc();
void pfree(void *ptr);
void init_pmm();

#endif
