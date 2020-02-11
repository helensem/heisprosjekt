

#include "queue.h"

void addRequest(floor_nr floor, order_type button) {
    requests [floor][button] = 1;
}

int getRequest(floor_nr floor, order_type button) {
    return requests [floor][button];
}

int getNextRequest(floor_nr current_floor, elev_motor_direction_t dir){
    int next_floor = current_floor;
    
    
    switch (dir) {
        case DIRN_UP:
            while (next_floor < N_FLOORS + 1 ) {
                next_floor++;
                if (requests [next_floor][OUTSIDE_UP]==1||requests[next_floor][INSIDE_CALL] ==1){
                    return next_floor;
                }
            }
            break;
            
        case DIRN_DOWN:
            while (next_floor > 0) {
                next_floor--;
                if (requests [next_floor][OUTSIDE_DOWN]==1||requests[next_floor][INSIDE_CALL] ==1)
                    return next_floor;
            }
            break;
    }
}

void removeRequest(floor_nr floor, elev_motor_direction_t dirn) {
    requests [floor][INSIDE_CALL] = 0;
    switch (dirn) {
        case DIRN_DOWN:
            requests [floor][OUTSIDE_DOWN] = 0;
            break;
            
        case DIRN_UP:
            requests [floor][OUTSIDE_UP] = 0;
            break;
    }
}


void clear_all () {
    for (int i = 1, i < 5; i++){
        requests [i][OUTSIDE_UP] = 0;
        requests [i][OUTSIDE_DOWN]= 0;
        requests [i][INSIDE_CALL] = 0;
    }
}




