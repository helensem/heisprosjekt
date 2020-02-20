
#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

#include "hardware.h"


#define N_FLOORS 4
#define N_BUTTONS 3


//Lager matrix for hver type bestilling. 4 etasjer og 3 ulike bstillinger
//settes til en om aktiv bestilling og 0 om fullført/ingen aktiv bestilling
static int requests = [N_FLOORS]*[N_BUTTONS];



/**
  We add a request to the queue AKA set the requested floor and order to 1
  @param floor, the requested floor
  @param button, what typed of request we want
*/

void addRequest(int floor, HardwareOrder button);


/**
 Check if we have the requested floor
 @param floor, the requested floor
 @param button, what typed of request we want
 @return 1 if the order is requested, 0 if not active
 */

bool getRequest(int floor, HardwareOrder button);


/**
 A magic algoritm to find the next request that is making sense for the elevator
 @param current_floor, where the elevator is
 @param dir, the direction of the elevator
 @return the next floor
 */

int getNextRequest(int &current_floor, HardwareMovement &dir);



/**
 remove the requests as we move through them AKA set the request to 0
 @param floor, the requested floor
 @param button, what typed of request we want
 */
void removeRequest(int floor);

/**
 removes all the requests
 */
void clear_all();


#endif // #ifndef __INCLUDE_QUEUE_H__

