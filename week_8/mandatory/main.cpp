#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

istream &operator>>(istream &in, Track &track) { // Precondition:
  assert(true);
  /*  Postcondition:
      the content of the first 8 lines from in have been read and are stored in
     the corresponding members of track. The following (empty) line from in has
     also been read.
  */
  // implement this function
  return in;
}

int match_tracks(const vector<Track> &tracks, string track, bool display) {
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
      if (display)
        show_track(current, def, cout);

      count++;
    }
  }
  return count;
}

bool find_artist(const vector<string> &artists, string artist) {
  assert(artist != "");
  /* Postcondition: true is returned if the artist is found in the list of
   * artists, false is returned if it is not.
   */
  for (int i = 0; i < size(artists); i++) {
    if (artists.at(i) == artist)
      return true;
  }

  return false;
}

int match_artists(const vector<Track> &tracks, string artist, bool display) {
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
        !find_artist(artists, current.artist)) {
      artists.push_back(current.artist);
      if (display)
        show_track(current, def, cout);
      count++;
    }
  }

  return count;
}

int match_cds(const vector<Track> &tracks, string artist, bool display) {
  // implement this function
  return 0;
}

int number_of_cds(const vector<Track> &tracks) {
  // implement this function
  return 0;
}

int read_tracks(string filename, vector<Track> &tracks,
                bool show_content) { // Precondition:
  assert(true);
  /*  Postcondition:
      tracks is a copy of the tracks that are found in the file with file name
     filename, and result is the number of tracks that have been read. Only if
     show_content, then all read tracks are shown on screen.
  */
  // implement this function
  return 0;
}

#ifndef TESTING
int main() { // Precondition:
  assert(true);
  /*  Postcondition:
      the music database "Tracks.txt" has been read (if present and correctly
     formatted). The assignment queries have been executed and their result has
     been shown on screen. In case of the bonus assignment, the user has been
     able to query the database and has seen the results of these queries.
  */
  return 0;
}
#endif
