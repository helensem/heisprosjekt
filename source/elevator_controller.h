
/**
 @brief Runs the state machine and is the overall brain of the elevator
 */
#ifndef ELEVATOR_CONTROLLER_H__
#define ELEVATOR_CONTROLLER_H__

#include "timer.h"
#include "hardware.h"
#include "queue.h"

typedef enum { //også litt usikker på hvor det er best å putte disse 
    DOWN,
    UP
} Direction;
//enum for direction til heisen, denne er kun nødvendig å vite iforhold til om heisen skal betjene down-orders eller up-orders.


typedef struct {
    int floor;
    int above;
} Floor
//Struct for heisens nåværende etasje. Dersom heisen er i bevegelse, settes above til 1 (heisen er over floor) Dette er greit å vite om vi stopper midt mellom etasjer.


typedef enum {
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    STOP,
    DOOR_OPENED,
} state;

//enum for state til heisen


/**
 @brief Function related to the emergency stop button. Clears all requests and stops the elevator.
 */

void emergency_stop ();

/**
 @brief Function related to the idle state. Looks for new requests, our first state
 @param elevators current floor 
 */
void idle ();

/**
 @brief Function related to the opened door state. 
 @param elevators current floor 
 */
void door_opening ();

/**
 @brief Function related to when the elevator is moving upwards. 
 @param elevators current floor 
 */
void moving_up ();

/**
 @brief Function related to when the elevator is moving downwards. 
 @param elevators current floor 
 */
void moving_down ();




/**
 @brief Function that knows which floor the elevator is currently in
 @return current floor, -1 if error.
 */

int get_current_floor ();



/**
 @brief General function for the elevator
 */

void elevator_controller ();

/** 
 * @brief when an order button is pressed, it is added to the queue 
 */
void request_control ()

#endif // #ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__

