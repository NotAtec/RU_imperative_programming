/********************************************************************
    Course: Imperative Programming - Assignment 9
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 18.11.2022
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

struct Length {
  int minutes; // #minutes (0..)
  int seconds; // #seconds (0..59)
};

struct Track {
  string artist;  // name of artist
  string cd;      // cd title
  int year;       // year of appearance (if known)
  int track;      // track number
  string title;   // track title
  string tags;    // tags
  Length time;    // playing time
  string country; // main countr(y/ies) of artist
};

typedef Track El; // as explained in lecture, define algorithms on El

struct Slice {
  int from;   // from >= 0
  int length; // length >= 0
};

/********************************************************************
    Overloads (From week 8)
********************************************************************/

ostream &operator<<(ostream &out, const Length length) {
  // Precondition:
  assert(true);
  /*  Postcondition:
      the value of length is shown via out in the format: minutes, ':', seconds
     (two digits)
  */

  out << length.minutes << ":";

  if (length.seconds < 10)
    out << "0";

  out << length.seconds;

  return out;
}

istream &operator>>(istream &in, Length &length) {
  // Precondition:
  assert(true);
  /*  Postcondition:
      the value of length has been read from in: first minutes, then ':', then
     seconds
  */
  char temp;

  in >> length.minutes >> temp >> length.seconds;

  return in;
}

ostream &operator<<(ostream &out, const Track &track) { // Precondition:
  assert(true);
  /*  Postcondition:
      the value of track is shown via out.
  */
  return out << track.artist << " - " << track.track << ". " << track.title
             << " (" << track.cd << ", " << track.year << ") [" << track.time
             << "]";
}

istream &operator>>(istream &in, Track &track) { // Precondition:
  assert(true);
  /*  Postcondition:
      the content of the first 8 lines from in have been read and are stored in
     the corresponding members of track. The following (empty) line from in has
     also been read.
  */

  getline(in, track.artist);
  getline(in, track.cd);
  in >> track.year >> track.track;
  in.ignore();
  getline(in, track.title);
  getline(in, track.tags);
  in >> track.time;
  in.ignore();
  getline(in, track.country);
  in.ignore();

  return in;
}

/********************************************************************
    Helper Functions
********************************************************************/

int size(const vector<El> &data) { // Precondition:
  assert(true);
  /*  Postcondition:
      result is the size of data, converted to int
  */
  return static_cast<int>(data.size());
}

void swap(El &a, El &b) { // Precondition:
  assert(true);
  /*  Postcondition:
      value of a has been assigned to b and vice versa
  */
  const El TEMP = a;
  a = b;
  b = TEMP;
}

Slice make_slice(int from, int length) { // Precondition:
  assert(from >= 0 && length >= 0);
  /*  post-condition:
      return slice with given from and length
  */
  Slice s = {from, length};
  return s;
}

Slice make_slice(const vector<El> &data) { // Precondition:
  assert(true);
  /*  Postcondition:
      returns the slice for the entire vector data.
  */
  Slice s = {0, size(data)};
  return s;
}

bool valid_slice(Slice s) { // Precondition:
  assert(true);
  /*  Postcondition:
      returns true only if all selector values of s are not negative.
  */
  return 0 <= s.from && 0 <= s.length;
}

bool valid_slice(const vector<El> &data, Slice s) { // Precondition:
  assert(true);
  /*  Postcondition:
      returns true only if s is a valid slice for data
  */
  return valid_slice(s) && s.from + s.length <= size(data);
}

int first(Slice s) { // Precondition:
  assert(valid_slice(s));
  /*  Postcondition:
      result is index of first element in s (s.from)
  */
  return s.from;
}

int last(Slice s) { // Precondition:
  assert(valid_slice(s));
  /*  Postcondition:
      result is index of last element in s (s.from + s.length - 1)
  */
  return s.from + s.length - 1;
}

/********************************************************************
    Comparison Operators
********************************************************************/

