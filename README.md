# FollowTheBlackLine
Final Project in Microprocessor Technology. Written in C. The program is designed to have a car follow a black line made of electrical tape and get to a point then come back to the initial spot.

Anthony Livingston    Follow the Black Line

PROGRAM FUNCTION: 
  This program is designed to use the 2 sensors on the rear wheel drive car to follow a black tape line.
As the sensors read specific values, the car will react in different ways. These 
ways defined as turning the wheels to realign the car onto the black tape line.
Once the car is to the end of the line it would turn around and come back to the beginning.

SUBROUTINES/FUNCTIONS/INTERRUPT ROUTINES: 
  delay_ms() is a function defined in the my_io_apps.c file. Which will have the program
  delay a certain amount of time at that point.

  Drive() is a function that will run the car through each state. The function sends required signals to the outputs
  based on the inputs from the sensors. 

Input/Output
  The input used is the adc0 pin on the protoboard. Which is port used for the sensors.
  The outputs used are LEDs and motors. The LED on the Freescale Basys board was used to tell 
  what state the car was in. The LEDs were set as the port b, c, and d. Using pins b(18,19)
  c(0,1,2,4) and d(1). The motors were set at PWM_0 and PWM_1. 

VARIABLES:
  Gloabal Variable:
    Sensor 1 and 2
    minimum and maximum reflection values for the sensors
    state -> to run the switch
    t -> to see if the motors are stopped and should turn around.
