#include "scenario.h"

#include "world.h"

#include <wx/wx.h>

#include <cstring>
#include <cerrno>
#include <fstream>
#include <algorithm>



/******************************************************************************
** Define characters used in the *.scenario file format
******************************************************************************/
static constexpr char CHARLES_NORTH = 'n';
static constexpr char CHARLES_NORTH_ON_BALL = 'N';
static constexpr char CHARLES_EAST = 'e';
static constexpr char CHARLES_EAST_ON_BALL = 'E';
static constexpr char CHARLES_SOUTH = 's';
static constexpr char CHARLES_SOUTH_ON_BALL = 'S';
static constexpr char CHARLES_WEST = 'w';
static constexpr char CHARLES_WEST_ON_BALL = 'W';
static constexpr char TILE_FLOOR = '.';
static constexpr char TILE_FLOOR_WITH_BALL = 'o';
static constexpr char TILE_WALL = 'X';



/******************************************************************************
** Helper functions to validate and (de)serialize to/from characters
******************************************************************************/

static bool IsCharlesChar(char c) {
    return c == CHARLES_NORTH || c == CHARLES_EAST || c == CHARLES_SOUTH || c == CHARLES_WEST
        || c == CHARLES_NORTH_ON_BALL || c == CHARLES_EAST_ON_BALL
        || c == CHARLES_SOUTH_ON_BALL || c == CHARLES_WEST_ON_BALL;
}

static bool IsValidChar(char c) {
    return c == TILE_FLOOR || c == TILE_FLOOR_WITH_BALL || c == TILE_WALL || IsCharlesChar(c);
}

static bool IsBallChar(char c) {
    return c == TILE_FLOOR_WITH_BALL
        || c == CHARLES_NORTH_ON_BALL || c == CHARLES_EAST_ON_BALL
        || c == CHARLES_SOUTH_ON_BALL || c == CHARLES_WEST_ON_BALL;
}

static TileType GetTileTypeForChar(char c) {
    switch(c) {
        case TILE_FLOOR:
        case TILE_FLOOR_WITH_BALL:
            return TileType::Ground;
        case TILE_WALL:
            return TileType::Wall;
        default:
            throw std::invalid_argument("c");
    }
}

static Direction GetDirectionForChar(char c) {
    switch(c) {
        case CHARLES_NORTH:
        case CHARLES_NORTH_ON_BALL:
            return DIR_NORTH;
        case CHARLES_EAST:
        case CHARLES_EAST_ON_BALL:
            return DIR_EAST;
        case CHARLES_SOUTH:
        case CHARLES_SOUTH_ON_BALL:
            return DIR_SOUTH;
        case CHARLES_WEST:
        case CHARLES_WEST_ON_BALL:
            return DIR_WEST;
        default:
            throw std::invalid_argument("c");
    }
}

static char GetCharlesChar(Direction dir, bool onBall) {
    switch(dir) {
        case DIR_NORTH: return onBall ? CHARLES_NORTH_ON_BALL : CHARLES_NORTH;
        case DIR_EAST:  return onBall ? CHARLES_EAST_ON_BALL : CHARLES_EAST;
        case DIR_SOUTH: return onBall ? CHARLES_SOUTH_ON_BALL : CHARLES_SOUTH;
        case DIR_WEST:  return onBall ? CHARLES_WEST_ON_BALL : CHARLES_WEST;
        default:
            throw std::invalid_argument("dir");
    }
}

static char GetTileChar(TileType type, bool onBall) {
    switch(type) {
        case TileType::Wall:   return TILE_WALL;
        case TileType::Ground: return onBall ? TILE_FLOOR_WITH_BALL : TILE_FLOOR;
        default:
            throw std::invalid_argument("type");
    }
}



/******************************************************************************
** Scenario implementation
******************************************************************************/

static std::string s_error = "";

bool Scenario::SaveTo(std::string path, const World& world) {
    std::ofstream os(path);

    if(!os.is_open()) {
        s_error = wxString::Format("Failed to open file: %s", strerror(errno));
        return false;
    }

    return SaveTo(os, world);
}

bool Scenario::SaveTo(std::ostream& os, const World& world) {
    for(int y = 0; y < world.m_height; ++y) {
        for(int x = 0; x < world.m_width; ++x) {
            Tile tile = world.GetTileAt(x, y);

            if(world.m_pos.x == x && world.m_pos.y == y) {
                os << GetCharlesChar(world.m_dir, tile.hasBall);
            } else {
                os << GetTileChar(tile.type, tile.hasBall);
            }
        }

        os << '\n';
    }

    if(!os) {
        s_error = wxString::Format("Failed to write output: %s", strerror(errno));
        return false;
    }

    return true;
}

