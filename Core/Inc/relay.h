#ifndef __RELAY_H
#define __RELAY_H

#include  "stdint.h"

typedef struct
{
    uint8_t time_hour;
	uint8_t time_minute;
	uint8_t relay_state;

}Time_Register ;

void relay_register_scan(const Time_Register *time_register);

#endif