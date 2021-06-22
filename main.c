#include <LPC17xx.h>
#include <stdbool.h>
#include <stdio.h>

#define PART 3

/*
Names:

1. r4tahir@uwaterloo.ca

2. m359pate@uwaterloo.ca


*/

//PART 1 
int part_1(void) {
	
	//Setting LED 
	LPC_GPIO2->FIODIR |= (1<<6);
	
	//loop for Polling
	while(1==1) {
		
		//checking for button press
		if (LPC_GPIO2->FIOPIN & (1<<10)) {
			
			//LED is set to 1 on button press
			LPC_GPIO2->FIOSET |= (1<<6);
			
		} else {
			
			//the LED is cleared
			LPC_GPIO2->FIOCLR |= (1<<6);
		}
	}
}

//PART 2
int part_2(void) {
	//Infinite loop for continuity
	while(1){
		//Check if pressed
		if (!(LPC_GPIO1->FIOPIN & (1 << 20))) {
			if(!(LPC_GPIO1->FIOPIN & (1 << 23)))  {
				printf("The Joystick is North and Pressed.\n"); //North position
			}
			else if (!(LPC_GPIO1->FIOPIN & (1 << 25))) {
				printf("The Joystick is South and Pressed.\n"); //South position
			}
			else if (!(LPC_GPIO1->FIOPIN & (1 << 24))) {
				printf("The Joystick is East and Pressed.\n"); //East position
			}
			else if (!(LPC_GPIO1->FIOPIN & (1 << 26))) {
				printf("The Joystick is West and Pressed.\n"); //West position
			}
			else {
				printf("The Joystick is Centre and Pressed.\n"); //Centre position
			}
		}
		//Otherwise not pressed, same positions
		else {
			if(!(LPC_GPIO1->FIOPIN & (1 << 23)))  {
				printf("The Joystick is North and Released.\n");
			}
			else if (!(LPC_GPIO1->FIOPIN & (1 << 25))) {
				printf("The Joystick is South and Released.\n");
			}
			else if (!(LPC_GPIO1->FIOPIN & (1 << 24))) {
				printf("The Joystick is East and Released.\n");
			}
			else if (!(LPC_GPIO1->FIOPIN & (1 << 26))) {
				printf("The Joystick is West and Released.\n");
			}
			else {
				printf("The Joystick is Centre and Released.\n");
			}
		}
	}
}

//PART 3
int part_3(void) {
	
	//int array for LED vals
	int binValues[8];
	
	//Set LEDs to outputs
	
	//port 2
	for(int i = 2; i <= 6; i++) {
		
		LPC_GPIO2->FIODIR |= (1<<i);
		
	}
	
	//port 1
	LPC_GPIO1->FIODIR |= (1u<<31);
	LPC_GPIO1->FIODIR |= (1u<<29);
	LPC_GPIO1->FIODIR |= (1u<<28);
	
	while(1==1) {
		
		//store user input, -1 initialized to show failure
		
		int value = -1;
		
		printf("Enter a number between 0 and 255 \n");
		scanf("%d", &value);
		
		if(value < 0 || value > 255) {
			
			printf("Number is not in specified range \n");
		}
		else {
			//clear binary values
			for(int i = 0; i < 8; i++) {
				binValues[i]=0;
			}
		}
		
		//counter for loop
		int counter = 0;
		
		//converting input to binary 
		while(value != 0) {
			
			binValues[counter] = value%2;
			value = value/2;
			counter++;
		}
		
		//check values in the array to see which LEDs to set
		if (binValues[0]) {
				//Set bit at left-most position
				LPC_GPIO1 -> FIOSET |= (1u << 28);
			} else {
				// Clear bit at left-most position
				LPC_GPIO1 -> FIOCLR |= (1u << 28);
			}
			if (binValues[1]) {
				LPC_GPIO1 -> FIOSET |= (1u << 29);
			} else {
				LPC_GPIO1 -> FIOCLR |= (1u << 29);
			}
			if (binValues[2]) {
				LPC_GPIO1 -> FIOSET |= (1u << 31);
			} else {
				LPC_GPIO1 -> FIOCLR |= (1u << 31);
			}
			if (binValues[3]) {
				LPC_GPIO2 -> FIOSET |= (1 << 2);
			} else {
				LPC_GPIO2 -> FIOCLR |= (1 << 2);
			}
			if (binValues[4]) {
				LPC_GPIO2 -> FIOSET |= (1 << 3);
			} else {
				LPC_GPIO2 -> FIOCLR |= (1 << 3);
			}
			if (binValues[5]) {
				LPC_GPIO2 -> FIOSET |= (1 << 4);
			} else {
				LPC_GPIO2 -> FIOCLR |= (1 << 4);
			}
			if (binValues[6]) {
				LPC_GPIO2 -> FIOSET |= (1 << 5);
			} else {
				LPC_GPIO2 -> FIOCLR |= (1 << 5);
			}
			if (binValues[7]) {
				LPC_GPIO2 -> FIOSET |= (1 << 6);
			} else {
				LPC_GPIO2 -> FIOCLR |= (1 << 6);
			}
	}
	
}

//PART 4
int part_4(void) {
	
	LPC_SC->PCONP |= (1 << 12); //Power on ADC
	
	LPC_PINCON->PINSEL1 &= ~(0x03 << 18); //Clear bits 18 and 19
	LPC_PINCON->PINSEL1 |= (0x01 << 18); //Set bits 18 and 19 to AD0.2
	
	LPC_ADC->ADCR = (1 << 2) | (1 << 21) | (4 << 8); //Select analog input, enable ADCR circuitry, set clock divisor to sampling rate of 5MHz
	
	while(1) {
		
		LPC_ADC->ADCR |= (1 << 24); //Start conversion
		
		//Continue reading until conversion complete
		while(!(LPC_ADC->ADGDR & (1u << 31))) {
			
			uint16_t adcVal = (LPC_ADC->ADGDR >> 4) & 0xfff; //Read value from bits 4 - 15
			printf("ADC Value: %f\n", (adcVal*(3.5/4095))); //Factor value for correct output
			
		}
	}
}


int main(void){
	
	#if PART == 1
	part_1();
	
	#elif PART == 2
	part_2();
	
	#elif PART == 3
	part_3();
	
	#elif PART == 4
	part_4();
	
	#endif
	
}