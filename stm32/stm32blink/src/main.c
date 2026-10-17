#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_rcc.h"

#define led LL_GPIO_PIN_7
int main(){
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
    LL_GPIO_InitTypeDef gi={0};
    gi.Pin=led;
    gi.Mode=LL_GPIO_MODE_OUTPUT;
    gi.Speed=LL_GPIO_SPEED_FREQ_LOW;
    gi.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
    gi.Pull=LL_GPIO_PULL_NO;

    LL_GPIO_InitTypeDef gii={0};
    gii.Pin=led;
    gii.Mode=LL_GPIO_MODE_OUTPUT;
    gii.Speed=LL_GPIO_SPEED_FREQ_LOW;
    gii.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
    gii.Pull=LL_GPIO_PULL_NO;

    LL_GPIO_Init(GPIOB,&gi);
    LL_GPIO_Init(GPIOC,&gii);

    LL_GPIO_SetOutputPin(GPIOC,led);

    while(1){
        LL_GPIO_TogglePin(GPIOB,led);
        LL_GPIO_TogglePin(GPIOC,led);
        for(volatile uint32_t i=0;i<200000;++i);
    }
}