bool operator==(const Track &a, const Track &b) { // Precondition:
  assert(true);
  /*  Postcondition:
      returns true only if all selector values of a are equal to their
     counterparts of b
  */

  return a.artist == b.artist && a.cd == b.cd && a.year == b.year &&
         a.track == b.track;
}

bool operator!=(const Track &a, const Track &b) { // Precondition:
  assert(true);
  /*  Postcondition:
      returns true only if any selector values of a are not equal to their
     counterparts of b
  */
  return !(a == b);
}

bool operator<(const Track &a, const Track &b) { // Precondition:
  assert(true);
  /*  Postcondition:
      check the assignment for the proper definition of < on Tracks
  */

  if (a.artist == b.artist) {
    if (a.cd == b.cd) {
      if (a.year == b.year) {
        if (a.track != b.track) {
          return a.track < b.track;
        }
      } else {
        return a.year < b.year;
      }
    } else {
      return a.cd < b.cd;
    }
  } else {
    return a.artist < b.artist;
  }

  return false;
}

bool operator>(const Track &a, const Track &b) { // Precondition:
  assert(true);
  /*  Postcondition:
      returns true only if a does not precede b according to the ordering < on
     Tracks (don't forget to implement operator<)
  */
  return b < a;
}

bool operator<=(const Track &a, const Track &b) { // Precondition:
  assert(true);
  /*  Postcondition:
      returns true only if a < b or a == b according to their definitions on
     Tracks (don't forget to implement operator< and operator==)
  */
  return a < b || a == b;
}

bool operator>=(const Track &a, const Track &b) { // Precondition:
  assert(true);
  /*  Postcondition:
      returns true only if a > b or a == b according to their definitions on
     Tracks (don't forget to implement operator< and operator==)
  */
  return a > b || a == b;
}

bool is_sorted(const vector<El> &data, Slice s) { // pre-condition:
  assert(valid_slice(data, s));
  /*  post-condition:
      result is true if data[first (s)] <= data[first (s) + 1] ...
     data[last(s)-1] <= data[last(s)]
  */
  for (int i = first(s); i < last(s); i++) {
    if (data.at(i) > data.at(i+1)) {
      return false;
    }
  }
  return true;
}

/********************************************************************
    Insertion Sort Algo
********************************************************************/

void insert(vector<El> &data, Slice s) { // Precondition:
  assert(valid_slice(data, s) && s.length > 0 &&
         is_sorted(data, make_slice(s.from, s.length - 1)));
  /*  Postcondition:
      data[last(s)] is moved in data[first(s)]...data[last(s)] and is_sorted
     (data, s)
  */
  while (s.length > 1 && data.at(last(s)) < data.at(last(s) - 1)) {
    swap(data.at(last(s)), data.at(last(s) - 1));
    s.length--;
  }
}

void insertion_sort(vector<El> &data) { // Precondition:
  assert(true);
  /*  Postcondition:
      data is sorted in increasing order, according to < and == on El (don't
     forget to implement operator< and operator==)
  */
  int sorted = 1;
  while (sorted < size(data)) {
    insert(data, make_slice(0, sorted + 1));
    sorted++;
  }
}

/********************************************************************
    Selection Sort Algo
********************************************************************/
int max_value_at(const vector<El> &data, Slice s) { // Precondition:
  assert(valid_slice(data, s));
  /*  Postcondition:
      data[result] is the maximum of every element in data[first (s)] ...
     data[last (s)]
  */
  int stored = first(s);
  for (int i = first(s) + 1; i <= last(s); i++) {
    if (data.at(i) > data.at(stored)) {
      stored = i;
    }
  }

  return stored;
}

void selection_sort(vector<El> &data) { // Precondition:
  assert(true);
  /*  Postcondition:
      data is sorted in increasing order, according to < and == on El (don't
     forget to implement operator< and operator==)
  */
  for (int unsorted = size(data); unsorted > 1; unsorted--) {
    int max = max_value_at(data, make_slice(0, unsorted));
    swap(data.at(max), data.at(unsorted - 1));
  }
}

