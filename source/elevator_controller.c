
#ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__
#define __INCLUDE_ELEVATOR_CONTROLLER_H__

#include <stdio.h>
#include "elevator_controller.h"
#include <unistd.h>
#include "hardware.h"

//legg inn enda mer sikkerhet 



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

int current_floor = get_current_floor ();
int next_floor = getNextRequest (current_floor, HARDWARE_MOVEMENT_UP);
//usikker på om globale variabler her eller i main. Må det referanse på disse?


void emergency_stop () {
    hardware_command_movement (HARDWARE_MOVEMENT_STOP);
    clear_all_order_lights();
    clear_all (); //mulighet for å ta denne ut av funksjonen og sette inn etter (for clean slate)
    hardware_command_stop_light (1);
    if (current_floor!=-1) {
        hardware_command_door_open (1);
    }
    if (!hardware_read_stop_signal ()) {
        hardware_command_stop_light (0);
        current_state = IDLE;
    }
    
}

// Kan være noe problem med get_current floor i tilfelle heisen er i midten 
void idle () {
    if (current_floor == -1) {
        hardware_command_movement (HARDWARE_MOVEMENT_DOWN);
    }
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

void door_opening () {
    if (current_floor != -1){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_order_light(current_floor, HARDWARE_ORDER_INSIDE, 0);
    hardware_command_door_open (1);
    }
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
        hardware_command_door_open (0);
        current_state = IDLE;
    } 
}

void moving_up () {
    hardware_command_movement (HARDWARE_MOVEMENT_UP);
    if (hardware_read_floor_sensor(next_floor) && (getRequest(next_floor,HARDWARE_ORDER_DOWN)||getRequest(next_floor,HARDWARE_ORDER_INSIDE)|| getRequest (next_floor, HARDWARE_MOVEMENT_UP)) {
        current_state = DOOR_OPENED; 
    } 
    if (hardware_read_floor_sensor(3)&& requests [3][HARDWARE_ORDER_DOWN]==0 &&requests [3][HARDWARE_ORDER_INSIDE]==0 ) {
        current_state = IDLE;
    }
    if (hardware_read_stop_signal ()) {
        current_state = STOP; 
    }
}

void moving_down () {
  hardware_command_movement (HARDWARE_MOVEMENT_DOWN);
    if (hardware_read_floor_sensor(next_floor) && (getRequest(next_floor,HARDWARE_ORDER_DOWN)||getRequest(next_floor,HARDWARE_ORDER_INSIDE)|| getRequest (next_floor, HARDWARE_MOVEMENT_UP)) {
        current_state = DOOR_OPENED; 
    } 
    if (hardware_read_floor_sensor(0)&& requests [0][HARDWARE_ORDER_UP]==0 && requests [0][HARDWARE_ORDER_INSIDE]==0 ) {
        current_state = IDLE;
    }
    if (hardware_read_stop_signal ()) {
        current_state = STOP; 
    }  
}

void request_control (){    //Brukte eksempelet i main til å lage
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        /* Internal orders */
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
            hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
            addRequest (f, HARDWARE_ORDER_INSIDE);
        }
        
        /* Orders going up */
        if(hardware_read_order(f, HARDWARE_ORDER_UP)){
            hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
            addRequest (f, HARDWARE_ORDER_UP);
        }
        
        /* Orders going down */
        if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
            hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
            addRequest (f, HARDWARE_ORDER_DOWN);
        }
    }


void elevator_controller (state &current_state) { //Her må det hvertfall brukes referanse right?
    switch (current_state) {
        case IDLE:
            idle();
            break;
        case STOP:
            emergency_stop ();
            //clear_all ();  alternativ til at den ikke tar inn noen ordre mens i stop
            //clear_all_order_lights ();
            break;
        case DOOR_OPENED:
            door_opening ();
            break;
        case MOVING_UP:
            moving_up ();
            break;
        case MOVING_DOWN:
            moving_down ();
            break;
        default:
            break;
    }
    
}









#endif // #ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__


