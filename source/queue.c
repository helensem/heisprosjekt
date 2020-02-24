


#include "queue.h"

//lage egen array for down og up orders med N_FLOORS


//disse fungerere rett og slett litt enklere enn en matrise


int up_orders [N_FLOORS];
int down_orders [N_FLOORS];


void add_order(int floor, HardwareOrder button) {
    if (button == HARDWARE_ORDER_INSIDE) {  //En bestilling på innsiden kan legges inn i begge
        up_orders[floor] = 1;
        down_orders[floor] = 1;
    }
    else if (button==HARDWARE_ORDER_UP) {
        up_orders[floor] = 1;
    }
    else if (button == HARDWARE_ORDER_DOWN) {
        down_orders[floor] = 1;
    }
}


//fuck me, gjør den enkler for gad dammit.
void get_next_order(Floor *p_current_floor, Direction *p_current_dir, int *p_next_floor) { //Legg merke til at next_floor er en peker, dette er for at vi kan oppdatere den enklere, vi tar inn referanse av next_floor og da kan den endre seg uten at vi må tilordne den noe. Da slipper vi også noe stress med at next_floor blir minus 1.
    if ((*p_current_dir) == UP) {
        for (int f = (*p_current_floor).floor; f < N_FLOORS; f++) {
            if (up_orders[f]) {
                *p_next_floor = f;
                return;
            }
        }
    }
    else if ((*p_current_dir) == DOWN) {
        for (int f = (*p_current_floor).floor; f>=0; f--) {
            if (down_orders[f]) {
                *p_next_floor=f;
                return;
            }
        }
    }
    else {
        *p_next_floor = floor;
    }
}


void remove_order(int floor) {
    up_orders[floor]=0;
    down_orders[floor]=0;
}



void clear_all_orders() {
    for (int f = 0; f < N_FLOORS; f++){
        up_orders [f] = 0;
        down_orders [f] = 0;
    }
}




