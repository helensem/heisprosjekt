
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdio.h>
#include <time.h>
#include "timer.h"

time_t start_time;
time_t end_time;


void start:timer() {
    start_time = time (NULL);
}

int check_timer() {
    end_time = time (NULL);
    return ((end_time - start_time) => 3);
}
 //bytt ut alle bool med int

#endif // #ifndef __INCLUDE_TIMER_H__
