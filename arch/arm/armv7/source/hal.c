#include <hal.h>

//TODO: Move back, time functions to this file
void _interrupt_tick(void)
{
    //TODO: See if needed
}
void _hardware_init(void){
    // _c_int00();
	_init_cpu_arch();
	_cpu_reg_init();
	pok_arch_init();
	// jet_boot();
}

// void _context_init(jmp_buf *ctx, size_t sp, size_t ss, size_t ra){
// 	uint32_t *ctx_p;
// 	uint32_t *ptr;
	
// 	ctx_p = (uint32_t *)ctx;
	
// 	ctx_p[CONTEXT_SP] = sp + ss;
// 	ctx_p[CONTEXT_RA] = ra;
	
// 	ctx_p[CONTEXT_PSP] = sp + ss - 16*4;
// 	ptr = (uint32_t *)ctx_p[CONTEXT_PSP];
// 	*(ptr + 14) = ra;
// 	*(ptr + 15) = 0x01000000;
// }

