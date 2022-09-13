#pragma once

#include "util/include_guard.h"
#include "util/common_worldgen.h"
#include "../framework/assignment.h"

#include <vector>

#define DEBUG_CAVE_EXERCISE 0
#define USE_LEGACY_BONUS 0

extern void test_agent();
extern void path_agent();
extern void cave_agent();
#if USE_LEGACY_BONUS
extern void shamrock_agent();
#else
extern void find_center_agent();
extern void clean_up_agent();
#endif

class PathExercise : public RandomExercise {
    using Path = std::vector<Position>;

public:
    PathExercise(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0x48151623, category) {}

protected:
    World Create() override {
        constexpr int WIDTH = 30;
        constexpr int HEIGHT = 25;
        constexpr int MIN_SEGMENT = 2;

        // A path is a sequence of initial position, corners, and finally end position.
        Path path;

        // Generate potential paths until a valid one is found.
        do {
            path = GeneratePath(WIDTH, HEIGHT, MIN_SEGMENT);
        } while(!IsValidPath(path));

        // Determine the direction Charles is initially facing based on first path segment.
        Direction initialDirection = GetSegmentDirection(path[0], path[1]);

        // Generate the world, placing Charles at the start of the path.
        World world(WIDTH, HEIGHT, path[0], initialDirection);

        EncloseInWalls(world);

        for(auto i = 1u; i < path.size(); ++i) {
            ConnectPathSegment(world, path[i-1], path[i]);
        }

        return world;
    };

private:
    void ExtendSegment(int& coord, int maxCoord, int minSegment) {
        // Check how much room there is to extend in both the positive and negative direction.
        int negMargin = coord - 1;
        int posMargin = maxCoord - 2 - coord;

        // Place segment towards the direction that has more room, with a randomly generated length.
        if(negMargin > posMargin) {
            coord -= NextRandomInt(minSegment, negMargin);
        } else {
            coord += NextRandomInt(minSegment, posMargin);
        }
    }

    Path GeneratePath(int width, int height, int minSegment) {
        Path path;
        Position pos;

        // Generate an initial position where the path starts.
        pos.x = NextRandomInt(1, width - 2);
        pos.y = NextRandomInt(1, height - 2);

        path.push_back(pos);

        // Generate the subsequent segments, alternating between horizontal and vertical segments.
        for(int segment = NextRandomInt(5, 9); segment > 0; --segment) {
            // Create segment by moving pos to the end of the segment.
            if(segment % 2 == 0) {
                // Even segments are horizontal.
                ExtendSegment(pos.x, width, minSegment);
            } else {
                // Uneven segments are vertical.
                ExtendSegment(pos.y, height, minSegment);
            }

            // Add segment to the path.
            path.push_back(pos);
        }

        return path;
    }

    // Check if pos intersects with the path segment (start, end).
    bool Intersects(Position pos, Position start, Position end) const {
        int minX = Min(start.x, end.x);
        int maxX = Max(start.x, end.x);
        int minY = Min(start.y, end.y);
        int maxY = Max(start.y, end.y);

        return minX <= pos.x && pos.x <= maxX && minY <= pos.y && pos.y <= maxY;
    }

    // Check if pos intersects with any path segment in path.
    bool Intersects(const Path& path, Position pos) const {
        for(auto i = 1u; i < path.size(); ++i) {
            if(Intersects(pos, path[i-1], path[i])) {
                return true;
            }
        }

        return false;
    }

    // Check in how many directions pos can continue.
    int GetPossibleDirections(const Path& path, Position pos) const {
        int options = 0;

        if(Intersects(path, {pos.x + 1, pos.y})) options++;
        if(Intersects(path, {pos.x - 1, pos.y})) options++;
        if(Intersects(path, {pos.x, pos.y + 1})) options++;
        if(Intersects(path, {pos.x, pos.y - 1})) options++;

        return options;
    }

    // Check if path is a valid path, i.e. can be solved with the intended algorithm.
    bool IsValidPath(const Path& path) const {
        // Make sure no T-junctions exist.
        for(Position pos : path) {
            if(GetPossibleDirections(path, pos) > 2) {
                return false;
            }
        }

        // Make sure path ends cleanly, and does not loop back into itself.
        return GetPossibleDirections(path, path.back()) == 1;
    }

    // Get the relative direction of position b respective to position a.
    Direction GetSegmentDirection(Position a, Position b) const {
        int dx = a.x - b.x;
        int dy = a.y - b.y;

        // Do not allow diagonal segments, i.e exactly one of dx and dy must be 0.
        assert((dx == 0) ^ (dy == 0));

        if(dx != 0) {
            return dx < 0 ? DIR_EAST : DIR_WEST;
        } else {
            return dy < 0 ? DIR_SOUTH : DIR_NORTH;
        }
    }

