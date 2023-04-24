/*
 * Jackson Newman
 */

#include "stm32l476xx.h"

void GPIO_Init(void){	
	//Enable the clock for GPIO port C.
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	//Configure pins 5, 6, 8, and 9 as output.
	GPIOC->MODER &= ~GPIO_MODER_MODE5;
	GPIOC->MODER &= ~GPIO_MODER_MODE6;
	GPIOC->MODER &= ~GPIO_MODER_MODE8;
	GPIOC->MODER &= ~GPIO_MODER_MODE9;
	GPIOC->MODER |= GPIO_MODER_MODE5_0;
	GPIOC->MODER |= GPIO_MODER_MODE6_0;
	GPIOC->MODER |= GPIO_MODER_MODE8_0;
	GPIOC->MODER |= GPIO_MODER_MODE9_0;
	
	
	//Set the output speed of the pins to fast.
	GPIOC->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR5)|(GPIO_OSPEEDER_OSPEEDR6)|(GPIO_OSPEEDER_OSPEEDR8)|(GPIO_OSPEEDER_OSPEEDR9);
	
	//Set the output type of the pins to push-pull.
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT5;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT6;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT8;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT9;

	//Set the pins to no pull-up, no pull-down.
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD5;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD6;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD8;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD9;
}


#define DELAY 600	// delay between steps of the sequences

//SW1(C5), SW2(C6), SW3(C8), SW4(C9)
void Full_Stepping_Clockwise(void){
	//step 1
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for(int i = 0; i < DELAY; i++){}
	//step 2
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	GPIOC->ODR |= GPIO_ODR_OD6;
	for(int i = 0; i < DELAY; i++);
	//step 3
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD8;
	for(int i = 0; i < DELAY; i++);
	//step 4
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD5;
	for(int i = 0; i < DELAY; i++);
}

void Full_Stepping_CounterClockwise(void){
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	GPIOC->ODR |= GPIO_ODR_OD5;
	for(int i = 0; i < DELAY; i++){}
	//step 2
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR |= GPIO_ODR_OD8;
	for(int i = 0; i < DELAY; i++);
	//step 3
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD6;
	for(int i = 0; i < DELAY; i++);
	//step 4
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for(int i = 0; i < DELAY; i++);
}

void Half_Stepping_Clockwise(void){
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD6;
	GPIOC->ODR |= GPIO_ODR_OD9;
	for(int i = 0; i < DELAY; i++){}
	//step 2
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for(int i = 0; i < DELAY; i++);
	//step 3
	GPIOC->ODR |= GPIO_ODR_OD8;
	for(int i = 0; i < DELAY; i++);
	//step 4
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	for(int i = 0; i < DELAY; i++);
	//step 5
	GPIOC->ODR |= GPIO_ODR_OD5;
	for(int i = 0; i < DELAY; i++){}
	//step 6
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	for(int i = 0; i < DELAY; i++);
	//step 7
	GPIOC->ODR |= GPIO_ODR_OD9;
	for(int i = 0; i < DELAY; i++);
	//step 8
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	for(int i = 0; i < DELAY; i++);
}

void Half_Stepping_CounterClockwise(void){
	//step 1
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	GPIOC->ODR |= GPIO_ODR_OD9;
	GPIOC->ODR |= GPIO_ODR_OD5;
	for(int i = 0; i < DELAY; i++){}
	//step 2
	GPIOC->ODR &= ~GPIO_ODR_OD9;
	for(int i = 0; i < DELAY; i++);
	//step 3
	GPIOC->ODR |= GPIO_ODR_OD8;
	for(int i = 0; i < DELAY; i++);
	//step 4
	GPIOC->ODR &= ~GPIO_ODR_OD5;
	for(int i = 0; i < DELAY; i++);
	//step 5
	GPIOC->ODR |= GPIO_ODR_OD6;
	for(int i = 0; i < DELAY; i++){}
	//step 6
	GPIOC->ODR &= ~GPIO_ODR_OD8;
	for(int i = 0; i < DELAY; i++);
	//step 7
	GPIOC->ODR |= GPIO_ODR_OD9;
	for(int i = 0; i < DELAY; i++);
	//step 8
	GPIOC->ODR &= ~GPIO_ODR_OD6;
	for(int i = 0; i < DELAY; i++);
}


int main(void){
	GPIO_Init();
	// Rotate 360 degrees either clockwise or counter-clockwise
	for(int i = 0; i < 512; i++){
		Half_Stepping_Clockwise();
	}
}
