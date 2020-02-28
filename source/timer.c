

#include <stdio.h>
#include "timer.h"

static time_t offset_time;

void reset_timer(){
    offset_time = 0;
    return;
}


void start_timer() {
    offset_time = time (NULL);
    return;
}

int check_timer() {
    if (offset_time == 0) {
        start_timer ();
    }
    if(hardware_read_obstruction_signal()){
        reset_timer();
        return 0;
    }
    if((time (NULL) >= (offset_time + 3))){
        reset_timer();
        return 1;
    }
    else{
        return 0;
    }
}

