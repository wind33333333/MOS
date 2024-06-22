#include "lib.h"
#include "printk.h"
#include "ioapic.h"
#include "ap.h"
#include "acpi.h"
#include "idt.h"
#include "apic.h"
#include "memory.h"
#include "gdt.h"
#include "tss.h"
#include "papg.h"
#include "cpuinfo.h"
#include "hpet.h"

__attribute__((section(".init_text"))) void Kernel_init(void) {
    unsigned int cpu_id;
    pos_init();                                  //初始化输出控制台
    get_cpuinfo(&cpu_id);                     //获取cpu信息
    memory_init();                               //初始化内存管理器
    gdt_init();                                  //初始化GDT
    tss_init(cpu_id);                            //初始化TSS
    idt_init();                                  //初始化IDT
    acpi_init();                                 //初始化acpi
    hpet_init();                                 //初始化hpet
    ioapic_init();                               //初始化ioapic
    apic_init();                                 //初始化apic
    ap_init(cpu_id);                             //初始化ap核
    papg_init();                                 //初始化内核页表




//    BOCHS_DG();
//    unsigned long i = 0xffff;
//    APIC_SET_TSCDEADLINE(cpu_info.tsc_frequency);
    sti();
    while (1);
}