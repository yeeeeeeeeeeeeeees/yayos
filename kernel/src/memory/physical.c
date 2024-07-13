#include "../include/printf.h"
#include "../include/physical.h"
#include "../include/requests.h"

#include "../limine.h"

__attribute__((used, section(".requests")))
static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

pmm_entry_t *head = {0};

static void add_page(uint64_t base) {
    pmm_entry_t *new = (pmm_entry_t *)(base+hhdm_request.response->offset);
    if (head == NULL) {
        head = new;
        return;
    }
    new->next = head;
    head = new;
}

void *palloc() {
    void *page_address = (void *)((uint64_t)head-hhdm_request.response->offset);
    if (head == NULL) {
        kprintf(KRED "[critical] out of physical memory\n");
        return (void*)0;
    }
    head = head->next;
    return page_address;
}

void pfree(void *ptr) {
    add_page((uint64_t)ptr+hhdm_request.response->offset);
}

void init_pmm() {
    for (int i=0;i<memmap_request.response->entry_count;i++) {
        uint64_t entry_base = memmap_request.response->entries[i]->base;
        uint64_t entry_type = memmap_request.response->entries[i]->type;
        uint64_t entry_size = memmap_request.response->entries[i]->length;
        if (entry_type == 0) {
            kprintf(KCYN "entry %d in memmap = %llx | size = %lld\n", i, entry_base, entry_size / 0x1000);
            for (uint64_t k=0;k<entry_size;k+=0x1000) {
                add_page(entry_base+k);
            }
        }
    }
}
