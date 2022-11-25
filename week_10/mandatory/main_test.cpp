#include "main.cpp"
#include "gtest/gtest.h"

const vector<Track> TEST_DB = {
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
    ,{"All them witches",               "Dying surfer meets his maker",2015,7, "Instrumental 2 (welcome to the caveman future)"
                                                                                                             ,"alternative,rock,instrumental",     { 2,33},"U.S.A."}
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
};

const vector<Track> TEST_DB_SORTED = {
     {"Adele",                          "19",                          2008,1, "Daydreamer",                  "pop,debut album",                   { 3,40},"England"}
    ,{"Adele",                          "19",                          2008,2, "Best for last",               "pop,debut album",                   { 4,18},"England"}
    ,{"Adele",                          "19",                          2008,3, "Chasing pavements",           "pop,debut album",                   { 3,30},"England"}
    ,{"Adele",                          "19",                          2008,4, "Cold shoulder",               "pop,debut album",                   { 3,11},"England"}
    ,{"Adele",                          "19",                          2008,5, "Crazy for you",               "pop,debut album",                   { 3,28},"England"}
    ,{"Adele",                          "19",                          2008,6, "Melt my heart to stone",      "pop,debut album",                   { 3,23},"England"}
    ,{"Adele",                          "19",                          2008,7, "First love",                  "pop,debut album",                   { 3,10},"England"}
    ,{"Adele",                          "19",                          2008,8, "Right as rain",               "pop,debut album",                   { 3,17},"England"}
    ,{"Adele",                          "19",                          2008,9, "Make you feel my love",       "pop,debut album",                   { 3,32},"England"}
    ,{"Adele",                          "19",                          2008,10,"My same",                     "pop,debut album",                   { 3,15},"England"}
    ,{"Adele",                          "19",                          2008,11,"Tired",                       "pop,debut album",                   { 4,18},"England"}
    ,{"Adele",                          "19",                          2008,12,"Hometown glory",              "pop,debut album",                   { 4,31},"England"}
    ,{"Adele",                          "21",                          2011,1, "Rolling in the deep",         "pop",                               { 3,49},"England"}
    ,{"Adele",                          "21",                          2011,2, "Rumour has it",               "pop",                               { 3,43},"England"}
    ,{"Adele",                          "21",                          2011,3, "Turning tables",              "pop",                               { 4,10},"England"}
    ,{"Adele",                          "21",                          2011,4, "Don't you remember",          "pop",                               { 4, 3},"England"}
    ,{"Adele",                          "21",                          2011,5, "Set fire to the rain",        "pop",                               { 4, 1},"England"}
    ,{"Adele",                          "21",                          2011,6, "He won't go",                 "pop",                               { 4,37},"England"}
    ,{"Adele",                          "21",                          2011,7, "Take it all",                 "pop",                               { 3,48},"England"}
    ,{"Adele",                          "21",                          2011,8, "I'll be waiting",             "pop",                               { 4, 1},"England"}
    ,{"Adele",                          "21",                          2011,9, "One and only",                "pop",                               { 5,48},"England"}
    ,{"Adele",                          "21",                          2011,10,"Lovesong",                    "pop",                               { 5,16},"England"}
    ,{"Adele",                          "21",                          2011,11,"Someone like you",            "pop",                               { 4,47},"England"}
    ,{"All them witches",               "Dying surfer meets his maker",2015,1, "Call me star",                "alternative,rock",                  { 3,54},"U.S.A."}
    ,{"All them witches",               "Dying surfer meets his maker",2015,2, "El centro",                   "alternative,rock,instrumental",     { 8,25},"U.S.A."}
    ,{"All them witches",               "Dying surfer meets his maker",2015,3, "Dirt preachers",              "alternative,rock",                  { 3,44},"U.S.A."}
    ,{"All them witches",               "Dying surfer meets his maker",2015,4, "This is where it falls apart","alternative,rock",                  { 7, 2},"U.S.A."}
    ,{"All them witches",               "Dying surfer meets his maker",2015,5, "Mellowing",                   "alternative,instrumental",          { 3,11},"U.S.A."}
    ,{"All them witches",               "Dying surfer meets his maker",2015,6, "Open passageways",            "alternative,rock",                  { 3,14},"U.S.A."}
    ,{"All them witches",               "Dying surfer meets his maker",2015,7, "Instrumental 2 (welcome to the caveman future)"
                                                                                                             ,"alternative,rock,instrumental",     { 2,33},"U.S.A."}
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
};

