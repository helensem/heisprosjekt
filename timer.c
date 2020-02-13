
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__


bool startTimer ()
{
    unsigned int time;
    
    unsigned int count_down_time=3;
    
    
    clock_t x_startTime=clock();  // start clock
    time=count_down_time_in_secs;   // update timer
    
    while (time>0)
    {
    clock_t x_countTime=clock(); // update timer difference
        time_left=count_down_time-1; // subtract to get difference
        }
    if (time = 0) {
        return 1;
    }


#endif // #ifndef __INCLUDE_TIMER_H__

