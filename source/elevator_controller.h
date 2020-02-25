
/**
 @brief Runs the state machine and is the overall brain of the elevator
 */
#ifndef ELEVATOR_CONTROLLER_H__
#define ELEVATOR_CONTROLLER_H__

#include "timer.h"
#include "hardware.h"


/**
 @brief enum for Direction.
 */
typedef enum {
    DOWN,
    UP
} Direction;

/**
 @brief struct for flooer. int floor says which floor the elevator was previously at. above says if the elevator is above that current floor
 */
typedef struct {
    int floor;
    int above;
} Floor;


/**
 @brief enum for the states of the elevator
 */
typedef enum {
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    STOPPING,
    DOOR_OPENED
} State;



/**
 @brief Function related to the emergency stop button. Clears all requests and stops the elevator.
 @param p_current_floor, pointer to the struct of type floor, where the elevator is
 @param p_current_state, pointer to our current state
 */

void emergency_stop(Floor *p_current_floor, State *p_current_state);

/**
 @brief Function related to the idle state. Looks for new requests, our first state
 @param p_current_state, pointer to elevators current state
 @param p_current_floor, pointer elevators current position
 @param p_current_dir, pointer to elevators direction
 @param p_next_floor, pointer to elevators next floor
 */
void idle(State *p_current_state, Direction *p_current_dir, Floor *p_current_floor, int *p_next_floor);

/**
 @brief Function related to the opened door state. 
 @param p_current_state, pointer to elevators current state
 @param p_current_floor, pointer to elevators current position
 */
void door_opening(State *p_current_state, Floor *p_current_floor);

/**
 @brief Function related to when the elevator is moving upwards. 
 @param p_current_state, pointer to elevators current state
 */
void moving_up(Floor *p_current_floor, State *p_current_state, int *p_next_floor);

/**
 @brief Function related to when the elevator is moving downwards. 
 @param p_current_state, pointer to elevators current srate
 */

void moving_down(Floor *p_current_floor, State *p_current_state, int *p_next_floor);





#endif // #ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__

