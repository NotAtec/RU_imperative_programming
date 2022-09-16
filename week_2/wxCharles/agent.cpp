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

void face_north();
void face_east();

void follow_line();
void check_direction();
void reset_to(int steps, int turns);

void put_column_of_balls();
void walk_to_opposite();

void find_center_of_axis(bool vertical);

void clean_to_wall(bool final_ball);
void move_to_center(int x);
void clean_horizontal();

/******************************************************************************
** Exercises
******************************************************************************/
void test_agent() {}

// Exercise 1 - Follow contiguous path of balls
void path_agent() {
  // For Exercise 1 I have made one assumption: Walls only exist on the edges of
  // the world, As such, there will never exist a situation where there is a
  // wall on the left whilst there is also a wall on the right of Charles.

  // Loop follows all lines until the end
  while (on_ball()) {
    follow_line();
    check_direction();
  }

  // Code snippet is used to move back to the path, and face east.
  reset_to(1, 0);
  face_east();
}

// Exercise 2 - Create Stalactites & Stalagmites
void cave_agent() {
  // First move to a line where it's required to place balls.
  step();

  // Repeat for all lines where balls are required.
  while (!in_front_of_wall()) {
    put_column_of_balls();
    step();
  }

  // Setup Charles for the mirrored second part.
  walk_to_opposite();
}

// Bonus 1 - Find the Center
void find_center_agent() {
  // Find Center of the Horizontal Axis, set vertical parameter to false
  find_center_of_axis(false);

  // Find Center of the Horizontal Axis, set vertical parameter to true
  find_center_of_axis(true);

  // Setup to face east like in the instruction
  face_east();
}

// Bonus 2 - Clean up Balls
void clean_up_agent() {
  // Clean up the northern half of the vertical line
  face_north();
  clean_to_wall(false);

  clean_horizontal();

  // Move to center of vertical line, and remove the southern half
  move_to_center(0);
  clean_to_wall(true);

  // Move back to the center and face east
  move_to_center(2);
  face_east();
}

/******************************************************************************
** Function Definitions
******************************************************************************/

// Functions for facing certain cardinal directions

// Function makes Charles face north
void face_north() {
  while (!north())
    turn_left();
}

// Function makes Charles face East
void face_east() {
  face_north();
  turn_right();
}

// Function makes Charles face South
void face_south() {
  face_east();
  turn_right();
}

// Simple functions
// All functions that simply repeat some steps

// Function makes Charles turn 'x' amount of times.
void turn_times(int x) {
  while (x > 0) {
    turn_right();
    x -= 1;
  }
}

// Function makes Charles step 'x' amount of times.
void step_times(int x) {
  while (x > 0) {
    step();
    x -= 1;
  }
}

// Function makes Charles move to a certain position after turning around.
void reset_to(int steps, int turns) {
  turn_times(2);
  step_times(steps);
  turn_times(turns);
}

// Movement functions

// Function makes Charles move to the nearest wall, without thinking about
// balls.
void walk_to_wall() {
  while (!in_front_of_wall())
    step();
}

// Function makes Charles move to the ball for finding center.
void walk_to_ball() {
  while (!on_ball() && !in_front_of_wall())
    step();

  turn_times(2);
  if (on_ball())
    step();
}

// Function makes Charles follow a line of balls.
void follow_line() {
  while (on_ball() && !in_front_of_wall())
    step();

  // In case of an overshoot, use this snippet to move back to the line.
  if (!on_ball())
    reset_to(1, 2);
}

// Function makes Charles setup for the mirrored part of the exercise.
void walk_to_opposite() {
  turn_right();
  walk_to_wall();
  turn_right();
}

// Setup Functions

// Function places final ball & moves back up when hitting a wall in a column
void column_return() {
  put_ball();
  turn_times(2);
  walk_to_wall();
  turn_right();
}

// Function places a line of balls, and moves back up.
void put_column_of_balls() {
  turn_right();

  while (!in_front_of_wall()) {
    put_ball();
    step();
  }

  column_return();
  
}

// Cleanup Functions

// Function makes Charles clean balls until the wall
void clean_to_wall(bool final_ball) {
  step();

  // Pick up all balls between the center and the wall
  while(!in_front_of_wall()) {
    get_ball();
    step();
  }

  // Pick up the ball at the wall if required
  if(final_ball) {
    get_ball();
  }
}

// Function makes Charles turn around & move to the first ball on the line
void find_center_ball() {
  while(!on_ball())
    step();
}

// Function moves Charles back to ball
void move_to_center(int x) {
  turn_times(x);
  find_center_ball();
}

// Function cleans the horizontal line
void clean_horizontal() {
  turn_left();
  clean_to_wall(true);

  move_to_center(2);
  clean_to_wall(true);

  move_to_center(2);

  face_south();
  get_ball();
}

// Direction finding functions

// Function checks right side for ball.
void check_right() {
  turn_right();

  // Edgecase: Right is a wall instead of a cell
  // Check wall before checking the side.
  if (in_front_of_wall())
    // Due to the assumption of only 1 side wall, we know the other side must be
    // empty with no ball As such we can move to the empty square.
    reset_to(1, 0);
  else
    step();
}

// Function sets up Charles to check right side.
void setup_right(bool left) {
  if (left)
    turn_left();
  else
    turn_right();

  check_right();
}

// Function checks left side after edgecase check
void check_left() {
  step();

  if (!on_ball()) {
    reset_to(1, 0);
    setup_right(true);
  }
}

// Function checks left & right for continuation of path.
void check_direction() {
  // Check left side
  turn_left();

  // Edgecase: Left is a wall instead of a cell
  // Check for wall before actually checking a side.
  if (in_front_of_wall())
    setup_right(false);
  else
    check_left();
}

// Function makes Charles find the center of an axis.
// Boolean indicates if a vertical or horizontal axis should be used.
void find_center_of_axis(bool vertical) {
  if (vertical) {
    face_south();
    step();
    walk_to_ball();
  }

  while (!on_ball()) {
    put_ball();
    step();
    walk_to_ball();
  }
}
