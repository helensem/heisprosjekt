
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdio.h>
#include <time.h>
#include "timer.h"

time_t start_time;
time_t end_time;


void startTimer(void) {
    start_time = time (NULL);
}

bool check_timer(void) {
    end_time = time (NULL);
    return ((end_time - start_time) => 3);
}


#endif // #ifndef __INCLUDE_TIMER_H__
