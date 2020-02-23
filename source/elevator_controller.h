
/**
 @brief Runs the state machine and is the overall brain of the elevator
 */
#ifndef ELEVATOR_CONTROLLER_H__
#define ELEVATOR_CONTROLLER_H__

#include "timer.h"
#include "hardware.h"
#include "driver/io.h"
#include "driver/channels.h"

typedef enum { //også litt usikker på hvor det er best å putte disse 
    DOWN,
    UP
} Direction;
//enum for direction til heisen, denne er kun nødvendig å vite iforhold til om heisen skal betjene down-orders eller up-orders.


typedef struct {
    int floor;
    int above;
} Floor;


typedef enum {
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    STOPPING,
    DOOR_OPENED
} State;

extern State current_state;
extern  Floor current_floor;
extern  Direction current_dir;
extern  int next_floor;

/**
 @brief Function that knows which floor the elevator is currently in
 @return current floor, -1 if error.
 */

int get_current_floor ();

    


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





#endif // #ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__

