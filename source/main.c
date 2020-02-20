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
    
    

    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    
    state elevator_state = IDLE;

    while(1){
        
        int elevator_floor = get_current_floor ();
        int elev_next_floor = getNextRequest (current_floor, HARDWARE_MOVEMENT_UP);
        
        
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
            }
        }
        
        
        elevator_controller (elevator_state);
        request_control ();


        /* All buttons must be polled, like this: */
       

    return 0;
}
