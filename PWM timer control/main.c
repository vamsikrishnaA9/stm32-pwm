/*
Generating a PWM signal of 1KHZ using Timer4 
We can change frequency by changing TIM4->CCR4 value. 

*/


#include "stm32f10x.h"
#include "gp_drive.h"

int main(){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN; //enabling Port B alternative function
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;  // Enabling Timer4 clock
	
	GPIOB->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_CNF9_1; //setting PB9 pins as output 
	GPIOB->CRH &= ~(GPIO_CRH_CNF9_0);
	

	
	
	
	TIM4 -> CCER |= TIM_CCER_CC4E; //Timer value capture and control enable
	TIM4->CR1 |= TIM_CR1_ARPE; 
	TIM4 -> CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;  

//PWM freq = Fclk/PSC/ARR  72Mhz/72000 = 1Kzh pwm	
	TIM4->PSC = 72;   //prescaler value
	TIM4->ARR = 1000;  //Auto reload register 
	TIM4->CCR4 =250;  //loading value to capture control register for compare
	
	TIM4->EGR |= TIM_EGR_UG; //update on reaching desired counter
	TIM4->CR1 |= TIM_CR1_CEN; //Counter intiated here:start counting here
	
	
	while(1){
		
	Write_gp(PB,9,TIM4->CNT); //led blinking with 1Khz signal frequeny
	}
	
	
}
