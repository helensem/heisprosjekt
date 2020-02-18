
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdio.h>
#include <time.h>
#include "timer.h"


static clock_t timeout_time;

void timer_init(void) {
    timeout_time = 0;
}

void startTimer(void) {
    timeout_time = clock() + 3 * CLOCKS_PER_SEC;
}

_Bool check_timer(void) {
    return (clock() >= timeout_time);
}


#endif // #ifndef __INCLUDE_TIMER_H__
