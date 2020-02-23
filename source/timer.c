

#include <stdio.h>
#include <time.h>
#include "timer.h"

time_t start_time;
time_t end_time;


void start_timer() {
    start_time = time (NULL);
    return;
}

int check_timer() {
    end_time = time (NULL);
    return ((end_time - start_time) == 3);
}
 //bytt ut alle bool med int

