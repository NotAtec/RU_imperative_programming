#include "framework/charles.h"
#include "assignments/demo.h"

void test_agent() {

}

void static_agent() {
    // Finding the ball marks the exit, so keep searching until it is found.
    while(!on_ball()) {
        // Walk to the next corner or exit.
        while(!in_front_of_wall() && !on_ball()) {
            step();
        }

        // If at a corner, then turn left (as all corners are left corners).
        if(in_front_of_wall()) {
            turn_left();
        }
    }
}

static void clean_to_wall() {
    // Pick up balls until Charles is in front of a wall.
    while(!in_front_of_wall()) {
        get_ball();
        step();
    }
}

void random_agent() {
    // Traverse and clean up the Z shape.
    clean_to_wall();
    turn_right();
    clean_to_wall();
    turn_left();
    clean_to_wall();

    // Pick up the final ball.
    get_ball();
}

void exercise1_agent() {
    step();
    step();
    get_ball();
}

void exercise2_agent() {
    while(!in_front_of_wall()) {
        step();
        if(on_ball()) {
            mark("Found the ball");
            pause();
            get_ball();
        }
    }
}
