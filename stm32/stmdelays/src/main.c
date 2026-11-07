#include "stm32l4xx.h"

volatile uint32_t msticks=0;

void SysTick_Handler(){
    msticks++;
}

void delay(uint32_t d){
    uint32_t ct=msticks;
    while(msticks-ct<d){
        //wait
    }
}

int main(){
    SysTick_Config(SystemCoreClock/1000);
    delay(500);
}