#include <stdlib.h>

#include "stm32l4xx.h"
#include "stm32l4xx_conf.h"

void SystemClock_Config(void){

    /* Clock init stuff */ 
    
    LL_UTILS_PLLInitTypeDef sUTILS_PLLInitStruct = {
        .PLLM = LL_RCC_PLLM_DIV_2, 
        .PLLN = 20,
        .PLLR = LL_RCC_PLLR_DIV_2
    };
    
    LL_UTILS_ClkInitTypeDef sUTILS_ClkInitStruct = {
        LL_RCC_SYSCLK_DIV_1, 
        LL_RCC_APB1_DIV_1, 
        LL_RCC_APB2_DIV_1
    };
    
    LL_PLL_ConfigSystemClock_HSI(&sUTILS_PLLInitStruct, &sUTILS_ClkInitStruct);
    
    LL_Init1msTick(SystemCoreClock);
}

// led module

static LL_GPIO_InitTypeDef GPIO_InitStruct;

void led_init(void)
{
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);

    /* Set up port A parameters */
    LL_GPIO_StructInit(&GPIO_InitStruct); // init the struct defaults 

    GPIO_InitStruct.Pin = LL_GPIO_PIN_5;                    // GPIO pin 5; on Nucleo there is an LED
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;         // output speed
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;             // set as output 
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;   // make it a push pull

    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);                  // initialize PORT A
}


int main(void){

    SystemClock_Config();

    led_init();
    
    /* Toggle forever */
    while(1){
        LL_mDelay(100);
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
    }

    return 0;
}
