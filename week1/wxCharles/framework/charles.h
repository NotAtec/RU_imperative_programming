#pragma once

// Actions Charles can perform to interact with the world
extern void step();
extern void turn_left();
extern void turn_right();
extern void get_ball();
extern void put_ball();

// Sensors Charles can use to observe the world
extern bool in_front_of_wall();
extern bool north();
extern bool on_ball();

// Debug utilities
extern void pause();
extern void mark(const char* str);