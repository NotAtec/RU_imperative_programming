#include "world.h"

const char* DescribeSimulationError(SimulationError error) {
    switch(error) {
        case SimulationError::MaxStepsExceeded:
            return "Charles exceeded the maximum number of steps";
        case SimulationError::PlaceBallOnBall:
            return "Charles tried to place a ball on top of another ball";
        case SimulationError::StepIntoWall:
            return "Charles tried to step into a wall";
        case SimulationError::StepOutOfWorld:
            return "Charles tried to step out of the world";
        case SimulationError::TakeMissingBall:
            return "Charles tried to pick up a ball that does not exist";
        case SimulationError::Timeout:
            return "The agent took too long to simulate";
        default:
            return "An unknown simulation error occurred";
    }
}

Position operator+(const Position& pos, Direction dir) {
    static int x_delta_lut[4] = {0, 1, 0, -1};
    static int y_delta_lut[4] = {-1, 0, 1, 0};

    int x_delta = x_delta_lut[static_cast<int>(dir)];
    int y_delta = y_delta_lut[static_cast<int>(dir)];

    return {pos.x + x_delta, pos.y + y_delta};
}

void World::Step() {
    Position new_pos = m_pos + m_dir;

    if(!IsValidPosition(new_pos)) {
        throw SimulationException(SimulationError::StepOutOfWorld);
    } else if(GetTileTypeAt(new_pos) == TileType::Wall) {
        throw SimulationException(SimulationError::StepIntoWall);
    } else {
        m_pos = new_pos;
    }
}

void World::TurnLeft() {
    m_dir = static_cast<Direction>((static_cast<int>(m_dir) + NUM_DIRS - 1) % NUM_DIRS);
}

void World::TurnRight() {
    m_dir = static_cast<Direction>((static_cast<int>(m_dir) + 1) % NUM_DIRS);
}

void World::PlaceBall() {
    if(HasBallAt(m_pos)) {
        throw SimulationException(SimulationError::PlaceBallOnBall);
    }

    SetBallAt(m_pos, true);
}

void World::TakeBall() {
    if(!HasBallAt(m_pos)) {
        throw SimulationException(SimulationError::TakeMissingBall);
    }

    SetBallAt(m_pos, false);
}

bool World::IsOnBall() const {
    return HasBallAt(m_pos);
}

bool World::IsInFrontOfWall() const {
    Position new_pos = m_pos + m_dir;

    return IsValidPosition(new_pos) && GetTileTypeAt(new_pos) == TileType::Wall;
}

bool World::IsFacingNorth() const {
    return m_dir == DIR_NORTH;
}

bool World::PerformAction(Action action) {
    switch(action) {
        case Action::InFrontOfWall:
            return IsInFrontOfWall();
        case Action::OnBall:
            return IsOnBall();
        case Action::FacingNorth:
            return IsFacingNorth();
        case Action::PlaceBall:
            PlaceBall();
            break;
        case Action::TakeBall:
            TakeBall();
            break;
        case Action::Step:
            Step();
            break;
        case Action::TurnLeft:
            TurnLeft();
            break;
        case Action::TurnRight:
            TurnRight();
            break;
        // Do nothing on debug/pseudo actions.
        case Action::EndSimulation:
        case Action::AbortSimulationMaxSteps:
        case Action::AbortSimulationTimeout:
        case Action::Mark:
        case Action::Pause:
            break;
    }

    return false;
}

Tile World::GetTileAt(Position pos) const {
    assert(IsValidPosition(pos));

    return m_tiles[pos.x + pos.y * m_width];
}

void World::SetTileAt(Position pos, Tile tile) {
    assert(IsValidPosition(pos));

    m_tiles[pos.x + pos.y * m_width] = tile;
}

TileType World::GetTileTypeAt(Position pos) const {
    assert(IsValidPosition(pos));

    return m_tiles[pos.x + pos.y * m_width].type;
}

void World::SetTileTypeAt(Position pos, TileType type) {
    assert(IsValidPosition(pos));

    m_tiles[pos.x + pos.y * m_width].type = type;
}

bool World::HasBallAt(Position pos) const {
    assert(IsValidPosition(pos));

    return m_tiles[pos.x + pos.y * m_width].hasBall;
}

void World::SetBallAt(Position pos, bool ball) {
    assert(IsValidPosition(pos));

    m_tiles[pos.x + pos.y * m_width].hasBall = ball;
}

bool World::IsValidPosition(Position pos) const {
    return pos.x >= 0 && pos.y >= 0 && pos.x < m_width && pos.y < m_height;
}