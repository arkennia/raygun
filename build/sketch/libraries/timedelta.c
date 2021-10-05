#line 1 "c:\\Users\\faane\\Documents\\Arduino\\raygun\\libraries\\timedelta.c"
#include "timedelta.h"

#include <Arduino.h>

unsigned long delta = 0;

static unsigned long prev_time = 0;

void timedelta_update()
{
        unsigned long cur_time = millis();
        delta = curTime - prev_time;
}