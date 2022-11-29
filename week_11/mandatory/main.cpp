#include <cassert>
#include <iostream>

using namespace std;

int length(const string &s) {
  // Pre-condition:
  assert(true);
  // Post-condition: return value is length of `s` as a signed integer
  return static_cast<int>(s.length());
}

int naive_power(int x, int n) {
  // Pre-Condition:
  assert(n >= 0);
  // Post-condition: Return value is x to the power of n.
  if (n == 0)
    return 1;

  return x * naive_power(x, n - 1);
}

int power(int x, int n) {
  // Pre-condition:
  assert(n >= 0);
  // Post-condition: Return value is x to the power of n.
  // This function is of complexity O(log n), because of a divide and conquer
  // approach.

  if (n == 0)
    return 1;

  int pow = power(x, n / 2);

  if (n % 2 == 0)
    return pow * pow;
  else
    return x * pow * pow;
}

bool palindrome1(string text, int i, int j) {
  // Pre-Condition:
  assert(i >= 0 && j >= 0);
  // Post-Condition: Return if the string is a palindrome, or not.

  if (i == j)
    return true;

  if (text.at(i) != text.at(j))
    return false;

  if (j < i + 1)
    return palindrome1(text, i + 1, j - 1);

  return true;
}

bool palindrome2(string text, int i, int j) {
  // Pre-Condition:
  assert(i >= 0 && j >= 0);
  // Post-Condition: Return if the string is a palindrome, or not.
  // Case-insensitively.

  if (i == j)
    return true;

  if (tolower(text.at(i)) != tolower(text.at(j)))
    return false;

  if (j < i + 1)
    return palindrome2(text, i + 1, j - 1);

  return true;
}

bool palindrome3(string text, int i, int j) {
  // Pre-Condition:
  assert(i >= 0 && j >= 0);
  // Post-Condition: Return if the string is a palindrome, or not.
  // Case-insensitively, and ignoring non-alphanumeric characters.

  if (i == j)
    return true;

  if (!isalnum(text.at(i)))
    return palindrome3(text, i + 1, j);

  if (!isalnum(text.at(j)))
    return palindrome3(text, i, j - 1);

  if (tolower(text.at(i)) != tolower(text.at(j)))
    return false;

  if (j < i + 1)
    return palindrome3(text, i + 1, j - 1);

  return true;
}

bool match_chars(string chars, int i, string source, int j) {
  // Pre-condition:
  assert(i >= 0 && j >= 0);
  // Post-Condition: Return if the characters in `chars` are present in
  // `source`, skipped characters in source are allowed.

  if (i == static_cast<int>(chars.length()))
    return true;

  if (j == static_cast<int>(source.length()))
    return false;

  if (chars.at(i) == source.at(j))
    return match_chars(chars, i + 1, source, j + 1);

  return match_chars(chars, i, source, j + 1);
}

#ifndef TESTING
int main() {
  // Pre-condition:
  assert(true);
  // Post-condition: user has entered a line of text, and program has printed
  // return value of all palindrome functions on that line of text
  return 0;
}
#endif
