
#ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__
#define __INCLUDE_ELEVATOR_CONTROLLER_H__

#include <stdio.h>
#include "elevator_controller.h"
#include <unistd.h>
#include "hardware.h"

//legg inn enda mer sikkerhet



static state current_state;
static Floor current_floor;
static Direction current_dir

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


//usikker på om globale variabler her eller i main. Må det referanse på disse?


void emergency_stop () {
    hardware_command_movement (HARDWARE_MOVEMENT_STOP);
    clear_all_order_lights();
    clear_all (); //mulighet for å ta denne ut av funksjonen og sette inn etter (for clean slate)
    hardware_command_stop_light (1);
    if (current_floor!=-1) {
        hardware_command_door_open (1);
        if (!hardware_read_stop_signal()) {
            current_state = DOOR_OPENED;
            return;
        }
    }
    if (!hardware_read_stop_signal ()) {
        hardware_command_stop_light (0);
        current_state = IDLE;
        return;
    }
    
}

// Kan være noe problem med get_current floor i tilfelle heisen er i midten 
void idle () {
    if (hardware_read_stop_signal) {
        current_state = STOP;
        return;
    }
    
    hardware_command_movement (HARDWARE_MOVEMENT_STOP);
    if (next_floor!=-1) {
        if (next_floor < current_floor.floor){
            current_floor.floor--;
            current_floor.above = 1;
            dir = DOWN;
            current_state = MOVING_DOWN;
            return;
        }
        if (next_floor > current_floor.floor) {
            dir = UP;
            current_floor.above = 1;
            current_state = MOVING_UP;
            return;//sett inn return hver gang du switcher state
        }
        if (next_floor == current_floor.floor){
            current_state = IDLE;
            return;
        }
    }
}

void door_opening () {
    if (current_floor.floor != -1){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_order_light(current_floor.floor, HARDWARE_ORDER_INSIDE, 0);
    hardware_command_door_open (1);
    }
    remove_order (current_floor.floor);
    if (!hardware_read_obstruction_signal ()){  //litt usikker på om dette vil funke riktig :)
        start_timer ();
        if (check_timer()){
            hardware_command_door_open (0);
            current_state = IDLE;
            return;
    }
    } 
}

void moving_up () {
    hardware_command_movement (HARDWARE_MOVEMENT_UP);
    if (hardware_read_floor_sensor(next_floor)) {
        current_state = DOOR_OPENED;
        return;
    } 
    if (hardware_read_floor_sensor(3)&& down_orders[3]==0 ) {
        current_state = IDLE;
        return;
    }
    if (hardware_read_stop_signal ()) {
        current_state = STOP;
        return;
    }
}

void moving_down () {
    hardware_command_movement (HARDWARE_MOVEMENT_DOWN);
    if (hardware_read_floor_sensor(next_floor) {
        current_state = DOOR_OPENED;
        return;
    } 
    if (hardware_read_floor_sensor(0)&& up_orders [0] ==0) {
        current_state = IDLE;
        return;
    }
    if (hardware_read_stop_signal ()) {
        current_state = STOP;
        return;
    }  
}

void request_control (){    //Brukte eksempelet i main til å lage
    for(int f = 0; f < N_FLOORS; f++){
        /* Internal orders */
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
            hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
            add_order(f, HARDWARE_ORDER_INSIDE);
        }
        
        /* Orders going up */
        if(hardware_read_order(f, HARDWARE_ORDER_UP)){
            hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
            add_order(f, HARDWARE_ORDER_UP);
        }
        
        /* Orders going down */
        if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
            hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
            add_order(f, HARDWARE_ORDER_DOWN);
        }
    }


void elevator_controller (state current_state) { //Her må det hvertfall brukes referanse right?
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


