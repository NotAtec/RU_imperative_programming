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
void walk_to_beginning_of_next_line();
void find_ball_on_line();
void grab_every_available_ball_on_line();

/******************************************************************************
** Exercises
******************************************************************************/
void test_agent() {

}

// Exercise 1 - Clean up a string of balls
void string_agent() { 
  // Clear the line, and check each time if we need to turn to prevent moving into a wall
  while(on_ball()){
    get_ball();
    step();
    
    // Check if we are in front of a wall and need to turn right
    if(in_front_of_wall()){
      turn_right();
    }
  }
}

// Exercise 2: Clear ball chaos
void chaos_agent() {
  // Setup to east part of map
  face_east();
  walk_to_facing_wall();

  // Clear line & walk to next line
  while(on_ball()) { 
    grab_every_available_ball_on_line();
    walk_to_beginning_of_next_line();
  }

  walk_to_start(); // Reset to starting position to finish the exercise.
}

// Bonus Exercise: Put balls around rectangle
void block_agent() {
  // Move to top-left corner of the rectangle
  find_ball_on_line();
  face_south();
  walk_to_facing_wall();
  face_east();

  // Put balls around the rectangle
  while(!on_ball()) {
    turn_right(); // Setup to check if Charles is in front of wall
    while(in_front_of_wall()) { // Place ball and move to next square
      turn_left();
      put_ball();
      step();
      turn_right();
    }

    // Fill in corners aswell
    put_ball();
    step();
  }

  // Return to starting point
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

void walk_to_beginning_of_next_line() {
  // Function will move Charles to the start of the next line.
  move_down();
  face_east();
  walk_to_facing_wall();
}

void walk_to_start() {
  // Walk Charles to origin cell
  face_north();
  walk_to_facing_wall();
  face_west();
  walk_to_facing_wall();
  face_east(); // Make Charles face east like in the beginning.
}

void find_ball_on_line() {
  // Function will move Charles along line, until a cell with a ball in it is found.
  while(!on_ball()) {
    step();
  }
}

// Functions for making Charles do something other than just walking
void grab_every_available_ball_on_line() {
  //We assume we are at the east wall, facing east.
  face_west();
  while(on_ball()) { // Move along until no more balls are available
    get_ball();
    if (!in_front_of_wall()) { // Only go to next cell if that doesn't make Charles run into a wall.
      step();
    }
  }
}