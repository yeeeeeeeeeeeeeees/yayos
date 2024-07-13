#include "../include/requests.h"

__attribute__((used, section(".requests")))
struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};
