
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdio.h>
// To use time library of C
#include <time.h>

void delay()
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * 3;
    
    // Storing start time
    clock_t start_time = clock();
    
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

#endif // #ifndef __INCLUDE_TIMER_H__


