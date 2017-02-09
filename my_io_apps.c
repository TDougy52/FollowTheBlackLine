/*   My_io_apps.c contains these functions that handle input and output features on our proto board

init_gpio_x(pin, io)  // initialize parallel i/o pin as either input (0) our output (1)  x=a,b,c,d or e
gpi_x(pin)            // returns the value from the input in   x=a,b,c,d or e
gpo_x(pin, value)     // sends the value (1 or 0) to the output pin   x=a,b,c,d or e

init_pbs()   //initialize the 4 push buttons
init_leds()  //initialize 4 leds
leds(i)      //  show the binary value i on the leds

delay_100us(x)     // delays  x * 100us  approximately 
 
init_adc0()         //initialize the 0 analog to digital converter
adc0_value(channel)  // returns the 12 bit value for the specified channel

init_PWM_0_0(period)  // initialize the PWM for timer 0 and channel 0 to have a period in micro seconds
PWM_0_0_PW(pulse width)  // set the pulse width in microseconds for timer 0, channel 0

init_PWM_0_1(period)  // initialize the PWM for timer 0 and channel 0 to have a period in micro seconds
PWM_0_1_PW(pulse width)  // set the pulse width in microseconds for timer 0, channel 0

init keypad()  // initiaze the keypad
char anykey()   //return a 1 if anyeky is pushed on the keypad
char getkey()    //return the ascii character of the keypad button pushed.
 
 */




/********** delay_100us  delay_ms**************/
/*Time wasting delay routines.  Specify a numerical argument, generate a delay roughly eqaul to that value.  For more accurate delays use the crystal clock with the systick interrupt  */

void delay_100us(int x){
	int i=0,j=0;
	
	for(j=0;j<x;j++){
	for(i=0;i<205;i++);
	 }
  }

void delay_ms(int x){
	int i=0,j=0;
	
	for(j=0;j<x;j++){
	for(i=0;i<10;i++)delay_100us(1);
	 }
  }


/* ************************ init_gpio_n(pin,dd)************************
 
 Use these init functions to turn on an io for basic parallel input or output.
 
 int pin; is the pin number fomr 0 to 31
 in dd;   is the data direction  1 for output, 0 for input.
 
ex.  to use the pin A13 for input and D3 for output

init_gpio_a(13,0);
init_gpio_d(3,1);
  
 * 
 * */
void init_gpio_a(int pin,int dd)
{
	
	
// Turn on clock for port A
    
     SIM_SCGC5|=SIM_SCGC5_PORTA_MASK;
     
// Convert the specific pins to the GPIO module.  See table 10.3.1 in Users Guide 
     

     PORTA_PCR(pin)=PORT_PCR_MUX(1);
     PORTA_PCR(pin)|=PORT_PCR_PE_MASK;
          
     if(dd==1){
             GPIOA_PDDR|=1<<pin;
               }
     else GPIOA_PDDR&=~(1<<pin);
    }

void init_gpio_b(int pin,int dd)
{
	
// Turn on clock for port B
    
     SIM_SCGC5|=SIM_SCGC5_PORTB_MASK;
     
// Convert the specific pins to the GPIO module. 
     

     PORTB_PCR(pin)=PORT_PCR_MUX(1);
     PORTB_PCR(pin)|=PORT_PCR_PE_MASK;
     
     if(dd==1){
             GPIOB_PDDR|=1<<pin;
               }
     else GPIOB_PDDR&=~(1<<pin);
    }
void init_gpio_c(int pin,int dd)
{
	
// Turn on clock for port C
    
     SIM_SCGC5|=SIM_SCGC5_PORTC_MASK;
     
// Convert the specific pins to the GPIO module. 

     PORTC_PCR(pin)=PORT_PCR_MUX(1);
     PORTC_PCR(pin)|=PORT_PCR_PE_MASK;
     
     if(dd==1){
             GPIOC_PDDR|=1<<pin;
               }
     else GPIOC_PDDR&=~(1<<pin);
    }
void init_gpio_d(int pin,int dd)
{
	
// Turn on clock for port D
    
     SIM_SCGC5|=SIM_SCGC5_PORTD_MASK;
     
// Convert the specific pins to the GPIO module. 
   
     PORTD_PCR(pin)=PORT_PCR_MUX(1);
     PORTD_PCR(pin)|=PORT_PCR_PE_MASK;
     
     if(dd==1){
             GPIOD_PDDR|=1<<pin;
               }
     else GPIOD_PDDR&=~(1<<pin);
    }
void init_gpio_e(int pin,int dd)
{
	
// Turn on clock for port E
    
     SIM_SCGC5|=SIM_SCGC5_PORTE_MASK;
     
// Convert the specific pins to the GPIO module. 
     
     PORTE_PCR(pin)=PORT_PCR_MUX(1);
     PORTE_PCR(pin)|=PORT_PCR_PE_MASK;
     
     if(dd==1){
             GPIOE_PDDR|=1<<pin;
               }
     else GPIOE_PDDR&=~(1<<pin);
    }

