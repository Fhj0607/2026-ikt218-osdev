#include <gdt.h>

/* The GDT contains three entries: empty, code, and data. */
#define GDT_ENTRY_COUNT 3

/* Access settings for the code segment. */
#define GDT_ACCESS_CODE 0x9A

/* Access settings for the data segment. */
#define GDT_ACCESS_DATA 0x92

/* Flags used for 32-bit protected mode. */
#define GDT_FLAGS_32BIT_GRANULAR 0xCF

/* Structure for one GDT entry. */
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

/* Structure used when loading the GDT. */
struct gdt_pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/* Assembly function that loads the GDT. */
extern void gdt_load(struct gdt_pointer* gdt_pointer);

/* The actual GDT table. */
static struct gdt_entry gdt[GDT_ENTRY_COUNT];

/* Pointer that tells the CPU where the GDT is. */
static struct gdt_pointer gdt_ptr;

/* Sets up one entry in the GDT. */
static void gdt_set_entry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    gdt[index].limit_low = (uint16_t)(limit & 0xFFFF);          /* segment limit */
    gdt[index].base_low = (uint16_t)(base & 0xFFFF);            /* base address */
    gdt[index].base_middle = (uint8_t)((base >> 16) & 0xFF);    /* base address */
    gdt[index].access = access;                                 /* access rights */
    gdt[index].granularity = (uint8_t)(((limit >> 16) & 0x0F) | (flags & 0xF0)); /* flags */
    gdt[index].base_high = (uint8_t)((base >> 24) & 0xFF);      /* base address */
}

/* Creates and loads the GDT. */
void gdt_init(void)
{
    gdt_ptr.limit = (uint16_t)(sizeof(gdt) - 1);    /* size of GDT */
    gdt_ptr.base = (uint32_t)&gdt;                  /* address of GDT */

    gdt_set_entry(0, 0, 0, 0, 0);                   /* empty entry */
    gdt_set_entry(1, 0, 0xFFFFF, GDT_ACCESS_CODE, GDT_FLAGS_32BIT_GRANULAR); /* code segment */
    gdt_set_entry(2, 0, 0xFFFFF, GDT_ACCESS_DATA, GDT_FLAGS_32BIT_GRANULAR); /* data segment */

    gdt_load(&gdt_ptr);                             /* load the GDT */
}