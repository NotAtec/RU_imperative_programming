#include "main.cpp"
#include "gtest/gtest.h"

#include <sstream>

const static vector<Track> TEST_DB = {
                        {"Adele",                          "19",                          2008,1, "Daydreamer",                  "pop,debut album",                   { 3,40},"England"}
                       ,{"Adele",                          "19",                          2008,10,"My same",                     "pop,debut album",                   { 3,15},"England"}
                       ,{"Adele",                          "19",                          2008,11,"Tired",                       "pop,debut album",                   { 4,18},"England"}
                       ,{"Adele",                          "19",                          2008,12,"Hometown glory",              "pop,debut album",                   { 4,31},"England"}
                       ,{"Adele",                          "19",                          2008,2, "Best for last",               "pop,debut album",                   { 4,18},"England"}
                       ,{"Adele",                          "19",                          2008,3, "Chasing pavements",           "pop,debut album",                   { 3,30},"England"}
                       ,{"Adele",                          "19",                          2008,4, "Cold shoulder",               "pop,debut album",                   { 3,11},"England"}
                       ,{"Adele",                          "19",                          2008,5, "Crazy for you",               "pop,debut album",                   { 3,28},"England"}
                       ,{"Adele",                          "19",                          2008,6, "Melt my heart to stone",      "pop,debut album",                   { 3,23},"England"}
                       ,{"Adele",                          "19",                          2008,7, "First love",                  "pop,debut album",                   { 3,10},"England"}
                       ,{"Adele",                          "19",                          2008,8, "Right as rain",               "pop,debut album",                   { 3,17},"England"}
                       ,{"Adele",                          "19",                          2008,9, "Make you feel my love",       "pop,debut album",                   { 3,32},"England"}
                       ,{"Adele",                          "21",                          2011,1, "Rolling in the deep",         "pop",                               { 3,49},"England"}
                       ,{"Adele",                          "21",                          2011,10,"Lovesong",                    "pop",                               { 5,16},"England"}
                       ,{"Adele",                          "21",                          2011,11,"Someone like you",            "pop",                               { 4,47},"England"}
                       ,{"Adele",                          "21",                          2011,2, "Rumour has it",               "pop",                               { 3,43},"England"}
                       ,{"Adele",                          "21",                          2011,3, "Turning tables",              "pop",                               { 4,10},"England"}
                       ,{"Adele",                          "21",                          2011,4, "Don't you remember",          "pop",                               { 4, 3},"England"}
                       ,{"Adele",                          "21",                          2011,5, "Set fire to the rain",        "pop",                               { 4, 1},"England"}
                       ,{"Adele",                          "21",                          2011,6, "He won't go",                 "pop",                               { 4,37},"England"}
                       ,{"Adele",                          "21",                          2011,7, "Take it all",                 "pop",                               { 3,48},"England"}
                       ,{"Adele",                          "21",                          2011,8, "I'll be waiting",             "pop",                               { 4, 1},"England"}
                       ,{"Adele",                          "21",                          2011,9, "One and only",                "pop",                               { 5,48},"England"}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,1, "Call me star",                "alternative,rock",                  { 3,54},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,2, "El centro",                   "alternative,rock,instrumental",     { 8,25},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,3, "Dirt preachers",              "alternative,rock",                  { 3,44},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,4, "This is where it falls apart","alternative,rock",                  { 7, 2},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,5, "Mellowing",                   "alternative,instrumental",          { 3,11},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,6, "Open passageways",            "alternative,rock",                  { 3,14},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,7, "Instrumental 2 (welcome to the caveman future)","alternative,rock,instrumental",     { 2,33},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,8, "Talisman",                    "alternative,rock",                  { 6, 7},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,9, "Blood and sand / milk and endless waters","alternative,rock",      { 7,20},"U.S.A."}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,1, "The sun roars into view",     "jazz,instrumental,experimental",    { 7,37},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was"  ,2015,2, "Won't be a thing to become",  "jazz,instrumental,experimental",    { 3,24},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,3, "In the vespers",              "jazz,instrumental,experimental",    { 6, 2},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,4, "And still they move",         "jazz,instrumental,experimental",    { 2,56},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,5, "With the dark hug of time",   "jazz,instrumental,experimental",    { 6,34},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,6, "The rest of us",              "jazz,instrumental,experimental",    { 6,30},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,7, "Never were the way she was",  "jazz,instrumental,experimental",    { 8,12},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,8, "Flight",                      "jazz,instrumental,experimental",    { 1,38},"U.S.A.,Canada"}
                       ,{"The decemberists",               "The tain",                    2005,1, "The tain (parts i-iv)",       "progressive,experimental,folk,rock",{18,35},"U.S.A."}
                       } ;

