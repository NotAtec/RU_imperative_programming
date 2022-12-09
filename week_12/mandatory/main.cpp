/********************************************************************
    Course: Imperative Programming - Assignment 12
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 09.12.2022
********************************************************************/

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/********************************************************************
    Global Definitions
********************************************************************/

struct gift {
  int price;
  string name;
};

int budgets[6];           // Budget for each person
vector<gift> wishlist[6]; // Wishlist for each person
vector<gift> giftstore{}; // All gifts in the store

/********************************************************************
    Function Prototype Declarations
********************************************************************/
bool operator==(const gift &a, const gift &b);
gift gift_from_string(string str);
gift find_gift(const string &name);

void load_giftstore(const string &filename);
void load_wishlist(const string &filename, const int idx);
void load_files();

bool valid(const vector<gift> gifts);
bool match_gifts(const vector<gift> &cur, int i, const vector<gift> &wishlist,
                 int j);
void improve(const vector<gift> &cur, vector<gift> &best);
int sum(const vector<gift> list, int from);
int minimum(const vector<gift> &list, int from);
void show(const vector<gift> &cur, ostream &dest);

int recursive_gifts(vector<gift> &cur, vector<gift> &best,
                    const vector<gift> &wishlist, int c, int t);
int gifts(vector<gift> &cur, vector<gift> &best, const vector<gift> &wishlist,
          int c, int t);

/********************************************************************
    Function Definitions
********************************************************************/

bool operator==(const gift &a, const gift &b) {
  // Pre-condition:
  assert(true);
  // Post-condition: Two gifts are equal if they have the same name.

  return a.name == b.name;
}

gift find_gift(const string &name) {
  // Pre-condition:
  assert(true);
  // Post-condition: The gift with the given name is returned.

  for (int i = 0; i < static_cast<int>(size(giftstore)); i++) {
    if (giftstore.at(i).name == name) {
      return giftstore.at(i);
    }
  }

  return gift{-1, ""};
}

gift gift_from_string(string str) {
  // Pre-condition:
  assert(str != "");
  // Post-condition: The price & name are processed from the string to a gift
  // struct, which is returned.

  int start = 0;
  int end = str.find(" ");

  int price = stoi(str.substr(start, end - start));
  string name = str.substr(end + 1);
  gift temp;

  temp.name = name;
  temp.price = price;

  return temp;
}

void load_giftstore(const string &filename) {
  // Pre-condition:
  assert(true);
  // Post-Condition: all gifts are loaded from file on disk to vector
  // 'giftstore'.
  ifstream file(filename);
  if (!file) {
    cerr << "Could not open file " << filename << endl;
    exit(1);
  }

  string line;
  while (getline(file, line)) {
    gift processed = gift_from_string(line);
    giftstore.push_back(processed);
  }
}

void load_wishlist(const string &filename, const int idx) {
  // Pre-condition:
  assert(true);
  // Post-condition: The budget of a person is loaded into array, and the wished
  // items are loaded into a separate array.

  ifstream file(filename);
  if (!file) {
    cerr << "Could not open file " << filename << endl;
    exit(1);
  }

  string line;
  getline(file, line);
  if (line != "")
    budgets[idx] = stoi(line);

  while (getline(file, line)) {
    if (line != "") {
      gift temp = find_gift(line);
      if (temp.price != -1) {
        wishlist[idx].push_back(temp);
      }
    }
  }
}

void load_files() {
  // Pre-condition:
  assert(true);
  // Post-condition: Giftstore and all wishlists are loaded into memory from
  // file on disk.

  load_giftstore("giftstore.txt");
  string files[6] = {"Andrew.txt",  "Belle.txt",  "Chris.txt",
                     "Desiree.txt", "Edward.txt", "Fabienne.txt"};

  for (int i = 0; i < 6; i++) {
    load_wishlist(files[i], i);
  }
}

bool valid(const vector<gift> gifts) {
  // Pre-condition:
  assert(true);
  // Post-Condition: Gift list is checked if all prices are valid.

  for (int i = 0; i < static_cast<int>(size(gifts)); i++) {
    if (gifts.at(i).price < 0)
      return false;
  }

  return true;
}

