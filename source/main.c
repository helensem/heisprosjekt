#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <unistd.h>
#include "queue.h"
#include "elevator_controller.h"
#include "timer.h"


static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}


//legg inn global variabel direction
//legg inn at heisen må flytte seg til en etasje for å få state idle 

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

    printf("Elevator starting");
    
    current_stare = IDLE;
    

    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    dir = DOWN;
    int floor = -1;
    while (floor==-1) {
        floor = get_current_floor ();
    }
    hardware_command_movement (HARDWARE_MOVEMENT_STOP);
    current_floor.floor = floor;
    current_floor.above = 0;
    
    
   /* static int m_global;
    void update_int (int *p_m_global) {
        *p_m = tall;
    }
    
    update_int (&m_global);*/
    
    //få inn pekere :)
    

    while(1){
        floor = get_current_floor ();
        if (floor != -1) {
            current_floor = floor;
        }
        
        get_next_order (&next_floor);
        
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
            }
        }
        
        request_control ();
        
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
    


        /* All buttons must be polled, like this: */
       

    return 0;
}
