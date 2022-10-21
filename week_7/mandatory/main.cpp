/********************************************************************
    Course: Imperative Programming - Assignment 7
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 21.10.2022
********************************************************************/

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/********************************************************************
    Global Variable Definitions
********************************************************************/

const int MAX_NO_OF_WORDS = 25000;
// the maximum number of words to read from a text file

string content[MAX_NO_OF_WORDS] = {};
// the read content of a text file (at most MAX_NO_OF_WORDS words)

/********************************************************************
    Helper Functions
********************************************************************/

bool read_word(ifstream &infile, string &word) { // precondition:
  assert(infile.is_open());
  /*  postcondition:
      result is true only if a word is read from `infile`, and this word is
     assigned to `word`. result is false otherwise, and the value of `word`
     should not be used.
  */
  infile >> word;
  return !infile.fail();
}

int helper_sequence(string sequence[10], string seq_string) {
  // pre-condition
  assert(true);
  /** post-condition
   *  This method converts from string to array, for use in the commands.
   * Returns the count of words in sequence.
   */

  string word = "";
  int seq_counter = 0;

  for (auto x : seq_string) {
    if (x == ' ' || x == '\0') {
      sequence[seq_counter] = word;
      seq_counter++;
      word = "";
    } else
      word += x;
  }
  sequence[seq_counter] = word;

  for (int i = 0; i < seq_counter + 1; i++)
    cout << sequence[i] << endl;

  return seq_counter + 1;
}

/********************************************************************
    Commands
********************************************************************/

int enter_command(string filename) { // precondition:
  assert(true);
  /*  postcondition:
      if result is a positive number then the text file with file name
     `filename` has been successfully opened and closed after reading, and
     result number of words have been read from that file (at most
     MAX_NO_OF_WORDS) and are stored in that order in `content`. if result is
     zero, then either the text file was empty or has not been opened.
  */
  int counter = 0;

  ifstream infile;
  infile.open(filename);

  if (!infile.is_open()) {
    cout << "[FileError]: Operation failed. Please check the filename.\n";
    return 0;
  }

  string word = "";
  while (read_word(infile, word) && counter < MAX_NO_OF_WORDS) {
    content[counter] = word;
    counter++;
  }

  // Error code -1 used for logging error when buffer is full
  // but did not reach EOF
  if (read_word(infile, word))
    return MAX_NO_OF_WORDS;

  return counter;
}

int count_command(string content[], int no_of_words, string terms[],
                  int no_of_terms) { // precondition:
  assert(no_of_words >= 0 && no_of_terms > 0);
  /*  postcondition:
      result is the number of occurrences of the word sequence `terms` (which
     has `no_of_terms` elements) in `content` (which has `no_of_words` elements)
      (the result is obviously zero in case `no_of_words` < `no_of_terms`)
  */
  int counter = 0;
  bool flag = false;

  for (int i = 0; i < no_of_words; i++) {
    if (content[i] == terms[0]) {
      flag = true;

      for (int j = 1; j < no_of_terms; j++) {
        if (content[i + j] != terms[j])
          flag = false;
      }
    }
    if (flag) {
      counter++;
      flag = false;
    }
  }

  return counter;
}

string where_command(string content[], int no_of_words, string terms[],
                     int no_of_terms, int &count) {
  assert(no_of_words >= 0 && no_of_terms >= 0);
  // Post-condition: Result is a string of indices, separated by spaces. Each
  // index is the first index of an occurency of a word-sequence `terms`If there
  // are no found indices, the string remains empty.
  bool flag = false;
  string indices;
  int temp;

  for (int i = 0; i < no_of_words; i++) {
    if (content[i] == terms[0]) {
      flag = true;
      temp = i;

      for (int j = 1; j < no_of_terms; j++) {
        if (content[i + j] != terms[j])
          flag = false;
      }
    }

    if (flag) {
      indices = indices + " " + to_string(temp);
      count++;
      flag = false;
    }
  }

  return indices;
}

string context_command() {

}
/********************************************************************
    Command Processing
********************************************************************/

void enter_helper(int word_count) {
  cout << "\tThis file contains " + to_string(word_count) + " words.";
  if (word_count == MAX_NO_OF_WORDS) {
    cout << "[BufferError]: Buffer exceeded. Could not read all file "
            "data.\n";
  }
}

void content_helper(int word_count) {
  cout << "\t";
  for (int i = 0; i < word_count; i++)
    cout << content[i] << " ";
}

void count_helper(string command, int word_count) {
  string seq_string = command.substr(command.find(" ") + 1);
  string sequence[10] = {};

  int seq_count = count_command(content, word_count, sequence,
                                helper_sequence(sequence, seq_string));

  cout << "\tThe sequence `" << seq_string << "` has been seen " << seq_count
       << " times";
}

void where_helper(string command, int word_count) {
  string seq_string = command.substr(command.find(" ") + 1);
  string sequence[10] = {};
  int count = 0;

  string indices = where_command(content, word_count, sequence,
                                 helper_sequence(sequence, seq_string), count);

  cout << "\tThe sequence `" << seq_string << "` is seen at indices:" << indices
       << " and has been seen " << count << " times.";
}

void context_helper(string command, int word_count) {
  string seq_string = command.erase(0, command.find(" "));
  int m = stoi(seq_string.substr(0, seq_string.find(" ")));
  seq_string = seq_string.erase(0, command.find(" "));
  string sequence[10] = {};
  int count = 0;

  string indices = where_command(content, word_count, sequence,
                                 helper_sequence(sequence, seq_string), count);

  // Grab all indices from string
  // For all indices:
  // Get context (pos - m to pos - 1 ) before
  // Print context before
  // Print sequence
  // Get context (pos + 1 to pos + m) after
  // Print context after
  // Next index.
}

#ifndef TESTING
int main() {
  string filename = "";
  cout << "Please enter filename [eg. file.txt]: ";
  getline(cin, filename);

  int word_count = enter_command(filename);

  string command = "";
  do {
    cout << "\nPlease enter a command: \n(user@ip_week_7)$: ";
    getline(cin, command);

    if (command == "enter " + filename)
      enter_helper(word_count);
    else if (command == "content")
      content_helper(word_count);
    else if (command.find("count") != string::npos)
      count_helper(command, word_count);
    else if (command.find("where") != string::npos)
      where_helper(command, word_count);
    else if (command.find("context") != string::npos)
      context_helper(command, word_count);

    cin.clear();
  } while (command != "stop");
}
#endif