bool match_gifts(const vector<gift> &cur, int i, const vector<gift> &wishlist,
                 int j) {
  // Pre-condition:
  assert(valid(cur) && valid(wishlist) && i >= 0 && j >= 0);
  // Post-Condition: Result is true only if gifts in 'cur' appear in 'wishlist',
  // in order, allowing to skip gifts in wishlist.

  if (i >= static_cast<int>(size(cur))) {
    return true;
  } else if (j >= static_cast<int>(size(wishlist))) {
    return false;
  } else if (cur.at(i).name == wishlist.at(j).name) {
    return match_gifts(cur, i + 1, wishlist, j + 1);
  } else {
    return match_gifts(cur, i, wishlist, j + 1);
  }
}

void show(const vector<gift> &cur, ostream &dest) {
  // Pre-condition:
  assert(true);
  // Post-condition: The current gift list is printed to `cout`.

  for (int i = 0; i < static_cast<int>(size(cur)); i++) {
    dest << cur.at(i).name << endl;
  }
  cout << endl;
}

void improve(const vector<gift> &cur, vector<gift> &best) {
  // Pre-condition:
  assert(true);
  // Post-condition: The current gift list is compared to the best gift list,
  // and the best gift list is updated if the current gift list is better.

  if (static_cast<int>(size(cur)) > static_cast<int>(size(best))) {
    best = cur;
  }
}

int sum(const vector<gift> list, int from) {
  // Pre-condition:
  assert(from >= 0);
  // Post-condition: The sum of the prices of the gifts in the list starting at
  // 'from' is returned.

  int sum = 0;
  for (int i = from; i < static_cast<int>(size(list)); i++) {
    sum += list.at(i).price;
  }

  return sum;
}

int minimum(const vector<gift> &list, int from) {
  // Pre-condition:
  assert(true);
  // Post-condition: The price of the cheapest gift in the list is returned.

  if (static_cast<int>(size(list)) == 0 || static_cast<int>(size(list)) <= from)
    return 0;

  int min = list.at(from).price;
  for (int i = from; i < static_cast<int>(size(list)); i++) {
    if (list.at(i).price < min)
      min = list.at(i).price;
  }

  return min;
}

int recursive_gifts(vector<gift> &cur, vector<gift> &best,
                    const vector<gift> &wishlist, int c, int t) {
  // Pre-condition:
  assert(valid(wishlist) && 0 <= c && c <= static_cast<int>(size(wishlist)) &&
         match_gifts(cur, 0, wishlist, 0) && match_gifts(best, 0, wishlist, 0));
  // Post-condition: The number of gift lists that can be made with the given
  // wishlist and budget is returned.

  if (t == 0) {
    improve(cur, best);

    return 1;
  } else if (t < 0) {
    return 0;
  } else if (c >= static_cast<int>(size(wishlist))) {
    improve(cur, best);
    return 0;
  } else if (sum(cur, 0) + sum(wishlist, c) < sum(best, 0)) {
    return 0;
  } else if (minimum(wishlist, c) > t) {
    improve(cur, best);
    return 0;
  } else {
    cur.push_back(wishlist.at(c));
    int r1 =
        recursive_gifts(cur, best, wishlist, c + 1, t - wishlist.at(c).price);
    cur.pop_back();
    int r2 = recursive_gifts(cur, best, wishlist, c + 1, t);
    return r1 + r2;
  }
}

int gifts(vector<gift> &cur, vector<gift> &best, const vector<gift> &wishlist,
          int c, int t) {
  // Pre-condition:
  assert(valid(wishlist) && 0 <= c && c <= static_cast<int>(size(wishlist)) &&
         match_gifts(cur, 0, wishlist, 0) && match_gifts(best, 0, wishlist, 0));
  // Post-condition: The optimal gift list is computed and printed, the
  // remaining budget is returned.

  recursive_gifts(cur, best, wishlist, c, t);
  return t - sum(best, 0);
}

/********************************************************************
    Main function
********************************************************************/

#ifndef TESTING
int main() { // Precondition:
  assert(true);
  /*  Postcondition: the gift store has been loaded, and the optimal gift
     lists of each name (Andrew ... Fabienne) has been computed and printed to
     `cout`
  */
  load_files();

  string names[6] = {"Andrew",  "Belle",  "Chris",
                     "Desiree", "Edward", "Fabienne"};
  ofstream out("best_gifts.txt");
  if (!out.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }
  for (int i = 0; i < 6; i++) {
    vector<gift> cur;
    vector<gift> best;
    out << "Gifts for " << names[i] << ":" << endl;
    int remaining = gifts(cur, best, wishlist[i], 0, budgets[i]);
    show(best, out);
    out << "Remaining budget: " << remaining << endl;
  }

  return 0;
}
#endif