TEST(operators_extra, less_than_artist)
{
    const Track TRACK1 = {"artist1", "cd1", 1984, 1, "title", "tags", {1, 1}, "country"};
    const Track TRACK2 = {"artist2", "cd1", 1984, 1, "title", "tags", {1, 1}, "country"};

    EXPECT_LT(TRACK1, TRACK2);
    EXPECT_FALSE(TRACK1 < TRACK1);
    EXPECT_GT(TRACK2, TRACK1);
}

TEST(operators_extra, less_than_cd)
{
    const Track TRACK1 = {"artist1", "cd2", 1984, 1, "title", "tags", {1, 1}, "country"};
    const Track TRACK2 = {"artist1", "cd3", 1984, 1, "title", "tags", {1, 1}, "country"};
    const Track TRACK3 = {"artist2", "cd1", 1984, 1, "title", "tags", {1, 1}, "country"};

    EXPECT_LT(TRACK1, TRACK2);
    EXPECT_FALSE(TRACK1 < TRACK1);
    EXPECT_GT(TRACK2, TRACK1);
    EXPECT_LT(TRACK2, TRACK3);
}

TEST(operators_extra, less_than_year)
{
    const Track TRACK1 = {"artist1", "cd1", 1985, 1, "title", "tags", {1, 1}, "country"};
    const Track TRACK2 = {"artist1", "cd1", 1986, 1, "title", "tags", {1, 1}, "country"};
    const Track TRACK3 = {"artist1", "cd2", 1984, 1, "title", "tags", {1, 1}, "country"};
    const Track TRACK4 = {"artist2", "cd1", 1984, 1, "title", "tags", {1, 1}, "country"};

    EXPECT_LT(TRACK1, TRACK2);
    EXPECT_FALSE(TRACK1 < TRACK1);
    EXPECT_GT(TRACK2, TRACK1);
    EXPECT_LT(TRACK2, TRACK3);
    EXPECT_LT(TRACK2, TRACK4);
}

TEST(operators_extra, less_than_track)
{
    const Track TRACK1 = {"artist1", "cd1", 1984, 2, "title", "tags", {1, 1}, "country"};
    const Track TRACK2 = {"artist1", "cd1", 1984, 3, "title", "tags", {1, 1}, "country"};
    const Track TRACK3 = {"artist1", "cd1", 1985, 1, "title", "tags", {1, 1}, "country"};
    const Track TRACK4 = {"artist1", "cd2", 1984, 1, "title", "tags", {1, 1}, "country"};
    const Track TRACK5 = {"artist2", "cd1", 1984, 1, "title", "tags", {1, 1}, "country"};

    EXPECT_LT(TRACK1, TRACK2);
    EXPECT_FALSE(TRACK1 < TRACK1);
    EXPECT_GT(TRACK2, TRACK1);
    EXPECT_LT(TRACK2, TRACK3);
    EXPECT_LT(TRACK2, TRACK4);
    EXPECT_LT(TRACK2, TRACK5);
}

void debug_database_difference(const vector<Track>& database, const vector<Track>& expected)
{
    /* Use the code below to debug issues with the test failing.
       It could be that only two out of 40+ tracks are swapped due to a tiny
       bug with your < or == operators for example.
       With this code it is much easier to isolate the exact problem cases.
       It does assume the == operator works correctly on Tracks. */
    for(int i = 0; i < size(database); i++) {
        if(database[i] != expected[i]) {
            cout << "Found incorrect element at index " << i << endl;
            cout << "You have:  " << database[i] << endl;
            cout << "Should be: " << expected[i] << endl << endl;
        }
    }
}

/* We would like to test with integers for simplicity, but this is not possible
   with the typedef setup we use for El, as we cannot change it on the fly. If
   we use templated functions we do not have this problem, but this is outside
   the scope of this course. We make due with this improvised solution where we
   create tracks that have empty/equal fields, except for the track number, thus
   allowing us to effectively test with 'integers' as the data that matters.
*/
Track make_track (int n)
{
    return {"", "", 0, n, "", "", {}, ""};
}

