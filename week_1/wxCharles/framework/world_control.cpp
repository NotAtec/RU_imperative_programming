#include "world_control.h"

#include <wx/dcbuffer.h>

#define DEBUG_WORLD_RENDERING 0

static constexpr int TILE_SIZE = 8;
static constexpr int TAIL_MARGIN = 1;
static constexpr int TAIL_START = 2;
static constexpr int BALL_SIZE = 2;
#define BALL_BRUSH *wxGREEN_BRUSH
#define WALL_BRUSH *wxGREY_BRUSH
#define GROUND_BRUSH *wxWHITE_BRUSH
#define CHARLES_BRUSH *wxRED_BRUSH

bool WorldControl::Create(wxWindow* parent, wxWindowID id,
                          const wxPoint& pos, const wxSize& size, 
                          long style, const wxValidator& validator) {

    // Set the zoom scale to the default zoom scale, but do not yet update the UI.
    // Doing so before wxControl::Create will trigger an error.
    SetZoomScale(DEFAULT_ZOOM_SCALE, false);

    // Bind event handlers to their respective events.
    Bind(wxEVT_PAINT, &WorldControl::OnPaint, this, wxID_ANY);
    Bind(wxEVT_ERASE_BACKGROUND, &WorldControl::OnEraseBackground, this, wxID_ANY);

    return wxControl::Create(parent, id, pos, size, style, validator);
}

wxSize WorldControl::DoGetBestClientSize() const {
    int width = m_world.GetWidth() * m_tileSize;
    int height = m_world.GetHeight() * m_tileSize;

    return {width, height};
}

void WorldControl::SetWorld(const World& world) {
    bool newSize = world.GetWidth() != m_world.GetWidth() || world.GetHeight() != m_world.GetHeight();

    m_world = world;

    // Update size (constraints) if world size has changed.
    if(newSize) {
        SetInitialSize(DoGetBestClientSize());
        SetMaxClientSize(DoGetBestClientSize());
    }

    // Force UI to redraw world.
    Refresh();
    Update();
}

void WorldControl::SetZoomScale(int scale, bool update) {
    assert(scale >= 1);

    int tailMargin = TAIL_MARGIN * scale;
    int tailStart = TAIL_START * scale;

    m_zoomScale = scale;
    m_tileSize = TILE_SIZE * scale;
    m_ballSize = BALL_SIZE * scale;

    // Define Charles shape when facing east.
    m_charlesShapes[DIR_EAST] = {wxPoint
        {0, tailMargin},
        {m_tileSize - 1, (m_tileSize / 2) - 1},
        {0, m_tileSize - 1 - tailMargin},
        {tailStart, (m_tileSize / 2) - 1}
    };

    // Translate east shape to west shape by flipping across the x axis.
    m_charlesShapes[DIR_WEST] = m_charlesShapes[DIR_EAST];
    for(auto& p : m_charlesShapes[DIR_WEST]) {
        p.x = m_tileSize - 1 - p.x;
    }

    // Translate east shape to south shape by rotating 90 degrees to the right.
    m_charlesShapes[DIR_SOUTH] = m_charlesShapes[DIR_EAST];
    for(auto& p : m_charlesShapes[DIR_SOUTH]) {
        std::swap(p.x, p.y);
    }

    // Translate south shape to north shape by flipping across the y axis.
    m_charlesShapes[DIR_NORTH] = m_charlesShapes[DIR_SOUTH];
    for(auto& p : m_charlesShapes[DIR_NORTH]) {
        p.y = m_tileSize - 1 - p.y;
    }

    // Force UI to redraw world and update control size.
    if(update) {
        SetInitialSize(DoGetBestClientSize());
        SetMaxClientSize(DoGetBestClientSize());
        Refresh();
        Update();
    }
}

wxImage WorldControl::PaintToPNG() const {
    // Create bitmap of the correct size, and a DC that draws to the bitmap.
    wxBitmap bitmap(DoGetBestClientSize());
    wxMemoryDC dc(bitmap);

    // Paint client area to the bitmap, and return it as an image.
    DoPaint(dc);

    return bitmap.ConvertToImage();
}

void WorldControl::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    // Use a double buffered DC to help reduce flickering.
    wxBufferedPaintDC dc(this);

#if DEBUG_WORLD_RENDERING
    // Output the size of the client area being painted.
    wxSize clientSize = GetClientSize();
    std::cout << "w = " << clientSize.GetWidth() << ", h = " << clientSize.GetHeight() << '\n';
#endif

    DoPaint(dc);
}

void WorldControl::OnEraseBackground(wxEraseEvent& WXUNUSED(event)) {
    // Do nothing when erasing the background.
    // We will fully overwrite this during the foreground painting anyway.
    // It is also recommended to help reduce flickering when resizing.
}

void WorldControl::DoPaint(wxDC& dc) const {
#if DEBUG_WORLD_RENDERING
    // Clear background with red, making it easier to spot issues.
    // For example, if the client size being rendered is larger than intended.
    dc.SetBackground(*wxRED_BRUSH);
    dc.Clear();
#endif

    // Use solid black to draw (out)lines.
    dc.SetPen(*wxBLACK_PEN);

    // Draw world.
    for(int y = 0; y < m_world.GetHeight(); ++y) {
        for(int x = 0; x  < m_world.GetWidth(); ++x) {
            Tile tile = m_world.GetTileAt(x, y);

            // Draw tile.
            if(tile.type == TileType::Wall) {
                dc.SetBrush(WALL_BRUSH);
                dc.DrawRectangle(x * m_tileSize, y * m_tileSize, m_tileSize, m_tileSize);
                dc.DrawLine(x * m_tileSize, y * m_tileSize, (x + 1) * m_tileSize, (y + 1) * m_tileSize);
                dc.DrawLine((x + 1) * m_tileSize, y * m_tileSize, x * m_tileSize, (y + 1) * m_tileSize);
            } else if(tile.type == TileType::Ground) {
                dc.SetBrush(GROUND_BRUSH);
                dc.DrawRectangle(x * m_tileSize, y * m_tileSize, m_tileSize, m_tileSize);
            }

            // Draw ball on tile if need be.
            if(tile.hasBall) {
                dc.SetBrush(BALL_BRUSH);
                dc.DrawCircle(x * m_tileSize + m_tileSize / 2, y * m_tileSize + m_tileSize / 2, m_ballSize);
            }
        }
    }

    // Draw Charles polygon.
    Position pos = m_world.GetPosition();
    Direction dir = m_world.GetDirection();

    dc.SetBrush(CHARLES_BRUSH);
    dc.DrawPolygon(m_charlesShapes[dir].size(), m_charlesShapes[dir].data(), pos.x * m_tileSize, pos.y * m_tileSize);
}