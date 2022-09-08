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

void face_north();
void face_west();
void face_south();
void face_east();

void walk_to_facing_wall();
void walk_to_start();

void move_down();
void set_to_next_line();
void find_ball_on_line();

void sweep_line();
void sweep_until_clear();

void get_available_ball();

/******************************************************************************
** Exercises
******************************************************************************/
void test_agent() {

}

// Exercise 1 - Clean up a string of balls
void string_agent() { 
  //
  while(on_ball()){
    get_ball();
    step();
    
    // Scenario 2: Check if we are in front of a wall and need to turn right
    if(in_front_of_wall()){
      turn_right();
    }
  }
}

void chaos_agent() { // Part 2
  walk_to_facing_wall(); // Setup to the east of the grid to start sweeping
  while(on_ball()) { 
    // Loop will make Charles sweep the line, then set to the next line. On the start it checks if the line will be empty.
    face_west();
    sweep_until_clear();
    set_to_next_line();
  }

  walk_to_start(); // Reset to starting position to finish the exercise.
}

void block_agent() { // Bonus Assignment
  find_ball_on_line();
  face_south();
  walk_to_facing_wall();
    
  while(in_front_of_wall()) {
    put_ball();
    face_east();
    step();
    face_south();  
  }

  put_ball();
  step();
  face_west();

  while(in_front_of_wall()) {
    put_ball();
    face_south();
    step();
    face_west();
  }

  put_ball();
  step();
  face_north();

  while(in_front_of_wall()) {
    put_ball();
    face_west();
    step();
    face_north();
  }  

  put_ball();
  step();
  face_east();

  while(in_front_of_wall()) {
    put_ball();
    face_north();
    step();
    face_east();
  }  

  put_ball();
  walk_to_start();
}


/******************************************************************************
** Function Definitions
******************************************************************************/

// Functions for setting Charles direction
void face_north() {
  while(!north()) {
    turn_left();
  }
}

void face_west() {
  face_north();
  turn_left();
}

void face_south() {
  face_north();
  turn_left();
  turn_left();
}

void face_east() {
  face_north();
  turn_right();
}


// Functions for moving Charles to certain points in space
void walk_to_facing_wall() {
  // Function will continue straight ahead, skipping balls, and move safely to the wall Charles is facing
  while(!in_front_of_wall()) {
    step();
  }
}

void move_down() {
  // Function will move Charles down one line.
  face_south();
  step();
}

void set_to_next_line() {
  // Function will move Charles to the start of the next line, facing west.
  move_down();
  face_east();
  walk_to_facing_wall();
}

void walk_to_start() {
  // Function will reset Charles to the starting position, facing the way he faced at the start.
  face_north();
  walk_to_facing_wall();
  face_west();
  walk_to_facing_wall();
  face_east();
}

void find_ball_on_line() {
  // Function will move Charles along line, until a cell with a ball in it is found.
  while(!on_ball()) {
    step();
  }
}


// Functions for sweeping a line and clearing all balls on it
void sweep_line() {
  // Function will continue straight ahead when safe to do so, and pick up balls along the way
  while(!in_front_of_wall()) {
    get_available_ball();
    step();
  }

  get_available_ball(); // Pick up one more time, in case there is a ball right in front of the wall
}

void sweep_until_clear() {
  // Function will sweep line until ball is not visible on new cell
  while(!in_front_of_wall() && on_ball()) {
    get_available_ball();
    step();
  }
}


// Function for safely getting ball if one is available
void get_available_ball() {
  if(on_ball()) {
    get_ball();
  }
}
