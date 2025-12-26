#include "main.h"
#include "relay.h"
#include <stdint.h>
#include <stdio.h>

#include "DS3231.h"

void relay_ctrl(const uint8_t relay_num, const uint8_t relay_state)
{
    switch (relay_num) {
        case 1:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, relay_state);
            break; 
        case 2:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, relay_state);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, relay_state);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, relay_state);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, relay_state);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, relay_state);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, relay_state);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, relay_state);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, relay_state);
            break;
        case 10:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, relay_state);
            break;
        case 11:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, relay_state);
            break;
        case 12:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, relay_state);
            break;
        case 13:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, relay_state);
            break;
        case 14:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, relay_state);
            break;
        case 15:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, relay_state);
            break;
        case 16:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, relay_state);
            break;
        default:
            break;
    }		
}

void relay_register_scan(const Time_Register *time_register)
{
    for (uint8_t i = 1; i <= 16; i++) {
        if(time_register[i -1].time_hour == DS3231_Time.hour  && time_register[i - 1].time_minute == DS3231_Time.min) {
            relay_ctrl(i, time_register->relay_state);
            printf("relay_num：%d, state:%d\r\n", i, time_register[i -1].relay_state);
        }
    }
}