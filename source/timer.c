
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdio.h>
// To use time library of C
#include <time.h>
#include "timer.h"


static clock_t timeout_time;

void timer_init(void) {
    timeout_time = 0;
}

void startTimer(void) {
    timeout_time = clock() + TIMEOUT_PERIOD_SECONDS * CLOCKS_PER_SEC;
}

bool check_timer(void) {
    return (clock() >= timeout_time);
}


#endif // #ifndef __INCLUDE_TIMER_H__


