#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_system.h"

#define led LL_GPIO_PIN_7

void EXTI15_10_IRQHandler(){
    if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13)!=0){
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
        LL_GPIO_TogglePin(GPIOB,led);
        LL_GPIO_TogglePin(GPIOC,led);
    }
}

int main(){
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_GPIO_InitTypeDef li={0};
    li.Pin=led;
    li.Speed=LL_GPIO_SPEED_FREQ_LOW;
    li.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
    li.Mode=LL_GPIO_MODE_OUTPUT;
    li.Pull=LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOB,&li);

    LL_GPIO_InitTypeDef gi={0};
    gi.Pin=led;
    gi.Speed=LL_GPIO_SPEED_FREQ_LOW;
    gi.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
    gi.Mode=LL_GPIO_MODE_OUTPUT;
    gi.Pull=LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOC,&li);
    LL_GPIO_SetOutputPin(GPIOC,led);

    LL_GPIO_InitTypeDef bi={0};
    bi.Pin=LL_GPIO_PIN_13;
    bi.Mode=LL_GPIO_MODE_INPUT;
    bi.Pull=LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOC,&bi);

    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC,LL_SYSCFG_EXTI_LINE13);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_13);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_13);

    NVIC_SetPriority(EXTI15_10_IRQn,0);
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    while(1){}


}