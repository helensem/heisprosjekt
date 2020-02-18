
#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__


#ifndef timer_h
#define timer_h

#include <stdio.h>
#include <stdbool.h>
//#include <"elev.h"> //skal brukes

#define TIMEOUT_PERIOD_SECONDS 3


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
bool check_timer( void );




#endif // #ifndef __INCLUDE_TIMER_H__

