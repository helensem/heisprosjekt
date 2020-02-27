


#include "queue.h"


static int up_orders [HARDWARE_NUMBER_OF_FLOORS];
static int down_orders [HARDWARE_NUMBER_OF_FLOORS];


void add_order(int floor, HardwareOrder button) {
    switch (button) {
        case HARDWARE_ORDER_INSIDE:
            up_orders[floor] = 1;
            down_orders[floor] = 1;
            break;
        case HARDWARE_ORDER_DOWN:
            down_orders[floor] = 1;
            break;
        case HARDWARE_ORDER_UP:
            up_orders[floor] = 1;
            break;
        default:
            break;
    }
}


int get_order_in_current_direction(int floor, Direction *p_current_dir) {
    if (*p_current_dir == UP) {
        for (int f = floor; f < HARDWARE_NUMBER_OF_FLOORS; f++) {
            if (up_orders[f]) {
                return f;
            }
        }
        if (down_orders [HARDWARE_NUMBER_OF_FLOORS-1] == 1){
            return 3;
        }
    }
    else if ((*p_current_dir) == DOWN){
        for (int f = floor; f>=0; f--) {
            if (down_orders[f]) {
                return f;
            }
        }
        if (up_orders[0]) {
            return 0;
        }
    }
    return -1;
}

void get_next_order(Floor *p_current_floor, Direction *p_current_dir, int *p_next_floor) {
    *p_next_floor = get_order_in_current_direction(p_current_floor->floor, p_current_dir);
    if (*p_next_floor==-1) {
        if (*p_current_dir==UP){
            *p_current_dir = DOWN;
            *p_next_floor = get_order_in_current_direction(HARDWARE_NUMBER_OF_FLOORS-1, p_current_dir);
            return;
        }
        else if (*p_current_dir == DOWN){
            *p_current_dir = UP;
            *p_next_floor = get_order_in_current_direction (1, p_current_dir);
            return;
        }
    }
    return;
}

int check_floor_for_orders(int floor, Direction dir) {
    if (dir == UP){
        if (hardware_read_floor_sensor(floor) && (up_orders[floor])){
            return 1;
         }
    }
    if (dir == DOWN) {
        if (hardware_read_floor_sensor(floor) && (down_orders[floor]))
        return 1; 
    }
    return 0;
}


void remove_order(int floor) {
    up_orders[floor]=0;
    down_orders[floor]=0;
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
    return;
}



void clear_all_orders() {
    for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        up_orders[f] = 0;
        down_orders[f] = 0;
    }
    return;
}