    // Connect the path segment (start, end) by placing balls on it.
    void ConnectPathSegment(World& world, Position start, Position end) const {
#if 0
        // Debug path creation by marking corners and final position.
        world.SetTileTypeAt(end, TileType::Wall);
#endif        
        Direction dir = GetSegmentDirection(start, end);

        if(dir == DIR_EAST) {
            PlaceBallRow(world, start.x, start.y, end.x + 1);
        } else if(dir == DIR_WEST) {
            PlaceBallRow(world, end.x, end.y, start.x + 1);
        } else if(dir == DIR_NORTH) {
            PlaceBallColumn(world, end.x, end.y, start.y + 1);
        } else if(dir == DIR_SOUTH) {
            PlaceBallColumn(world, start.x, start.y, end.y + 1);
        }
    }
};

class CaveExercise : public RandomExercise {
public:
    CaveExercise(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0x42108abc, category) {}

protected:
    World Create() override {
        constexpr int MAX_SLAB_WIDTH = 5;
        constexpr int MARGIN = 1;

        int width = NextRandomInt(30, 40);
        int height = NextRandomInt(25, 30);

        World world(width, height, {1,1});

        EncloseInWalls(world);

        // Create top stalactites.
        int remaining = width - 2 - 2 * MARGIN;
        int slabX = 1 + MARGIN;
        while(remaining != 0) {
            int slabWidth = NextRandomInt(1, Min(remaining, MAX_SLAB_WIDTH));
            int slabHeight = NextRandomInt(2, (height / 2) - 1);

            // Place a row of walls for the slab itself.
            PlaceWallRow(world, slabX, slabHeight, slabX + slabWidth);

#if DEBUG_CAVE_EXERCISE
            // Fill the rectangle up to the slab with balls.
            for(int x = 0; x < slabWidth; ++x) {
                PlaceBallColumn(world, slabX + x, 1, slabHeight);
            }
#endif

            slabX += slabWidth;
            remaining -= slabWidth;
        }

        // Create bottom stalagmites.
        remaining = width - 2 - 2 * MARGIN;
        slabX = 1 + MARGIN;
        while(remaining != 0) {
            int slabWidth = NextRandomInt(1, Min(remaining, MAX_SLAB_WIDTH));
            int slabHeight = NextRandomInt(height / 2, height - 3);

            // Place a row of walls for the slab itself.
            PlaceWallRow(world, slabX, slabHeight, slabX + slabWidth);

#if DEBUG_CAVE_EXERCISE
            // Fill the rectangle up to the slab with balls.
            for(int x = 0; x < slabWidth; ++x) {
                PlaceBallColumn(world, slabX + x, slabHeight + 1, height - 1);
            }
#endif

            slabX += slabWidth;
            remaining -= slabWidth;
        }

        return world;
    };
};

