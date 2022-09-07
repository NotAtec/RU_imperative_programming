#pragma once

#include <wx/wx.h>

#include <array>

#include "world.h"

class WorldControl : public wxControl {
public:
    static constexpr int DEFAULT_ZOOM_SCALE = 4;

    WorldControl() {}

    WorldControl(wxWindow* parent, wxWindowID id,
                 const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
                 long style = wxSUNKEN_BORDER, const wxValidator& validator = wxDefaultValidator) {
        Create(parent, id, pos, size, style, validator);
    }

    bool Create(wxWindow* parent, wxWindowID id,
                const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
                long style = wxSUNKEN_BORDER, const wxValidator& validator = wxDefaultValidator);
    wxImage PaintToPNG() const;
    void SetZoomScale(int scale, bool update = true);
    int GetZoomScale() const { return m_zoomScale; }
    
    void SetWorld(const World& world);
    World& GetWorld() { return m_world; }

protected:
    // Overrides
    wxSize DoGetBestClientSize() const override;

    // Event handlers
    void OnPaint(wxPaintEvent& event);
    void OnEraseBackground(wxEraseEvent& event);

private:
    void DoPaint(wxDC& dc) const;

    World m_world;
    int m_zoomScale;
    int m_tileSize;
    int m_ballSize;
    std::array<std::array<wxPoint, 4>, NUM_DIRS> m_charlesShapes;
};