bool Scenario::LoadFrom(std::string path, World& world) {
    std::ifstream is(path);

    if(!is.is_open()) {
        s_error = wxString::Format("Failed to open file: %s", strerror(errno));
        return false;
    }

    return LoadFrom(is, world);
}

bool Scenario::LoadFrom(std::istream& is, World& world) {
    std::vector<std::string> content;

    if(!LoadAndValidate(is, content)) {
        return false;
    }   

    CreateFromValidatedContent(content, world);

    return true;
}

bool Scenario::LoadAndValidate(std::istream& is, std::vector<std::string>& content) {
    std::string line;
    int lineNumber = 0;
    int columnNumber = 0;
    size_t lineLength = 0;
    Position charles = {-1, -1};

    // Loop over all lines in the file.
    while(std::getline(is, line)) {
        ++lineNumber;
        columnNumber = 0;

        // Strip out CR ('\r', carriage return) characters to deal with files originating from different platforms.
        // NOTE: This will desync columnNumber, but this is only an issue if they occur before the end of the line, which is a non-issue.
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        // Empty lines are allowed, and are skipped
        if(!line.empty()) {
            if(lineLength == 0) {
                // Use length of the first line as the world width.
                lineLength = line.length();
            } else if(line.length() != lineLength) {
                // Subsequent lines must use the same width.
                s_error = wxString::Format(
                    "Invalid line width on line %d (expected %u, but got %u)", 
                    lineNumber, lineLength, line.length()
                );
                return false;
            }

            // Loop over all characters in the current line, and verify they are valid.
            for(char c : line) {
                ++columnNumber;

                if(!IsValidChar(c)) {
                    // Character was not one of the tile or Charles characters.
                    s_error = wxString::Format("Invalid character '%c' on line %d:%d", c, lineNumber, columnNumber);
                    return false;
                } else if(IsCharlesChar(c)) {
                    // Found Charles character, verify it is not a duplicate one.
                    if(charles.x == -1 && charles.y == -1) {
                        // Have not seen Charles before.
                        charles.x = columnNumber;
                        charles.y = lineNumber;
                    } else {
                        // Have seen Charles before.
                        s_error = wxString::Format(
                            "Found second Charles at line %d:%d (first seen at line %d:%d",
                            lineNumber, columnNumber, charles.y, charles.x
                        );
                        return false;
                    }
                }
            }

            // Current line has been validated, and contains no issues.
            content.push_back(line);
        }
    }
    
    // Ensure world has non-zero dimensions, and contains Charles. Also check for errors during getline.
    if(lineLength == 0 || content.empty()) {
        s_error = "World dimensions must be at least 1x1";
        return false;
    } else if(charles.x == -1 && charles.y == -1) {
        s_error = "World must contain Charles";
        return false;
    } else if(!is && !is.eof()) {
        // Report if getline failed for reasons other than the end of the file being reached.
        s_error = wxString::Format("Failed to read next line: %s", lineNumber, strerror(errno));
        return false;
    }

    return true;
}

void Scenario::CreateFromValidatedContent(const std::vector<std::string>& content, World& world) {
    world.m_width = content[0].length();
    world.m_height = content.size();

    world.m_tiles.resize(world.m_width * world.m_height);

    for(int y = 0; y < world.m_height; ++y) {
        for(int x = 0; x < world.m_width; ++x) {
            char c = content[y][x];
            bool hasBall = IsBallChar(c);
            TileType type;

            if(IsCharlesChar(c)) {
                world.m_pos.x = x;
                world.m_pos.y = y;
                world.m_dir = GetDirectionForChar(c);
                type = TileType::Ground;
            } else {
                type = GetTileTypeForChar(c);
            }

            world.SetTileAt(x, y, {type, hasBall});
        }
    }
}

const std::string& Scenario::GetLastError() {
    return s_error;
}


/******************************************************************************
** World << and >> operators implementation
******************************************************************************/

std::istream& operator>>(std::istream& is, World& world) {
    if(!Scenario::LoadFrom(is, world)) {
        is.setstate(std::ios_base::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const World& world) {
    if(!Scenario::SaveTo(os, world)) {
        os.setstate(std::ios_base::failbit);
    }

    return os;
}