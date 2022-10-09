/******************************************************************************
** Course: Imperative Programming - Assignment 2
** Authors: Jeroen Brinkhorst [S1101799]
**          Andrei Ujica [S1102725]
** Date: 15.09.2022
******************************************************************************/

#include "assignments/assignment2.h"
#include "framework/charles.h"

/******************************************************************************
** Function Prototypes
******************************************************************************/

void check_what_direction_path_takes();
void walk_to_path_corner();
void face_the_opposite_direction();
void face_east();

void put_column_of_balls();
void walk_to_wall();
void walk_to_opposite_corner();

void walk_to_ball();
void find_center_of_axis(bool vertical);


/******************************************************************************
** Exercises
******************************************************************************/

void test_agent() {

}

void path_agent() {
    while (on_ball()){
        walk_to_path_corner();
        check_what_direction_path_takes();
    }

    // Position Charles on the last ball, facing East
    step();
    face_east();
}

void cave_agent() {
    step();
    while(!in_front_of_wall()){
        put_column_of_balls();
        step();
    }    

    walk_to_opposite_corner();
}

void find_center_agent() {
    // Find Center of the Horizontal Axis, set vertical parameter to false
    find_center_of_axis(false);

    // Find Center of the Horizontal Axis, set vertical parameter to true
    find_center_of_axis(true);
}

void clean_up_agent() {

}

/******************************************************************************
** Function Definitions
******************************************************************************/

void walk_to_path_corner(){
    while(on_ball()){
        step();
    }

    // In order to know that we are not on the path anymore, we need to go out of the path
    // so this snippet just moves us back to the path corner, facing back the way we came.
    face_the_opposite_direction();
    step();
}

void check_what_direction_path_takes(){
    // If we got to a corner then the path cannot continue in front/behind Charles
    // so we just check left and right sides for the continuation of the path.
    
    // Check Left Side
    turn_left();
    step();
    if(!on_ball()){
        //Check Right Side
        face_the_opposite_direction();
        step();
        step();
        if (!on_ball())
            // We are at the end, just position Charles for coming back 
            face_the_opposite_direction();
        }
}

void face_the_opposite_direction(){
    turn_left();
    turn_left();
}

void face_east(){
    while(!north())
        turn_left();
    turn_right();
}

void face_south(){
    face_east();
    turn_right();
}

void find_center_of_axis(bool vertical){
    
    if(vertical){
        face_south();
        step();
        walk_to_ball();
    }

    while(!on_ball()){
        put_ball();
        step();
        walk_to_ball();
    }
}

void put_column_of_balls(){
    turn_right();

    while(!in_front_of_wall()){
        put_ball();
        step();
    }

    put_ball();
    face_the_opposite_direction();
    walk_to_wall();
    turn_right();
}

void walk_to_wall(){
    while(!in_front_of_wall())
        step();
}

void walk_to_opposite_corner(){
    // Because the function is run 2 times, we need to move Charles to 
    // the mirrored corner
    turn_right();
    walk_to_wall();
    turn_right();
}

void walk_to_ball(){
    while(!on_ball() && !in_front_of_wall())
        step();
    
    face_the_opposite_direction();
    if(on_ball())
        step();
}
