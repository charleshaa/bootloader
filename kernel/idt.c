#include "idt.h"
#include "x86.h"

// CPU context used when saving/restoring context from an interrupt
typedef struct regs_st {
    uint32_t gs, fs, es, ds;
    uint32_t ebp, edi, esi;
    uint32_t edx, ecx, ebx, eax;
    uint32_t number, error_code;
    uint32_t eip, cs, eflags, esp, ss;
} regs_t;

// Build and return an IDT entry.
// selector is the code segment selector in which resides the ISR (Interrupt Service Routine)
// offset is the address of the ISR (NOTE: for task gates, offset must be 0)
// type indicates the IDT entry type
// dpl is the privilege level required to call the associated ISR
static idt_entry_t idt_build_entry(uint16_t selector, uint32_t offset, uint8_t type, uint8_t dpl) {
	idt_entry_t entry;
    entry.offset15_0 = offset & 0xffff;
    entry.selector = selector;
    entry.reserved = 0;
    entry.type = type;
    entry.dpl = dpl;
    entry.p = 1;
    entry.offset31_16 = (offset >> 16) & 0xffff;
	return entry;
}
// La idt
static idt_entry_t idt[256];

// Pointer vers la IDT
static idt_ptr_t idt_ptr;

// Exception handler
void exception_handler(regs_t *regs) {

}

// Interruption handler
void interruption_handler(regs_t *regs){

}

void idt_init() {

    // Initialisation de 256 entrées à 0
    for(int i=0; i<256; i++)
    {
        idt[i] = idt_build_entry(0,0,0,0);
    }

    // La limite de idt_ptr
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)idt; // Base of idt is the first element of idt
    // On créée les entrées d'exceptions
    idt[0] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[1] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_1, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[2] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_2, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[3] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_3, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[4] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_4, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[5] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_5, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[6] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_6, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[7] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_7, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[8] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_8, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[9] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_9, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[10] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_10, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[11] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_11, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[12] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_12, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[13] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_13, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[14] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_14, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[15] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_15, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[16] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_16, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[17] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_17, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[18] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_18, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[19] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_19, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[20] = idt_build_entry(GDT_KERNER_CODE_SELECTOR, (uint32_t)&_exception_20, TYPE_INTERRUPT_GATE, DPL_KERNEL);

    // Entrées pour les interruptions
    idt[32] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_0, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[33] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_1, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[34] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_2, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[35] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_3, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[36] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_4, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[37] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_5, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[38] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_6, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[39] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_7, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[40] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_8, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[41] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_9, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[42] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_10, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[43] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_11, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[44] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_12, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[45] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_13, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[46] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_14, TYPE_INTERRUPT_GATE, DPL_KERNEL);
    idt[47] = idt_build_entry(GDT_KERNEL_CODE_SELECTOR, (uint32_t)&_irq_15, TYPE_INTERRUPT_GATE, DPL_KERNEL);


}
