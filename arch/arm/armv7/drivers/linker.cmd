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

MEMORY
{
	/* Interrupt vector */
    VECTORS (X) : origin=0x08000000 length=0x00000020
    FLASH   (RX) : origin=0x08000020 length=0x0003FFE0
    RAM    (RW) : origin=0x20000000 length=0x00010000
}

/*----------------------------------------------------------------------------*/

/* Section Configuration                                                      */

/*----------------------------------------------------------------------------*/
 
SECTIONS
{
	/* Int vectors first */
    .intvecs :       align{} > VECTORS
    /* Rest of code to user mode flash region */
    .text        align(32) : {} > FLASH
    .data        align(32) : {} > RAM
    .bss       align(32) : {} > RAM
    .heap         align(32) : {} > RAM
    .stack         align(32) : {} > RAM
}

/*----------------------------------------------------------------------------*/
/* Stack & Heap Definitions                                                   */
/*----------------------------------------------------------------------------*/
/* Stack size = 8K */

STACK_SIZE = 0x00002000;

/* Compute stack start and end in RAM */
STACK_START = 0x20000000 + 0x00010000;
STACK_END = STACK_START - STACK_SIZE;

/*Heap begins immediately after _ebss (end of BSS) and grows up to STACK_END */
HEAP_START = 0x20000000 + 0x00010000;
HEAP_END = STACK_END;

/*----------------------------------------------------------------------------*/

/* Exported Symbols (optional for debugging/use in C startup)                  */

/*----------------------------------------------------------------------------*/
 
/* Provide symbols for C runtime or debug */

PROVIDE(__StackTop   = STACK_START);

PROVIDE(__StackLimit = STACK_END);

PROVIDE(__HeapBase   = HEAP_START);

PROVIDE(__HeapLimit  = HEAP_END);

/*----------------------------------------------------------------------------*/
/* Misc                                                                       */
__archive2_begin = 0x00200000;
/*----------------------------------------------------------------------------*/
