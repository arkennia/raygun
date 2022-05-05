#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

static unsigned long prev_time = 0;
static unsigned long cur_time = 0;
static unsigned long delta = 0; // pass to functions that require an input of passed time

inline unsigned long get_delta()
{
        cur_time = millis();
        delta = cur_time - prev_time;
        prev_time = cur_time;
        return delta;
}

#endif /* UTIL_H */
