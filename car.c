
/*
;*****************************************************************************
Anthony Livingston    Follow the Black Line
;-----------------------------------------------------------------------------
; PROGRAM FUNCTION: 

This program is designed to use the 2 sensors on the rear wheel drive car to follow a black tape line.
As the sensors read specific values, the car will react in different ways. These 
ways defined as turning the wheels to realign the car onto the black tape line.
Once the car is to the end of the line it would turn around and come back to the beginning.

;------------------------------------------------------------------------------
;SUBROUTINES/FUNCTIONS/INTERRUPT ROUTINES: 

Describe each function you are using, the input/output variables if any.  If there is a complicated
decision structure, describe that as best you can.

delay_ms() is a function defined in the my_io_apps.c file. Which will have the program
delay a certain amount of time at that point.

Drive() is a function that will run the car through each state. The function sends required signals to the outputs
based on the inputs from the sensors. 

;-------------------------------------------------------------------------------
;Input/Output

The input used is the adc0 pin on the protoboard. Which is port used for the sensors.
The outputs used are LEDs and motors. The LED on the Freescale Basys board was used to tell 
what state the car was in. The LEDs were set as the port b, c, and d. Using pins b(18,19)
c(0,1,2,4) and d(1). The motors were set at PWM_0 and PWM_1. 

;------------------------------------------------------------------------------
;VARIABLES:

global and local variables of note and what they are.
Gloabal Variable:
Sensor 1 and 2
minimum and maximum reflection values for the sensors
state -> to run the switch
t -> to see if the motors are stopped and should turn around.


;*****************************************************************************

*/


//*********Required includes.  Don't modify************************
#include "derivative.h" /* include peripheral declarations */
#include "mcg.h" /* using XTAL and PLL does not work returns errors*/

//*********** My includes *************************
#include "my_io_apps.c" /* include peripheral declarations */
#include "my_interrupts.c" 


/******* Prototype Function declarations ******/
void delay_ms(int);
void Drive(void);
/**************Global Variables Here************************/
volatile int Sensor1;
volatile int Sensor2;
int Sens1min;
int Sens1max;
int Sens2min;
int Sens2max;
int state;
volatile int t;
/***********************************************************/

   int main(void) {
 
//*******Local Variable Declarations for main *****************
	

//******Initial Chip Settings******************

//  The student user should not make changes here unless
//explicitly instructed to do so
int pll_err=pll_init(8000000,0,1,4,24,1);     //Use the crystal oscillator to drive the PLL

//******User chip module initializations***************************************
     init_gpio_b(18,1);
     init_gpio_b(19,1);
     init_gpio_d(1,1);
     
     gpo_b(18,1);
     gpo_b(19,1);
     gpo_d(1,1);
   //initialize LEDs as an output
     init_gpio_c(0,1);
     init_gpio_c(1,1);
     init_gpio_c(2,1);
     init_gpio_c(4,1);
   
     init_PWM_0_0(20000);
     init_PWM_0_1(20000);
     PWM_0_0_pw(0);//right motor
     PWM_0_1_pw(0);//left motor
     
   
	
	//initialize button to turn on lights
	 init_gpio_a(1,0);
	 init_gpio_a(2,0);
	 init_gpio_a(4,0);
	 
	 gpo_a(1,0);
	 gpo_a(2,0);
	 gpo_a(4,0);
	
	
	 
	//initialize Sensors ......Sensor 1 is left sensor....... Sensor 2 is right sensor

     syst_tick_init();   

   //initialize LEDs as off
    gpo_c(0,1);
    gpo_c(1,1);
    gpo_c(2,1);
    gpo_c(3,1);
   //blue LED using delay
   
   init_adc0();
   
   Sensor1=adc0_value(9);//b1
   Sensor2=adc0_value(8);//b0
   
   Sens1min=500;//off tape
   Sens1max=1500;//on tape
   Sens2min=500;//off tape
   Sens2max=1500;//on tape
   
   state=0;
   
  
             
	          
//*************The infinte loop.  Could use while(1);	
 

  
	for(;;) 
	{
		Sensor1=adc0_value(9);
		Sensor2=adc0_value(8);
		Drive();				 
	}
			
		return 0;	
	
   }
	
	

   void Drive(void){
	   switch (state)
   	{
   		
   		case 0:{
   			//white light
   		     gpo_b(18,0);
   		     gpo_b(19,0);
   		     gpo_d(1,0);
   			
   			
   			if(!(gpi_a(4))) {state = 4;}
   			
   	}
   		break;
   		case 1:{//left motor off moves left
   			//blue light
   		     gpo_b(18,1);//green
   		     gpo_b(19,1);//red
   		     gpo_d(1,0);//blue
   		     
   			PWM_0_0_pw(1500);
   			PWM_0_1_pw(1100);
   			
   			

   			if(Sensor1<Sens1min && Sensor2>Sens2max){
   				state=2;
   			}
   			if(Sensor1>Sens1max && Sensor2>Sens2max){
   				state=3;
   			}
   			if(Sensor1<Sens1min && Sensor2<Sens2min){
   				state=4;
   			}
   			
   		}
   		break;	
   		case 2:{//right motor off moves right
   			//purple light
   		     gpo_b(18,1);
   		     gpo_b(19,0);
   		     gpo_d(1,0);
   		     
   			PWM_0_0_pw(1900);
   			PWM_0_1_pw(1500);
   						

   			if(Sensor1>Sens1max && Sensor2<Sens2min){
   				state=1;
   			}
   			if(Sensor1>Sens1max && Sensor2>Sens2max){
   				state=3;
   			}
   			if(Sensor1<Sens1min && Sensor2<Sens2min){
   				state=4;
   			}
   						
   		}
   		break;
   		case 3:{// both motors off     stop
   			//red light
   		     gpo_b(18,0);
   		     gpo_b(19,1);
   		     gpo_d(1,1);
   		
  	  
   		
   			PWM_0_0_pw(1900);
   			PWM_0_1_pw(1900);
   			t=0;
   			if(t==0){
   				if(Sensor1<Sens1min && Sensor2>Sens2max){
   				state=2;
   				}
   				t=t+1;
   			}
   			else if(t==1){
   				state=5;
   			}
   		
   			
   	}	
   		break;	
   		case 4:{// both motors on move forward
   			//green light
   		     gpo_b(18,1);
   		     gpo_b(19,0);
   		     gpo_d(1,1);
   		     
   			PWM_0_0_pw(1900);//driving forward full
   			PWM_0_1_pw(1100);//drive forward full
   				

   			if(Sensor1>Sens1max && Sensor2<Sens2min){
   				state=1;
   			}
   			if(Sensor1<Sens1min && Sensor2>Sens2max){
   				state=2;
   			}
   			if(Sensor1>Sens1max && Sensor2>Sens2max){
   				state=3;
   			}
   			
   		}
   		break;
   		case 5:{
   			
   		}
   		break;
   		default:
   			break;
   		}
	  
   }
   
   
   
   
