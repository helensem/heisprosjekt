


#include "queue.h"

//lage egen array for down og up orders med N_FLOORS


//disse fungerere rett og slett litt enklere enn en matrise


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


//fuck me, gjør den enkler for gad dammit.
int queue_next(Floor *p_current_floor, Direction *p_current_dir) { //Legg merke til at next_floor er en peker, dette er for at vi kan oppdatere den enklere, vi tar inn referanse av next_floor og da kan den endre seg uten at vi må tilordne den noe. Da slipper vi også noe stress med at next_floor blir minus 1.
    int next_floor;
    if ((*p_current_dir) == UP) {
        for (int f = (*p_current_floor).floor +1; f < HARDWARE_NUMBER_OF_FLOORS; f++) {
            if (up_orders[f]) {
                next_floor = f;
                return next_floor;
            }
        }
        if (down_orders [HARDWARE_NUMBER_OF_FLOORS-1] ==1){
            return 3;
        }
    }
    else if ((*p_current_dir) == DOWN){
        for (int f = (*p_current_floor).floor-1; f>=0; f--) {
            if (down_orders[f]) {
                next_floor=f;
                return next_floor;
            }
        }
        if (up_orders[0]) {
            return 0;
        }
    }
    return -1;
}

void get_next_order(int *p_next_floor, Direction *p_current_dir, Floor *p_current_floor) {
    *p_next_floor = get_next_in_queue ((*p_current_floor).floor, *p_current_dir);
    if ((*p_next_floor)==-1) {
        if ((*p_current_dir)==UP){
            *p_current_dir = DOWN;
            *p_next_floor = queue_next(HARDWARE_NUMBER_OF_FLOORS-1, *p_current_dir);
            return;
        }
        else if (*p_current_dir == DOWN){
            *p_current_dir = UP;
            *p_next_floor = queue_next (0, *p_current_dir);
            return;
        }
    }
    return;
}


void remove_order(int floor) {
    up_orders[floor]=0;
    down_orders[floor]=0;
    return;
}



void clear_all_orders() {
    for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        up_orders [f] = 0;
        down_orders [f] = 0;
    }
    return;
}

void print_orders (){
    for (int f = 0; f < N_FLOORS; f++){
        printf ("%d\t", up_orders [f]);
        printf ("\n");
        printf ("%d\t", down_orders[f]);
        printf ("\n");
    }
    return;
}


