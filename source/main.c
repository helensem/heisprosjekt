#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include <unistd.h>
#include "queue.h"
#include "elevator_controller.h"
#include "timer.h"
#include "driver/io.h"


/*static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}
*/

//legg inn global variabel direction
//legg inn at heisen må flytte seg til en etasje for å få state idle 





int main(){

    printf("hei\n");

    int error = hardware_init();
    printf("asd");
    if(error != 0){
        printf("unable to initialize\n");
        fprintf(stderr, "Unable to initialize hardware\n");
        
        exit(1);
    }else{
        printf("able to initizlize\n");
    }

    //signal(SIGINT, sigint_handler);

    printf("Elevator starting\n");



    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    Direction current_dir = UP;
    int floor = -1;
    while(floor==-1) {
        floor= get_current_floor();
    
    }

    printf("ute av while\n");

    
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
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
        floor = get_current_floor();
        printf ("floor is %d\n", floor);
        printf ("current floor is %d\n", current_floor.floor);
        if(floor != current_floor.floor && floor != -1) {
            current_floor.floor = floor;  //Dette bør fikse problemet med at current floor ikke blir -1.
            current_floor.above = 0;
        }
        if (floor == -1) {
            current_floor.above = 1;
        }

        printf ("is above %d\n", current_floor.above);

        //if(current_floor.floor == -1) {
          //  current_state = IDLE;
            //current_floor.floor = 3; 
       // }

        print_orders ();

        //print_orders();
        
        get_next_order(&current_floor, &current_dir, &next_floor);
        printf ("next floor is %d\n", next_floor);

        
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
            }
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
                add_order(f, HARDWARE_ORDER_INSIDE);
            }
            /* Orders going up */
            else if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
                add_order(f, HARDWARE_ORDER_UP);
            }
            
            /* Orders going down */
            else if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
                add_order(f, HARDWARE_ORDER_DOWN);
            }
            /* Internal orders */
        }


        if(hardware_read_floor_sensor(3)) {
            current_dir = DOWN;
        }

        if(hardware_read_floor_sensor(0)){
            current_dir = UP;
        }

       
        switch(current_state) {
            case IDLE:
                idle(&current_state, &current_dir, &current_floor, &next_floor);
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

    


        /* All buttons must be polled, like this: */
       

    return 0;
}
