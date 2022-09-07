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

void test_agent() {

}

void string_agent() {
  while(!north()) { // Function will sweep all lines along the wall, until facing north
    sweep_line();
    turn_right();
  }

  sweep_line(); // Clear final line
  turn_right(); // Reset to starting position from North
}

void chaos_agent() {

}

void block_agent() {

}