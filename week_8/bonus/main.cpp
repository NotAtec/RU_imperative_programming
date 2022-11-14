/********************************************************************
    Course: Imperative Programming - Bonus Assignment 8
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 14.11.2022
********************************************************************/

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/********************************************************************
    Global Variable Definitions
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

struct TrackDisplay {
  bool showArtist;  // if true, show name of artist
  bool showAlbum;   // if true, show cd title
  bool showYear;    // if true, show year of appearance
  bool showTrack;   // if true, show track number
  bool showTitle;   // if true, show track title
  bool showTags;    // if true, show tags
  bool showLength;  // if true, show playing time
  bool showCountry; // if true, show countr(y/ies) of artist
};

/********************************************************************
    Helper Functions
********************************************************************/

int size(const vector<Track> &v) { return static_cast<int>(v.size()); }
int size(const vector<string> &v) { return static_cast<int>(v.size()); }

bool match(string sub, string source) { // Precondition:
  assert(true);
  /*  Postcondition:
      Result is true only if sub is a literal (case sensitive) sub string of
     source.
  */
  return source.find(sub) != string::npos;
}

bool find_string(const vector<string> &strings, string string) {
  // Precondition:
  assert(string != "");
  /* Postcondition: true is returned if the string is found in the list of
   * strings, false is returned if it is not.
   */
  for (int i = 0; i < size(strings); i++) {
    if (strings.at(i) == string)
      return true;
  }

  return false;
}

/********************************************************************
    Overloads
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

Length operator+(const Length &a, const Length &b) { // Precondition:
  assert(0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes &&
         0 <= b.seconds && b.seconds < 60);
  /*  Postcondition:
      Result is the sum of a and b.
  */

  Length sum = {a.minutes + b.minutes, a.seconds + b.seconds};

  if (sum.seconds >= 60) {
    sum.minutes++;
    sum.seconds -= 60;
  }

  return sum;
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
    Database processing
********************************************************************/

void show_track(Track track, TrackDisplay lt, ostream &os) { // Precondition:
  assert(true);
  /*  Postcondition:
      only the members of track are shown for which the corresponding member in
      lt is true.
  */
  if (lt.showArtist)
    os << track.artist << endl;
  if (lt.showAlbum)
    os << track.cd << endl;
  if (lt.showYear)
    os << track.year << endl;
  if (lt.showTrack)
    os << track.track << endl;
  if (lt.showTitle)
    os << track.title << endl;
  if (lt.showTags)
    os << track.tags << endl;
  if (lt.showLength)
    os << track.time << endl;
  if (lt.showCountry)
    os << track.country << endl;
}

int match_tracks(const vector<Track> &tracks, string track, bool display) {
  // Precondition:
  assert(true);
  /* Postcondition: The vector tracks is iterated over, and all cases where the
   * string 'track' is in the title, count is increased. Count is returned at
   * the end. If 'display' = T, track details are output to screen.
   */

  const TrackDisplay def = {true, true, true, true, true, true, true, true};
  int count = 0;

  for (int i = 0; i < size(tracks); i++) {
    const Track current = tracks.at(i);

    if (match(track, current.title)) {
      if (display){
        show_track(current, def, cout);
        cout << endl;
      }

      count++;
    }
  }
  return count;
}

int match_artists(const vector<Track> &tracks, string artist, bool display) {
  // Precondition:
  assert(true);
  /* Postcondition: The vector tracks is iterated over, and if the string under
   * var 'artist' is found in the track artist name for the first time, count is
   * increased. If 'display' = T, artist name will be output to cout.
   */

  const TrackDisplay def = {true,  false, false, false,
                            false, false, false, false};
  vector<string> artists;
  int count = 0;

  for (int i = 0; i < size(tracks); i++) {
    const Track current = tracks.at(i);

    if (match(artist, current.artist) &&
        !find_string(artists, current.artist)) {
      artists.push_back(current.artist);

      if (display){
        show_track(current, def, cout);
        cout << endl;
      }
      count++;
    }
  }

  return count;
}

