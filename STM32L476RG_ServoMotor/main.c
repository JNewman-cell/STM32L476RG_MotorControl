/*
 * Jackson Newman
 */

#include "stm32l476xx.h"

void SERVO_Pin_Init(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE0;
	GPIOA->MODER |= GPIO_MODER_MODE0_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED0;
	
	//Alternate Function
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL0_1;
	
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
}

void TIM5_CH1_Init(){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM5EN;
	
	TIM5->CR1 &= ~TIM_CR1_DIR;
	
	TIM5->PSC = 39;
	
	TIM5->ARR = 1999;
	
	TIM5->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM5->CCMR1 |= TIM_CCMR1_OC1M_1;
	TIM5->CCMR1 |= TIM_CCMR1_OC1M_2;
	TIM5->CCMR1 |= TIM_CCMR1_OC1PE;
	
	TIM5->CCER |= TIM_CCER_CC1E;
	
	TIM5->CCR1 = 1000;
	
	TIM5->CR1 |= TIM_CR1_CEN;
}


void Servo_Move_Left_90_Degree(){
	// function to move the servo to +90 degrees
	TIM5->CCR1 = 70;
}

void Servo_Move_Center(){
	// function to move the servo to 0 degrees
	TIM5->CCR1 = 160;
}

void Servo_Move_Right_90_Degree(){
	// function to move the servo to -90 degrees
	TIM5->CCR1 = 270;
}


int main() {
		int i;
	
		SERVO_Pin_Init();
		TIM5_CH1_Init();
		
    while(1) {
			// Move servo to +90 degrees, 0 degrees, and -90 degrees
			Servo_Move_Right_90_Degree();
			
			for(i=0;i<100000;i++);  		// delay
			Servo_Move_Center();
			
			for(i=0;i<100000;i++);  		// delay
			Servo_Move_Left_90_Degree();
			
			for(i=0;i<100000;i++);  		// delay
    }
}
