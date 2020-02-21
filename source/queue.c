

#include "queue.h"

//lage egen array for down og up orders med N_FLOORS

static int up_orders [N_FLOORS];
static int down_orders [N_FLOORS];


void add_order(int floor, HardwareOrder button) {
    if (button == HARDWARE_ORDER_INSIDE) {
        up_orders [floor] = 1;
        down_orders [floor] = 1;
    }
    else if (button==HARDWARE_ORDER_UP) {
        up_orders [floor] = 1;
    }
    else if (button == HARDWARE_ORDER_DOWN) {
        down_orders [floor] = 1;
    }
}



//fuck me, gjør den enkler for gad dammit.
void get_next_order (int floor, Direction dir, int *p_next_floor) {
    if (dir == UP) {
        for (int f = floor; f < N_FLOORS; f++) {
            if (up_orders [floor]) {
                *p_next_floor = f;
                return;
            }
        }
    }
    if (dir == DOWN) {
        for (int f = floor; f>=0; f--) {
            if (down_orders [f]) {
                *p_next_floor=f;
                return;
            }
        }
    }
}


void remove_order(int floor) {
    up_orders [floor]=0;
    down_orders [floor]=0;
}



void clear_all() {
    for (int f = 0, f < N_FLOORS; f++){
        up_orders [f] = 0;
        down_orders [f] = 0;
    }
}