TEST(sorting_extra, is_sorted)
{
    const vector<Track> TRACKS = {
        make_track(3),
        make_track(1),
        make_track(2),
        make_track(3),
        make_track(4),
        make_track(5),
        make_track(4),
    };

    EXPECT_TRUE(is_sorted(TRACKS, make_slice(0, 1)));
    EXPECT_FALSE(is_sorted(TRACKS, make_slice(0, 2)));
    EXPECT_TRUE(is_sorted(TRACKS, make_slice(1, 5)));
    EXPECT_FALSE(is_sorted(TRACKS, make_slice(1, 6)));
}

TEST(sorting_extra, insert1)
{
    vector<Track> actual = {
        make_track(1),
        make_track(2),
        make_track(4),
        make_track(5),
        make_track(3)
    };
    const vector<Track> EXPECTED = {
        make_track(1),
        make_track(2),
        make_track(3),
        make_track(4),
        make_track(5)
    };

    insert(actual, make_slice(0, 4));
    EXPECT_EQ(actual, EXPECTED);
}

TEST(sorting_extra, insert_begin)
{
    vector<Track> actual = {
        make_track(1),
        make_track(2),
        make_track(4),
        make_track(5),
        make_track(0)
    };
    const vector<Track> EXPECTED = {
        make_track(0),
        make_track(1),
        make_track(2),
        make_track(4),
        make_track(5)
    };

    insert(actual, make_slice(0, 4));
    EXPECT_EQ(actual, EXPECTED);
}

TEST(sorting_extra, insert_end)
{
    vector<Track> actual = {
        make_track(1),
        make_track(2),
        make_track(4),
        make_track(5),
        make_track(6)
    };
    const vector<Track> EXPECTED = {
        make_track(1),
        make_track(2),
        make_track(4),
        make_track(5),
        make_track(6)
    };

    insert(actual, make_slice(0, 4));
    EXPECT_EQ(actual, EXPECTED);
}

TEST(sorting_extra, max_value_at)
{
    const vector<Track> TRACKS = {
        make_track(1),
        make_track(3),
        make_track(2),
    };
    const int EXPECTED = 1;

    EXPECT_EQ(max_value_at(TRACKS, make_slice(TRACKS)), EXPECTED);
}

TEST(sorting_extra, max_value_at_begin)
{
    const vector<Track> TRACKS = {
        make_track(6),
        make_track(3),
        make_track(2),
    };
    const int EXPECTED = 0;

    EXPECT_EQ(max_value_at(TRACKS, make_slice(TRACKS)), EXPECTED);
}

TEST(sorting_extra, max_value_at_end)
{
    const vector<Track> TRACKS = {
        make_track(1),
        make_track(3),
        make_track(5),
    };
    const int EXPECTED = 2;

    EXPECT_EQ(max_value_at(TRACKS, make_slice(TRACKS)), EXPECTED);
}

TEST(sorting_extra, bubble)
{
    vector<Track> actual = {
        make_track(2),
        make_track(1),
        make_track(5),
        make_track(4),
        make_track(3)
    };
    const vector<Track> EXPECTED = {
        make_track(1),
        make_track(2),
        make_track(4),
        make_track(3),
        make_track(5)
    };

    EXPECT_TRUE(bubble(actual, make_slice(actual)));
    EXPECT_EQ(actual, EXPECTED);
    EXPECT_TRUE(bubble(actual, make_slice(actual)));
}

TEST(sorting_extra, bubble_noswap)
{
    vector<Track> actual = {
        make_track(1),
        make_track(2),
        make_track(3),
        make_track(4),
        make_track(5)
    };
    const vector<Track> EXPECTED = {
        make_track(1),
        make_track(2),
        make_track(3),
        make_track(4),
        make_track(5)
    };

    EXPECT_FALSE(bubble(actual, make_slice(actual)));
    EXPECT_EQ(actual, EXPECTED);
}

