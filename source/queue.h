
#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

/**
 @file
 @brief queue system for the elevator, and includes the functions to get the next floor
 */

#include "hardware.h"
#include "elevator_controller.h"


#define N_FLOORS 4
#define N_BUTTONS 3


/**
  @brief We add a request to the queue AKA set the requested floor and order to 1
  @param [in] floor, the requested floor
  @param [in] button, what typed of request we want
*/

void add_order(int floor, HardwareOrder button);


/**
 @brief checks the array of the current direction for an order
 @param [in] floor, offset where the elevator starts looking for orders
 @param [in] p_current_dir, pointer to the direction of the elevator
 @return next floor if order in the same directon, -1 otherwise
 
 */

int get_order_in_current_direction(int floor, Direction *p_current_dir);

/**
@brief checks the arrays to find the next request that is making sense for the elevator
@param [in] p_current_floor, pointer to where the elevator is
@param [in, out] p_current_dir, pointer to the direction of the elevator
@param [out] p_next_floor, a pointer to the next floor
*/
void get_next_order(Floor *p_current_floor, Direction *p_current_dir, int *p_next_floor);


/**
@brief checks the current floor if there are any orders there 
@param [in] floor, the floor wished to be checked
@param [in] dir, the direction of the elevator
@return 1 if order is on floor, 0 otherwise 
*/
int check_floor_for_orders(int floor, Direction dir);



/**
 @brief remove the requests as we move through them AKA set the request to 0
 @param [in] floor, the requested floor
 */
void remove_order(int floor);

/**
 @brief removes all the orders
 */
void clear_all_orders();



#endif // #ifndef __INCLUDE_QUEUE_H__

