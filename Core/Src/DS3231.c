#include "DS3231.h"
#include "i2c.h"
#include "usart.h"

DS3231_RegisterType DS3231_Register;
DS3231_TimeType DS3231_Time;
void DS3231_Init()
{
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, (uint8_t *)str, RX_BUFFER_SIZE);
}
/*一次性读取所有的寄存器*/
void DS3231_Read_All()
{
    uint8_t temp[1] = {0};
    /*设置寄存器指针位置*/
    HAL_I2C_Master_Transmit(&hi2c2, 0xD0, temp, 1, 0xffff);

    HAL_I2C_Master_Receive(&hi2c2, 0xD1, (uint8_t *)&(DS3231_Register), sizeof(DS3231_Register), 0xffff);
}

void DS3231_Update()
{
    HAL_I2C_Mem_Write(&hi2c2,0xD0,0x00,1,(uint8_t *)&DS3231_Register,sizeof(DS3231_Register),0xffff);
}

uint8_t bcd2dec(uint8_t bcd)
{
    return ( (bcd) >> 4 ) * 10 + ( (bcd) & 0x0f );
}

uint8_t dec2bcd(uint8_t dec)
{
    return (( (dec)/10 ) << 4) + ( (dec) % 10 );
}

void DS3231_Read_Time()
{
    DS3231_Time.sec = bcd2dec(DS3231_Register.Seconds);
    DS3231_Time.min = bcd2dec(DS3231_Register.Minutes);

    if((DS3231_Register.Hours & 0x40) == 0x40)
    {
        DS3231_Time.hour_form = HOUR_FORM_12;
        DS3231_Time.AM_PM = (DS3231_Register.Hours) & 0x20;
        DS3231_Time.hour = bcd2dec(DS3231_Register.Hours & 0x1F);
    }
    else
    {
        DS3231_Time.hour_form = HOUR_FORM_24;
        DS3231_Time.hour = bcd2dec(DS3231_Register.Hours);
    }

    DS3231_Time.year = bcd2dec(DS3231_Register.Year);
    DS3231_Time.mon = bcd2dec(DS3231_Register.Month_Century);
    DS3231_Time.date = bcd2dec(DS3231_Register.Date);
    DS3231_Time.day = DS3231_Register.Day;
}

void DS3231_Set_Time(DS3231_TimeType* time)
{
    DS3231_Register.Seconds = dec2bcd(time->sec);
    DS3231_Register.Minutes = dec2bcd(time->min);

    if(time->hour_form == HOUR_FORM_12)
    {

        DS3231_Register.Hours = (0x40 | (time->AM_PM<<5))|(dec2bcd(time->hour));
    }
    else
    {
        DS3231_Register.Hours = dec2bcd(time->hour);
    }

    DS3231_Register.Year = dec2bcd(time->year);
    DS3231_Register.Month_Century = dec2bcd(time->mon);
    DS3231_Register.Date = dec2bcd(time->date);
    DS3231_Register.Day = time->day;
}