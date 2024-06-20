#include "apic.h"

__attribute__((section(".init_text"))) void apic_init(void) {
    __asm__ __volatile__ (
            "movl    $0x1b,%%ecx  \n\t"         //IA32_APIC_BASE=0x1b 寄存器
            "rdmsr                \n\t"
            "or      $0xc00,%%eax \n\t"         //bit10启用x2apic ,bit11启用xapic
            "wrmsr                \n\t"

            "movl   $0x80f,%%ecx  \n\t"         //SVR寄存器
            "rdmsr                \n\t"
            "bts    $8,%%eax      \n\t"         //bit0-7伪中断号，bit8启用local apic
            "btr    $12,%%eax     \n\t"         //bit12禁用自动广播EOI
            "wrmsr                \n\t"

            "movl   $0x808,%%ecx  \n\t"         //TPR优先级寄存器
            "movl   $0,%%edx      \n\t"
            "movl   $0x10,%%eax   \n\t"
            "wrmsr                \n\t"

            "movl   $0x832,%%ecx    \n\t"         //定时器寄存器
            "movl   $0x0,%%edx      \n\t"
            "movl   $0x20020,%%eax  \n\t"         //bit0-7中断向量号,bit16屏蔽标志 0未屏蔽 1屏蔽,bit17 18 00/一次计数 01/周期计数 10/TSC-Deadline
            "wrmsr                  \n\t"

            "movl   $0x83E,%%ecx    \n\t"         //分频器寄存器
            "movl   $0x0,%%edx      \n\t"
            "movl   $0xA,%%eax      \n\t"          //bit013 0:2 1:4 2:8 3:16 8:32 9:64 0xA:128 0xB:1
            "wrmsr                  \n\t"


//            //qemu操作CMCI寄存器会报错暂时禁用
//            "movl $0x82F,%%ecx \n\t"           //CMCI寄存器
//            "movl $0x0,%%edx \n\t"
//            "movl $0x10021,%%eax \n\t"         //bit0-7中断号，bit8-10投递模式000 fixed, bit16屏蔽标志 0未屏蔽 1屏蔽
//            "wrmsr \n\t"
//            "1:\tjmp 1b \n\t"


            "movl   $0x833,%%ecx    \n\t"          //温度传感寄存器
            "movl   $0x0,%%edx      \n\t"
            "movl   $0x10022,%%eax  \n\t"          //bit0-7中断号，bit8-10投递模式000 fixed, bit16屏蔽标志 0未屏蔽 1屏蔽
            "wrmsr                  \n\t"

            "movl   $0x834,%%ecx    \n\t"          //性能监控寄存器
            "movl   $0x0,%%edx      \n\t"
            "movl   $0x10023,%%eax  \n\t"          //bit0-7中断号，bit8-10投递模式000 fixed, bit16屏蔽标志 0未屏蔽 1屏蔽
            "wrmsr                  \n\t"

            "movl   $0x835,%%ecx    \n\t"          //LINT0寄存器
            "movl   $0x0,%%edx      \n\t"
            "movl   $0x10024,%%eax  \n\t"          //bit0-7中断号，bit8-10投递模式000 fixed, bit13电平触发极性0高电平触发 1低电平触发,bit15触发模式0边沿 1电平，bit16屏蔽标志 0未屏蔽 1屏蔽
            "wrmsr                  \n\t"

            "movl   $0x836,%%ecx    \n\t"          //LINT1寄存器
            "movl   $0x0,%%edx      \n\t"
            "movl   $0x10025,%%eax  \n\t"          //bit0-7中断号，bit8-10投递模式000 fixed, bit13电平触发极性0高电平触发 1低电平触发, bit15触发模式0边沿 1电平，bit16屏蔽标志 0未屏蔽 1屏蔽
            "wrmsr                  \n\t"

            "movl   $0x837,%%ecx    \n\t"          //错误寄存器
            "movl   $0x0,%%edx      \n\t"
            "movl   $0x10026,%%eax  \n\t"          //bit0-7中断号，bit16屏蔽标志 0未屏蔽 1屏蔽
            "wrmsr                  \n\t"
            :: :"%rax", "%rcx", "%rdx");

    unsigned long time = 0x100000;
    APIC_SET_COUNTER(time);

    return;
}