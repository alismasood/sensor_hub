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

static LL_GPIO_InitTypeDef led_gpio_init_struct;

void led_init(void)
{
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG); // TODO: is this config specific to this GPIO? Check SYSCFG section of reference manual. May nto be necessary.

    LL_GPIO_StructInit(&led_gpio_init_struct); // init the struct defaults 

    led_gpio_init_struct.Pin = LL_GPIO_PIN_5;                    // GPIO pin 5; on Nucleo there is an LED
    led_gpio_init_struct.Speed = LL_GPIO_SPEED_FREQ_LOW;         // output speed
    led_gpio_init_struct.Mode = LL_GPIO_MODE_OUTPUT;             // set as output 
    led_gpio_init_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;   // make it a push pull

    LL_GPIO_Init(GPIOA, &led_gpio_init_struct);                  // initialize PORT A
}

// button module

static LL_GPIO_InitTypeDef button_gpio_init_struct;

void button_init(void)
{
    // Peripheral Clock Enable
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);

    // Pin Initialization
    LL_GPIO_StructInit(&button_gpio_init_struct); // init the struct defaults 

    button_gpio_init_struct.Pin = LL_GPIO_PIN_13;                 
    button_gpio_init_struct.Speed = LL_GPIO_SPEED_FREQ_LOW;       
    button_gpio_init_struct.Mode = LL_GPIO_MODE_INPUT;             

    LL_GPIO_Init(GPIOC, &button_gpio_init_struct);                  // initialize PORT A
}

// uart module

static LL_GPIO_InitTypeDef usart_gpio_init_struct;
static LL_USART_InitTypeDef usart_init_struct;

void usart_init(void)
{
    // 92 PB6 USART1_TX ST-LINK-UART1_TX
    // 93 PB7 USART1_RX ST-LINK-UART1_RX
    
    // TODO: Clock Configuration

    // TX Pin Configuration
    LL_GPIO_StructInit(&usart_gpio_init_struct);
    
    usart_gpio_init_struct.Pin = LL_GPIO_PIN_6;
    usart_gpio_init_struct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    usart_gpio_init_struct.Mode = LL_GPIO_MODE_ALTERNATE;
    usart_gpio_init_struct.Alternate = LL_GPIO_AF_7;
    usart_gpio_init_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;

    LL_GPIO_Init(GPIOB, &usart_gpio_init_struct);

    // RX Pin Configuration
    // Uses same struct as TX.
    usart_gpio_init_struct.Pin = LL_GPIO_PIN_7;

    LL_GPIO_Init(GPIOB, &usart_gpio_init_struct);

    // USART Configuration
    LL_USART_StructInit(&usart_init_struct);

    LL_USART_Init(USART1, &usart_init_struct);
    LL_USART_Enable(USART1);

} 

int main(void){

    SystemClock_Config();

    led_init();
    button_init();

    /* Toggle forever */
    while(1){

        if(!LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13))
        {
            LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
        }

        LL_mDelay(100);
    }

    return 0;
}
