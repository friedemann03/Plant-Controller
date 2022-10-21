//
// Created by Friedemann Drepper on 17.10.22.
//

#include "controller_power.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_pwr.h"
#include "main.h"
#include "subsystem_gpio.h"
#include "subsystem_uart.h"
#include "subsystem_adc.h"
#include "subsystem_i2c.h"
#include "subsystem_tim.h"
#include "log_module.h"
#include "controller_led.h"
#include "controller_tank.h"
#include "controller_button.h"
#include "subsystem_rtc.h"
#include "system_events.h"


extern void SystemClock_Config(void);


static bool buttonWakeUp;

void Power_Controller_Set_ButtonWakeUp(void) {
    buttonWakeUp = true;
}

void Power_Controller_StopMode(void) {

    LOG_DEBUG("Entering STOP Mode now.");

    // enabling the wakeup function in the button controller
    Button_Controller_EnableWakeUp();

    // Disable all subsystems and GPIOs (setting them to analog) to minimize power consumption
    Uart_Subsystem_DeInit();
    Tim_Subsystem_DeInit();
    Adc_Subsystem_DeInit();
    I2c_Subsystem_DeInit();
    Gpio_Subsystem_DeInit();

    /* Configure User push-button as external interrupt generator */
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = USER_BTN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

    /* Suspend Tick increment to prevent wakeup by Systick interrupt.
     Otherwise, the Systick interrupt will wake up the device within 1ms (HAL time base) */
    HAL_SuspendTick();

    //Switch to HSI clock before entering stop mode, needed so we can turn HSE off before entering (page 87 of RM)
    /* Enable HSI if not enabled */
    if (LL_RCC_HSI_IsReady() != 1) {
        /* Enable HSI */
        LL_RCC_HSI_Enable();
        while (LL_RCC_HSI_IsReady() != 1) {
            /* Wait for HSI ready */
        }
    }

    /* Set HSI as SYSCLCK source */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI) {}

    //Disable the HSE now that the HSI is enabled
    LL_RCC_HSE_Disable();
    LL_RCC_PLL_Disable();

    // ENTERING STOP MODE
    /* We enable again the PWR peripheral */
    __HAL_RCC_PWR_CLK_ENABLE();
    /* Request to enter SLEEP mode */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    // EXITING STOP MODE

    /* Reconfigure the Clock Tree after wakeup */
    SystemClock_Config();

    /*Disable the write-protection*/
    __HAL_RTC_WRITEPROTECTION_DISABLE(&hrtc);
    /*Wait until the shadow registers are synchronized*/
    HAL_RTC_WaitForSynchro(&hrtc);
    /*Enable again the write-protection to prevent registers corruption*/
    __HAL_RTC_WRITEPROTECTION_ENABLE(&hrtc);

    /* Resume Tick interrupt if disabled prior to sleep mode entry */
    HAL_ResumeTick();

    if (buttonWakeUp) {
        System_Event_Trigger_Event(EVENT_LONG_BUTTON_PRESS);
    } else {
        System_Event_Trigger_Event(EVENT_RTC_WAKEUP);
    }

    /* Reinitialize all Subsystems */
    Gpio_Subsystem_Init();
    Uart_Subsystem_Init();
    Tim_Subsystem_Init();
    Adc_Subsystem_Init();
    I2c_Subsystem_Init();

    LOG_DEBUG("Exiting STOP Mode now.");
    
}