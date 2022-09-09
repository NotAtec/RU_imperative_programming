#pragma once

#include <memory>

#include <wx/wx.h>
#include <wx/listctrl.h>

class TraceListControl : public wxListCtrl {
public:
    TraceListControl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

    void UpdateFromActiveTrace();

protected:
    wxString OnGetItemText(long item, long column) const override;
    wxListItemAttr* OnGetItemAttr(long item) const override;

private:
    bool m_empty;
    std::unique_ptr<wxListItemAttr> m_normalAttr;
    std::unique_ptr<wxListItemAttr> m_errorAttr;
};