

#include <stdio.h>
#include "timer.h"

static clock_t start_time; 


void start_timer() {
    start_time = time (NULL);
    return;
}

int check_timer() {
    return (time (NULL) >= (start_time + 3));
}
 //bytt ut alle bool med int

