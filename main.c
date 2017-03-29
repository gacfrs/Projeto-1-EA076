/* ###################################################################
 **     Filename    : main.c
 **     Project     : Projeto1-Semaforo-dimiefrauches
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2017-03-13, 14:23, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */         
  
/* MODULE main */

/*##########################################################################
 * 	EA076 C - Projeto 1 - main.c
 * 	Dimitri Reis			RA 145869
 * 	Guilherme Frauches	RA 155591
 *
 *  O programa simula um semáforo inteligente com leds, sensor de luminosidade
 *  e detecção de pedestres.
 * 
 *##########################################################################*/

/* Inlcusão de módulos necessários para compilar o projeto */
#include "Cpu.h"
#include "Events.h"
#include "LED_red_car.h"
#include "BitIoLdd1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "LED_yellow_car.h"
#include "BitIoLdd4.h"
#include "LED_green_car.h"
#include "BitIoLdd5.h"
#include "LED_red_man.h"
#include "BitIoLdd6.h"
#include "LED_green_man.h"
#include "BitIoLdd7.h"
#include "BUTTON.h"
#include "BitIoLdd8.h"

/* Inclusão de módulos compartilhados usados no projeto */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* Variáveis de controle do tempo */
int cont = 0;
int cont_green = 16;
int cont_yellow = 22;
int cont_max = 38;
int cont_blink = 4;

/* Variáveis de controle dos periféricos */
int button;
int noite;

int main(void){
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization. ***/

	for(;;){
		while(noite){					// Verifica se deve operar no modo noturno
			LED_red_car_ClrVal();			// Apaga todos os LEDs
			LED_green_car_ClrVal();
			LED_red_man_ClrVal();
			LED_green_man_ClrVal();

			if(!(cont%2))				// Pisca o LED amarelo
				LED_yellow_car_ClrVal();
			if(cont%2)
				LED_yellow_car_SetVal();
		}

		if(cont<cont_green){				// Período do LED verde dos carros
			LED_red_car_ClrVal();			// Somente seta o LED verde dos carros e o LED vermelho dos pedestres
			LED_yellow_car_ClrVal();
			LED_green_car_SetVal();
			LED_red_man_SetVal();
			LED_green_man_ClrVal();

			if(button)
				cont=cont_green-2;		// Aproxima o contador para o fim do período do LED verde dos carros
		}
		else if(cont<cont_yellow){			// Período do LED amarelo dos carros
			LED_red_car_ClrVal();			// Somente seta o LED amarelo e o LED vermelho dos pedestres
			LED_yellow_car_SetVal(); 	 			 
			LED_green_car_ClrVal();
			LED_red_man_SetVal();
			LED_green_man_ClrVal();
		}
		else if(cont<cont_max-cont_blink){ 		// Período do LED vermelho dos carros
			LED_red_car_SetVal();			// Somente seta o LED vermelho dos carros e o LED verde dos pedestres
			LED_yellow_car_ClrVal(); 	 			 
			LED_green_car_ClrVal();
			LED_red_man_ClrVal();
			LED_green_man_SetVal();
		}
		else{						// Últimos instantes do LED vermelho dos carros
			LED_green_man_ClrVal();			// Somente seta o LED vermelho dos carros
			
			if(!(cont%2))				// Pisca o LED vermelho dos pedestres
				LED_red_man_ClrVal();
			if(cont%2)
				LED_red_man_SetVal();
		}
	}

	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
	PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of RTOS startup code.  ***/
	/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/

} /*** END OF MAIN ***/

/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
