/**
 @brief timer functions
 */

#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__


#include <stdio.h>
#include <stdbool.h>


/**
 @brief Starts the timer
 */
void start_timer( );

/**
 @brief checks if timer is done by checking the difference between passed time and start time
 @return 1 if timer is done, 0 otherwise
 */
int check_timer();




#endif // #ifndef __INCLUDE_TIMER_H__