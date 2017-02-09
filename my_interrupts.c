/*   My_interrupts.c
* 

Several interrupt initializations and interrupt handlers here

syst_tick_init()  //initialize the syst_tick application to interrupt every 1ms
SysTick_Handler() //increment the global variable sys_ticks

void init_TPM1()    // initialize the TPM1 timer to interrupt on overflow 
FTM1_IRQHandler() // timer over

init_port_interrupt_a1(char edge)    //initialize the port interrupt for port a.  Specify edge 1,2 or 3
PORTA_IRQHandler()                   // handler for interrupt


 
 */
//#include "TPM1.h"
#include "stdint.h"
#include "derivative.h"
#include "arm_cm0.h"

#define FTM1_CLOCK  (48000000)
#define FTM1_CLK_PRESCALE   6// Prescale Selector value - see comments in Status Control (SC) section for more details
#define FTM1_OVERFLOW_FREQUENCY 50  

volatile uint32_t tpm1_ticks = 0;
volatile int sys_ticks=0;


/***********************Systick Interrupt******************
 This interrupt requires an initialization.  It is a CPU interrupt 
 on the ARMcore M0+ module, not the K25Z.  Once activated with 
 the initialization it will generate a SysTick_Handler interrupt every 1ms.  
*/ 
void syst_tick_init(void){
/*void syst_tick_init(char x){    //lets implement this at some point to get more flexibility from sys_tick   
		SYST_RVR=48*x;    //This is the counter modulus or reset value.  	*/
	
	SYST_RVR=48000;    //This is the counter modulus or reset value.  
	//The processor clock is 48MHz so counting up to 48000 should take 1ms
	
	//SYST_RVR=0xffffff;    //The RVR can only hold 24 bits or 16M.  Thus,
	                      //the longest we can delay is 16M/48M ~ .25s

	SYST_CVR=0;        //this is the actual counter.. must be initialized 
	                   //to 0 to start       
	SYST_CSR=0x7;       //use the processor clock/enable exceptions when 
	                   //CVR=0/enable systick
	 
}
 
/****************SysTick_Handler*********************************
This occurs when enabled in sys tick int.

freq = f bus clock / RVR

The ticks variable should increment every  SYST_RVR / 48MHz seconds. 
 Ex. A value SYST_RVR=48000 should take 1ms.*/

void SysTick_Handler(void){
	
	sys_ticks++;
		
	
}



void FTM1_IRQHandler()
{
        //Clear the overflow mask if set.   According to the reference manual, we clear by writing a logic one!
		if(TPM1_SC & TPM_SC_TOF_MASK)
		{
			TPM1_SC |= TPM_SC_TOF_MASK;
		}
		
		if(tpm1_ticks<0xFFFFFFFF)
			tpm1_ticks++;
}


void init_TPM1()
{
               
               //Clock Setup for the TPM requires a couple steps.
               
   			
               //First, select the clock you want to use
               //See Page 124 of f the KL25 Sub-Family Reference Manual, Rev. 3, September 2012
               SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;// We Want MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual, Rev. 3, September 2012)
               SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);  //clear first, then set these bits to 01
               SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); //We want the MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual, Rev. 3, September 2012)
  

				//Then enable the Clock to the FTM1 Module
				//See Page 207 of f the KL25 Sub-Family Reference Manual, Rev. 3, September 2012
				SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK; 
               
               //The TPM Module has Clock.  Now set up the peripheral
               
               //Blow away the control registers to ensure that the counter is not running
               TPM1_SC = 0;
               TPM1_CONF = 0;
               
               //While the counter is disabled we can setup the prescaler
               
               TPM1_SC = TPM_SC_PS(FTM1_CLK_PRESCALE);
               TPM1_SC |= TPM_SC_TOIE_MASK; //Enable Interrupts for the Timer Overflow
               
               //Setup the mod register to get the correct  Period
               
               TPM1_MOD = FTM1_CLOCK/(1<<(FTM1_CLK_PRESCALE+1))/FTM1_OVERFLOW_FREQUENCY;
               
               //Enable the TPM COunter
               TPM1_SC |= TPM_SC_CMOD(1);
               
               //Enable TPM1 IRQ on the NVIC
               enable_irq (INT_TPM1-16);  //This sets the NVIC_ICPR and NVIC_ISER registers declaring the interrupt 
              
                              
}


/*****************************************************************************************************
 *              Init portn interrupt_nx(char edge)
 *              
 * These interrupts are activated by edges on parallel port pins.  
 * 
 * n:  a,d   only
 * 
 * x: number 0-31
 * 
 * edge: 0 turn off the interrupt
 *       1 rising edge
 *       2 falling edge
 *       3 rising and falling edge
 * The pin initialization function 
 * 
 * init_gpio_a is called to create an input pin.
 * 
 * To create another interrupt for pin d3, for example
 * 
 * replace  PORTA_PCR(1)  with PORTD_PCR(3)
 * 
 * 
 * */
void init_port_interrupt_a1(char edge){
	
	init_gpio_a(1,0);
	if(edge==1)PORTA_PCR(1)|=PORT_PCR_IRQC(0b1001);
	else if(edge==2)PORTA_PCR(1)|=PORT_PCR_IRQC(0b1010);
	else if(edge==3)PORTA_PCR(1)|=PORT_PCR_IRQC(0b1011);
	else PORTA_PCR(1)|=PORT_PCR_IRQC(0);
			
    enable_irq (INT_PORTA-16);  //This sets the NVIC_ICPR and NVIC_ISER registers declaring the interrupt 			
} 


/***********************************************************************
 *                    PORTA_IRQHandler                                  
 ***********************************************************************
 This is the IRQ routine for the interrupt generated by some action on pinA1
 
 It will perform this routine whenever the action specified in the initialization
 occurs.  The initialization is set to interrupt on either a rising, falling or either
 type of edge.
 
 Before exiting the routine the interrupt flag ISF flag is cleared by writing a 1 to it.
 ************************************************************************/

void PORTA_IRQHandler()
{
	static char i=0;
	delay_100us(100);
	  i^=1;
	  gpo_c(1,i);
	 
 /*****You must include this step clearing the interrupt flag.  Don't remove*******/
 PORTA_PCR(1)|=PORT_PCR_ISF_MASK;
/***********************************************************************************/
}




