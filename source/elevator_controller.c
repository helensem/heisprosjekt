
#ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__
#define __INCLUDE_ELEVATOR_CONTROLLER_H__

#include <stdio.h>
#include "elevator_controller.h"



void emergency_stop () {
    hardware_command_movement (HARDWARE_MOVEMENT_STOP);
    clear_all (); //mulighet for å ta denne ut av funksjonen og sette inn etter (for clean slate)
    hardware_command_stop_light (1);
    if (get_current_floor!=-1) {
        hardware_command_door_open (1);
    }
    
}

int get_current_floor () {
    if (io_read_bit(SENSOR_FLOOR1))
        return 0;
    else if (io_read_bit(SENSOR_FLOOR2))
        return 1;
    else if (io_read_bit(SENSOR_FLOOR3))
        return 2;
    else if (io_read_bit(SENSOR_FLOOR4))
        return 3;
    else
        return -1;
}




#endif // #ifndef __INCLUDE_ELEVATOR_CONTROLLER_H__


