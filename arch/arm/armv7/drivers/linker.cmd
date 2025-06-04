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
    VECTORS (X)  : origin=0x00000000 length=0x00001000
    FLASH   (RX) : origin=0x00001000 length=0x000FFFE0
    S_FLASH (RX) : origin=0x00100FE0 length=0x00100000
    HEAP    (RW) : origin=0x00200FE0 length=0x00010000
    KRAM    (RW) : origin=0x00210FE0 length=0x00004000
    URAM    (RW) : origin=0x00214FE0 length=0x00067FFF
}

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
	/* Int vectors first */
    .intvecs :               {} > VECTORS
    /* Rest of code to user mode flash region */
    .text        align(32) : {} > FLASH
    .const       align(32) : {} > FLASH
    .data        align(32) : {} > KRAM
    .bss         align(32) : {} > KRAM
    .cinit                 : {} > FLASH
    .shared_code align(32) : {} > S_FLASH
    .sysheap     align(32) : {} > HEAP


}

/*----------------------------------------------------------------------------*/
/* Misc                                                                       */
__archive2_begin = 0x00200000;
/*----------------------------------------------------------------------------*/
