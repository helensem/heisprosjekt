
#ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__
#define __INCLUDE_ELEVATOR_CONTROLLER_H__

#include "channels.h"
#include "io.h"
#include "timer.h"
#include "hardware.h"
#include "queue.h"
#include "channels.h"


typedef enum {
    IDLE,
    MOVING_UP,
    STOP,
    DOOR_OPENED,
} current_state;

/**
 Function related to the emergency stop button. Clears all requests and stops the elevator.
 */

void emergency_stop ();


void obstruction ();


/**
 Function that knows which floor the elevator is currently in
 @return current floor, -1 if error.
 */

int get_current_floor ();



/**
 General function for the elevator
 */

void elevator_controller ();



#endif // #ifndef __INCLUDE_TIMER_H__

