/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    RTX_EX1.C
 *      Purpose: Your First RTX example program
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 1999-2009 KEIL, 2009-2013 ARM Germany GmbH
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of ARM  nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/

#include "cmsis_os.h"
#include "lpc17xx.h"

/* Forward reference */
void threadX (void const *argument);

/* Thread IDs */
osThreadId main_id;
osThreadId threadX_id;
int recurso;
/* Thread definitions */
osThreadDef(threadX, osPriorityNormal, 1, 0);

/*----------------------------------------------------------------------------
 *   Thread X
 *---------------------------------------------------------------------------*/
void threadX (void const *argument) {
uint32_t i;

  LPC_GPIO3->FIODIR |= (1<<25);	 // P3.25 definido como salida  
  LPC_GPIO3->FIOCLR |= (1<<25);	 // P3.25 apagado 
  for (i=0;i<0x00007FFF;i++) {

      LPC_GPIO3->FIOPIN |= (1<<25);  // Apago LED 
      osDelay (50);			         
      LPC_GPIO3->FIOPIN &= ~(1<<25); // Enciendo LED 
      osDelay (50);
  }
}

/*----------------------------------------------------------------------------
 *   Main Thread
 *---------------------------------------------------------------------------*/
int main (void) {
uint32_t i;
	osStatus status;
  /* Get main thread ID */
  main_id = osThreadGetId();
  /* Create thread X */
  threadX_id = osThreadCreate(osThread(threadX), NULL);

  LPC_GPIO3->FIODIR |= (1<<26);	 // P3.69 definido como salida  
  LPC_GPIO3->FIOCLR |= (1<<26);	 // P3.26 apagado 	
  for (i=0;i<0x00007FFF;i++) {    /* do-this */
      LPC_GPIO3->FIOPIN |= (1<<26);  // Apago LED 
      osDelay (100);			         
      LPC_GPIO3->FIOPIN &= ~(1<<26); // Enciendo LED 
      osDelay (100);
  }
	status=osThreadTerminate(threadX_id);
	while(1);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
