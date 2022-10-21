#include "main.cpp"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

const string ALICE_FILENAME = "Alice's Adventures In Wonderland.txt";
const string DESKTOP_FILENAME = "desktop.txt";
const int NO_OF_WORDS_DESKTOP = 10;
string content_desktop [NO_OF_WORDS_DESKTOP] = {"Rose", "is", "a", "rose", "is", "a", "rose", "is", "a", "rose."};
const string VOGON_POEM_FILENAME = "Vogon poem.txt";
const int NO_OF_WORDS_VOGON_POEM = 78;
string content_vogon_poem [NO_OF_WORDS_VOGON_POEM] = {"O", "freddled", "gruntbuggly"
                                                     ,"Thy", "micturations", "are", "to", "me"
                                                     ,"As", "plurdled", "gabbleblotchits", "on", "a", "lurgid", "bee"
                                                     ,"That", "mordiously", "hath", "bitled", "out", "its", "earted", "jurtles"
                                                     ,"Into", "a", "rancid", "festering..."
                                                     ,"Now", "the", "jurpling", "slayjid", "agrocrustules"
                                                     ,"Are", "splurping", "hagrilly", "up", "the", "axlegrurts"
                                                     ,"And", "living", "glupules", "frat", "and", "slipulate"
                                                     ,"Like", "jowling", "meated", "liverslime"
                                                     ,"Groop,", "I", "implore", "thee,", "my", "foonting", "turlingdromes"
                                                     ,"And", "hooptiously", "drangle", "me", "with", "crinkly", "bindlewurdles"
                                                     ,"Or", "else", "I", "shall", "rend", "thee", "in", "the", "gobberwarts", "with", "my", "blurglecruncheon,", "see", "if", "I", "don't."
                                                     };
const int NO_OF_TERMS1_DESKTOP = 1;
const int NO_OF_TERMS2_DESKTOP = 2;
string terms1_desktop [NO_OF_TERMS1_DESKTOP] = {"rose"};
string terms2_desktop [NO_OF_TERMS2_DESKTOP] = {"is", "a"};
const int NO_OF_TERMS1_VOGON_POEM = 1;
const int NO_OF_TERMS2_VOGON_POEM = 2;
string terms1_vogon_poem [NO_OF_TERMS1_VOGON_POEM] = {"the"};
string terms2_vogon_poem [NO_OF_TERMS2_VOGON_POEM] = {"meated", "liverslime"};
const int NO_OF_TERMS1_ALICE = 1;
const int NO_OF_TERMS2_ALICE = 2;
string terms1_alice [NO_OF_TERMS1_ALICE] = {"Alice"};
string terms2_alice [NO_OF_TERMS2_ALICE] = {"White","Rabbit"};

bool equal_content (string data1 [], string data2 [], int length)
{// precondition:
    assert (length >= 0);
/*  postcondition:
    result is true only if the first length words in data1 are equal to the first length words in data2
    (which is true in case of length 0).
*/
    for (int i = 0 ; i < length ; i++)
        if (data1[i] != data2[i])
            return false;       // counter example found, so result is false
    return true;
}

bool content_after_enter_is_equal (string filename, string data [], int length)
{// precondition:
    assert (length >= 0);
/*  postcondition:
    returns true only if first length words that are read from text file with file name filename are equal to the
    the first length words in data.
*/
    const int NO_OF_WORDS_READ = enter_command (filename);
    return equal_content (content, data, length);
}

int result_count_command (string filename, string terms [], int no_of_terms)
{// precondition:
    assert (no_of_terms > 0);
/*  postcondition:
    returns the counted number of occurrences of the sequence of terms in the read content of the text file with file name filename.
*/
    const int NO_OF_WORDS_READ = enter_command (filename);
    return count_command (content, NO_OF_WORDS_READ, terms, no_of_terms);
}

TEST (commands, enter_check_no_of_words)
{
    EXPECT_EQ (enter_command (ALICE_FILENAME), MAX_NO_OF_WORDS);
    EXPECT_EQ (enter_command (VOGON_POEM_FILENAME), NO_OF_WORDS_VOGON_POEM);
    EXPECT_EQ (enter_command (DESKTOP_FILENAME), NO_OF_WORDS_DESKTOP);
}

TEST (commands, enter_check_content)
{
    EXPECT_TRUE (content_after_enter_is_equal (VOGON_POEM_FILENAME, content_vogon_poem, NO_OF_WORDS_VOGON_POEM));
    EXPECT_TRUE (content_after_enter_is_equal (DESKTOP_FILENAME,    content_desktop,    NO_OF_WORDS_DESKTOP));
}

TEST (commands, count)
{
    EXPECT_EQ (result_count_command (DESKTOP_FILENAME,    terms1_desktop,    NO_OF_TERMS1_DESKTOP),    2);
    EXPECT_EQ (result_count_command (DESKTOP_FILENAME,    terms2_desktop,    NO_OF_TERMS2_DESKTOP),    3);
    EXPECT_EQ (result_count_command (VOGON_POEM_FILENAME, terms1_vogon_poem, NO_OF_TERMS1_VOGON_POEM), 3);
    EXPECT_EQ (result_count_command (VOGON_POEM_FILENAME, terms2_vogon_poem, NO_OF_TERMS2_VOGON_POEM), 1);
    EXPECT_EQ (result_count_command (ALICE_FILENAME,      terms1_alice,      NO_OF_TERMS1_ALICE),      216);
    EXPECT_EQ (result_count_command (ALICE_FILENAME,      terms2_alice,      NO_OF_TERMS2_ALICE),      9);
}
