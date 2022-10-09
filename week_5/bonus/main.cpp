/********************************************************************
    Course: Imperative Programming - Bonus Assignment 5
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 9.10.2022
********************************************************************/

#include <cassert> // for assertion checking
#include <fstream> // for file I/O
#include <iostream>
#include <string> // for string manipulation

using namespace std;
int seed = 0;

/********************************************************************
    Function Declarations
********************************************************************/

void initialise_pseudo_random(int r);
int next_pseudo_random_number();
char decrypt_char(char a, int r);
bool string_contains_date(string str);

bool similar_to_english(string str);
bool user_decryption_confirmation(string &sentence);
int brute_force_value_of_r(const string INPUT_FILE);
void use_otp(const string INPUT_FILE, const string OUTPUT_FILE, int r);

void decrypt_cyphertext(const string INPUT_FILE);

/********************************************************************
    Helper Functions
********************************************************************/

bool string_contains_date(string str) {
  // pre-condition:
  assert(str.length() > 0);
  /* post-condition:
     We know for sure if the title contains a date or not
  */

  // As we cannot use arrays, and std::string.contains is a C++23 feature,
  // we have to do this ugly implementation

  // Check if the string contains a month
  if (str.find("December") != string::npos ||
      str.find("November") != string::npos ||
      str.find("October") != string::npos ||
      str.find("September") != string::npos ||
      str.find("August") != string::npos || str.find("July") != string::npos ||
      str.find("June") != string::npos || str.find("May") != string::npos ||
      str.find("April") != string::npos || str.find("March") != string::npos ||
      str.find("February") != string::npos ||
      str.find("January") != string::npos)
    return true;

  // Check if the string contains a year
  for (int i = 1900; i < 2000; i++)
    if (str.find(to_string(i)) != string::npos)
      return true;

  return false;
}

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

bool similar_to_english(string str) {
  // pre-condition
  assert(str.length() > 0);
  /* post-condition
     Returns true if string contains dates or more than 90% letters
  */

  // Title could be a date, so it contains day, months, years or a combination
  if (string_contains_date(str))
    return true;

  // Title could have lots of letters and spaces
  int no_letters = 0;
  int no_spaces = 0;
  for (char &c : str) {
    if (isalpha(c))
      no_letters++;
    if (isspace(c))
      no_spaces++;
  }

  return static_cast<double>(no_letters) / str.length() >= 0.9 &&
         no_spaces >= 2;
}

bool user_decryption_confirmation(string &sentence) {
  // pre-condition:
  assert(sentence.length() > 0);
  /* post-condition:
     The user confirms that the text decrypted using the found value for 'r'
     is human readable
  */

  char response;
  cout << "\tPlease confirm that this sentence is human-readable:\n"
       << "\t'" << sentence << "'\n"
       << "[Y/N]: ";
  cin >> response;

  return response == 'Y';
}

/********************************************************************
    Decryption Functions
********************************************************************/

char decrypt_char(char a, int r) {
  // pre-condition:
  assert(r > 0 && r <= 65536);
  /* post-condition:
     Character a is rotated by r
  */

  if (a >= 32)
    a = (a + 64 - (r % 96)) % 96 + 32;

  return a;
}

int brute_force_value_of_r(const string INPUT_FILE) {
  // pre-condition
  assert(true);
  /* post-condition
     Value of the "r" used to encrypt is known and returned
  */
  cout << "[INFO] Started brute force of 'r'\n";
  string decrypted_line = "";
  string line;
  ifstream infile;

  infile.open(INPUT_FILE);
  getline(infile, line);
  infile.close();

  for (int r = 1; r < 65536; r++) {
    initialise_pseudo_random(r);

    for (char &c : line)
      decrypted_line += decrypt_char(c, next_pseudo_random_number());

    if (similar_to_english(decrypted_line))

      if (user_decryption_confirmation(decrypted_line)) {
        cout << "[INFO] Succesfully found 'r' value [" << r << "]." << endl;
        return r;
      }

    decrypted_line = "";
  }

  return -1;
}

void use_otp(const string INPUT_FILE, const string OUTPUT_FILE, int r) {
  // pre-condition
  assert(true);
  /* post-condition
     Text is decrypted and written to output file
  */

  cout << "[INFO] Started Decryption ..\n";
  char c;
  ifstream infile;
  ofstream outfile;

  initialise_pseudo_random(r);

  infile.open(INPUT_FILE);
  outfile.open(OUTPUT_FILE, fstream::out);

  while (infile.get(c))
    outfile.put(decrypt_char(c, next_pseudo_random_number()));

  infile.close();
  outfile.close();

  cout << "[INFO] Decryption finished.\n";
}

void decrypt_cyphertext(const string INPUT_FILE) {
  // pre-condition
  assert(true);
  /* post-condition
     Text is decrypted and written to output file
  */

  const string OUTPUT_FILE = "source.txt";

  int r = brute_force_value_of_r(INPUT_FILE);
  use_otp(INPUT_FILE, OUTPUT_FILE, r);
}

int main() {
  decrypt_cyphertext("secret.txt");
  return 0;
}
