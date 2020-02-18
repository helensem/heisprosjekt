
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdio.h>
// To use time library of C
#include <time.h>
#include "timer.h"

static time_t start = time (NULL);
int run_time = 3; 


_Bool check_timer(){
    if (time (NULL) == start + run_time) {
        return 1;}
return 0;
}



#endif // #ifndef __INCLUDE_TIMER_H__


