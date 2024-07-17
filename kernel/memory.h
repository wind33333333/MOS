#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "printk.h"
#include "lib.h"
#include "cpuinfo.h"

void  memory_init(unsigned char bsp_flags);
void * alloc_pages(unsigned long required_length);
int free_pages(void *pages_addr,unsigned long required_length);

extern unsigned long kenelstack_top;
extern unsigned long _start_text;

#define E820_SIZE    0x500
#define E820_BASE    0x504

#define PAGE_OFFSET	((unsigned long)0xffff800000000000)
#define PAGE_4K_SHIFT	12
#define PAGE_4K_SIZE	(1UL << PAGE_4K_SHIFT)
#define PAGE_4K_MASK	(~ (PAGE_4K_SIZE - 1))
#define PAGE_4K_ALIGN(addr)	(((unsigned long)(addr) + PAGE_4K_SIZE - 1) & PAGE_4K_MASK)

#define HADDR_TO_LADDR(addr)	((unsigned long)(addr) & (~PAGE_OFFSET))
#define LADDR_TO_HADDR(addr)	((unsigned long *)((unsigned long)(addr) | PAGE_OFFSET))

struct E820
{
    unsigned long address;
    unsigned long length;
    unsigned int	type;
}__attribute__((packed));

typedef struct {
    struct E820 	e820[12];
    unsigned long 	e820_length;

    unsigned long * bits_map;
    unsigned long 	bits_size;
    unsigned long   bits_length;

    unsigned long   total_pages;
    unsigned long   alloc_pages;
    unsigned long   free_pages;

    unsigned long 	kernel_start;
    unsigned long   kernel_end;

    unsigned char   lock;
} Global_Memory_Descriptor;

Global_Memory_Descriptor memory_management_struct = {0};

#endif
