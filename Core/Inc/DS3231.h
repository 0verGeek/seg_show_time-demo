//
// Created by alber on 2025/12/9.
//

#ifndef YLX_DRIVER_DEMO_DS3231_H
#define YLX_DRIVER_DEMO_DS3231_H

#define HOUR_FORM_12  12
#define HOUR_FORM_24  24
#define RX_BUFFER_SIZE 64

#include "stdint.h"

char str[RX_BUFFER_SIZE] = {0};

/*DS3231寄存器结构体*/
typedef struct
{
    uint8_t Seconds;
    uint8_t Minutes;
    uint8_t Hours;
    uint8_t Day;
    uint8_t Date;
    uint8_t Month_Century;
    uint8_t Year;

    uint8_t Alarm_1_Seconds;
    uint8_t Alarm_1_Minutes;
    uint8_t Alarm_1_Hours;
    uint8_t Alarm_1_Day_Date;

    uint8_t Alarm_2_Minutes;
    uint8_t Alarm_2_Hours;
    uint8_t Alarm_2_Day_Date;

    uint8_t Control;
    uint8_t Control_Status;
    uint8_t Aging_Offset;
    uint8_t Temp_MSB;
    uint8_t Temp_LSB;
}DS3231_RegisterType;

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t hour_form; // 12小时制或24小时制
    uint8_t AM_PM;     // 上下午标志，12小时制时有效
    uint8_t year;
    uint8_t mon;
    uint8_t date;
    uint8_t day;
}DS3231_TimeType;

typedef enum
{
    SECONDS=0,
    MINUTES,
    HOURS,
    DAY,
    DATE,
    MONTH_CENTURY,
    YEAR,
    ALARM_1_SECONDS,
    ALARM_1_MINUTES,
    ALARM_1_HOURS,
    ALARM_1_DAY,
    ALARM_1_DATE,
    ALARM_2_MINUTES,
    ALARM_2_HOURS,
    ALARM_2_DAY_DATE,
    CONTROL,
    CONTROL_STATUS,
    AGING_OFFSET,
    TEMP_MSB,
    TEMP_LSB
}DS3231_REG;

void DS3231_Read_All();
void DS3231_Update();
void DS3231_Read_Time();
void DS3231_Set_Time(DS3231_TimeType* time);

extern DS3231_TimeType DS3231_Time;


#endif //YLX_DRIVER_DEMO_DS3231_H