

#include <stdio.h>
#include "timer.h"

static time_t timeout_time;

void reset_timer(){
    timeout_time = 0;
    return;
}


void start_timer() {
    timeout_time = time (NULL);
    return;
}

int check_timer() {
    if (timeout_time == 0) {
        start_timer ();
    }
    if(hardware_read_obstruction_signal()){
        reset_timer();
        return 0;
    }
    if((time (NULL) >= (timeout_time + 3))){
        reset_timer();
        return 1;
    }
    else{
        return 0;
    }
}
 //bytt ut alle bool med int