bool operator== (const Length& a, const Length& b)
{// Precondition:
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*  Postcondition:
    Result is true only if a and b represent the same time length
*/
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator== (const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    Result is true only if all fields of a and b are equal
*/
    return a.artist  == b.artist  &&
           a.cd      == b.cd      &&
           a.country == b.country &&
           a.tags    == b.tags    &&
           a.time    == b.time    &&
           a.title   == b.title   &&
           a.track   == b.track   &&
           a.year    == b.year;
}

TEST(operators, length_add)
{
    const int NUM_TESTS = 9;
    const Length L1     = {42,55};
    const Length L2     = { 3, 4};
    const Length L3     = {24, 6};
    const Length ACTUAL[NUM_TESTS] = {
        L1+L1,
        L1+L2,
        L1+L3,
        L2+L1,
        L2+L2,
        L2+L3,
        L3+L1,
        L3+L2,
        L3+L3
    };
    const Length EXPECTED[NUM_TESTS] = {
        Length{85,50},
        Length{45,59},
        Length{67, 1},
        Length{45,59},
        Length{ 6, 8},
        Length{27,10},
        Length{67, 1},
        Length{27,10},
        Length{48,12},
    };

    for (int i = 0 ; i < 9 ; i++) {
        EXPECT_EQ (EXPECTED[i], ACTUAL[i]);
    }
}

TEST(operators, length_input)
{
    const int NUM_TESTS = 8;
    const string INPUT[NUM_TESTS] = {
        "0:0",
        "1:2",
        "00:01",
        "123:45",
        "  1:08",
        "2:32      ",
        "   \t4:53 ",
        " \n 3:52"
    };
    const Length EXPECTED[NUM_TESTS] = {
        {0, 0},
        {1, 2},
        {0, 1},
        {123, 45},
        {1, 8},
        {2, 32},
        {4, 53},
        {3, 52}
    };

    for(int i = 0; i < NUM_TESTS; ++i) {
        Length actual;
        stringstream ss(INPUT[i]);

        ss >> actual;

        EXPECT_EQ(EXPECTED[i], actual);
    }
}

TEST(operators, length_output)
{
    const int NUM_TESTS = 4;
    const Length INPUT[NUM_TESTS] = {
        {0, 0},
        {1, 2},
        {213, 13},
        {13, 5}
    };
    const string EXPECTED[NUM_TESTS] = {
        "0:00",
        "1:02",
        "213:13",
        "13:05"
    };

    for(int i = 0; i < NUM_TESTS; ++i) {
        stringstream actual;

        actual << INPUT[i];

        EXPECT_EQ(EXPECTED[i], actual.str());
    }
}

TEST(operators, track_input)
{
    const string INPUT =
        "The decemberists\n"
        "The tain\n"
        "2005\n"
        "1\n"
        "The tain (parts i-iv)\n"
        "progressive,experimental,folk,rock\n"
        "18:35\n"
        "U.S.A.\n"
        "\n";
    const Track EXPECTED = {
        "The decemberists",
        "The tain",
        2005,
        1,
        "The tain (parts i-iv)",
        "progressive,experimental,folk,rock",
        {18,35},
        "U.S.A."
    };
    Track actual;
    stringstream ss(INPUT);

    ss >> actual;

    EXPECT_EQ(EXPECTED, actual);
    // Make sure we have consumed the trailing newline as well.
    EXPECT_TRUE(ss.ignore().eof());
}

TEST(operators, track_output1)
{
    const TrackDisplay TD{};
    const Track INPUT = {
        "The decemberists",
        "The tain",
        2005,
        1,
        "The tain (parts i-iv)",
        "progressive,experimental,folk,rock",
        {18,35},
        "U.S.A."
    };
    const string EXPECTED = "";
    stringstream ss;

    show_track(INPUT, TD, ss);

    EXPECT_EQ(EXPECTED, ss.str());
}

TEST(operators, track_output2)
{
    const TrackDisplay TD{true, true, true, true, true, true, true, true};
    const Track INPUT = {
        "The decemberists",
        "The tain",
        2005,
        1,
        "The tain (parts i-iv)",
        "progressive,experimental,folk,rock",
        {18,35},
        "U.S.A."
    };
    const string EXPECTED =
        "The decemberists\n"
        "The tain\n"
        "2005\n"
        "1\n"
        "The tain (parts i-iv)\n"
        "progressive,experimental,folk,rock\n"
        "18:35\n"
        "U.S.A.\n";
    stringstream ss;

    show_track(INPUT, TD, ss);

    EXPECT_EQ(EXPECTED, ss.str());
}

TEST(operators, track_output3)
{
    const TrackDisplay TD{true, false, true, true, false, true, true, false};
    const Track INPUT = {
        "The decemberists",
        "The tain",
        2005,
        1,
        "The tain (parts i-iv)",
        "progressive,experimental,folk,rock",
        {18,35},
        "U.S.A."
    };
    const string EXPECTED =
        "The decemberists\n"
        "2005\n"
        "1\n"
        "progressive,experimental,folk,rock\n"
        "18:35\n";
    stringstream ss;

    show_track(INPUT, TD, ss);

    EXPECT_EQ(EXPECTED, ss.str());
}

TEST(commands, match_tracks1)
{
    const string MATCH = "my";
    const int EXPECTED = 2;
    EXPECT_EQ(EXPECTED, match_tracks(TEST_DB,MATCH,false));
}

TEST(commands, match_tracks2)
{
    const string MATCH = "is";
    const int EXPECTED = 2;
    EXPECT_EQ(EXPECTED, match_tracks(TEST_DB,MATCH,false));
}

TEST(commands, match_tracks3)
{
    const string MATCH = "and";
    const int EXPECTED = 2;
    EXPECT_EQ(EXPECTED, match_tracks(TEST_DB,MATCH,false));
}

TEST(commands, match_artists1)
{
    const string MATCH = "A";
    const int EXPECTED = 2;
    EXPECT_EQ(EXPECTED, match_artists(TEST_DB,MATCH,false));
}

TEST(commands, match_artists2)
{
    const string MATCH = "em";
    const int EXPECTED = 2;
    EXPECT_EQ(EXPECTED, match_artists(TEST_DB,MATCH,false));
}

TEST(commands, match_artists3)
{
    const string MATCH = "ts";
    const int EXPECTED = 2;
    EXPECT_EQ(EXPECTED, match_artists(TEST_DB,MATCH,false));
}

TEST(commands, match_cds1)
{
    const string MATCH = "A";
    const int EXPECTED = 3;
    EXPECT_EQ(EXPECTED, match_cds(TEST_DB,MATCH,false));
}

TEST(commands, match_cds2)
{
    const string MATCH = "em";
    const int EXPECTED = 2;
    EXPECT_EQ(EXPECTED, match_cds(TEST_DB,MATCH,false));
}

TEST(commands, match_cds3)
{
    const string MATCH = "ts";
    const int EXPECTED = 2;
    EXPECT_EQ(EXPECTED, match_cds(TEST_DB,MATCH,false));
}

TEST(commands, number_of_cds)
{
    const int EXPECTED = 5;
    EXPECT_EQ(EXPECTED, number_of_cds(TEST_DB));
}

TEST(read, read_db_with_zero_tracks)
{
    vector<Track> the_tracks;
    EXPECT_EQ(read_tracks ("TracksZeroTrackDB.txt", the_tracks, false), 0);
}

TEST(read, read_db_with_one_track)
{
    vector<Track> the_tracks;
    EXPECT_EQ(read_tracks ("TracksOneTrackDB.txt", the_tracks, false), 1);
}

TEST(read, read_testDB)
{
    vector<Track> the_tracks;
    EXPECT_EQ(read_tracks ("TracksTestDB.txt", the_tracks, false), 41);
    EXPECT_EQ(the_tracks,TEST_DB);
}

TEST(read, read_MusicDB)
{
    vector<Track> the_tracks;
    EXPECT_EQ(read_tracks ("Tracks.txt", the_tracks, false), 6868);
}
