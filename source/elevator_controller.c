

#include <stdio.h>
#include "elevator_controller.h"
#include <unistd.h>
#include "queue.h"


//legg inn enda mer sikkerhet

//Dersom structene og enumene skal brukes i main av globale variabler, må de i header-fil eller c fila?

//globale variabler for heisens state
 //vet ikke hvor jeg skal putte diise (main?)

int get_current_floor() {
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

//I elevator controller har vi rett og slett oversatt FSM-diagrammet til koden. I main vil vi finne en switch case for hver state. For hver state har vi en tilhørende funksjon. Der de første linjene for hver funksjon sier noe om hva som skal gjøres (stoppe motor, sette på lys, kjøre opp/ned f.eks) if-setningene er conditionene våre (eller pilene på FSM diagrammet) og hva som skal skje for at vi skal bytte state. Dermed vil heisen da hele tiden hoppe mellom de ulike statene (forhåpentligvis)


void emergency_stop(Floor *p_current_floor, State *p_current_state) {                                     //tilhørende til STOP state, altså emergency-stop kun (vanlig stopp på etasjer er i DOOR_OPENED).
    hardware_command_movement (HARDWARE_MOVEMENT_STOP); //MOTOREN STOPPES
    clear_all_order_lights();
 //mulighet for å ta denne ut av funksjonen og sette inn etter (for clean slate)
    //LEGGE INN NOE HER FOR AT HEISEN IKKE SKAL TA INN BESTILLINGER
    
    hardware_command_stop_light (1); //LYSET SLÅR SEG PÅ
    if ((*current_floor).floor!=-1 && (*current_floor).above==0) {
        hardware_command_door_open (1);  //DERSOM VI ER PÅ EN ETASJE, SÅ SKAL DØREN ÅPNE SEG
        if (!hardware_read_stop_signal()) {  //DERSOM DØREN ER ÅPEN OG STOPSIGNALET BRYTES, SKAL VI TIL DOOR_OPENED
            (*p_current_state) = DOOR_OPENED;
            return;
        }
    }
    if (!hardware_read_stop_signal ()) { //ELLERS SKAL VI TIL IDLE
        hardware_command_stop_light (0);
        (*p_current_state) = IDLE;
        return;
    }
}

void idle (State *p_current_state, Direction *p_current_dir, Floor *p_current_floor, int *p_next_floor) {  //Funskjon tilhørende idle state. Start-tilstand til heisen. Heisen er i ro og leter etter bestillinger, og bestemmer om den skal kjøre opp, ned eller forbli i ro
    if (hardware_read_stop_signal()) {  //ALLTID HA EN READ_STOP I ALLE TILSTANDER
        (*p_current_state) = STOPPING;
        return;
    }
    hardware_command_movement (HARDWARE_MOVEMENT_STOP); //MOTOREN MÅ STOPPES SÅNN I TILFELLE
    if ((*p_next_floor) < (*p_current_floor).floor){ //DERSOM NEXT_FLOOR ER UNDER CURRENT_FLOOR, SKAL HEISEN KJØRE NED
        (*p_current_floor).floor--;
        (*p_current_floor).above = 1;   //LEGG OGSÅ MERKE TIL AT CURRENT_FLOOR DEKREMENTERES OG ABOVE SETTER TIL 1, FORDI DA ER VI JO OVER ETASJEN UNDER, BASICALLY
        (*p_current_dir) = DOWN; //DIRECTION MÅ SETTES NED
        (*p_current_state) = MOVING_DOWN;  //ALT DETTE KAN TEKNISK SETTES INN I MOVING_DOWN, MEN DET ER VEL LITT HIPP SOM HAPP (håper jeg)
        return;
    }
    else if ((*p_next_floor) > (*p_current_floor).floor) { //SAME PROCEDURE, BARE AT NEXT_FLOOR ER OVER, OG VI FLYTTER OSS OPP
        (*p_current_dir) = UP;
        (*p_current_floor).above = 1;
        (*p_current_state) = MOVING_UP;
         return;//sett inn return hver gang du switcher state, for å slippe at funksjonen fortsetter nedover
    }
    else if (next_floor == current_floor.floor){ //I FUNKSJONEN GET_NEXT_REQUEST VIL NEXT_FLOOR ALLTID SETTES TIL CURRENT_FLOOR DERSOM DET IKKE ER NOE BESTILLINGER, VI BLIR DER VI ER
        (*p_current_state) = IDLE;
        return;
    }
}

void door_opening(State *p_current_state, Floor *p_current_floor) { //FUNKSJON TIL DOOR OPENING
    hardware_command_movement(HARDWARE_MOVEMENT_STOP); //STOPP HEISEN
    hardware_command_order_light((*p_current_floor).floor, HARDWARE_ORDER_INSIDE, 0); //VI FJERNER ORDER_LIGHTS (ELLER PUTTE DEN I REMOVER order?)
    hardware_command_order_light (*p_current_floor).floor, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light (*p_current_floor).floor, HARDWARE_ORDER_DOWN, 0);
    hardware_command_door_open (1); //DØREN ÅPNER SEG
    remove_order ((*p_current_floor).floor);
    if (hardware_read_stop_signal()) { //stop må som vanlig være her
        (*p_current_state) = STOPPING;
        return;
    }
    if (!hardware_read_obstruction_signal ()){  //litt usikker på om dette vil funke riktig :) basically hvis obstruksjon ikke leses, så fortsetter vi sånn vi vil fortsette som vanlig
        start_timer (); //Timer starter
        if (check_timer()){ //hvis timeren er ferdig, så er vi tilbake på idle
            hardware_command_door_open (0);
            (*p_current_state) = IDLE;
            return;
        }
    }
    else { //hvis obstruction signal leses, så blir heisen værende i door opened.
        (*p_current_state) = DOOR_OPENED;
        return;
    }
}

void moving_up(State *p_current_state) {
    hardware_command_movement (HARDWARE_MOVEMENT_UP);
    if (hardware_read_floor_sensor(next_floor)) { //Vi beveger oss opp til vi finner next floor
        (*p_current_state) = DOOR_OPENED;
        return;
    }
    if (hardware_read_stop_signal ()) {
        (*p_current_state) = STOPPING;
        return;
    }
}

void moving_down(State *p_current_state) { //same as ususal
    hardware_command_movement (HARDWARE_MOVEMENT_DOWN);
    if (hardware_read_floor_sensor(next_floor)) {
        (*p_current_state) = DOOR_OPENED;
        return;
    } 
    if (hardware_read_stop_signal ()) {
        (*p_current_state) = STOPPING;
        return;
    }  
}











