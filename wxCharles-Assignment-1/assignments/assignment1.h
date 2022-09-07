#pragma once

#include "util/include_guard.h"
#include "util/common_worldgen.h"
#include "../framework/assignment.h"

// Function declarations for agents implemented by student.
extern void test_agent();
extern void string_agent();
extern void chaos_agent();
extern void block_agent();

class StringWithBallsExercise : public StaticExercise {
public:
    using StaticExercise::StaticExercise;

protected:
    World Create() override {
        int width = 20;
        int height = 10;

        World world(width, height, {1, 1});

        // Create world that is enclosed in walls, and has a line of balls along the inside walls.
        EncloseInWalls(world);
        PlaceBallRow(world, 1, 1, width - 1);
        PlaceBallRow(world, 1, height - 2, width - 1);
        PlaceBallColumn(world, 1, 2, height - 2);
        PlaceBallColumn(world, width - 2, 2, height - 2);

        return world;
    };
};

class ChaosWithBallsExercise : public RandomExercise {
public:
    ChaosWithBallsExercise(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0x1337c0de, category) {}

protected:
    World Create() override {
        int width = NextRandomInt(20, 30);
        int height = NextRandomInt(20, 25);
        int lanes = NextRandomInt(height / 3, height * 2 / 3);

        World world(width, height, {1, 1});

        EncloseInWalls(world);

        // Place lanes/rows of balls, starting at the top row, and moving down without gaps.
        // Each lane is at least 1 ball long, and always reaches the right-most wall.
        for(int lane = 1; lane <= lanes; ++lane) {
            int start = NextRandomInt(width / 5, width - 2);

            PlaceBallRow(world, start, lane, width - 1);
        }

        return world;
    }
};

class AroundTheBlockExercise : public RandomExercise {
public:
    AroundTheBlockExercise(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0xbeefcafe, category) {}

protected:
    World Create() override {
        int width = NextRandomInt(30, 40);
        int height = NextRandomInt(25, 30);
        int blockX = NextRandomInt(width / 4, width / 2);
        int blockY = NextRandomInt(height / 3, height / 2);
        int blockWidth = NextRandomInt(width / 4, width / 3);
        int blockHeight = NextRandomInt(height / 4, height / 3);

        World world(width, height, {1, 1});

        EncloseInWalls(world);
        PlaceWallRectangleOutline(world, blockX, blockY, blockWidth, blockHeight);

        // Place a ball on the 'northern-most' lane so that Charles can find the 'north-west' corner of the rectangle.
        world.SetBallAt({blockX, 1}, true);

        return world;
    };
};

class Assignment1 : public Assignment {
public:
    Assignment1() {
        // Set up generic test agent.
        AddAgent("Test\tCtrl+0", "Test agent", "", test_agent);

        // Set up mandatory exercises and agents.
        AddExercise(
            new StringWithBallsExercise("String with balls\tAlt+1", "Exercise 1.1: cleaning up a string of balls", "Mandatory")
        )->AttachAgent(AddAgent("String with balls\tCtrl+1", "Agent for exercise 1.1", "Mandatory", string_agent));
        AddExercise(
            new ChaosWithBallsExercise("Chaos with balls\tAlt+2", "Exercise 1.2: cleaning up chaos with balls", "Mandatory")
        )->AttachAgent(AddAgent("Chaos with balls\tCtrl+2", "Agent for exercise 1.2", "Mandatory", chaos_agent));

        // Set up bonus exercise and agent.
        AddExercise(
            new AroundTheBlockExercise("Around the block\tAlt+3", "Bonus: around the block...", "Bonus")
        )->AttachAgent(AddAgent("Around the block\tCtrl+3", "Agent for bonus exercise", "Bonus", block_agent));
    }
};

CREATE_ASSIGNMENT(Assignment1)