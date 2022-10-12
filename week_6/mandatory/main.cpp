
/********************************************************************
    Course: Imperative Programming - Assignment 6
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 12.10.2022
********************************************************************/
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

/********************************************************************
    Global Variable Definitions
********************************************************************/

enum Cell { // a cell is either Dead or Live (we use the fact that dead = 0 and
            // live = 1)
  Dead = 0,
  Live
};

const char DEAD = '.';
const char LIVE = '*';
const int NO_OF_ROWS = 40;
const int NO_OF_COLUMNS = 60;

/********************************************************************
    Function Definitions
********************************************************************/

// Part 1: get cell in bounded universe
Cell cell_at(Cell universe[NO_OF_ROWS][NO_OF_COLUMNS], int row, int column) {
  // pre-condition:
  assert(true);
  // Post-condition: enum type Cell is returned with Dead if cell is read as
  // dead, and live if it is live. Returns Dead if out of bounds.

  if (row > NO_OF_ROWS || row < 0 || column > NO_OF_COLUMNS || column < 0 ||
      (universe[row][column] != Dead && universe[row][column] != Live)) {
    return Dead;
  }

  return universe[row][column];
}

//  Part 2: setting the scene
bool read_universe_file (string filename, Cell universe [NO_OF_ROWS][NO_OF_COLUMNS])
{
    // pre-conditions, post-conditions, implementation
    return false;
}

void show_universe (Cell universe [NO_OF_ROWS][NO_OF_COLUMNS])
{
    // pre-conditions, post-conditions, implementation
}

//  Part 3: the next generation
void next_generation (Cell now [NO_OF_ROWS][NO_OF_COLUMNS], Cell next [NO_OF_ROWS][NO_OF_COLUMNS])
{
    // pre-conditions, post-conditions, implementation
}

#ifndef TESTING
int main ()
{
    return 0;
}
#endif