TEST(sorting_extra, is_a_heap)
{
    const vector<Track> HEAP1 = {
        make_track(4),
        make_track(3), make_track(2),
        make_track(2), make_track(2), make_track(2), make_track(3)
    };
    const vector<Track> HEAP2 = {
        make_track(4),
        make_track(3), make_track(2),
        make_track(7), make_track(2), make_track(2), make_track(1)
    };

    EXPECT_TRUE(is_a_heap(HEAP1, make_slice(0, 1)));
    EXPECT_TRUE(is_a_heap(HEAP1, make_slice(0, 2)));
    EXPECT_TRUE(is_a_heap(HEAP1, make_slice(0, 3)));
    EXPECT_TRUE(is_a_heap(HEAP1, make_slice(0, 4)));
    EXPECT_TRUE(is_a_heap(HEAP1, make_slice(0, 5)));
    EXPECT_TRUE(is_a_heap(HEAP1, make_slice(0, 6)));
    EXPECT_FALSE(is_a_heap(HEAP1, make_slice(0, 7)));
    EXPECT_TRUE(is_a_heap(HEAP2, make_slice(0, 3)));
    EXPECT_FALSE(is_a_heap(HEAP2, make_slice(0, 4)));
    EXPECT_FALSE(is_a_heap(HEAP2, make_slice(0, 5)));
    EXPECT_FALSE(is_a_heap(HEAP2, make_slice(0, 6)));
    EXPECT_FALSE(is_a_heap(HEAP2, make_slice(0, 7)));
}

TEST(sorting_extra, push_up)
{
    vector<Track> actual = {
        make_track(5),
        make_track(3), make_track(2),
        make_track(2), make_track(1), make_track(1), make_track(4)
    };
    const vector<Track> EXPECTED = {
        make_track(5),
        make_track(3), make_track(4),
        make_track(2), make_track(1), make_track(1), make_track(2)
    };

    push_up(actual, 6);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(sorting_extra, push_up_root)
{
    vector<Track> actual = {
        make_track(5),
        make_track(3), make_track(2),
        make_track(2), make_track(1), make_track(1), make_track(7)
    };
    const vector<Track> EXPECTED = {
        make_track(7),
        make_track(3), make_track(5),
        make_track(2), make_track(1), make_track(1), make_track(2)
    };

    push_up(actual, 6);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(sorting_extra, build_heap)
{
    vector<Track> tracks = {
        make_track(1), make_track(4), make_track(2), make_track(2), make_track(1), make_track(7), make_track(3)
    };

    build_heap(tracks);
    EXPECT_TRUE(is_a_heap(tracks, make_slice(tracks)));
}

TEST(sorting_extra, push_down)
{
    vector<Track> actual = {
        make_track(1),
        make_track(7), make_track(6),
        make_track(4), make_track(5), make_track(3), make_track(2)
    };
    const vector<Track> EXPECTED = {
        make_track(7),
        make_track(5), make_track(6),
        make_track(4), make_track(1), make_track(3), make_track(2)
    };

    push_down(actual, 6);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(sorting_extra, pick_heap)
{
    vector<Track> actual = {
        make_track(7),
        make_track(5), make_track(6),
        make_track(4), make_track(1), make_track(3), make_track(2)
    };
    const vector<Track> EXPECTED = {
        make_track(1), make_track(2), make_track(3), make_track(4), make_track(5), make_track(6), make_track(7)
    };

    pick_heap(actual);
    EXPECT_EQ(actual, EXPECTED);
}

TEST(sorting, insertion_sort)
{
    vector<Track> database = TEST_DB;
    insertion_sort(database);
    debug_database_difference(database, TEST_DB_SORTED);
    EXPECT_EQ(TEST_DB_SORTED, database);
}

TEST(sorting, selection_sort)
{
    vector<Track> database = TEST_DB;
    selection_sort(database);
    debug_database_difference(database, TEST_DB_SORTED);
    EXPECT_EQ(TEST_DB_SORTED, database);
}

TEST(sorting, bubble_sort)
{
    vector<Track> database = TEST_DB;
    bubble_sort(database);
    debug_database_difference(database, TEST_DB_SORTED);
    EXPECT_EQ(TEST_DB_SORTED, database);
}

TEST(sorting, heap_sort)
{
    vector<Track> database = TEST_DB;
    heap_sort(database);
    debug_database_difference(database, TEST_DB_SORTED);
    EXPECT_EQ(TEST_DB_SORTED, database);
}
