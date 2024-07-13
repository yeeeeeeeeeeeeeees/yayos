#ifndef VIRTUAL_H
#define VIRTUAL_H

#include <stdint.h>

typedef struct PageTable {
    uint64_t entries[512];
} PageTable;

void map_virt_to_phys(PageTable *pml4, uint64_t virtual, uint64_t physical, uint64_t flags);
void init_paging();

#endif

