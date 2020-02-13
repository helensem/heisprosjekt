
#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

#include "channels.h"
#include "io.h"


#define N_FLOORS 4
#define N_BUTTONS 3

typedef enum {
    OUT_OF_REACH = -1,
    FIRST = 1,
    SECOND = 2,
    THIRD = 3,
    FOURTH = 4
} floor_nr;


typedef enum {
    UNKNOWN = -1,
    OUTSIDE_UP = 0,
    OUTSIDE_DOWN = 1,
    INSIDE_CALL = 2,
} order_type;

//lager enums for å forenkle ting litt

//Lager matrix for hver type bestilling. 4 etasjer og 3 ulike bstillinger
//settes til en om aktiv bestilling og 0 om fullført/ingen aktiv bestilling
static int requests = [N_FLOORS]*[N_BUTTONS];



/**
  We add a request to the queue AKA set the requested floor and order to 1
  @param floor, the requested floor
  @param button, what typed of request we want
*/

void addRequest(floor_nr floor, order_type button);


/**
 Check if we have the requested floor
 @param floor, the requested floor
 @param button, what typed of request we want
 @return 1 if the order is requested, 0 if not active
 */

int getRequest(floor_nr floor, order_type button);


/**
 A magic algoritm to find the next request that is making sense for the elevator
 @param current_floor, where the elevator is
 @param dir, the direction of the elevator
 @return the next floor
 */

int getNextRequest(floor_nr current_floor, elev_motor_direction_t dirn);



/**
 remove the requests as we move through them AKA set the request to 0
 @param floor, the requested floor
 @param button, what typed of request we want
 */
void remove_order(floor_nr floor, elev_motor_direction_t dirn);

/**
 removes all the requests
 */
void clear_all();


#endif // #ifndef __INCLUDE_IO_H__

