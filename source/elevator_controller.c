

#include <stdio.h>
#include "elevator_controller.h"
#include <unistd.h>
#include "queue.h"



void emergency_stop(Floor *p_current_floor, State *p_current_state) {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    clear_all_order_lights();
    clear_all_orders();
    hardware_command_stop_light(1);
    if (p_current_floor->above==0) {
        hardware_command_door_open(1);
        if (!hardware_read_stop_signal()) {  
            hardware_command_stop_light(0);
            *p_current_state = DOOR_OPENED;
            return;
        }
    }
    if (!hardware_read_stop_signal()) {
        hardware_command_stop_light(0);
        *p_current_state = IDLE;
        return;
    }
}

void idle(State *p_current_state, Floor *p_current_floor, int *p_next_floor){  
    if (hardware_read_stop_signal()) {
        *p_current_state = STOPPING;
        return;
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    if (*p_next_floor < p_current_floor->floor && *p_next_floor!= -1 ){
        if (p_current_floor->above == 0) {
        (*p_current_floor).floor--;
        p_current_floor->above = 1;
        }
        *p_current_state = MOVING_DOWN;
        return;
    }
    else if(*p_next_floor > p_current_floor->floor && *p_next_floor!= -1) {
         *p_current_state = MOVING_UP;
         return;
    }
    else if (*p_next_floor == p_current_floor->floor && *p_next_floor!= -1){
         if (p_current_floor->above ==1) { 
             *p_next_floor=p_current_floor->floor;
             *p_current_state = MOVING_DOWN;
             return;
             }
        else {
            *p_current_state = DOOR_OPENED;
            return;
             }
    }
    else{
        *p_current_state = IDLE;
        return;
    }
}

void door_opening(State *p_current_state, Floor *p_current_floor) {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_door_open(1);
    remove_order(p_current_floor->floor);
    if (hardware_read_stop_signal()) {
        reset_timer();
        *p_current_state = STOPPING;
        return;
    }
    if (check_timer()){
            hardware_command_door_open(0);
            *p_current_state = IDLE;
            return;
        }
    }
    

void moving_up(Floor *p_current_floor, State *p_current_state, int *p_next_floor) {
    hardware_command_movement (HARDWARE_MOVEMENT_UP);
    if (hardware_read_floor_sensor(*p_next_floor)){
        *p_current_state = DOOR_OPENED;
        return;
    }
    if (hardware_read_stop_signal()) {
        *p_current_state = STOPPING;
        return;
    }
    if (check_floor_for_orders(p_current_floor->floor,UP)) {
        *p_current_state = DOOR_OPENED;
        return;
    }
}

void moving_down(Floor *p_current_floor, State *p_current_state, int *p_next_floor) {
    hardware_command_movement (HARDWARE_MOVEMENT_DOWN);
    if (hardware_read_floor_sensor(p_current_floor->floor)&&(!check_floor_for_orders(p_current_floor->floor, DOWN))){
        (*p_current_floor).floor --;
    }
    if (hardware_read_floor_sensor((*p_next_floor))) {
        *p_current_state = DOOR_OPENED;
        return;
    } 
    if (hardware_read_stop_signal()) {
        *p_current_state = STOPPING;
        return;
    }  
    if (check_floor_for_orders(p_current_floor->floor,DOWN)) {
        *p_current_state = DOOR_OPENED;
        return;
    }
}











