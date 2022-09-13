#pragma once

#include <cassert>
#include <vector>
#include <iostream>
#include <exception>

enum class SimulationError {
    StepOutOfWorld,
    StepIntoWall,
    PlaceBallOnBall,
    TakeMissingBall,
    Timeout,
    MaxStepsExceeded
};

const char* DescribeSimulationError(SimulationError error);

/**
 * @brief Exception thrown when the simulation kernel encounters an error.
 *
 */
class SimulationException : public std::exception {
public:
    SimulationException(SimulationError error) : m_error{error} {}

    /**
     * @brief Returns the string that explains the kind of simulation error encountered.
     *
     * @return The explanatory string.
     */
    const char* what() const noexcept override { return DescribeSimulationError(m_error); }

    /**
     * @brief Returns the simulation error encountered.
     *
     * @return The simulation error.
     */
    SimulationError GetError() const { return m_error; }

private:
    SimulationError m_error;
};

enum class TileType {
    Wall,
    Ground
};

enum class Action {
    Step,
    TurnLeft,
    TurnRight,
    PlaceBall,
    TakeBall,
    InFrontOfWall,
    OnBall,
    FacingNorth,
    Mark,
    Pause,
    EndSimulation,
    AbortSimulationTimeout,
    AbortSimulationMaxSteps
};

enum Direction {
    DIR_NORTH = 0,
    DIR_EAST = 1,
    DIR_SOUTH = 2,
    DIR_WEST = 3,
    NUM_DIRS = 4
};

struct Position {
    int x;
    int y;
};

struct Tile {
    TileType type;
    bool hasBall;
};

class World {
    // Grant *.scenario loader/saver access to World internals.
    friend class Scenario;

public:
    World(int width = 1, int height = 1, Position pos = {0, 0}, Direction dir = DIR_EAST)
     : m_width{width}, m_height{height}, m_pos{pos}, m_dir{dir} {
         assert(width >= 1);
         assert(height >= 1);
         assert(IsValidPosition(pos));

        m_tiles.resize(width * height, {TileType::Ground, false});
    }

    void Step();
    void TurnLeft();
    void TurnRight();
    void PlaceBall();
    void TakeBall();
    bool IsOnBall() const;
    bool IsInFrontOfWall() const;
    bool IsFacingNorth() const;
    bool PerformAction(Action action);

    Tile GetTileAt(int x, int y) const { return GetTileAt({x, y}); }
    Tile GetTileAt(Position pos) const;
    void SetTileAt(int x, int y, Tile tile) { SetTileAt({x, y}, tile); }
    void SetTileAt(Position pos, Tile tile);
    TileType GetTileTypeAt(Position pos) const;
    void SetTileTypeAt(Position pos, TileType type);
    bool HasBallAt(Position pos) const;
    void SetBallAt(Position pos, bool ball);
    bool IsValidPosition(Position pos) const;

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    Position GetPosition() const { return m_pos; }
    Direction GetDirection() const { return m_dir; }

    void SetPosition(Position pos);
    void SetDirection(Direction dir);

private:
    std::vector<Tile> m_tiles;
    int m_width;
    int m_height;
    Position m_pos;
    Direction m_dir;
};