/*************  gpi_x and gpo_x    ****************/
/*
gpo_x:  Use these routines to set, or clear a single parallel output

ex, to set the 13th bit on port A and to clear it later
gpo_a(13,1);  //set
.
.
gp_a(13,0);    //clear

gpi_x:  Use these routines to read the value of a specfic bit on a pararllel port

ex.  to read D3 and make a decision based on its value

if(gpi_d(3))....

*/

int gpi_a(int pin)
{
    if(GPIOA_PDIR&(1<<pin))return 1;
    else return 0;
    }
void gpo_a(int pin, int val)
   { 
	if(val==1)GPIOA_PDOR|=1<<pin;
	else if (val==0)GPIOA_PDOR&=~(1<<pin);
	    }
int gpi_b(int pin)
{
    if(GPIOB_PDIR&(1<<pin))return 1;
    else return 0;
    }
void gpo_b(int pin, int val)
   { 
	if(val==1)GPIOB_PDOR|=1<<pin;
	else if (val==0)GPIOB_PDOR&=~(1<<pin);
	    }
int gpi_c(int pin)
{
    if(GPIOC_PDIR&(1<<pin))return 1;
    else return 0;
    }
void gpo_c(int pin, int val)
   { 
	if(val==1)GPIOC_PDOR|=1<<pin;
	else if (val==0)GPIOC_PDOR&=~(1<<pin);
	    }

int gpi_d(int pin)
{
    if(GPIOD_PDIR&(1<<pin))return 1;
    else return 0;
    }
void gpo_d(int pin, int val)
   { 
	if(val==1)GPIOD_PDOR|=1<<pin;
	else if (val==0)GPIOD_PDOR&=~(1<<pin);
	    }

int gpi_e(int pin)
{
    if(GPIOE_PDIR&(1<<pin))return 1;
    else return 0;
    }
void gpo_e(int pin, int val)
   { 
	if(val==1)GPIOE_PDOR|=1<<pin;
	else if (val==0)GPIOE_PDOR&=~(1<<pin);
	    }

/**************bit set and bit clear****************
 Use these to set or clear bits in a register.  Note that when you invoke them
you must use the unary operator & to send the location of the variable, not that value
of the variable.  Ex  bit_set(&GPIOA_PDDR,13);*/
void bit_set(int p,int val){
	int *pt;
	pt=p;
	*pt|=1<<val;
	}

void bit_clr(int p,int val){
	int *pt;
	pt=p;
	*pt&=~(1<<val);
	}
//***************************************************


 /****************  ADC0  initialization  ********************************/
//Initialize PTC1 as ADC15  A to D 
void init_adc0(void){    
 
      // Turn on the clock for ADC0	
        SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;


         ADC0_SC1A=0x0;     //start it with no channel selected
         ADC0_SC2=0;
         
         ADC0_CFG1=0x4;   //  12 bit conversion, single ended, full speed bus clock normal operation
         ADC0_CFG2=0;
}

/*****************ADC0 channel select*****************************/

/* adc0_value returns a 12 bit value proportional to the analog value at the pin selected.
   The partial list is:
                     -------
   ADC0_23  PTE30    |  |  |  PTC1    ADC0_15
        4B    E29    |  |  |    C2         11
        7A    E23    |  |  |    B3         13
        3     E22    |  |  |    B2         12
        4A    E21    |  |  |    B1         9
        0     E20    |  |  |    B0         8 
                     -------
                     
     For example, if you want to use the PTB2 pin as an atod
     
     init_adc0();
     
     
     x=adc0_value(12);  will return the analog value.
     
 */

int adc0_value(int adc0_se){
       
      ADC0_SC1A=adc0_se;
	
	  while(!(ADC_SC1_COCO_MASK&ADC0_SC1A));
	
	  return ADC0_RA;
}
/*initialize the push buttons*/
void init_pbs(void){
    
    init_gpio_a(1,0);
    init_gpio_a(2,0);
    init_gpio_a(4,0);
    init_gpio_a(5,0);
    
}
/* Initialize the leds*/
void init_leds(void){
    init_gpio_c(0,1);
    init_gpio_c(1,1);
    init_gpio_c(2,1);
    init_gpio_c(3,1);
    
    gpo_c(0,1);
    gpo_c(1,1);
    gpo_c(2,1);
    gpo_c(3,1);
             
}

void leds(char i){
	
	GPIOC_PDOR=~i;
	
}

/**************************************************************************************
 *                         Init PWM PORTC 1 timer 0 channel 0 (int period in us)
 * 
 * This function will initialze the C1 pin to be a PWM signal from timer 0, channel 0.
 * 
 * The initialization will first set up the system/ARM registers, then the TPM registers
 * from Freescale.
 * 
 * The argument will set the PWM period in us.  (1000) will create a 1ms PWM signal
 * */

void init_PWM_0_0(int mod)

{

	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); 
  
     SIM_SCGC5|=SIM_SCGC5_PORTC_MASK;	//>> Use new pin value here (Port value A,B,C,D or E)
     SIM_SCGC6 |=SIM_SCGC6_TPM0_MASK;   //>> Use new timer value here (timer 0,1 or 2)
     PORTC_PCR(1)=PORT_PCR_MUX(4);		//>> Use pin n and mux value here.  Its mux 3 usually, sometimes 4.  See table 10.3
		       
			
		        
