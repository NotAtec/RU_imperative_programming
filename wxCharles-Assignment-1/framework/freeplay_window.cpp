#include "freeplay_window.h"

#include "res/charles-icon.xpm"

static constexpr wxKeyCode STEP_KEY = WXK_SPACE;
static constexpr wxKeyCode TURN_LEFT_KEY = WXK_LEFT;
static constexpr wxKeyCode TURN_RIGHT_KEY = WXK_RIGHT;
static constexpr wxKeyCode TAKE_BALL_KEY = WXK_UP;
static constexpr wxKeyCode PLACE_BALL_KEY = WXK_DOWN;
static constexpr wxKeyCode EXIT_KEY = WXK_ESCAPE;

FreePlayFrame::FreePlayFrame(const World& world, int zoomScale): wxFrame(NULL, wxID_ANY, "wxCharles - Free Play") {
    SetIcon(xpm_charles);

    CreateStatusBar();
    SetStatusText("left/right = turn left/right, up/down = take/place ball, spacebar = step");

    m_worldSizerV = new wxBoxSizer(wxVERTICAL);
    m_worldSizerH = new wxBoxSizer(wxHORIZONTAL);
    m_worldControl = new WorldControl(this, wxID_ANY);

    m_worldControl->SetWorld(world);
    m_worldControl->SetZoomScale(zoomScale);
    m_worldControl->Bind(wxEVT_KEY_DOWN, &FreePlayFrame::OnKeyDown, this);

    m_worldSizerH->Add(m_worldControl, 1, wxALIGN_CENTER);
    m_worldSizerV->Add(m_worldSizerH, 1, wxALIGN_CENTER);

    m_worldSizerH->Fit(m_worldControl);
    m_worldSizerV->Fit(m_worldControl);

    m_worldSizerV->SetSizeHints(m_worldControl);
    SetSizerAndFit(m_worldSizerV);
}

void FreePlayFrame::OnKeyDown(wxKeyEvent& event) {
    switch (event.GetKeyCode()) {
        case STEP_KEY:
            PerformAction(Action::Step);
            break;
        case TURN_LEFT_KEY:
            PerformAction(Action::TurnLeft);
            break;
        case TURN_RIGHT_KEY:
            PerformAction(Action::TurnRight);
            break;
        case TAKE_BALL_KEY:
            PerformAction(Action::TakeBall);
            break;
        case PLACE_BALL_KEY:
            PerformAction(Action::PlaceBall);
            break;
        case EXIT_KEY:
            Close(true);
            break;
    }
}

void FreePlayFrame::PerformAction(Action action) {
    try {
        m_worldControl->GetWorld().PerformAction(action);

        // Force redraw of UI.
        m_worldControl->Refresh();
        m_worldControl->Update();
    } catch(SimulationException& e) {
        wxLogError(wxString::Format("Failed to perform action\n\n%s", e.what()));
    }
}