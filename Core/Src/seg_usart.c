#include "seg_usart.h"
#include <stdio.h>
#include <sys/_intsup.h>
#include "usart.h"
#include "math.h"

#define USART &huart2



void seg_show_num(float num, const bool buff_or_not, uint8_t brightness)
{
    brightness = brightness > 8 ? 8 : (brightness < 1 ? 1 : brightness);

    int dot= check_dot(num);

    char buf[30];
    if(num > 9999 || num < -999)
        sprintf(buf, "X----408");
    else
        sprintf(buf, "X%04d%d%d%d", (int)(pow(10,dot) * num), 4 - dot , buff_or_not ? 1 : 0, brightness);

    HAL_UART_Transmit(USART, (uint8_t *)buf, 8, HAL_MAX_DELAY);
}

void seg_show_time(uint8_t hours, uint8_t minutes) {
  // uint8_t seconds = sTime.Seconds;
  char buf[30];
  sprintf(buf, "X%02d%02d218", hours, minutes);
  HAL_UART_Transmit(&huart2, (uint8_t *)buf, 8, HAL_MAX_DELAY);
}
int check_dot(float num)
{
    int dot = 0;
    // 步骤1：提取小数部分并放大10000倍（4位小数），转成整数
    int decimal_part = (int)(fabs(num - (int)num) * 10000 + 0.5); // +0.5是四舍五入
    // 步骤2：判断小数部分有几位有效数字
    while (decimal_part % 10 == 0 && decimal_part != 0) {
        decimal_part /= 10;
    }
    // 步骤3：计算小数位数
    if (decimal_part != 0) {
        dot = (uint8_t)log10(decimal_part) + 1;
    }

    return dot;
}