#if USE_LEGACY_BONUS
class ShamrockExercise : public RandomExercise {
public:
    ShamrockExercise(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0x7355608, category) {}

protected:
    World Create() override {
        int xMargin = NextRandomInt(4, 6);
        int yMargin = NextRandomInt(2, 4);
        int leaves = NextRandomInt(1, 4);
        int leafWidth = EnsureUneven(NextRandomInt(5, 7));
        int leafHeight = EnsureUneven(NextRandomInt(3, 5));

        int height = 2 + yMargin * 2 + leafHeight * 4 + 1;
        int width = 2 + xMargin * 2 + leafWidth * 4 + 1;
        int cX = width / 2;
        int cY = height / 2;

        World world(width, height, {1, 1});

        EncloseInWalls(world);

        // Mark center of the shamrock, connecting the stems.
        world.SetTileTypeAt({cX, cY}, TileType::Wall);

        // Always place stem to south leaf.
        PlaceWallColumn(world, cX, cY + 1, cY + leafHeight + 1);

        // Place north leaf and stem, except when generating two leaves.
        if(leaves != 2) {
            PlaceWallRectangleOutline(world, cX - leafWidth / 2, cY - leafHeight * 2, leafWidth, leafHeight);
            PlaceWallColumn(world, cX, cY - leafHeight, cY);
        }
        
        // Place west and east leaves and stems, except when generating a single leaf.
        if(leaves != 1) {
            PlaceWallRectangleOutline(world, cX - leafWidth * 2, cY - leafHeight / 2, leafWidth, leafHeight);
            PlaceWallRectangleOutline(world, cX + leafWidth + 1, cY - leafHeight / 2, leafWidth, leafHeight);

            PlaceWallRow(world, cX - leafWidth, cY, cX);
            PlaceWallRow(world, cX + 1, cY, cX + leafWidth + 1);
        }

        // Place south leaf if generating four leaves.
        if(leaves == 4) {
            PlaceWallRectangleOutline(world, cX - leafWidth / 2, cY + leafHeight + 1, leafWidth, leafHeight);
        }

        // Place a ball on the north lane so that Charles can find the shamrock.
        int maxOffset = leaves == 1 ? leafWidth / 2 : leafWidth * 3 / 2;
        int ballX = NextRandomInt(cX - maxOffset, cX + maxOffset);

        world.SetBallAt({ballX, 1}, true);

        return world;
    };

private:
    int EnsureUneven(int value) const {
        return value % 2 == 0 ? value + 1 : value;
    }
};
#else
class FindCenterExercise : public RandomExercise {
public:
    FindCenterExercise(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0x7355608, category) {}

protected:
    World Create() override {
        // Controls the number of empty tiles between the center and the walls.
        constexpr int MIN_TILES_H = 2;
        constexpr int MAX_TILES_H = 6;
        constexpr int MIN_TILES_V = 2;
        constexpr int MAX_TILES_V = 6;

        // Create a world with uneven width and height so that there is always a clear center.
        int width = 3 + NextRandomInt(MIN_TILES_H, MAX_TILES_H) * 2;
        int height = 3 + NextRandomInt(MIN_TILES_V, MAX_TILES_V) * 2;
        World world(width, height, {1, 1});

        EncloseInWalls(world);

        return world;
    }
};

class CleanUpExercise : public FindCenterExercise {
public:
    using FindCenterExercise::FindCenterExercise;

protected:
    World Create() override {
        World world = FindCenterExercise::Create();
        int width = world.GetWidth();
        int height = world.GetHeight();

        // Create the T shape of balls.
        PlaceBallRow(world, 1, 1, width - 1);
        PlaceBallColumn(world, width / 2, 1, height - 1);

        world.SetPosition({width / 2, height / 2});

        return world;
    }
};
#endif

class Assignment2 : public Assignment {
public:
    Assignment2() {
        // Create a custom cave agent that calls the student cave_agent twice.
        auto caveAgent = []{
            cave_agent();
            cave_agent();
        };
#if ! USE_LEGACY_BONUS
        // Create a custom bonus agent that calls both parts in one agent.
        auto bonusAgent = []{
            find_center_agent();
            clean_up_agent();
        };
#endif

        // Set up generic test agent.
        AddAgent("Test\tCtrl+0", "Test agent", "", test_agent);

        // Set up mandatory exercises and agents.
        AddExercise(
            new PathExercise("Hansl and Gretl\tAlt+1", "Exercise 2.1: Hansl and Gretl", "Mandatory")
        )->AttachAgent(AddAgent("Hansl and Gretl\tCtrl+1", "Agent for exercise 2.1", "Mandatory", path_agent));
        AddExercise(
            new CaveExercise("Stalactites and Stalagmites\tAlt+2", "Exercise 2.2: Cave", "Mandatory")
        )->AttachAgent(AddAgent("Stalactites and Stalagmites\tCtrl+2", "Agent for exercise 2.2", "Mandatory", caveAgent));

        // Set up bonus exercise and agent.
#if USE_LEGACY_BONUS
        AddExercise(
            new ShamrockExercise("Shamrock\tAlt+3", "Bonus: follow shamrock...", "Bonus")
        )->AttachAgent(AddAgent("Shamrock\tCtrl+3", "Agent for bonus exercise", "Bonus", shamrock_agent));
#else
        AddExercise(
            new FindCenterExercise("Find the center\tAlt+3", "Bonus 2.1: find the center...", "Bonus")
        )->AttachAgent(AddAgent("Find the center\tCtrl+3", "Agent for bonus exercise 2.1", "Bonus", find_center_agent));
        AddExercise(
            new CleanUpExercise("Clean up balls\tAlt+4", "Bonus 2.2: clean up balls...", "Bonus")
        )->AttachAgent(AddAgent("Clean up balls\tCtrl+4", "Agent for bonus exercise 2.2", "Bonus", clean_up_agent));

        AddAgent("Combined\tCtrl+5", "Combines agents for bonus exercise 2.1 and 2.2", "Bonus", bonusAgent);
#endif
    }
};

CREATE_ASSIGNMENT(Assignment2)