int match_cds(const vector<Track> &tracks, string artist, bool display) {
  // Precondition:
  assert(true);
  /* Postcondition: The vector tracks is iterated over, and if the string under
   * var 'artist' is found in the track artist name, and the accompanying cd is
   * found for the first time, count is increased. If display = T, artistname,
   * albumname & year of publication is output to cout.
   */

  const TrackDisplay def = {true,  true,  true,  false,
                            false, false, false, false};
  vector<string> albums;
  int count = 0;

  for (int i = 0; i < size(tracks); i++) {
    const Track current = tracks.at(i);

    if (match(artist, current.artist) && !find_string(albums, current.cd)) {
      albums.push_back(current.cd);
      if (display)
        show_track(current, def, cout);
      count++;
    }
  }

  return count;
}

int number_of_cds(const vector<Track> &tracks) {
  // Precondition:
  assert(true);
  /* Postcondition: */

  vector<string> albums;
  int count = 0;

  for (int i = 0; i < size(tracks); i++) {
    const Track current = tracks.at(i);
    if (!find_string(albums, current.cd)) {
      albums.push_back(current.cd);
      count++;
    }
  }

  return count;
}

int read_tracks(string filename, vector<Track> &tracks,
                bool show_content) { // Precondition:
  assert(true);
  /*  Postcondition:
      tracks is a copy of the tracks that are found in the file with file name
     filename, and result is the number of tracks that have been read. Only if
     show_content, then all read tracks are shown on screen.
  */
  int count = 0;

  ifstream data(filename, ifstream::in);

  while (!data.eof()) {
    Track temp;
    data >> temp;
    tracks.push_back(temp);
    count++;
    if (show_content)
      show_track(temp,
                 TrackDisplay{true, true, true, true, true, true, true, true},
                 cout);
  }

  // Clean up data, last is removed due to the structuring of files with 2 \n at
  // end. Last count is removed due to same reason, it will do the entire
  // procedure once too many.
  tracks.pop_back();
  count--;

  return count;
}

/********************************************************************
    CLI Methods
********************************************************************/

void track_track(vector<Track> &tracks, string track) {
    // Precondition:
    assert(true);
    /* Postcondition
       All tracks that match the title given by user are outputted
    */ 

    int no_of_matches = match_tracks(tracks, track, true);
    cout << "Number of found tracks: " << no_of_matches;
}

void artist_artist(vector<Track> &tracks, string artist) {
    // Precondition:
    assert(true);
    /* Postcondition
       All artists that match the input given by user are outputted
    */ 

    int no_of_matches = match_artists(tracks, artist, true);
    cout << "Number of found artists: " << no_of_matches;
}

void cds_artist(vector<Track> &tracks, string artist) {
    // Precondition:
    assert(true);
    /* Postcondition
       All artists that match the input given by user are outputted
    */ 

    int no_of_matches = match_cds(tracks, artist, true);
    cout << "Number of found cds: " << no_of_matches;
}

void cds(vector<Track> &tracks) {
    // Precondition:
    assert(true);
    /* Postcondition
       The number of albums in the database is outputted
    */ 

    int no_of_matches = number_of_cds(tracks);
    cout << "Number of found albums: " << no_of_matches << endl;
}

void cli(vector<Track> &tracks) {
    // Precondition
    assert(!tracks.empty());
    /* Postcondition
       The command line interface is printed and reponsive
    */ 

    string command = "";

    do {
        cout << "\nPlease enter a command: \n(user@ip_week_8)$: ";
        getline(cin, command);

        string query = command.substr(command.find(" ") + 1);
        string method = command.substr(0, command.find(" "));

        if (method == "track")
            track_track(tracks, query);
        else if (method == "artist")
            artist_artist(tracks, query);
        else if (method == "cds")
            cds_artist(tracks, query);
        else if (method == "#cds")
            cds(tracks);
        cin.clear();
  } while (command != "stop");
}

#ifndef TESTING
int main ()
{   
    vector<Track> tracks; 
    read_tracks("Tracks.txt", tracks, false);

    cli(tracks);

    return 0;
}
#endif