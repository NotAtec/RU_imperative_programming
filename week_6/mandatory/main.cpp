
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
    Helper Functions
********************************************************************/

// Override the cout operator so we can print out dead and alive characters
// easier.
ostream &operator<<(ostream &out, Cell c) {
  // Pre-Condition: -> Assert true is used to keep all exception handling as in
  // the original handling.
  assert(true);
  // Post-condition: Regular << functionality is done, or the character for DEAD
  // or LIVE is processed if an enum is passed.

  switch (c) {
  case Dead:
    out << DEAD;
    break;
  case Live:
    out << LIVE;
    break;
  }

  return out;
}

Cell char_to_cell(char c) {
  // Pre-Condition:
  assert(c == DEAD || c == LIVE);
  // Post-Condition: A cell enum is returned with value that is equivalent to
  // the character given as input.

  if (c == DEAD)
    return Dead;

  return Live;
}

bool process_line(Cell universe[NO_OF_ROWS][NO_OF_COLUMNS], string line,
                  int &row, int &col) {
  // Pre-condition:
  assert(row >= 0 && col >= 0);
  // Post-Condition: A line of characters is checked for correct value, and then
  // put into the array as an enum.

  for (char c : line) {
    if (c != DEAD && c != LIVE)
      return false;

    universe[row][col] = char_to_cell(c);
    col++;
  }
  return true;
}

/********************************************************************
    Conway's Game of Life
********************************************************************/

// Part 1: get cell in bounded universe
Cell cell_at(Cell universe[NO_OF_ROWS][NO_OF_COLUMNS], int row, int column) {
  // pre-condition:
  assert(true);
  // Post-condition: enum type Cell is returned with Dead if cell is read as
  // dead, and live if it is live. Returns Dead if out of bounds.

  if (row > NO_OF_ROWS || row < 0 || column > NO_OF_COLUMNS || column < 0 ||
      (universe[row][column] != Dead && universe[row][column] != Live))
    return Dead;

  return universe[row][column];
}

//  Part 2: setting the scene
bool read_universe_file(string filename,
                        Cell universe[NO_OF_ROWS][NO_OF_COLUMNS]) {
  // Pre-Condition:
  assert(true);
  // Post-Condition: Iff no errors occur, true is returned && universe array
  // will have loaded in universe from text-file.

  ifstream config;
  config.open(filename);

  if (config.fail())
    return false;

  int row = 0;
  int col = 0;

  for (string line; getline(config, line);) {
    if (!process_line(universe, line, row, col))
      return false;

    if (col < NO_OF_COLUMNS)
      return false;

    col = 0;
    row++;
  }

  if (row < NO_OF_ROWS)
    return false;

  return true;
}

void show_universe(Cell universe[NO_OF_ROWS][NO_OF_COLUMNS]) {
  // Pre-Condition:
  assert(true);
  // Post-Condition: Universe is printed to console.

  cout << "Universe:\n\n";
  for (int i = 0; i <= NO_OF_ROWS; i++) {
    for (int j = 0; j <= NO_OF_COLUMNS; j++) {
      if (universe[i][j] != Dead && universe[i][j] != Live)
        cout << Dead;

      cout << universe[i][j];
    }
    cout << endl;
  }
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
