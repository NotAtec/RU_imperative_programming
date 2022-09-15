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

void face_north();
void face_east();
void turn_times(int x);

void walk_to_wall();
void line_of_balls();
void beginning_of_line();
void follow_line();

void reset_to(int steps, int turns);
void step_times(int x);

void find_next_line();
void check_left();
void check_right();

void setup_right();
void setup_next_part();
/******************************************************************************
** Exercises
******************************************************************************/
void test_agent() {

}

// Exercise 1 - Follow contiguous path of balls
void path_agent() {
  // For Exercise 1 I have made one assumption: Walls only exist on the edges of the world,
  // As such, there will never exist a situation where there is a wall on the left whilst there is also a wall on the right of Charles.

  // Loop follows all lines until the end
  while(on_ball()) {
    follow_line();
    find_next_line();
  }

  // After finishing the line, it will move back to the line and face east.
  reset_to(1, 0);
  face_east();
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

// Function makes Charles face North
void face_north() {
  while(!north()) {
    turn_left();
  }
}

// Function makes Charles face East
void face_east() {
  face_north();
  turn_right();
}

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

// Function makes Charles follow a line of balls.
void follow_line() {
  // Follow the line
  while(on_ball() & !in_front_of_wall()) {
    step();
  }

  // Move back to the line in case of an overshoot
  if(!on_ball()) {
    reset_to(2, 2);
  }
}

// Function makes Charles move to a certain position after turning around.
void reset_to(int steps, int turns) {
  turn_times(2);
  step_times(steps);
  turn_times(turns);
}

// Function makes Charles move x amount of times.
void step_times(int x) {
  while(x > 0) {
    step();
    x -= 1;
  }
}
// Functions to make charles look for balls.

// Function checks left side for ball, and if nothing or a wall is found, will check the right side.
void find_next_line() {
  turn_left();

  if(in_front_of_wall()) {
    setup_right(false);
  } else {
    check_left();
  }
}

// Function checks left side for ball.
void check_left() {
  step();
  if(!on_ball()) {
    reset_to(1, 0);
    setup_right(true);
  }
}

// Function checks right side for ball.
void check_right() {
  turn_right();
  if(in_front_of_wall()) {
    // Due to the assumption of only 1 side wall, we know the other side must be empty with no ball
    // As such we can move to the empty square.
    reset_to(1, 0);
  } else {
    step();
  }
}

// Functions to setup for further action

// Function will setup to check right side of previously walked line
void setup_right(bool left) {
  if(left) {
    turn_left();
  } else {
    turn_right();
  }
  check_right();
}

// Function makes Charles setup for the mirrored part of the exercise.
void setup_next_part() {
  turn_right();
  walk_to_wall();
  turn_right();
}
