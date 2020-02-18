
#ifndef ELEVATOR_CONTROLLER_H__
#define ELEVATOR_CONTROLLER_H__

#include "channels.h"
#include "io.h"
#include "timer.h"
#include "hardware.h"
#include "queue.h"


typedef enum {
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    STOP,
    DOOR_OPENED,
} state;


state current_state;

/**
 @brief Function related to the emergency stop button. Clears all requests and stops the elevator.
 */

void emergency_stop (int current_floor);

/**
 @brief Function related to the idle state. Looks for new requests, our first state
 @param elevators current floor 
 */
void idle (int current_floor);

/**
 @brief Function related to the opened door state. 
 @param elevators current floor 
 */
void door_opening (int current_floor);

/**
 @brief Function related to when the elevator is moving upwards. 
 @param elevators current floor 
 */
void moving_up (int current_floor);

/**
 @brief Function related to when the elevator is moving downwards. 
 @param elevators current floor 
 */
void moving_down (int current_floor);




/**
 @brief Function that knows which floor the elevator is currently in
 @return current floor, -1 if error.
 */

int get_current_floor ();



/**
 General function for the elevator
 */

void elevator_controller ();

/** 
 * @brief when an order button is pressed, it is added to the queue 
 */
void request_control ()

#endif // #ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__