/********************************************************************
    Bubble Sort Algo
********************************************************************/

bool bubble(vector<El> &data, Slice unsorted) { // Precondition:
  assert(valid_slice(data, unsorted));
  /*  Postcondition:
      immediate pairs in data with slice unsorted are swapped if left element is
     larger than right element, and result is true only if this is done at least
     once (don't forget to implement operator< and operator==)
  */
  bool bubble = false;

  for (int i = first(unsorted); i < last(unsorted); i++) {
    if (data.at(i) > data.at(i+1)) {
      swap(data.at(i), data.at(i+1));
      bubble = true;
    }
  }

  return bubble;
}

void bubble_sort(vector<El> &data) { // Precondition:
  assert(true);
  /*  Postcondition:
      data is sorted in increasing order, according to < and == on El (don't
     forget to implement operator< and operator==)
  */
  int unsorted = size(data);
  bool swapped = bubble(data, make_slice(0, unsorted));
  while (swapped) {
    unsorted--;
    swapped = bubble(data, make_slice(0, unsorted));
  }
}

/********************************************************************
    Heap Sort Algo
********************************************************************/

int left_sibling(int i) { // Precondition:
  assert(0 <= i);
  /*  Postcondition:
      result is the index (if existing) of the left sibling of an element at
     index i in a heap structured array/vector
  */
  return i - 1;
}

int right_sibling(int i) { // Precondition:
  assert(0 <= i);
  /*  Postcondition:
      result is the index (if existing) of the right sibling of an element at
     index i in a heap structured array/vector
  */
  return i + 1;
}

int parent(int i) { // Precondition:
  assert(0 <= i);
  /*  Postcondition:
      result is the index (if existing) of the parent of an element at index i
     in a heap structured array/vector
  */
  return (i - 1) / 2;
}

int left_child(int i) { // Precondition:
  assert(0 <= i);
  /*  Postcondition:
      result is the index (if existing) of the left child of an element at index
     i in a heap structured array/vector
  */
  return 2 * (i + 1) - 1;
}

int right_child(int i) { // Precondition:
  assert(0 <= i);
  /*  Postcondition:
      result is the index (if existing) of the right child of an element at
     index i in a heap structured array/vector
  */
  return 2 * (i + 1);
}

bool is_a_heap(const vector<El> &data, Slice s) { // Precondition:
  assert(valid_slice(data, s));
  /*  Postcondition:
      result is true only if all existing children in slice s of data have a
     value that is not greater than their parent
  */
  for (int i = first(s); i <= parent(last(s)); i++) {
    if (left_child(i) <= last(s) && data.at(i) < data.at(left_child(i))) {
      return false;
    }
    if (right_child(i) <= last(s) && data.at(i) < data.at(right_child(i))) {
      return false;
    }
  }
  return true;
}

void push_up(vector<El> &data, int elem) { // Precondition:
  assert(0 <= elem && elem < size(data) &&
         is_a_heap(data, make_slice(0, elem)));
  /*  Postcondition:
      data[0] ... data[elem] is a heap
  */
  while (elem > 0 && data.at(parent(elem)) < data.at(elem)) {
    swap(data.at(parent(elem)), data.at(elem));
    elem = parent(elem);
  }
}

void build_heap(vector<El> &data) { // Precondition:
  assert(true);
  /*  Postcondition:
      data is a heap structure
  */
  for (int i = 1; i < size(data); i++) {
    push_up(data, i);
  }
}

bool largest_child(vector<El> &data, int parent, int unsorted, El &child,
                   int &which) {
  // Precondition:
  assert(0 <= unsorted && unsorted < size(data) && 0 <= parent &&
         parent < size(data));
  // Postcondition: Result is true only if the element at parent in data has one
  // or two unsorted child elements; only in that case the value of the largest
  // child is child and its index position is which.

  if (left_child(parent) > unsorted) {
    return false;
  } else if (right_child(parent) > unsorted) {
    which = left_child(parent);
    child = data.at(which);
    return true;
  } else if (data.at(left_child(parent)) > data.at(right_child(parent))) {
    which = left_child(parent);
    child = data.at(which);
    return true;
  } else {
    which = right_child(parent);
    child = data.at(which);
    return true;
  }
}

