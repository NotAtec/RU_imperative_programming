#include "main.cpp"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>

using namespace std;

TEST(part_one, encryptControl)
{
    for(int c = 0; c < 32; c++) {
        for(int r : {0, 1, 32, 42, 96, 65535, 45774747}) {
            EXPECT_EQ(rotate_char(c, r, Encrypt), c);
        }
    }
}

TEST(part_one, encryptOther)
{
    EXPECT_EQ(rotate_char(' ', 0, Encrypt), ' ');
    EXPECT_EQ(rotate_char('1', 1, Encrypt), '2');
    EXPECT_EQ(rotate_char('a', 32, Encrypt), '!');
    EXPECT_EQ(rotate_char('G', 42, Encrypt), 'q');
    EXPECT_EQ(rotate_char('#', 96, Encrypt), '#');
    EXPECT_EQ(rotate_char('@', 65535, Encrypt), '\x7f');
    EXPECT_EQ(rotate_char('~', 45774747, Encrypt), '9');
}

TEST(part_one, decryptControl)
{
    for(int c = 0; c < 32; c++) {
        for(int r : {0, 1, 32, 42, 96, 65535, 45774747}) {
            EXPECT_EQ(rotate_char(c, r, Decrypt), c);
        }
    }
}

TEST(part_one, decryptOther)
{
    EXPECT_EQ(rotate_char(' ', 0, Decrypt), ' ');
    EXPECT_EQ(rotate_char('2', 1, Decrypt), '1');
    EXPECT_EQ(rotate_char('!', 32, Decrypt), 'a');
    EXPECT_EQ(rotate_char('q', 42, Decrypt), 'G');
    EXPECT_EQ(rotate_char('#', 96, Decrypt), '#');
    EXPECT_EQ(rotate_char('\x7f', 65535, Decrypt), '@');
    EXPECT_EQ(rotate_char('9', 45774747, Decrypt), '~');
}

TEST(part_one, inverse)
{
    for (int c = 0; c < 128; c++) {
        for(int r : {0, 1, 32, 42, 96, 65535, 45774747}) {
            EXPECT_EQ(rotate_char(rotate_char(c, r, Encrypt), r, Decrypt), c);
        }
    }
}

/* This code is used to unit test functions that operate on streams. You do not
   need to understand what it is doing. */
class OTPTest : public testing::Test {
protected:
    ifstream infile;
    ofstream outfile;

    void SetUp() override {
        infile.open("test.txt");
    };

    void TearDown() override {
        infile.close();
        outfile.close();
        outfile.clear();
    }
};

static bool streams_match(istream& ins, istream& refs) {
    char c, refc;

    // Loop over every character in the reference stream.
    while(refs.get(refc)) {
        // The input stream must also be able to read a character.
        // It must also match the reference character read from the reference stream.
        if(!ins.get(c) || c != refc) {
            return false;
        }
    }

    // Once the reference stream has reached the end, the input stream must also be fully consumed.
    // This guards against the input stream having additional characters.
    return !ins.get(c);
}

TEST_F(OTPTest, use_OTP_1)
{
    string valueout = "output1.txt";
    outfile.open(valueout.c_str());
    use_OTP(infile, outfile, Encrypt, 1);
    outfile.close();

    ifstream output, outputcheck;
    output.open(valueout.c_str());
    outputcheck.open("test_encrypted_with_1.txt");

    EXPECT_TRUE(streams_match(output, outputcheck));
}

TEST_F (OTPTest, use_OTP_42)
{
    string valueout = "output42.txt";
    outfile.open(valueout.c_str());
    use_OTP(infile, outfile, Encrypt, 42);
    outfile.close();

    ifstream output, outputcheck;
    output.open(valueout.c_str());
    outputcheck.open("test_encrypted_with_42.txt");

    EXPECT_TRUE(streams_match(output, outputcheck));
}

TEST_F (OTPTest, use_OTP_96)
{
    string valueout = "output96.txt";
    outfile.open(valueout.c_str());
    use_OTP(infile, outfile, Encrypt, 96);
    outfile.close();

    ifstream output, outputcheck;
    output.open(valueout.c_str());
    outputcheck.open("test_encrypted_with_96.txt");

    EXPECT_TRUE(streams_match(output, outputcheck));
}

TEST_F(OTPTest, use_OTP_65535)
{
    string valueout = "output65535.txt";
    outfile.open(valueout.c_str());
    use_OTP(infile, outfile, Encrypt, 65535);
    outfile.close();

    ifstream output, outputcheck;
    output.open(valueout.c_str());
    outputcheck.open("test_encrypted_with_65535.txt");

    EXPECT_TRUE(streams_match(output, outputcheck));
}
