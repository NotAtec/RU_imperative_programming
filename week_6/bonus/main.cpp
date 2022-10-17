
/********************************************************************
    Course: Imperative Programming - Bonus Assignment 6
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 17.10.2022
********************************************************************/
#include "animation.h"
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

void array_copy(Cell source[NO_OF_ROWS][NO_OF_COLUMNS],
                Cell dest[NO_OF_ROWS][NO_OF_COLUMNS]) {
  // Pre-Condition:
  assert(true);
  // Post-Condition: The source array is copied into the destination array.

  for (int i = 0; i < NO_OF_ROWS; i++) {
    for (int j = 0; j < NO_OF_COLUMNS; j++) {
      dest[i][j] = source[i][j];
    }
  }
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

  for (int i = 0; i <= NO_OF_ROWS; i++) {
    for (int j = 0; j <= NO_OF_COLUMNS; j++) {
      if (universe[i][j] != Dead && universe[i][j] != Live)
        cout << Dead;

      cout << universe[i][j];
    }
    cout << endl;
  }
}

// Helper Part 3:
void add_neighbour(Cell universe[NO_OF_ROWS][NO_OF_COLUMNS], int x, int y,
                   int &sum) {
  // Pre-Condition:
  assert(true);
  // Post-condition: One is added to the rolling count if a cell is found to be
  // alive.
  if (cell_at(universe, x, y) == Live)
    sum++;
}

// Helper Part 3, neighbours.
int neighbours(Cell universe[NO_OF_ROWS][NO_OF_COLUMNS], int row, int column) {
  // Pre-Condition:
  assert(true);
  // Post-Condition: The number of neighbours is returned.
  int neighbour_count = 0;

  for(int i = row - 1; i <= row + 1; i++) {
    for(int j = column - 1; j <= column + 1; j++) {
      if(!(i == row && j == column)) {
        if (cell_at(universe, i, j) == Live)
          neighbour_count++;
      }
    }
  }

  return neighbour_count;
}

//  Part 3: the next generation
void next_generation(Cell now[NO_OF_ROWS][NO_OF_COLUMNS],
                     Cell next[NO_OF_ROWS][NO_OF_COLUMNS]) {
  // Pre-Condition:
  assert(true);
  // Post-Condition: Next generation of universe is generated to second array

  for (int row = 0; row < NO_OF_ROWS; row++) {
    for (int col = 0; col < NO_OF_COLUMNS; col++) {
      // Get all alive neighbours
      int alive_neighbours = neighbours(now, row, col);

      // Apply rules
      if (alive_neighbours == 3 ||
          (alive_neighbours == 2 && cell_at(now, row, col) == Live))
        next[row][col] = Live;
      else
        next[row][col] = Dead;
    }
  }
}

#ifndef TESTING
int main() {
  Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
  Cell next[NO_OF_ROWS][NO_OF_COLUMNS];

  string filename;
  ifstream in;
  cout << "Enter filename: ";
  cin >> filename;


  if (!read_universe_file(filename, universe)) {
    cout << "Error reading file " << filename << endl;
    return 1;
  }

  int steps;
  cout << "Enter number of steps: ";
  cin >> steps;

  show_universe(universe);

  for(int i = 0; i < steps; i++) {
    sleep(10);
    clear_screen();
    set_cursor_position(0, 0);

    next_generation(universe, next);
    array_copy(next, universe);
    show_universe(universe);
  }

  ofstream out;
  cout << "Enter output filename, for last instance of universe: ";
  cin >> filename;
  out.open(filename, fstream::out);

  for (int i = 0; i < NO_OF_ROWS; i++) {
    for (int j = 0; j < NO_OF_COLUMNS; j++) {
      out << universe[i][j];
    }
    out << endl;
  }
}
#endif
