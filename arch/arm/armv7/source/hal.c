#include <hal.h>

//TODO: Move back, time functions to this file
void _interrupt_tick(void)
{
    //TODO: See if needed
}

void _hardware_init(void){
    _c_int00();
}