#include "main.cpp"
#include "gtest/gtest.h"

TEST(part1, naive_power_base)
{
    EXPECT_EQ(naive_power(0, 0), 1);
    EXPECT_EQ(naive_power(1, 0), 1);
    EXPECT_EQ(naive_power(-1, 0), 1);
    EXPECT_EQ(naive_power(2, 0), 1);
    EXPECT_EQ(naive_power(7, 0), 1);
}

TEST(part1, naive_power_recursive)
{
    EXPECT_EQ(naive_power(0, 1), 0);
    EXPECT_EQ(naive_power(0, 4), 0);
    EXPECT_EQ(naive_power(1, 1), 1);
    EXPECT_EQ(naive_power(1, 3), 1);
    EXPECT_EQ(naive_power(-1, 1), -1);
    EXPECT_EQ(naive_power(-1, 2), 1);
    EXPECT_EQ(naive_power(-1, 5), -1);
    EXPECT_EQ(naive_power(2, 1), 2);
    EXPECT_EQ(naive_power(2, 16), 65536);
    EXPECT_EQ(naive_power(7, 7), 823543);
}

TEST(part1, power_base)
{
    EXPECT_EQ(power(0, 0), 1);
    EXPECT_EQ(power(1, 0), 1);
    EXPECT_EQ(power(-1, 0), 1);
    EXPECT_EQ(power(2, 0), 1);
    EXPECT_EQ(power(7, 0), 1);
}

TEST(part1, power_recursive)
{
    EXPECT_EQ(power(0, 1), 0);
    EXPECT_EQ(power(0, 4), 0);
    EXPECT_EQ(power(1, 1), 1);
    EXPECT_EQ(power(1, 3), 1);
    EXPECT_EQ(power(-1, 1), -1);
    EXPECT_EQ(power(-1, 2), 1);
    EXPECT_EQ(power(-1, 5), -1);
    EXPECT_EQ(power(2, 1), 2);
    EXPECT_EQ(power(2, 16), 65536);
    EXPECT_EQ(power(7, 7), 823543);
}

TEST(part2, palindrome1)
{
    EXPECT_TRUE(palindrome1("", 0, 0));
    EXPECT_TRUE(palindrome1("a", 0, 0));
    EXPECT_TRUE(palindrome1("otto", 0, 3));
    EXPECT_FALSE(palindrome1("Otto", 0, 3));
    EXPECT_FALSE(palindrome1("Oo", 0, 1));
    EXPECT_FALSE(palindrome1("Imperative. Programming", 0, 22));
    EXPECT_FALSE(palindrome1("Madam, I'm Adam.", 0, 15));
}

TEST(part2, palindrome2)
{
    EXPECT_TRUE(palindrome2("", 0, 0));
    EXPECT_TRUE(palindrome2("a", 0, 0));
    EXPECT_TRUE(palindrome2("otto", 0, 3));
    EXPECT_TRUE(palindrome2("Otto", 0, 3));
    EXPECT_TRUE(palindrome2("Oo", 0, 1));
    EXPECT_FALSE(palindrome2("Imperative. Programming", 0, 22));
    EXPECT_FALSE(palindrome2("Madam, I'm Adam.", 0, 15));
}

TEST(part2, palindrome3)
{
    EXPECT_TRUE(palindrome3("", 0, 0));
    EXPECT_TRUE(palindrome3("a", 0, 0));
    EXPECT_TRUE(palindrome3("otto", 0, 3));
    EXPECT_TRUE(palindrome3("Otto", 0, 3));
    EXPECT_TRUE(palindrome2("Oo", 0, 1));
    EXPECT_FALSE(palindrome3("Imperative. Programming", 0, 22));
    EXPECT_TRUE(palindrome3("Madam, I'm Adam.", 0, 15));
}

TEST(part3, match_characters_base)
{
    EXPECT_TRUE(match_chars("", 0, "", 0));
    EXPECT_TRUE(match_chars("", 0, "a", 0));
    EXPECT_FALSE(match_chars("a", 0, "a", 1));
}

TEST(part3, match_characters)
{
    EXPECT_TRUE(match_chars("a", 0, "a", 0));
    EXPECT_FALSE(match_chars("a", 0, "b", 0));
    EXPECT_TRUE(match_chars("a", 0, "ab", 0));
    EXPECT_TRUE(match_chars("a", 0, "ba", 0));
    EXPECT_FALSE(match_chars("ab", 0, "ac", 0));
    EXPECT_TRUE(match_chars("ac", 0, "abc", 0));
    EXPECT_TRUE(match_chars("abc", 0, "abc", 0));
    EXPECT_TRUE(match_chars("abc", 0, "it is a bag of cards", 0));
    EXPECT_FALSE(match_chars("abc", 0, "it is a bag of books", 0));
    EXPECT_FALSE(match_chars("abc", 0, "it is a classy bag", 0));
    EXPECT_TRUE(match_chars("perm", 0, "imperative programming", 0));
    EXPECT_FALSE(match_chars("prime", 0, "imperative programming", 0));
}
