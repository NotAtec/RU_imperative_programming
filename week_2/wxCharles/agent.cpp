/******************************************************************************
** Course: Imperative Programming - Assignment 1
** Authors: Jeroen Brinkhorst [S1101799]
**          Andrei Ujica [S1102725]
** Date: 13.09.2022
******************************************************************************/

#include "framework/charles.h"
#include "assignments/assignment2.h"

/******************************************************************************
** Function Prototypes
******************************************************************************/

void turn_times(int x);

void walk_to_wall();
void line_of_balls();
void beginning_of_line();
void setup_next_part();

/******************************************************************************
** Exercises
******************************************************************************/
void test_agent() {

}

// Exercise 1 - Follow contiguous path of balls
void path_agent() {
  
}

// Exercise 2 - Create Stalactites & Stalagmites
void cave_agent() {
  // First move to a line where it's required to place balls.
  step();

  // Repeat for all lines where balls are required.
  while(!in_front_of_wall()) {
    turn_right();
    line_of_balls();
    beginning_of_line();
    turn_right();
    step();
  }

  // Setup Charles for the mirrored second part.
  setup_next_part();
}

void find_center_agent() {

}

void clean_up_agent() {

}

/******************************************************************************
** Function Definitions
******************************************************************************/

// Functions to make Charles turn around

// Function makes Charles turn 'x' amount of times.
void turn_times(int x) {
  while(x > 0) {
    turn_right();
    x -= 1;
  }
}

// Functions to make Charles move around the grid

// Function makes Charles move to the nearest wall, without thinking about balls.
void walk_to_wall() {
  while(!in_front_of_wall()) {
    step();
  }
}

// Function makes Charles place a line of balls to the next wall straight ahead.
void line_of_balls() {
  while(!in_front_of_wall()) {
    put_ball();
    step();
  }

  put_ball();
}

// Function makes Charles move to beginning of line after placing a line of balls.
void beginning_of_line() {
  turn_times(2);
  walk_to_wall();
}

// Function makes Charles setup for the mirrored part of the exercise.
void setup_next_part() {
  turn_right();
  walk_to_wall();
  turn_right();
}