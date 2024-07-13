#include "../include/virtual.h"
#include "../include/physical.h"
#include "../include/util.h"
#include "../include/printf.h"
#include "../include/requests.h"


#include "../limine.h"

void map_virt_to_phys(PageTable *pml4, uint64_t virtual, uint64_t physical, uint64_t flags) {
    uint64_t mask = 0b111111111;

    uint64_t pml4_index = (virtual >> 39) & mask;
    uint64_t pdpt_index = (virtual >> 30) & mask;
    uint64_t pd_index = (virtual >> 21) & mask;
    uint64_t pt_index = (virtual >> 12) & mask;

    if (!(pml4->entries[pml4_index] & 1)) {
        void *entry_page = palloc();
        memset(entry_page, 0, 0x1000);
        pml4->entries[pml4_index] = (uint64_t)entry_page | flags | 1; // make dat shit present cuh
    }
    PageTable *pdpt = (PageTable *)(pml4->entries[pml4_index] & ~0xFFF);

    if (!(pdpt->entries[pdpt_index] & 1)) {
        void *entry_page = palloc();
        memset(entry_page, 0, 0x1000);
        pdpt->entries[pdpt_index] = (uint64_t)entry_page | flags | 1;
    }
    PageTable *pd = (PageTable *)(pdpt->entries[pdpt_index] & ~0xFFF);

    if (!(pd->entries[pd_index] & 1)) {
        void *entry_page = palloc();
        memset(entry_page, 0, 0x1000);
        pd->entries[pd_index] = (uint64_t)entry_page | flags | 1;
    }
    PageTable *pt = (PageTable *)(pd->entries[pd_index] & ~0xFFF);

    pt->entries[pt_index] = physical | flags | 1;
}

void init_paging() {
    uint64_t page_for_pml4 = (uint64_t)palloc();
    // __asm__ volatile("1: jmp 1b");
    PageTable *pml4 = (PageTable *)(page_for_pml4 + hhdm_request.response->offset);
    uint64_t old_cr3;
    __asm__ volatile("movq %%cr3, %0" : "=r"(old_cr3));
    old_cr3 += hhdm_request.response->offset;
    for (int i=256;i<512;i++) {
        pml4->entries[i] = ((uint64_t *)old_cr3)[i];
    }
    __asm__ volatile("movq %0, %%cr3" : : "r" (pml4));
}
