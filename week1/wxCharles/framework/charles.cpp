#include "charles.h"

#include "trace.h"

void step() {
    g_activeTrace.AddAction(Action::Step);
}

void turn_left() {
    g_activeTrace.AddAction(Action::TurnLeft);
}

void turn_right() {
    g_activeTrace.AddAction(Action::TurnRight);
}

void get_ball() {
    g_activeTrace.AddAction(Action::TakeBall);
}

void put_ball() {
    g_activeTrace.AddAction(Action::PlaceBall);
}

bool in_front_of_wall() {
    return g_activeTrace.AddAction(Action::InFrontOfWall);
}

bool north() {
    return g_activeTrace.AddAction(Action::FacingNorth);
}

bool on_ball() {
    return g_activeTrace.AddAction(Action::OnBall);
}

void pause() {
    g_activeTrace.AddAction(Action::Pause);
}

void mark(const char* str) {
    g_activeTrace.AddMark(str);
}