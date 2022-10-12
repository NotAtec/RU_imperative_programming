#include "main.cpp"
#include "gtest/gtest.h"

// Note that the following array declarations only initialize 12x12 grids.
// The NO_OF_ROWS and NO_OF_COLUMNS constants have values 40 and 60 however.
// In this case the 'missing' values will be 'zero-initialized'.
// This means they will have the value 0, which corresponds to the enum member
// Dead. Effectively we only describe a portion of the top-left part of the
// universe to test with. The rest of the universe will implicitly be made up of
// dead cells.
Cell glider0[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Live, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

Cell glider1[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Live, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

Cell glider2[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Live, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

Cell glider3[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

Cell glider4[NO_OF_ROWS][NO_OF_COLUMNS] = {
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Live, Live, Live, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Live, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
    {Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead},
};

void array_copy(Cell source[NO_OF_ROWS][NO_OF_COLUMNS],
                Cell dest[NO_OF_ROWS][NO_OF_COLUMNS]) {
  for (int i = 0; i < NO_OF_ROWS; i++) {
    for (int j = 0; j < NO_OF_COLUMNS; j++) {
      dest[i][j] = source[i][j];
    }
  }
}

// Check if the inner part of two universes match.
// Note that by design the outer dead frame is not checked.
bool generation_match(Cell generation[NO_OF_ROWS][NO_OF_COLUMNS],
                      Cell reference[NO_OF_ROWS][NO_OF_COLUMNS]) {
  for (int i = 0; i < NO_OF_ROWS; i++) {
    for (int j = 0; j < NO_OF_COLUMNS; j++) {
      if (generation[i][j] != reference[i][j])
        return false;
    }
  }

  return true;
}

TEST(part1, cell_at) {
  Cell universe[NO_OF_ROWS][NO_OF_COLUMNS] = {
      {Live, Dead},
      {Dead, Live},
  };

  EXPECT_EQ(cell_at(universe, 0, 0), Live);
  EXPECT_EQ(cell_at(universe, 0, 1), Dead);
  EXPECT_EQ(cell_at(universe, 1, 0), Dead);
  EXPECT_EQ(cell_at(universe, 1, 1), Live);
  EXPECT_EQ(cell_at(universe, -1, -1), Dead);
  EXPECT_EQ(cell_at(universe, 0, NO_OF_COLUMNS + 10), Dead);
  EXPECT_EQ(cell_at(universe, -5, 0), Dead);
  EXPECT_EQ(cell_at(universe, NO_OF_ROWS, 0), Dead);
  EXPECT_EQ(cell_at(universe, NO_OF_ROWS + 4, NO_OF_COLUMNS + 8), Dead);
}

TEST(part2, read_universe_ok) {
  Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
  Cell expected[NO_OF_ROWS][NO_OF_COLUMNS] = {};
  expected[37][2] = Live;
  expected[37][3] = Live;
  expected[37][4] = Live;
  expected[38][4] = Live;
  expected[39][3] = Live;

  EXPECT_TRUE(read_universe_file("glider0.txt", universe));
  EXPECT_TRUE(generation_match(universe, expected));
}

TEST(part2, read_universe_missing) {
  Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
  EXPECT_FALSE(read_universe_file("this-file-does-not-exist.txt", universe));
}

TEST(part2, read_universe_bad_format1) {
  Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
  EXPECT_FALSE(read_universe_file("bad_format_1.txt", universe));
}

TEST(part2, read_universe_bad_format2) {
  Cell universe[NO_OF_ROWS][NO_OF_COLUMNS];
  EXPECT_FALSE(read_universe_file("bad_format_2.txt", universe));
}

TEST(part3, glider_0) {
  Cell now[NO_OF_ROWS][NO_OF_COLUMNS];
  Cell next[NO_OF_ROWS][NO_OF_COLUMNS];
  array_copy(glider0, now);
  next_generation(now, next);
  EXPECT_TRUE(generation_match(next, glider1));
}

TEST(part3, glider_1) {
  Cell now[NO_OF_ROWS][NO_OF_COLUMNS];
  Cell next[NO_OF_ROWS][NO_OF_COLUMNS];
  array_copy(glider1, now);
  next_generation(now, next);
  EXPECT_TRUE(generation_match(next, glider2));
}

TEST(part3, glider_2) {
  Cell now[NO_OF_ROWS][NO_OF_COLUMNS];
  Cell next[NO_OF_ROWS][NO_OF_COLUMNS];
  array_copy(glider2, now);
  next_generation(now, next);
  EXPECT_TRUE(generation_match(next, glider3));
}

TEST(part3, glider_3) {
  Cell now[NO_OF_ROWS][NO_OF_COLUMNS];
  Cell next[NO_OF_ROWS][NO_OF_COLUMNS];
  array_copy(glider3, now);
  next_generation(now, next);
  EXPECT_TRUE(generation_match(next, glider4));
}
