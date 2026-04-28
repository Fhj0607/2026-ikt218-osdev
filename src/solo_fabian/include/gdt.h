#pragma once

/* Fixed-size integer types used by the kernel. */
#include <libc/stdint.h>

/*
 * GDT selector values.
 * These are used when switching to protected mode.
 */
#define GDT_KERNEL_CODE_SELECTOR 0x08  /* code segment */
#define GDT_KERNEL_DATA_SELECTOR 0x10  /* data segment */

/* Sets up and loads the GDT. */
void gdt_init(void);