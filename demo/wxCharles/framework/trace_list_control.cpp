#include "trace_list_control.h"

#include "trace.h"

static const char* TRUE_STRING = "True";
static const char* FALSE_STRING = "False";

static wxString GetText(Event event) {
    switch (event.action) {
        case Action::FacingNorth:
            return wxString::Format("Facing north? (%s)", (event.data.sensor ? TRUE_STRING : FALSE_STRING));
        case Action::InFrontOfWall:
            return wxString::Format("In front of wall? (%s)", (event.data.sensor ? TRUE_STRING : FALSE_STRING));
        case Action::OnBall:
            return wxString::Format("On ball? (%s)", (event.data.sensor ? TRUE_STRING : FALSE_STRING));
        case Action::PlaceBall:
            return "Put ball";
        case Action::Step:
            return "Step";
        case Action::TakeBall:
            return "Get ball";
        case Action::TurnLeft:
            return "Turn left";
        case Action::TurnRight:
            return "Turn right";
        case Action::EndSimulation:
            return "End simulation";
        case Action::AbortSimulationMaxSteps:
            return "Abort simulation (max steps)";
        case Action::AbortSimulationTimeout:
            return "Abort simulation (timeout)";
        case Action::Pause:
            return "Pause";
        case Action::Mark:
            return wxString::Format("Mark: %s", event.data.mark);
        default:
            return "Unknown action";
    }
}

TraceListControl::TraceListControl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size) 
        : wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL | wxLC_SINGLE_SEL) {
    AppendColumn(wxT("Step"));
    AppendColumn(wxT("Event"));
    SetColumnWidth(0, 50);    
    SetColumnWidth(1, 150);

    // Create item attributes with default values, which control their appearance.
    // The error event, if one exists, is shown with a red text color.
    m_normalAttr = std::make_unique<wxListItemAttr>();
    m_errorAttr = std::make_unique<wxListItemAttr>();
    m_errorAttr->SetTextColour(*wxRED);
}

void TraceListControl::UpdateFromActiveTrace() {
    // The list control must always contain at least one item.
    // Either the trace is non empty, or otherwise a single N/A item is shown.
    SetItemCount(wxMax(1, g_activeTrace.GetEventCount()));

    // Remember whether the trace was empty or not.
    // This is important, as the trace can be updated in the background.
    // Such updates should not alter the displayed trace if it is empty however.
    m_empty = g_activeTrace.GetEventCount() == 0;

    // Updating the item count may not trigger a redraw, so request one manually.
    Refresh();
}

wxString TraceListControl::OnGetItemText(long index, long column) const {
    // If the trace is empty, then display N/A on all columns for the sole item displayed.
    if(m_empty) return "N/A";

    switch(column) {
        case 0:     return wxString::Format("%ld", index + 1);
        case 1:     return GetText(g_activeTrace.GetEvent(index));
        default:    return "?";
    }
}

wxListItemAttr* TraceListControl::OnGetItemAttr(long item) const {
    // Mark the last event in a trace with the error attributes if it triggered an error.
    bool isLast = item == static_cast<long>(g_activeTrace.GetEventCount()) - 1;

    return !m_empty && g_activeTrace.HasError() && isLast ? m_errorAttr.get() : m_normalAttr.get();
}