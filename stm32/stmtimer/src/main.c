#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_utils.h"

volatile uint32_t msticks=0;

void SysTick_Handler(){
    msticks++;
}

void SystemClock_Config(){
    SysTick_Config(4000000/1000);
}

void GPIO_init(){
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

    LL_GPIO_SetPinMode(GPIOB,LL_GPIO_PIN_7,LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOB,LL_GPIO_PIN_7,LL_GPIO_AF_2);

    LL_GPIO_SetPinMode(GPIOC,LL_GPIO_PIN_13,LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(GPIOC,LL_GPIO_PIN_13,LL_GPIO_PULL_NO);
}

void TIM4_init(){
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

    LL_TIM_SetPrescaler(TIM4,3);
    LL_TIM_SetAutoReload(TIM4,999);

    LL_TIM_OC_SetMode(TIM4,LL_TIM_CHANNEL_CH2,LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetCompareCH1(TIM4,0);
    LL_TIM_CC_EnableChannel(TIM4,LL_TIM_CHANNEL_CH2);
    LL_TIM_EnableCounter(TIM4);

}

int main(){
    SystemClock_Config();
    GPIO_init();
    TIM4_init();

    int32_t ccrval=0;
    int32_t step=10;
    uint32_t lastfade=0;
    uint8_t paused=0;
    uint8_t ls=0;

    while(1){
        uint8_t cbs=LL_GPIO_IsInputPinSet(GPIOC,LL_GPIO_PIN_13);
        if(cbs&&!ls){
            paused=!paused;
        }
        ls=cbs;

        if((msticks-lastfade)>=10&&(paused==0)){
            lastfade=msticks;
            ccrval+=step;
            if(ccrval>=999||ccrval<=0){
                step=-step;
            }
            LL_TIM_OC_SetCompareCH2(TIM4,(uint32_t)ccrval);
        }
    }

}