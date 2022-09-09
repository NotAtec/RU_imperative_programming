#pragma once

#include "../../framework/world.h"

// Disable unused function warnings on GCC/Clang.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

static int Min(int a, int b) {
    return a < b ? a : b;
}

static int Max(int a, int b) {
    return a > b ? a : b;
}

static void PlaceBallRow(World& world, int x1, int y, int x2) {
    for(int x = x1; x < x2; ++x) {
        world.SetBallAt({x, y}, true);
    }
}

static void PlaceBallColumn(World& world, int x, int y1, int y2) {
    for(int y = y1; y < y2; ++y) {
        world.SetBallAt({x, y}, true);
    }
}

static void PlaceWallRow(World& world, int x1, int y, int x2) {
    for(int x = x1; x < x2; ++x) {
        world.SetTileAt({x, y}, {TileType::Wall, false});
    }
}

static void PlaceWallColumn(World& world, int x, int y1, int y2) {
    for(int y = y1; y < y2; ++y) {
        world.SetTileAt({x, y}, {TileType::Wall, false});
    }
}

static void PlaceWallRectangleOutline(World& world, int x, int y, int w, int h) {
    // Place walls along top and bottom rows of the rectangle outline.
    PlaceWallRow(world, x, y, x + w);
    PlaceWallRow(world, x, y + h - 1, x + w);

    // Place walls along left and right columns of the rectangle outline.
    PlaceWallColumn(world, x, y + 1, y + h - 1);
    PlaceWallColumn(world, x + w - 1, y + 1, y + h - 1);
}

static void EncloseInWalls(World& world) {
    int width = static_cast<int>(world.GetWidth());
    int height = static_cast<int>(world.GetHeight());

    PlaceWallRectangleOutline(world, 0, 0, width, height);
}

// Restore unused function warnings on GCC/Clang.
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif