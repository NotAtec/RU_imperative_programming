
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

// Helper Part 3:
void add_neighbour(Cell universe[NO_OF_ROWS][NO_OF_COLUMNS], int x, int y, int &sum) {
  // Pre-Condition:
  assert(x > -1 && x < NO_OF_ROWS + 1 && y > -1 && y < NO_OF_COLUMNS + 1);
  // Post-condition: One is added to the rolling count if a cell is found to be alive. 
  if(cell_at(universe, x, y) == Live)
    sum++;
}

//  Part 3: the next generation
void next_generation(Cell now[NO_OF_ROWS][NO_OF_COLUMNS],
                     Cell next[NO_OF_ROWS][NO_OF_COLUMNS]) {
  // Pre-Condition:
  assert(true);
  // Post-Condition: Next generation of universe is generated to second array

  for (int row = 0; row < NO_OF_ROWS; row++) {
    for(int col = 0; col < NO_OF_COLUMNS; col++) {
      // Get all alive neighbours
      int alive_neighbours = 0;
      int x = row -1;
      int y = col -1;
      
      add_neighbour(now, x, y, alive_neighbours);
      y++;
      add_neighbour(now, x, y, alive_neighbours);
      y++;
      add_neighbour(now, x, y, alive_neighbours);
      x++;
      add_neighbour(now, x, y, alive_neighbours);
      y = y - 2;
      add_neighbour(now, x, y, alive_neighbours);
      x++;
      add_neighbour(now, x, y, alive_neighbours);
      y++;
      add_neighbour(now, x, y, alive_neighbours);
      y++;
      add_neighbour(now, x, y, alive_neighbours);

      // Apply rules
      if(alive_neighbours == 3 || (alive_neighbours == 2 && cell_at(now, row, col) == Live))
        next[row][col] = Live;
      else
        next[row][col] = Dead;
    }
  }
}

#ifndef TESTING
int main() { 
  Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
  Cell step[NO_OF_ROWS][NO_OF_COLUMNS];

  read_universe_file("glider0.txt", universe);

  show_universe(universe);
  next_generation(universe, step);
  show_universe(step);
}
#endif
