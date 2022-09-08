#include <wx/wx.h>

#include "simulation_window.h"

// Charles application instance
class CharlesApp : public wxApp {
public:
    virtual bool OnInit();
};

// Tell wxWidgets to implement the entry point in a platform independent manner
wxIMPLEMENT_APP(CharlesApp);

// Entry point of the application, create initial window and process command line arguments
bool CharlesApp::OnInit() {
    // TODO: process command line arguments.

    // Add support for loading and saving PNG files.
    wxImage::AddHandler(new wxPNGHandler);

    SimulationFrame* frame = new SimulationFrame();

    frame->Show(true);

    return true;
}
