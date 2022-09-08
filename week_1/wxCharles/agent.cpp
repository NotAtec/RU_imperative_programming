/******************************************************************************
** Course: Imperative Programming - Assignment 1
** Authors: Jeroen Brinkhorst [S1101799]
**          Andrei Ujica [S1102725]
** Date: 08.09.2022
******************************************************************************/

#include "framework/charles.h"
#include "assignments/assignment1.h"


/******************************************************************************
** Function Prototypes
******************************************************************************/

void turn_north();
void turn_east();
void turn_south();
void turn_west();

void walk_to_facing_wall();
void walk_to_left_corner();
void walk_to_first_ball_in_sight();
void move_to_next_line_and_face_west();

bool row_contains_ball();
bool next_to_wall();

void grab_every_available_ball_on_line();

/******************************************************************************
** Exercises
******************************************************************************/
void test_agent() {

}

// Exercise 1 - Clean up a string of balls
void string_agent() {
    // 
    while(on_ball()){
        // Scenario 1: we are not in front of a wall
        get_ball();
        step();

        // Scenario 2: we are in front of the wall, therefore we just need to turn right
        if(in_front_of_wall()){
            turn_right();
        }
    }
}

// Exercise 2: Clear ball chaos
void chaos_agent() {
    // Find the first ball from the first row containing balls 
    // (Check "row_contains_ball" method for reasoning)
    while(!row_contains_ball()){
        move_to_next_line_and_face_west();
        walk_to_facing_wall();
    }
    
    // Position Charles on the East wall
    turn_east();
    walk_to_facing_wall();

    // Clear all lines
    while(on_ball()){
        grab_every_available_ball_on_line();
        move_to_next_line_and_face_west();
    }

    // Return to starting point
    walk_to_left_corner();
}

// Bonus Exercise: Clear along the wall
void block_agent() {
    // Move to the top-left corner of the rectangle
    walk_to_first_ball_in_sight();
    turn_south();
    walk_to_facing_wall();
    turn_east();

    // Put balls around the rectangle
    while(!on_ball()){
        while(next_to_wall()){
            turn_left();
            put_ball();
            step();
        }

        // Fill in corners as well
        put_ball();
        step();
        }

    // Walk back to starting point
    walk_to_left_corner();
}

/******************************************************************************
** Function Definitions
******************************************************************************/

// Functions for setting the direction of Charles
void turn_north(){
    while(!north())
        turn_right();
}

void turn_east(){
    turn_north();
    turn_right();
}

void turn_south(){
    turn_east();
    turn_right();
}

void turn_west(){
    turn_south();
    turn_right();
}


// Functions for moving Charles to a certain point
void walk_to_facing_wall(){
    while(!in_front_of_wall())
        step();
}

void walk_to_left_corner(){
    turn_west();
    walk_to_facing_wall();
    turn_right();
    walk_to_facing_wall();
    turn_right();
}

void move_to_next_line_and_face_west(){
    turn_south();
    step();
    turn_west();
}

void walk_to_first_ball_in_sight(){
    while(!on_ball())
        step();
}

// Functions for checking the state of Charles
bool row_contains_ball(){
    // We cannot be sure that there is going to be a ball on the first row, as the problem does not specify it 
    // - "You can assume that each horizontal line of balls contains no holes."
    // - "You can also assume that there are no ‘empty’ horizontal lines in between horizontal lines of balls. "
    while(!in_front_of_wall()){
        if(on_ball())
            return true;
        step();
    }
    return false;
}

bool next_to_wall(){
    turn_right();
    return in_front_of_wall();
}

// Functions for making Charles do something
void grab_every_available_ball_on_line(){
    // We assume we are at the East wall, facing East
    turn_west();
    while(on_ball()){
        get_ball();
        step();
    }

    turn_east();
    walk_to_facing_wall();
}
