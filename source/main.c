#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <unistd.h>
#include "queue.h"
#include "elevator_controller.h"
#include "timer.h"


/*static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}
*/

//legg inn global variabel direction
//legg inn at heisen må flytte seg til en etasje for å få state idle 

int main(int argc, char *argv[]){

    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    //signal(SIGINT, sigint_handler);

    printf("Elevator starting");



    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    static Direction current_dir = DOWN;
    int floor = -1;
    while (floor==-1) {
        floor = get_current_floor ();
    }
    hardware_command_movement (HARDWARE_MOVEMENT_STOP);
    static State current_state = IDLE;
    static Floor current_floor; 
    current_floor.floor = floor;
    current_floor.above = 0;
    int next_floor = floor;
    
    
   /* static int m_global;
    void update_int (int *p_m_global) {
        *p_m = tall;
    }
    
    update_int (&m_global);*/
    
    //få inn pekere :)

    while(1){
        floor = get_current_floor ();
        if (floor == current_floor.floor) {
            current_floor.floor = floor;  //Dette bør fikse problemet med at current floor ikke blir -1.
            current_floor.above = 0;
        }

        //print_orders ();
        
        get_next_order (&current_floor, &current_dir, &next_floor);

        
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
            }
        }

        if (hardware_read_floor_sensor (0)){
            current_dir = UP;
        }

        if (hardware_read_floor_sensor(3)) {
            current_dir = DOWN;
        }

         for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
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
        /* Internal orders */
        
         }


       
        switch (current_state) {
            case IDLE:
                idle(&current_state, &current_dir, &current_floor, &next_floor);
                break;
            case STOPPING:
                emergency_stop (&current_floor, &current_state);
                clear_all_orders (); 
                clear_all_order_lights ();
                break;
            case DOOR_OPENED:
                door_opening (&current_state, &current_floor);
                break;
            case MOVING_UP:
                moving_up (&current_state, &next_floor);
                break;
            case MOVING_DOWN:
                moving_down (&current_state, &next_floor);
                break;
            default:
                break;
        }
        
    }
    


        /* All buttons must be polled, like this: */
       

    return 0;
}
