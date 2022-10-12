
/********************************************************************
    Course: Imperative Programming - Assignment 6
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 12.10.2022
********************************************************************/
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

/********************************************************************
    Global Variable Definitions
********************************************************************/

enum Cell {Dead=0, Live};                         // a cell is either Dead or Live (we use the fact that dead = 0 and live = 1)

const char DEAD             = '.' ;               // the presentation of a dead cell (both on file and screen)
const char LIVE             = '*' ;               // the presentation of a live cell (both on file and screen)
const int NO_OF_ROWS        = 40 ;                // the number of rows (height) of the universe (both on file and screen)
const int NO_OF_COLUMNS     = 60 ;                // the number of columns (width) of the universe (both on file and screen)

/********************************************************************
    Function Definitions
********************************************************************/

// Part 1: get cell in bounded universe
Cell cell_at (Cell universe [NO_OF_ROWS][NO_OF_COLUMNS], int row, int column)
{
    // pre-conditions, post-conditions, implementation
    return Dead;
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
