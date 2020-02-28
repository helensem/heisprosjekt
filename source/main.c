#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <unistd.h>
#include "queue.h"
#include "elevator_controller.h"
#include "timer.h"
#include "driver/io.h"




int main(){



    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }


    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    Direction current_dir = UP;
    int floor = -1;
    while(floor==-1) {
        floor = get_current_floor();
    }
    
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    static State current_state = IDLE;
    static Floor current_floor; 
    current_floor.floor = floor;
    current_floor.above = 0;
    int next_floor = floor;

    clear_all_order_lights();

    while(1){
        floor = get_current_floor();
        if(floor != -1 && current_state !=MOVING_DOWN) {
            current_floor.floor = floor; 
            current_floor.above = 0;
        }
        if (floor == -1) {
            current_floor.above = 1;
        }
        
        get_next_order(&current_floor, &current_dir, &next_floor);

        
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
            }
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
                add_order(f, HARDWARE_ORDER_INSIDE);
            }
    
            else if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
                add_order(f, HARDWARE_ORDER_UP);
            }
            
            else if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
                add_order(f, HARDWARE_ORDER_DOWN);
            }
        }


        if(hardware_read_floor_sensor(3)) {
            current_dir = DOWN;
        }

        if(hardware_read_floor_sensor(0)){
            current_dir = UP;
        }

       
        switch(current_state) {
            case IDLE:
                idle(&current_state, &current_floor, &next_floor);
                break;
            case STOPPING:
                emergency_stop(&current_floor, &current_state);
                break;
            case DOOR_OPENED:
                door_opening(&current_state, &current_floor);
                break;
            case MOVING_UP:
                moving_up(&current_floor, &current_state, &next_floor);
                break;
            case MOVING_DOWN:
                moving_down(&current_floor, &current_state, &next_floor);
                break;
            default:
                break;
        }
    }

    return 0;
}
