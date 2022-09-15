#pragma once

#include "world_control.h"
#include "trace_list_control.h"
#include "assignment.h"

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/thread.h>
#include <wx/event.h>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <optional>

enum class PlaybackState {
    NotAvailable,
    Paused,
    Running
};

class SimThread;

class SimulationEvent : public wxCommandEvent {
public:
    SimulationEvent(wxEventType eventType, std::shared_ptr<Agent> agent)
        : wxCommandEvent(eventType, wxID_ANY), m_error{SimulationError::Timeout}, m_hasError{false}, m_agent{agent} {}

    SimulationEvent(wxEventType eventType, std::shared_ptr<Agent> agent, SimulationError error)
        : wxCommandEvent(eventType, wxID_ANY), m_error{error}, m_hasError{true}, m_agent{agent} {}

    virtual wxEvent* Clone() const override { return new SimulationEvent(*this); }
    virtual wxEventCategory GetEventCategory() const override { return wxEVT_CATEGORY_THREAD; }

    SimulationError GetError() const { return m_error; }
    bool HasError() const { return m_hasError; }
    std::shared_ptr<Agent> GetAgent() const { return m_agent; }
private:
    SimulationError m_error;
    bool m_hasError;
    std::shared_ptr<Agent> m_agent;
};


wxDEFINE_EVENT(SIMULATION_COMPLETED, SimulationEvent);


class SimulationFrame : public wxFrame, public wxThreadHelper {
    friend class SimThread;

public:
    SimulationFrame();
protected:
    wxThread::ExitCode Entry() override;
private:
    void OnExit(wxCommandEvent& event);
    void OnToggleView(wxCommandEvent& event);
    void OnPlayPause(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnListItemActivated(wxListEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnPrevious(wxCommandEvent& event);
    void OnNextMark(wxCommandEvent& event);
    void OnPreviousMark(wxCommandEvent& event);
    void OnSendToFreePlay(wxCommandEvent& event);
    void OnPlaybackSpeedChanged(wxCommandEvent& event);
    void OnSimulationCompleted(SimulationEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnSelectVariant(wxSpinEvent& event);
    void OnResetWorld(wxCommandEvent& event);
    void OnCaptureAsPNG(wxCommandEvent& event);
    void OnZoomIn(wxCommandEvent& event);
    void OnZoomOut(wxCommandEvent& event);
    void OnResetZoom(wxCommandEvent& event);

    void RunSimulation(std::shared_ptr<Agent> agent);
    void SelectEvent(int index);
    void SetPlaybackState(PlaybackState state);
    void ConfigureUI(wxMenu* runMenu, wxMenu* exerciseMenu);
    void SetActiveExercise(std::shared_ptr<Exercise> activeExercise);
    void SelectVariant(int variant, bool suppressSimulation = false);
    void FitToWorldControl();

    bool m_runAttachedAgents;
    std::optional<SimulationError> m_lastSimError;
    std::optional<std::shared_ptr<Agent>> m_simAgent;
    std::shared_ptr<Exercise> m_activeExercise;
    std::unique_ptr<Assignment> m_assignment;
    int m_simTimeout;
    SimThread* m_simThread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_simulating;
    bool m_ignorePauseEvents;
    PlaybackState m_playbackState;
    TraceListControl* m_traceList;
    wxSplitterWindow* m_splitter;
    wxPanel* m_panel;
    wxTimer* m_timer;
    wxSlider* m_slider;
    wxSpinCtrl* m_variantSelect;
    WorldControl* m_worldControl;
    wxBoxSizer* m_worldSizerV;
    wxBoxSizer* m_worldSizerH;
    wxBoxSizer* m_sizer;
};