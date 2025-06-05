/*----------------------------------------------------------------------------*/
/* linker.cmd                                                      */
/*                                                                            */
/* 
* Copyright (C) 2019 Alexy Torres Aurora Dugo
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* Linker Settings                                                            */

--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */
/*----------------------------------------------------------------------------*/
MEMORY
{
    VECTORS     (RX) : origin = 0x00000000 length = 0x0000100 /* Vector table */
    FLASH0      (RX) : origin = 0x00000100 length = 0x000FF000 /* Remaining flash */
    RAM         (RW) : origin = 0x08000000 length = 0x00080000 /* Internal SRAM */
}
 
/*----------------------------------------------------------------------------*/
/* Section Allocation                                                         */
/*----------------------------------------------------------------------------*/
SECTIONS
{
    .intvecs : {}              > VECTORS       /* Interrupt vectors */
    .text    : {}              > FLASH0        /* Code */
    .const   : {}              > FLASH0        /* Constants */
    .cinit   : {}              > FLASH0        /* C init tables */
    .pinit   : {}              > FLASH0        /* Constructors (C++) */
    .binit   : {}              > FLASH0        /* Binit table (rare) */
 
    .data    : {}              > RAM AT > FLASH0 /* Initialized variables */
    .bss     : {}              > RAM           /* Uninitialized variables */
    .sysmem  : {}              > RAM           /* Heap */
    .stack   : {}              > RAM           /* Stack */
}
 
/*----------------------------------------------------------------------------*/
/* Stack and Heap Sizes                                                      */
/*----------------------------------------------------------------------------*/
__stack_size = 0x1000;  /* 4KB stack */
__heap_size  = 0x1000;  /* 4KB heap */
/*----------------------------------------------------------------------------*/
/* Misc                                                                       */
__archive2_begin = 0x00200000;
/*----------------------------------------------------------------------------*/
