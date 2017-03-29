/* ###################################################################
**     Filename    : Events.c
**     Project     : Projeto1-Semaforo-dimiefrauches
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-13, 14:23, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
        

/* ##########################################################################
 * 	EA076 C - Projeto 1 - Events.c
 * 	Dimitri Reis			RA 145869
 * 	Guilherme Frauches	RA 155591
 *
 *  O programa simula um semáforo inteligente com sensor de luminosidade
 *  e detecção de pedestres.
 * 
 * ##########################################################################*/

/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* Link das variáveis de controle do tempo*/
extern int cont;
extern int cont_max;

/* Link das variáveis de controle dos periféricos */
extern int button;
extern int noite;
uint8_t conversor;			// Variável de 8 bits que irá operar como ADC

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void){
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TI1_OnInterrupt(void){ 
	AD1_Measure(FALSE);		// Faz a leitura do LDR e pula para rotina AD1_OnEnd
	button = BUTTON_GetVal();	// Verifica o estaedo do botão (1 - pressionado, 0 - c.c.)
	cont++;				// Faz a contagem do tempo

	if (cont >= cont_max)		// Reinicia o ciclo do contador
		cont = 0;
}

/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AD1_OnEnd(void){
	AD1_GetValue8(&conversor);	// Converte o valor do LDR em 8 bits
	if(conversor>128)		// Define o estado da variável "noite"
		noite=1;		// 1 - Escuro
	else
		noite=0;		// 0 - Claro
}

/*
** ===================================================================
**     Event       :  AD1_OnCalibrationEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AD1_OnCalibrationEnd(void){
}
/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
