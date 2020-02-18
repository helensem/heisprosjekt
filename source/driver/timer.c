
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdio.h>
#include "timer.h"
#include <time.h>

// To use time library of C

void startTimer(void)
{
    // Converting time into milli_seconds
    int seconds = 3;
    
    // Storing start time
    clock_t start_time = clock();
    
    // looping till required time is not achieved
    if (clock() == (start_time + (seconds*CLOCKS_PER_SEC))){
        return;
    }
}



#endif // #ifndef __INCLUDE_TIMER_H__


