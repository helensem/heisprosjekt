
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__


#include <stdio.h>
#include <stdbool.h>




/**
 Sets up an initial timer
 */
void timer_init( void );


/**
 Starts the timer
 */
void startTimer( void );

/**
 checks if timer is done
 @return 1 if timer is done, 0 otherwise
 */
_Bool check_timer( void );




#endif // #ifndef __INCLUDE_TIMER_H__
