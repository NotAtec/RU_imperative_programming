#pragma once

#include "world_control.h"

#include <wx/wx.h>

class FreePlayFrame : public wxFrame {
public:
    FreePlayFrame(const World& world, int zoomScale);
private:
    void OnKeyDown(wxKeyEvent& event);
    void PerformAction(Action action);

    WorldControl*   m_worldControl;
    wxBoxSizer*     m_worldSizerH;
    wxBoxSizer*     m_worldSizerV;
};
