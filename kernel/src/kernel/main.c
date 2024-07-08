#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "../include/idt.h"
#include "../include/util.h"
#include "../include/printf.h"
#include "../include/physical.h"

#include "../limine.h"

__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);

__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};


__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;

void _start(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        kprintf(KRED "[yayos] base revision not supported (???), halting\n");
        hcf();
    }

    kprintf(KCYN "[yayos] c entry\n");

    init_idt();
    kprintf(KCYN "[info] idt set up\n");

    init_pmm();
    kprintf(KCYN "[info] pmm set up\n");

    hcf();
}
