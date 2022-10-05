#include <cassert> // for assertion checking
#include <fstream> // for file I/O
#include <iostream>

using namespace std;

enum Action { Encrypt, Decrypt };

int seed = 0;

void initialise_pseudo_random(int r) {
  //  pre-condition:
  assert(r > 0 && r <= 65536);
  /*  post-condition:
      seed has value r.
  */
  seed = r;
}

int next_pseudo_random_number() {
  //  pre-condition:
  assert(seed > 0 && seed <= 65536);
  /*  post-condition:
      result value > 0 and result value <= 65536 and result value != seed at
     entry of function
  */
  const int SEED75 = seed * 75;
  int next = (SEED75 & 65535) - (SEED75 >> 16);
  if (next < 0)
    next += 65537;
  seed = next;
  return next;
}

char rotate_char(char a, int r, Action action) {
  //  Pre-condition:
  assert(r >= 0);
  //  Post-condition: result is a character, rotated by integer R

  if (a >= 32) {
    if (action == Encrypt)
      a = (a - 32 + (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
    else
      a = (a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
  }

  return a;
}

bool contains_special_char(string str) {
  for (char &c : str) {
    if (c < 32) {
      return true;
      cout << endl
           << "Please make sure the name doesn't contain special characters!"
           << endl;
    }
  }
  return false;
}

void get_user_filenames(string &input, string &output) {
  do {
    if(input == output) {
      cout << "Make sure that the filenames aren't the same!" << endl;
    }

    cout << "Input the filename of the file to be encrypted / decrypted (No "
            "special characters): ";
    do {
      cin >> input;
    } while (contains_special_char(input));

    cout << "Input the filename of the file to output the result in: (No special "
            "characters)";
    do {
      cin >> output;
    } while (contains_special_char(output));
  } while (input == output);
}

bool open_input_and_output_file(ifstream &infile, ofstream &outfile) {
  //  Pre-condition:
  assert(true);
  //  Post-condition: result is true if filenames aren't equal, and both files
  //  have been opened successfully

  string input, output;
  get_user_filenames(input, output);
  
  infile.open(input);
  outfile.open(output);

  if(infile.fail() || outfile.fail())
    return false;

  return true;
}

Action get_user_action() { // Pre-condition:
  assert(true);
  /*  Post-condition:
      result is the Action that the user has indicated that the program should
     encrypt / decrypt
  */
  cout << "Do you want to encrypt the file? (y/n): ";
  string answer;
  cin >> answer;
  if (answer == "y")
    return Encrypt;
  else
    return Decrypt;
}

int initial_encryption_value() { // Pre-conditie:
  assert(true);
  /*  Post-condition:
      result is a value between 0 and 65355 (both inclusive)
  */
  int initial_value = -1;
  while (initial_value < 0 || initial_value > 65535) {
    cout << "Please enter the initial coding value (greater or equal to 0 and "
            "less than 65536)"
         << endl;
    cin >> initial_value;
  }
  return initial_value;
}

void use_OTP(ifstream &infile, ofstream &outfile, Action action,
             int initial_value) {
  //  Pre-condition:

  //  Post-condition:

  initialise_pseudo_random(initial_value);

  char c;
  while(infile.get(c)) {
    outfile.put(rotate_char(c, next_pseudo_random_number(), action));
    cout << c;
  }
}

#ifndef TESTING
int main() {
  const Action ACTION = get_user_action();
  ifstream input_file;
  ofstream output_file;
  if (!open_input_and_output_file(input_file, output_file)) {
    cout << "Program aborted." << endl;
    return -1;
  }
  const int INITIAL_VALUE = initial_encryption_value();
  use_OTP(input_file, output_file, ACTION, INITIAL_VALUE);
  input_file.clear();
  output_file.clear();
  input_file.close();
  output_file.close();

  if (!input_file || !output_file) {
    cout << "Not all files were closed succesfully. The output might be "
            "incorrect."
         << endl;
    return -1;
  }
  return 0;
}
#endif