#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_attr.h"

#define buttonpin GPIO_NUM_4
#define ledpin    GPIO_NUM_2

static int state=0;
static int64_t lasttime=0;

static void IRAM_ATTR buttonisr(void*arg){
    int64_t now=esp_timer_get_time();
    if(now-lasttime>50000){
        lasttime=now;
        state=!state;
        gpio_set_level(ledpin,state);
    }
}
void app_main() {
    gpio_config_t led={
        .pin_bit_mask=1ULL<<ledpin,
        .mode=GPIO_MODE_OUTPUT,
        .pull_up_en=GPIO_PULLUP_DISABLE,
        .pull_down_en=GPIO_PULLDOWN_DISABLE,
        .intr_type=GPIO_INTR_DISABLE,
    };
    gpio_config(&led);
    gpio_config_t butt={
        .pin_bit_mask=1ULL<<buttonpin,
        .mode=GPIO_MODE_INPUT,
        .pull_down_en=GPIO_PULLDOWN_DISABLE,
        .pull_up_en=GPIO_PULLUP_ENABLE,
        .intr_type=GPIO_INTR_NEGEDGE,
    };
    gpio_config(&butt);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(buttonpin,buttonisr,NULL);
}