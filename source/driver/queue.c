

#include "queue.h"

void addRequest(int floor, HardwareOrder button) {
    if (hardware_read_order(floor, button)){
        requests [floor-1][button] = 1;
    }
}

int getRequest(int floor, HardwareOrder button) {
    return requests [floor-1][button];
}

int getNextRequest(int current_floor, HardwareMovement dir){
    int next_floor = current_floor;
    int run_count = 0;
    if (run_count < 2) {
    switch (dir) {
        case HARDWARE_MOVEMENT_UP:
            while (next_floor < N_FLOORS + 1 ) {
                next_floor++;
                if (requests [next_floor-1][HARDWARE_ORDER_UP]==1||requests[next_floor-1][HARDWARE_ORDER_INSIDE] ==1){
                    run_count = 0;
                    return next_floor;
                }
                if (next_floor > 3){
                    run_count ++;
                    getNextRequest (current_floor, HARDWARE_MOVEMENT_DOWN);
                }
            }
            break;
            
        case HARDWARE_MOVEMENT_DOWN:
            while (next_floor > 0) {
                next_floor--;
                if (requests [next_floor-1][HARDWARE_ORDER_DOWN]==1||requests[next_floor-1][HARDWARE_ORDER_INSIDE] ==1){
                    run_count = 0;
                return next_floor;
            }
                if (next_floor <= 1){
                    run_count ++;
                    getNextRequest (current_floor, HARDWARE_MOVEMENT_UP);
                }
            }
            
            break;
       }
    }
    return -1;
}

void removeRequest(int floor) {
    requests [floor-1][HARDWARE_ORDER_UP] = 0;
    requests [floor-1][HARDWARE_MOVEMENT_DOWN]= 0;
    requests [floor-1][HARDWARE_ORDER_INSIDE] = 0;
    



void clear_all () {
    for (int i = 0, i < 4; i++){
        requests [i][HARDWARE_ORDER_UP] = 0;
        requests [i][HARDWARE_MOVEMENT_DOWN]= 0;
        requests [i][HARDWARE_ORDER_INSIDE] = 0;
    }
}




