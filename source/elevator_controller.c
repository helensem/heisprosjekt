
#ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__
#define __INCLUDE_ELEVATOR_CONTROLLER_H__

#include <stdio.h>
#include "elevator_controller.h"
#include <unistd.h>
#include "hardware.h"

int current_floor = get_current_floor ();
int next_floor = getNextRequest (current_floor, HARDWARE_MOVEMENT_UP);

int get_current_floor () {
    if (io_read_bit(SENSOR_FLOOR1))
        return 0;
    else if (io_read_bit(SENSOR_FLOOR2))
        return 1;
    else if (io_read_bit(SENSOR_FLOOR3))
        return 2;
    else if (io_read_bit(SENSOR_FLOOR4))
        return 3;
    else
        return -1;
}


void emergency_stop () {
    hardware_command_movement (HARDWARE_MOVEMENT_STOP);
    clear_all_order_lights();
    clear_all (); //mulighet for å ta denne ut av funksjonen og sette inn etter (for clean slate)
    hardware_command_stop_light (1);
    if (get_current_floor!=-1) {
        hardware_command_door_open (1);
    }
    
}

// Kan være noe problem med get_current floor i tilfelle heisen er i midten 
void idle (int current_floor) {
    hardware_command_movement (HARDWARE_MOVEMENT_STOP);
    if (next_floor!=0) {
        if (next_floor < current_floor){
            current_state = MOVING_DOWN;
        }
        if (next_floor > current_floor) {
            current_state = MOVING_UP;
        }
        if (next_floor == current_floor) {
            current_state = DOOR_OPENED;
        }
    }
    if (hardware_read_stop_signal) {
        current_state = STOP;
    }
}

void door_opening (int current_floor) {
    int next_floor = getNextRequest (current_floor, HARDWARE_MOVEMENT_UP);
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_order_light(current_floor, HARDWARE_ORDER_INSIDE, 0);
    hardware_command_door_open (1); 
    if (next_floor < current_floor||current_floor == 4){
        removeRequest(current_floor, HARDWARE_MOVEMENT_DOWN);
        hardware_command_order_light(current_floor, HARDWARE_ORDER_DOWN, 0);   
    }
    if (next_floor > current_floor||current_floor == 1){
        removeRequest (current_floor, HARDWARE_MOVEMENT_UP);
        hardware_command_order_light(current_floor, HARDWARE_ORDER_UP, 0); 
    }
    if (hardware_read_obstruction_signal) { 
        sleep (1);
    }
    startTimer ();
    if (check_timer()){
        hardware_command_door_open (1);
        current_state = IDLE;
    } 
}

void moving_up (int current_floor) {
    hardware_command_movement (HARDWARE_MOVEMENT_UP);
    if (requests [next_floor][HARDWARE_ORDER_UP]==1||requests [next_floor][HARDWARE_ORDER_INSIDE]==1) {
        current_state = DOOR_OPENED; 
    } 
    if (hardware_read_floor_sensor(3)&& requests [3][HARDWARE_ORDER_DOWN]==0 &&requests [3][HARDWARE_ORDER_INSIDE]==0 ) {
        current_state = MOVING_DOWN;
    }
    if (hardware_read_stop_signal ()) {
        current_state = STOP; 
    }
}

void moving_down (int current_floor) {
  hardware_command_movement (HARDWARE_MOVEMENT_DOWN);
    if (requests [next_floor][HARDWARE_ORDER_DOWN]==1||requests [next_floor][HARDWARE_ORDER_INSIDE]==1) {
        current_state = DOOR_OPENED; 
    } 
    if (hardware_read_floor_sensor(0)&& requests [0][HARDWARE_ORDER_DOWN]==0 &&requests [0][HARDWARE_ORDER_INSIDE]==0 ) {
        current_state = MOVING_UP;
    }
    if (hardware_read_stop_signal ()) {
        current_state = STOP; 
    }  
}

void request_control (){ 
    for (int floor = 0; floor < N_FLOORS; floor++) {
        for (int button = 0; button > 3; button++) {
            if (hardware_read_order(floor, button)) {
                hardware_command_order_light (floor, button, 1);
                addRequest (floor, button);
            }
        }
    }
}









#endif // #ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__


