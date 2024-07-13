#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
<<<<<<< Updated upstream
#include "../interrupts/idt.h"
#include "limine.h"
#include "../klib/util.h"
#include "../klib/printf.h"
=======

#include "../include/idt.h"

#include "../include/util.h"
#include "../include/printf.h"

#include "../include/physical.h"
#include "../include/virtual.h"

#include "../limine.h"
>>>>>>> Stashed changes

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
        kprintf("%s[yayos] base revision not supported (???), halting", KRED);
        hcf();
    }

    kprintf("%s[yayos] c entry\n", KCYN);
    init_idt();

    init_paging();
    kprintf(KCYN "[info] paging set up");

    hcf();
}
