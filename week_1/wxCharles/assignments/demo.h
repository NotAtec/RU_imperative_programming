#pragma once

#include "util/include_guard.h"
#include "util/common_worldgen.h"
#include "../framework/assignment.h"

// Function declarations for agents implemented by student.
extern void test_agent();
extern void static_agent();
extern void random_agent();
extern void exercise1_agent();
extern void exercise2_agent();

class DemoExercise : public StaticExercise {
public:
    // Inherit constructor from parent.
    using StaticExercise::StaticExercise;

protected:
    World Create() override {
        constexpr int WIDTH = 23;
        constexpr int HEIGHT = 24;
        constexpr int SPIRALS = 23;

        World world(WIDTH, HEIGHT, {WIDTH / 2, HEIGHT / 2}, DIR_NORTH);

        EncloseInWalls(world);

        int length = 1;
        Position pos = {WIDTH / 2 - 1, HEIGHT / 2};

        for(int i = 0; i < SPIRALS; ++i) {
            if(i % 4 == 0) {
                PlaceWallColumn(world, pos.x, pos.y, pos.y + length);
                pos.y += length;
            } else if(i % 4 == 1) {
                PlaceWallRow(world, pos.x, pos.y, pos.x + length + 1);
                pos.x += length;
            } else if(i % 4 == 2) {
                PlaceWallColumn(world, pos.x, pos.y - length, pos.y);
                pos.y -= length;
            } else {
                PlaceWallRow(world, pos.x - length, pos.y, pos.x);
                pos.x -= length;
            }

            length++;
        }

        world.SetTileAt({0, 1}, {TileType::Ground, true});

        return world;
    }
};

class DemoRandomExercise : public RandomExercise {
public:
    DemoRandomExercise(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0x1337abcd, category) {}

protected:
    World Create() override {
        int width = NextRandomInt(25, 30);
        int height = NextRandomInt(20, 25);
        int splitX = NextRandomInt(5, width-10);

        World world(width, height, {1, 1});

        EncloseInWalls(world);

        PlaceBallRow(world, 1, 1, splitX);
        PlaceBallColumn(world, splitX, 1, height - 2);
        PlaceBallRow(world, splitX, height - 2, width - 1);

        PlaceWallColumn(world, splitX + 1, 1, height - 2);
        PlaceWallColumn(world, splitX - 1, 2, height - 1);

        return world;
    }
};

class Exercise1 : public StaticExercise {
public:
    // Inherit constructor from parent.
    using StaticExercise::StaticExercise;

protected:
    World Create() override {
        World world(5, 3, {1, 1});

        EncloseInWalls(world);
        world.SetBallAt({3, 1}, true);

        return world;
    }
};

class Exercise2 : public RandomExercise {
public:
    Exercise2(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0xabcdef, category) {}

protected:
    World Create() override {
        int width = NextRandomInt(5, 10);
        int ballX = NextRandomInt(2, width - 2);

        World world(width, 3, {1, 1});

        EncloseInWalls(world);
        world.SetBallAt({ballX, 1}, true);

        return world;
    }
};

class DemoAssignment : public Assignment {
public:
    DemoAssignment() {
        AddAgent("Test\tCtrl+0", "Test agent", "", test_agent);

        AddExercise(
            new DemoExercise("Static demo\tAlt+1", "Demonstrate a static exercise", "Demo")
        )->AttachAgent(AddAgent("Static\tCtrl+1", "Agent for the static demo exercise", "Demo", static_agent));
        AddExercise(
            new DemoRandomExercise("Random demo\tAlt+2", "Demonstrate a random exercise", "Demo")
        )->AttachAgent(AddAgent("Random\tCtrl+2", "Agent for the random demo exercise", "Demo", random_agent));

        AddExercise(
            new Exercise1("Exercise1\tAlt+3", "First example exercise", "Example")
        )->AttachAgent(AddAgent("Exercise1\tCtrl+3", "Agent for the first example exercise", "Example", exercise1_agent));
        AddExercise(
            new Exercise2("Exercise2\tAlt+4", "Second example exercise", "Example")
        )->AttachAgent(AddAgent("Exercise2\tCtrl+4", "Agent for the second example exercise", "Example", exercise2_agent));
    }
};

CREATE_ASSIGNMENT(DemoAssignment)