void push_down(vector<El> &data, int unsorted) { // Precondition:
  assert(is_a_heap(data, make_slice(1, unsorted)));
  /*  Postcondition:
      data[0] ... data[unsorted] is a heap
  */
  int parent = 0;
  El child;
  int which;
  while (largest_child(data, parent, unsorted, child, which) &&
         data.at(parent) < child) {
    swap(data.at(parent), data.at(which));
    parent = which;
  }
}

void pick_heap(vector<El> &data) { // Precondition:
  assert(is_a_heap(data, make_slice(data)));
  /*  Postcondition:
      data is sorted in increasing order, according to < and == on El (don't
     forget to implement < and ==)
  */

  for (int i = size(data) - 1; i > 0; i--) {
    swap(data.at(0), data.at(i));
    push_down(data, i - 1);
  }
}

void heap_sort(vector<El> &data) { // Precondition:
  assert(true);
  /*  Postcondition:
      data is sorted in increasing order, according to < and == on El (don't
     forget to implement < and ==)
  */
  build_heap(data);
  pick_heap(data);
}

/********************************************************************
    Main Function
********************************************************************/

enum SortAlgorithm { InsertionSort, SelectionSort, BubbleSort, HeapSort };

const int SORT_ALGORITHMS = HeapSort + 1;
const string SORT_ALGORITHM_NAMES[SORT_ALGORITHMS] = {
    "Insertion sort", "Selection sort", "Bubble sort", "Heap sort"};

bool load_database(string filename, vector<El> &database) { // Precondition:
  assert(true);
  /*  Postcondition:
      `database` contains database loaded from file `filename` and return value
     is true if no errors occurred. return value is false otherwise.
  */
  ifstream database_file(filename);
  El element;

  if (!database_file.is_open()) {
    return false;
  }

  while (database_file >> element) {
    database.push_back(element);
  }

  return true;
}

SortAlgorithm get_sort_algorithm() { // Precondition:
  assert(true);
  /*  Postcondition:
      return value is the user chosen sorting algorithm.
  */
  int choice;

  do {
    cout << "\nSelect a sorting algorithm" << endl;
    for (int i = 1; i <= SORT_ALGORITHMS; i++) {
      cout << i << ". " << SORT_ALGORITHM_NAMES[i - 1] << endl;
    }

    cout << "> ";
    cin >> choice;

    if (choice < 1 || choice > SORT_ALGORITHMS) {
      cout << "Invalid sorting algorithm" << endl;
      cin.clear();
      cin.ignore(1000, '\n');
    }
  } while (choice < 1 || choice > SORT_ALGORITHMS);

  return static_cast<SortAlgorithm>(choice - 1);
}

#ifndef TESTING
int main() { // Precondition:
  assert(true);
  /*  Postcondition:
      The music database "Tracks.txt" has been read (if present and correctly
     formatted). The sorted database has been printed according to the user
     selected sorting algorithm.
  */
  vector<El> database;

  if (!load_database("Tracks.txt", database)) {
    cout << "Error: could not open Tracks.txt" << endl;
    return 1;
  }

  cout << "Loaded " << size(database) << " element(s) from database" << endl;
  SortAlgorithm algorithm = get_sort_algorithm();
  cout << "Sorting database using " << SORT_ALGORITHM_NAMES[algorithm] << endl;

  switch (algorithm) {
  case InsertionSort:
    insertion_sort(database);
    break;
  case SelectionSort:
    selection_sort(database);
    break;
  case BubbleSort:
    bubble_sort(database);
    break;
  case HeapSort:
    heap_sort(database);
    break;
  }

  cout << "Showing sorted database:" << endl;
  for (int i = 0; i < size(database); i++) {
    cout << database.at(i) << endl;
  }

  return 0;
}
#endif