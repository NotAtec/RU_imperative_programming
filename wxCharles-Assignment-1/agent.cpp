#include "framework/charles.h"
#include "assignments/assignment1.h"

void get_available_ball() {
  // Function checks if ball is available and will then pick up said ball
  if(on_ball()) {
    get_ball();
  }
}

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

void move_to_facing_wall() {
  // Function will continue straight ahead, skipping balls, and move safely to the wall Charles is facing
  while(!in_front_of_wall()) {
    step();
  }
}

void face_north() {
  // Function will make Charles face North
  while(!north()) {
    turn_left();
  }
}

void face_west() {
  // Function will make Charles face West
  face_north();
  turn_left();
}

void face_south() {
  // Function will make Charles face South
  face_north();
  turn_left();
  turn_left();
}

void face_east() {
  // Function will make Charles face East
  face_north();
  turn_right();
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
  move_to_facing_wall();
}

void reset_to_start() {
  // Function will reset Charles to the starting position, facing the way he faced at the start.
  face_north();
  move_to_facing_wall();
  face_west();
  move_to_facing_wall();
  face_east();
}

void test_agent() {

}

void string_agent() {
  while(!north()) { // Loop will sweep all lines along the wall, until facing north
    sweep_line();
    turn_right();
  }

  sweep_line(); // Clear final line
  turn_right(); // Reset to starting position from North
}

void chaos_agent() {
  move_to_facing_wall(); // Setup to the east of the grid to start sweeping
  while(on_ball()) { 
    // Loop will make Charles sweep the line, then set to the next line. On the start it checks if the line will be empty.
    face_west();
    sweep_until_clear();
    set_to_next_line();
  }

  reset_to_start(); // Reset to starting position to finish the exercise.
}

void block_agent() {

}