/**
 @brief timer functions
 */

#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__


#include <stdio.h>
#include <time.h>

/**
 @brief resets the timer
 */
void reset_timer()

/**
 @brief Sets the offset of the timer (start time)
 */
void start_timer( );

/**
 @brief checks if timer is done by checking the difference between passed time and start time, will reset if obstruction signal set. 
 @return 1 if timer is done, 0 otherwise
 */
int check_timer();




#endif // #ifndef __INCLUDE_TIMER_H__
