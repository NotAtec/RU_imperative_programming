#include "main.cpp"
#include "gtest/gtest.h"

/*
    3. compute the optimal gifts
    4. check that the remaining budget has the correct value
*/

TEST(giftstore_test, handles_empty_input) {
  load_giftstore("giftstore_empty.txt");
  EXPECT_EQ(giftstore.size(), 0);
}

TEST(giftstore_test, handles_correct_input) {
  load_giftstore("giftstore.txt");
  EXPECT_EQ(giftstore.size(), 70);
  EXPECT_EQ(giftstore[0].name, "book La sombra del viento by C.R. Zafon");
  EXPECT_EQ(giftstore[0].price, 995);
}

TEST(wishlist_test, handles_empty_input) {
  load_wishlist("wishlist_empty.txt", 1);
  EXPECT_EQ(wishlist[1].size(), 0);
}

TEST(wishlist_test, handles_correct_input) {
  load_wishlist("Andrew.txt", 0);
  EXPECT_EQ(wishlist[0].size(), 10);
  EXPECT_EQ(budgets[0], 5000);
  gift test = {1799, "cd A Darker Shade Of White by Navarone"};
  EXPECT_EQ(wishlist[0].at(0), test);
}

TEST(validity_test, handles_input) {
  vector<gift> list = {{1, "a"}, {2, "b"}, {3, "c"}};
  EXPECT_TRUE(valid(list));
  list = {{-1, "a"}, {2, "b"}, {3, "c"}, {2, "d"}};
  EXPECT_FALSE(valid(list));
}

TEST(improve_test, handles_empty_input) {
  vector<gift> cur;
  vector<gift> best;
  improve(cur, best);
  EXPECT_EQ(best.size(), 0);
}

TEST(improve_test, handles_input) {
  vector<gift> cur = {{1, "a"}, {2, "b"}, {3, "c"}};
  vector<gift> best = {{1, "a"}};
  improve(cur, best);
  EXPECT_EQ(best.size(), 3);

  cur = {{2, "b"}, {3, "c"}};
  best = {{1, "a"}, {2, "b"}, {3, "c"}};
  improve(cur, best);
  EXPECT_EQ(best.size(), 3);
}

TEST(sum_test, handles_empty_input) {
  vector<gift> list;
  EXPECT_EQ(sum(list, 0), 0);
}

TEST(sum_test, handles_input) {
  vector<gift> list = {{1, "a"}, {2, "b"}, {3, "c"}};
  EXPECT_EQ(sum(list, 0), 6);
  EXPECT_EQ(sum(list, 1), 5);
  EXPECT_EQ(sum(list, 2), 3);
  EXPECT_EQ(sum(list, 3), 0);
}

TEST(minimum_test, handles_empty_input) {
  vector<gift> list;
  EXPECT_EQ(minimum(list, 0), 0);
}

TEST(minimum_test, handles_input) {
  vector<gift> list = {{1, "a"}, {2, "b"}, {3, "c"}};
  EXPECT_EQ(minimum(list, 0), 1);
  EXPECT_EQ(minimum(list, 1), 2);
  EXPECT_EQ(minimum(list, 2), 3);
  EXPECT_EQ(minimum(list, 3), 0);
}

TEST(gifts_test, handles_inputs) {
  vector<gift> cur, best;
  vector<gift> wishlist = {{1, "a"}, {2, "b"}, {3, "c"}};
  int res = gifts(cur, best, wishlist, 0, 0);
  EXPECT_EQ(best.size(), 0);

  res = gifts(cur, best, wishlist, 0, 1);
  EXPECT_EQ(res, 0);
  EXPECT_EQ(best.size(), 1);

  res = gifts(cur, best, wishlist, 0, 3);
  EXPECT_EQ(best.size(), 2);
  EXPECT_EQ(res, 0);

  res = gifts(cur, best, wishlist, 0, 7);
  EXPECT_EQ(best.size(), 3);
  EXPECT_EQ(res, 1);
}

TEST(gifts_test, andrew_example) {
  vector<gift> cur, best;
  load_wishlist("Andrew.txt", 0);
  int res = gifts(cur, best, wishlist[0], 0, budgets[0]);

  EXPECT_EQ(res, 2);
}