//********Module/peripheral Configuration**************

     mod=mod*3;                         // Get the right value so that the argument is effecively in us.
     mod=mod>>1;        
     TPM0_MOD = mod;					//>> Use new timer value here (timer 0,1 or 2)
     TPM0_SC = TPM_SC_CMOD(1)|TPM_SC_PS(4);	//>> Use new timer value here (timer 0,1 or 2) PS=16, .66ms /clk
     TPM0_C0SC=0X28;					//>> Use new timer and channel values here (timer 0,1 or 2, channels 0,1,2,3,4,5)
     TPM0_C0V=00;						//>> Use new timer and channel values here (timer 0,1 or 2, channels 0,1,2,3,4,5)
}

void init_PWM_0_1(int mod)

{

	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); 
  
     SIM_SCGC5|=SIM_SCGC5_PORTC_MASK;				//>> Use new X value here (Port value A,B,C,D or E)
     SIM_SCGC6 |=SIM_SCGC6_TPM0_MASK;         		//>> Use new Y value here (timer 0,1 or 2)
     PORTC_PCR(2)=PORT_PCR_MUX(4);					//>> Use X n and mux value here.  Its mux 3 usually, sometimes 4.  See table 10.3
		        
//********Module/peripheral Configuration**************
     mod=mod*3;                          		// Get the right value so that the argument is effecively in us.
     mod=mod>>1;        
     TPM0_MOD = mod;							//>> Use new timer value here (timer 0,1 or 2)
     TPM0_SC = TPM_SC_CMOD(1)|TPM_SC_PS(4);		//>> Use new timer value here (timer 0,1 or 2) PS=16, .66ms /clk
     TPM0_C1SC=0X28;							//>> Use new timer and channel values here (timer 0,1 or 2, channels 0,1,2,3,4,5)
     TPM0_C1V=00;								//>> Use new timer and channel values here (timer 0,1 or 2, channels 0,1,2,3,4,5)
              }


void PWM_0_0_pw(int pw){
	pw=pw*3;
	pw=pw>>1;
	
	TPM0_C0V=pw;			//>> Use new timer and channel values here (timer 0,1 or 2, channels 0,1,2,3,4,5)
	 	
}

void PWM_0_1_pw(int pw){
	pw=pw*3;
	pw=pw>>1;
	
	TPM0_C1V=pw;								//>> Use new Y and Z values here (timer 0,1 or 2, channels 0,1,2,3,4,5)
	 	
}

//**********  Initialize the Keypad    ***********************

void init_keypad(void){
    init_gpio_b(0,1);   //output from MCU input to the keypad
    init_gpio_b(1,1);
    init_gpio_b(2,1);
    init_gpio_b(3,1);
    
    gpo_b(0,1);
    gpo_b(1,1);
    gpo_b(2,1);
    gpo_b(3,1);
    
    init_gpio_e(0,0);    //input to MCU output from keypad
    init_gpio_e(1,0);
    init_gpio_e(2,0);
    init_gpio_e(3,0);

}

char anykey(void){
	char temp=0;
	GPIOB_PDOR&=0xf0;
	delay_100us(1);
	temp=GPIOE_PDIR;
	if((temp&0x0f)==0x0f)return 0;
	else return 1;
}

char getkey(void){
	
		char temp=0;
		
		    GPIOB_PDOR&=0xf0;
		    GPIOB_PDOR|=0x07;
			delay_100us(1);
			
			temp=GPIOE_PDIR;
			temp&=0x0f;
			if(temp==0x07)return 'D';
			else if(temp==0x0b)return '#';
			else if(temp==0x0d)return '0';
			else if(temp==0x0e)return '*';
//****************************************************			
		    GPIOB_PDOR&=0xf0;
		    GPIOB_PDOR|=0x0b;
			delay_100us(1);
			
			temp=GPIOE_PDIR;
			temp&=0x0f;
			if(temp==0x07)return 'C';
			else if(temp==0x0b)return '9';
			else if(temp==0x0d)return '8';
			else if(temp==0x0e)return '7';

//******************************************************			
		    GPIOB_PDOR&=0xf0;
		    GPIOB_PDOR|=0x0d;
			delay_100us(1);
			
			temp=GPIOE_PDIR;
			temp&=0x0f;
			if(temp==0x07)return 'B';
			else if(temp==0x0b)return '6';
			else if(temp==0x0d)return '5';
			else if(temp==0x0e)return '4';
//*************************************************			
		    GPIOB_PDOR&=0xf0;
		    GPIOB_PDOR|=0x0e;
			delay_100us(1);
			
			temp=GPIOE_PDIR;
			temp&=0x0f;
			if(temp==0x07)return 'A';
			else if(temp==0x0b)return '3';
			else if(temp==0x0d)return '2';
			else if(temp==0x0e)return '1';
			
}


