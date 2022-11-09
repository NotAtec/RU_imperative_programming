#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

struct Length
{
	int minutes;							// #minutes (0..)
	int seconds;							// #seconds (0..59)
};

struct Track
{
	string artist;                          // name of artist
	string cd;                              // cd title
	int    year;                            // year of appearance (if known)
	int    track;							// track number
	string title;                           // track title
	string tags;                            // tags
	Length time;							// playing time
	string country;                         // main countr(y/ies) of artist
};

struct TrackDisplay
{
	bool showArtist;						// if true, show name of artist
	bool showAlbum;							// if true, show cd title
	bool showYear;							// if true, show year of appearance
	bool showTrack;							// if true, show track number
	bool showTitle;							// if true, show track title
	bool showTags;                          // if true, show tags
	bool showLength;						// if true, show playing time
	bool showCountry;                       // if true, show countr(y/ies) of artist
};

bool match (string sub, string source)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    Result is true only if sub is a literal (case sensitive) sub string of source.
*/
    return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length is shown via out in the format: minutes, ':', seconds (two digits)
*/

    // implement this function
    return out;
}

istream& operator>> (istream& in, Length& length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length has been read from in: first minutes, then ':', then seconds
*/
    // implement this function
    return in;
}

Length operator+ (const Length& a, const Length& b)
{// Precondition:
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*  Postcondition:
    Result is the sum of a and b.
*/
    // implement this function
    return {};
}

void show_track (Track track, TrackDisplay lt, ostream& os)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    only the members of track are shown for which the corresponding member in lt is true.
*/
    // implement this function
}

istream& operator>> (istream& in, Track& track)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the content of the first 8 lines from in have been read and are stored in the corresponding members of track.
    The following (empty) line from in has also been read.
*/
    // implement this function
    return in;
}

int match_tracks (const vector<Track>& tracks, string track, bool display)
{
    // implement this function
    return 0;
}

int match_artists (const vector<Track>& tracks, string artist, bool display)
{
    // implement this function
    return 0;
}

int match_cds (const vector<Track>& tracks, string artist, bool display)
{
    // implement this function
    return 0;
}

int number_of_cds (const vector<Track>& tracks)
{
    // implement this function
    return 0;
}

int read_tracks (string filename, vector<Track>& tracks, bool show_content)
{// Precondition:
    assert (true);
/*  Postcondition:
    tracks is a copy of the tracks that are found in the file with file name filename, and result
    is the number of tracks that have been read.
    Only if show_content, then all read tracks are shown on screen.
*/
    // implement this function
    return 0;
}

#ifndef TESTING
int main()
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the music database "Tracks.txt" has been read (if present and correctly formatted).
    The assignment queries have been executed and their result has been shown on screen.
    In case of the bonus assignment, the user has been able to query the database and has
    seen the results of these queries.
*/
	return 0;
}
#endif
