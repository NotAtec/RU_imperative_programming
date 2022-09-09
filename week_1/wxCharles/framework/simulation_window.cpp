#include "simulation_window.h"

#include "res/icons.xpm"
#include "res/charles-icon.xpm"
#include "freeplay_window.h"
#include "scenario.h"
#include "trace.h"

#include <wx/thread.h>

#ifndef __WINDOWS__
#include <pthread.h>
#endif

#include <chrono>
#include <unordered_map>

/**
 * @brief Simulation window title, which is supplemented based on the active exercise.
 *
 */
static constexpr const char* WINDOW_TITLE = "wxCharles";

/**
 * @brief Placeholder exercise shown when window is first opened.
 *
 */
class DefaultExercise : public StaticExercise {
public:
    DefaultExercise() : StaticExercise("Hello World", "") {}

    World Create() override {
        World world(20, 10, {1, 2});

        return world;
    }
};

/**
 * @brief Exercise implementation for exercises loaded from external scenario files.
 *
 */
class ExternalExercise : public StaticExercise {
public:
    ExternalExercise(std::string&& name, World&& world)
        : StaticExercise(name, ""), m_world{world} {}

    World Create() override { return m_world; }

private:
    World m_world;
};


/**
 * @brief Thread that performs the actual execution of the agent function.
 *
 */
class SimThread : public wxThread {
public:
    SimThread(std::function<void()> agent, SimulationFrame* frame) : m_agent{agent}, m_frame{frame} {}

    ExitCode Entry() override {
        // Set up the current thread so that it can be cancelled when using pthread.
        // Without this a spinlooping thread might not cancel, as it might not be calling any syscalls.
#ifndef __WINDOWS__
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
#endif
        std::optional<SimulationError> error;

        try {
            m_agent();
        } catch(SimulationException& ex) {
            error = ex.GetError();
        }

        // At this point simulation has completed, so acquire the mutex lock and update the simulating variable.
        {
            std::lock_guard<std::mutex> lck(m_frame->m_mutex);
            m_frame->m_simulating = false;
            m_frame->m_lastSimError = error;
        }

        // Notify the watchdog thread simulation has completed.
        m_frame->m_cv.notify_one();

        return 0;
    }

private:
    std::function<void()> m_agent;
    SimulationFrame* m_frame;
};

/**
 * @brief Utiliy class to dynamically build sub menus for a wxMenu as needed.
 *
 */
class CategoryMenuBuilder {
public:
    /**
     * @brief Construct a new CategoryMenuBuilder object.
     *
     * @param rootMenu The root menu to add sub menus to, which may not be null.
     */
    CategoryMenuBuilder(wxMenu* rootMenu) : m_rootMenu{rootMenu} {
        assert(rootMenu != nullptr);
    }

    /**
     * @brief Gets the wxMenu instance for the given category. If the category is an empty string, the root menu is used instead.
     * If the menu for the category does not yet exist, a new one is created with the category string as the displayed text.
     *
     * @param category The category string.
     * @return A pointer to tthe menu instance.
     */
    wxMenu* GetMenu(const std::string& category) {
        // An empty category means add directly to the root menu.
        wxMenu* menu = m_rootMenu;

        // If the category is non-empty, then find the correct menu instance for that category.
        if(!category.empty()) {
            auto search = m_categories.find(category);

            if(search != m_categories.end()) {
                // Return existing instance.
                menu = search->second;
            } else {
                // Create new instance.
                menu = new wxMenu;
                m_rootMenu->AppendSubMenu(menu, category);

                m_categories.insert({category, menu});
            }
        }

        return menu;
    }

private:
    wxMenu* m_rootMenu;
    std::unordered_map<std::string, wxMenu*> m_categories;
};

enum{
    ID_Hello = 1,
    ID_Toggle = 2,
    ID_PlayPause = 3,
    ID_Stop = 4,
    ID_Timer = 5,
    ID_Test = 6,
    ID_ListView = 7,
    ID_Next = 8,
    ID_Previous = 9,
    ID_NextMark = 10,
    ID_PreviousMark = 11,
    ID_SendToFreePlay = 12,
    ID_PlaybackSpeed = 13,
    ID_VariantSelect = 14,
    ID_ResetWorld = 15,
    ID_CapturePNG = 16,
    ID_RunAttachedAgent = 17,
    ID_DynamicMenuStart = 18
};



/******************************************************************************
** SimulationFrame member functions
******************************************************************************/

SimulationFrame::SimulationFrame() : wxFrame(NULL, wxID_ANY, WINDOW_TITLE) {
    SetIcon(xpm_charles);

    m_assignment = CreateAssignment();

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Open\tCtrl-O", "Open world from scenario file");
    menuFile->Append(wxID_SAVE, "&Save\tCtrl-S", "Save current world to scenario file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuView = new wxMenu;
    menuView->AppendCheckItem(ID_Toggle, "Show &event trace\tCtrl-T", "Toggle the visibility of the event trace window")->Check();
    menuView->AppendSeparator();
    menuView->Append(wxID_ZOOM_IN, "Zoom &in\tCtrl-=", "Draw the world with a larger scale");
    menuView->Append(wxID_ZOOM_OUT, "Zoom &out\tCtrl--", "Draw the world with a smaller scale");
    menuView->Append(wxID_ZOOM_100, "&Reset zoom\tCtrl-+", "Draw the world with the default scale");

    wxMenu* menuAgent = new wxMenu;
    wxMenu* menuExercise = new wxMenu;

    ConfigureUI(menuAgent, menuExercise);

    // Only add separator if assignment added at least one agent to the run menu.
    if(menuAgent->GetMenuItemCount() != 0) {
        menuAgent->AppendSeparator();
    }

    // Add menu item to enable/disable automatic running of attached agents, which is enabled by default.
    m_runAttachedAgents = true;
    menuAgent->AppendCheckItem(ID_RunAttachedAgent, "&Run attached agents", "Automatically run attached agents when switching between exercises and/or variants")->Check();
    menuAgent->Bind(wxEVT_MENU, [this](wxCommandEvent& WXUNUSED(event)) {
        m_runAttachedAgents = !m_runAttachedAgents;
    }, ID_RunAttachedAgent);

    wxMenu* menuWorld = new wxMenu;
    menuWorld->Append(ID_ResetWorld, "&Reset\tCtrl-R", "Reset world to initial state");
    menuWorld->Append(ID_CapturePNG, "&Capture as PNG", "Save current world as a PNG image");
    menuWorld->Append(ID_SendToFreePlay, "Open in &Free-Play", "Open current world in free play mode");

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuView, "&View");
    menuBar->Append(menuAgent, "&Agent");
    menuBar->Append(menuExercise, "&Exercise");
    menuBar->Append(menuWorld, "&World");

    SetMenuBar( menuBar );
    CreateStatusBar();

    Bind(wxEVT_MENU, &SimulationFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &SimulationFrame::OnToggleView, this, ID_Toggle);
    Bind(wxEVT_MENU, &SimulationFrame::OnZoomIn, this, wxID_ZOOM_IN);
    Bind(wxEVT_MENU, &SimulationFrame::OnZoomOut, this, wxID_ZOOM_OUT);
    Bind(wxEVT_MENU, &SimulationFrame::OnResetZoom, this, wxID_ZOOM_100);
    Bind(wxEVT_MENU, &SimulationFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &SimulationFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &SimulationFrame::OnResetWorld, this, ID_ResetWorld);
    Bind(wxEVT_MENU, &SimulationFrame::OnCaptureAsPNG, this, ID_CapturePNG);
    Bind(wxEVT_TOOL, &SimulationFrame::OnNext, this, ID_Next);
    Bind(wxEVT_TOOL, &SimulationFrame::OnPrevious, this, ID_Previous);
    Bind(wxEVT_TOOL, &SimulationFrame::OnNextMark, this, ID_NextMark);
    Bind(wxEVT_TOOL, &SimulationFrame::OnPreviousMark, this, ID_PreviousMark);
    Bind(wxEVT_TOOL, &SimulationFrame::OnPlayPause, this, ID_PlayPause);
    Bind(wxEVT_TOOL, &SimulationFrame::OnStop, this, ID_Stop);
    Bind(wxEVT_TOOL, &SimulationFrame::OnSendToFreePlay, this, ID_SendToFreePlay);
    Bind(wxEVT_TIMER, &SimulationFrame::OnTimer, this, ID_Timer);
    Bind(wxEVT_LIST_ITEM_ACTIVATED, &SimulationFrame::OnListItemActivated, this, ID_ListView);
    Bind(wxEVT_SLIDER, &SimulationFrame::OnPlaybackSpeedChanged, this, ID_PlaybackSpeed);
    Bind(SIMULATION_COMPLETED, &SimulationFrame::OnSimulationCompleted, this, wxID_ANY);
    Bind(wxEVT_CLOSE_WINDOW, &SimulationFrame::OnClose, this, wxID_ANY);
    Bind(wxEVT_SPINCTRL, &SimulationFrame::OnSelectVariant, this, ID_VariantSelect);

    wxToolBar* toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);

    // The toolbar MUST be set before adding tools for it to show up on OSX
    SetToolBar(toolbar);

    long sliderStyle = wxSL_HORIZONTAL;
#if __LINUX__
    // Use value label on Linux builds.
    // Value labels are not implemented on OSX, and render in an ugly way on Windows.
    sliderStyle |= wxSL_VALUE_LABEL;
#endif
    m_slider = new wxSlider(toolbar, ID_PlaybackSpeed, 10, 1, 100, wxDefaultPosition, wxSize(100, -1), sliderStyle);
    m_slider->SetSize(wxSize(100, -1));
    m_slider->SetToolTip("Actions per second Charles performs");

    m_variantSelect = new wxSpinCtrl(toolbar, ID_VariantSelect);
    m_variantSelect->SetSize(100, -1);
    m_variantSelect->SetToolTip("Variant of current exercise");

    // Uncomment the line below to center the tools on the toolbar.
    // Tools are currently left aligned, which keeps the variant spin control in place.
    // If tools are centered, it might move around when switching variants, which is frustrating for the user.
    //toolbar->AddStretchableSpace();
    toolbar->AddTool(ID_PlayPause, wxT("play_pause"), wxBitmap(xpm_play), wxT("Play/Resume"));
    toolbar->AddTool(ID_Stop, wxT("stop"), wxBitmap(xpm_stop), wxT("Stop"));
    toolbar->AddSeparator();
    toolbar->AddTool(ID_Previous, wxT("prev"), wxBitmap(xpm_prev), wxT("Previous"));
    toolbar->AddTool(ID_Next, wxT("next"), wxBitmap(xpm_next), wxT("Next"));
    toolbar->AddTool(ID_PreviousMark, wxT("prev_mark"), wxBitmap(xpm_prev_mark), wxT("Previous mark"));
    toolbar->AddTool(ID_NextMark, wxT("next_mark"), wxBitmap(xpm_next_mark), wxT("Next mark"));
    toolbar->AddSeparator();
    toolbar->AddControl(new wxStaticText(toolbar, wxID_ANY, wxT("Speed\t")));
    toolbar->AddControl(m_slider);
    toolbar->AddSeparator();
    toolbar->AddControl(new wxStaticText(toolbar, wxID_ANY, wxT("Variant\t")));
    toolbar->AddControl(m_variantSelect);
    toolbar->AddStretchableSpace();

    // Set help text shown in status bar on hover.
    toolbar->SetToolLongHelp(ID_Stop, "Stop playback and reset to initial world");
    toolbar->SetToolLongHelp(ID_Next, "Perform the next event");
    toolbar->SetToolLongHelp(ID_Previous, "Undo the last event");
    toolbar->SetToolLongHelp(ID_NextMark, "Perform events until the next mark event");
    toolbar->SetToolLongHelp(ID_PreviousMark, "Undo events until the previous mark event");

    toolbar->Realize();
    
    m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE);
    m_traceList = new TraceListControl(m_splitter, ID_ListView);
    m_panel = new wxPanel(m_splitter, wxID_ANY);

    m_worldSizerV = new wxBoxSizer(wxVERTICAL);
    m_worldSizerH = new wxBoxSizer(wxHORIZONTAL);
    m_worldControl = new WorldControl(m_panel, wxID_ANY);

    m_worldSizerH->Add(m_worldControl, 1, wxALIGN_CENTER);
    m_worldSizerV->Add(m_worldSizerH, 1, wxALIGN_CENTER);

    m_timer = new wxTimer(this, ID_Timer);
    m_simulating = false;

    m_splitter->SetMinimumPaneSize(80);
    m_splitter->SetSashGravity(1.0);
    m_splitter->SplitVertically(m_panel, m_traceList, -200);

    m_sizer = new wxBoxSizer(wxHORIZONTAL);
    m_sizer->Add(m_splitter, 1, wxEXPAND);
    SetSizerAndFit(m_sizer);

    SetActiveExercise(std::make_shared<DefaultExercise>());
}

void SimulationFrame::ConfigureUI(wxMenu* runMenu, wxMenu* exerciseMenu) {
    int nextId = ID_DynamicMenuStart;
    CategoryMenuBuilder runBuilder(runMenu);
    CategoryMenuBuilder exerciseBuilder(exerciseMenu);

    // Add all agents to the run menu under the correct category, and attach event handler that starts agent simulation.
    for(auto& agent : m_assignment->GetAgents()) {
        int windowId = nextId++;
        wxMenu* category = runBuilder.GetMenu(agent->category);

        category->Append(windowId, agent->name, agent->description);
        category->Bind(wxEVT_MENU, [this, &agent](wxCommandEvent& WXUNUSED(event)){
            RunSimulation(agent);
        }, windowId);
    }

    // Add all exercise to the exercise menu under the correct category, and attach event handler that sets the active exercise.
    for(auto& exercise : m_assignment->GetExercises()) {
        int windowId = nextId++;
        wxMenu* category = exerciseBuilder.GetMenu(exercise->GetCategory());

        category->Append(windowId, exercise->GetName(), exercise->GetDescription());
        category->Bind(wxEVT_MENU, [this, &exercise](wxCommandEvent& WXUNUSED(event)) {
            SetActiveExercise(exercise);
        }, windowId);
    }
}

void SimulationFrame::SetActiveExercise(std::shared_ptr<Exercise> activeExercise) {
    m_activeExercise = activeExercise;

    m_variantSelect->SetValue(m_activeExercise->GetMinVariant());
    m_variantSelect->SetRange(m_activeExercise->GetMinVariant(), m_activeExercise->GetMaxVariant());
    m_variantSelect->Enable(m_activeExercise->HasVariants());

    SelectVariant(m_activeExercise->GetMinVariant());
}

void SimulationFrame::SelectVariant(int variant, bool suppressSimulation) {
    // Stop playback if it is running.
    m_timer->Stop();
    SetPlaybackState(PlaybackState::Paused);

    World world = m_activeExercise->Create(variant);
    m_worldControl->SetWorld(world);

    // Reset active trace and update UI.
    // We must reset the trace first, as the trace list is updated based on its state.
    g_activeTrace.Initialize(world, 0);
    SetPlaybackState(PlaybackState::NotAvailable);

    // Make the UI fit the possibly resized world control.
    FitToWorldControl();

    // Set window title to reflect active exercise and variant if one exists.
    // Note that we take the 'clean' name, which removes the keyboard accelerator part.
    if(m_activeExercise->HasVariants()) {
        SetTitle(wxString::Format("%s - %s #%d", WINDOW_TITLE, m_activeExercise->GetCleanName(), variant));
    } else {
        SetTitle(wxString::Format("%s - %s", WINDOW_TITLE, m_activeExercise->GetCleanName()));
    }

    // If the exercise has an attached agent, then automatically simulate this agent, unless explicitly suppressed.
    // The user can suppress this globally, but it is also required for some internal actions, such as resetting the world.
    if(m_activeExercise->HasAttachedAgent() && m_runAttachedAgents && !suppressSimulation) {
        auto agent = m_activeExercise->GetAttachedAgent();

        // If the agent threw a simulation error last time it was simulated, then do not run it again.
        // This is to prevent spamming errors to the user, for instance as they scroll through variants.
        if(!agent->hadSimulationError) {
            RunSimulation(agent);
        } else {
            SetStatusText("Attached agent not ran due to prior simulation error");
        }
    }
}

void SimulationFrame::SetPlaybackState(PlaybackState state) {
    m_playbackState = state;
    wxToolBar* toolbar = GetToolBar();

    if(state == PlaybackState::NotAvailable) {
        m_traceList->UpdateFromActiveTrace();
        toolbar->SetToolLongHelp(ID_PlayPause, "Playback unavailable, run an agent first");
        SetStatusText("Playback unavailable, run an agent first");
    } else if(state == PlaybackState::Paused) {
        toolbar->SetToolNormalBitmap(ID_PlayPause, wxBitmap(xpm_play));
        toolbar->SetToolShortHelp(ID_PlayPause, wxT("Play/Resume"));
        toolbar->SetToolLongHelp(ID_PlayPause, "Start/Resume playback");
        SetStatusText("Playback paused");
    } else if(state == PlaybackState::Running) {
        toolbar->SetToolNormalBitmap(ID_PlayPause, wxBitmap(xpm_pause));
        toolbar->SetToolShortHelp(ID_PlayPause, wxT("Pause"));
        toolbar->SetToolLongHelp(ID_PlayPause, "Pause playback");
        SetStatusText("Playback running");
    }
}

// Simulation watchdog thread entry point.
wxThread::ExitCode SimulationFrame::Entry() {
    std::unique_lock<std::mutex> lck(m_mutex);
    auto timeout = std::chrono::milliseconds(m_simTimeout);

    // Wait until the simulation thread completes, or the timeout threshold is exceeded.
    if(m_cv.wait_for(lck, timeout, [this](){ return !m_simulating; })) {
        // Simulation completed before timeout occurred, so queue simulation completed event for UI thread.
        if(m_lastSimError.has_value()) {
            // If the simulation thread reported an error, then attach the error condition.
            wxQueueEvent(this, new SimulationEvent(SIMULATION_COMPLETED, m_simAgent.value(), m_lastSimError.value()));
        } else {
            wxQueueEvent(this, new SimulationEvent(SIMULATION_COMPLETED, m_simAgent.value()));
        }
    } else {
        // Timeout occurred, so forcefully abort simulation.
        g_activeTrace.Abort(Action::AbortSimulationTimeout);

        // The simulation thread is almost certainly stuck in a spinloop for this to occur.
        // The only way to end it is to forcefully kill it, otherwise it would continue eating away at the CPU/battery.
        // This is a nuclear option that may leave the C/C++ runtime in an undefined state.
        // As the thread is spinlooping, terminating it will probably not have a negative impact on the user mode code being ran.
        // For instance, the thread is not stuck in a bit of code actively modifying the active trace.
        // This means killing it *should* not impact the active trace, leaving it in a well defined state.
        m_simThread->Kill();
        m_simulating = false;

        // Queue simulation completed event for UI thread with a timeout error condition.
        wxQueueEvent(this, new SimulationEvent(SIMULATION_COMPLETED, m_simAgent.value(), SimulationError::Timeout));
    }

    return 0;
}

void SimulationFrame::RunSimulation(std::shared_ptr<Agent> agent) {
    // Prevent starting a simulation when one is already running.
    {
        std::lock_guard<std::mutex> lck(m_mutex);

        if(m_simulating) {
            wxLogError("Simulation already running, please wait for it to complete");
            return;
        }
    }

    // Lock UI while the simulation is running.
    // This should prevent the user from modifying the trace as it is being captured.
    m_traceList->Disable();
    GetToolBar()->Disable();

    g_activeTrace.Initialize(m_worldControl->GetWorld(), agent->maxActions);
    m_traceList->UpdateFromActiveTrace();

    m_simulating = true;
    m_simTimeout = agent->timeout;
    m_simAgent = agent;

    SetStatusText("Running agent simulation, please wait...");

    // Create and start the simulation thread.
    m_simThread = new SimThread(agent->agent, this);
    m_simThread->Run();

    // Create and start the simulation watchdog thread.
    CreateThread();
    GetThread()->Run();
}

void SimulationFrame::SelectEvent(int index) {
    index = wxMin(index, m_traceList->GetItemCount() - 1);

    if(index >= 0) {
        m_traceList->EnsureVisible(index);
        m_traceList->SetItemState(index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
}

void SimulationFrame::FitToWorldControl() {
    // Update size hints so that the minimum and actual window sizes reflect the new world size.
    m_worldSizerH->SetSizeHints(m_worldControl);
    m_worldSizerV->SetSizeHints(m_worldControl);
    m_panel->SetSizerAndFit(m_worldSizerV);
    m_sizer->Layout();
    SetSizerAndFit(m_sizer);

    // Ensure toolbar is not cut off by forcing a certain minimum width.
    SetMinSize(wxSize{wxMax(GetMinWidth(), 650), GetMinHeight()});
}



/******************************************************************************
** SimulationFrame event handlers
******************************************************************************/

void SimulationFrame::OnPlaybackSpeedChanged(wxCommandEvent& WXUNUSED(event)) {
    // Only update timer speed when currently playing.
    if(m_playbackState != PlaybackState::Running) return;

    // Restart timer with updated speed.
    m_timer->Start(1000 / m_slider->GetValue());
}

void SimulationFrame::OnTimer(wxTimerEvent& WXUNUSED(event)) {
    // If we are about to execute a pause action, then pause the playback.
    if(g_activeTrace.GetNextAction() == Action::Pause && !m_ignorePauseEvents) {
        m_timer->Stop();
        SetPlaybackState(PlaybackState::Paused);
    }

    m_worldControl->SetWorld(g_activeTrace.Next());

    SelectEvent(g_activeTrace.GetNextEvent());

    // If the next event to execute is the final event, then pause the playback.
    // The final event can never be executed, as it is either a pseudo or error event.
    if(g_activeTrace.AtFinalEvent()) {
        m_timer->Stop();
        m_ignorePauseEvents = false;
        SetPlaybackState(PlaybackState::Paused);
    }
}

void SimulationFrame::OnExit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}

void SimulationFrame::OnOpen(wxCommandEvent& WXUNUSED(event)) {
    // Prevent opening a scenario while a simulation is running.
    // This is needed as loading a scenario resets the active trace.
    {
        std::lock_guard<std::mutex> lck(m_mutex);

        if(m_simulating) {
            wxLogError("Simulation still running, please wait for it to complete");
            return;
        }
    }

    wxFileDialog dialog(this, "Open scenario file", "", "", "Scenario files (*.scenario)|*.scenario", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if(dialog.ShowModal() == wxID_OK) {
        World world;

        if(!Scenario::LoadFrom(dialog.GetPath().ToStdString(), world)) {
            wxMessageBox(Scenario::GetLastError(), "Error loading scenario", wxOK | wxCENTRE | wxICON_ERROR);
        } else {
            SetActiveExercise(std::make_shared<ExternalExercise>(dialog.GetFilename().ToStdString(), std::move(world)));
        }
    }
}

void SimulationFrame::OnSave(wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog dialog(this, "Save scenario file", "", "", "Scenario files (*.scenario)|*.scenario", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if(dialog.ShowModal() == wxID_OK) {
        if(!Scenario::SaveTo(dialog.GetPath().ToStdString(), m_worldControl->GetWorld())) {
            wxMessageBox(Scenario::GetLastError(), "Error saving scenario", wxOK | wxCENTRE | wxICON_ERROR);
        }
    }
}

void SimulationFrame::OnToggleView(wxCommandEvent& WXUNUSED(event)) {
    if(m_traceList->IsShown()) {
        m_splitter->Unsplit(m_traceList);
        m_splitter->SetMinimumPaneSize(0);
        
    } else {
        m_splitter->SplitVertically(m_panel, m_traceList, -200);
        m_splitter->SetMinimumPaneSize(80);
    }

    // Update size hints so that the minimum and actual window sizes reflect whether the trace list is shown or not
    m_panel->SetSizerAndFit(m_worldSizerV);
    SetSizerAndFit(m_sizer);
}

void SimulationFrame::OnPlayPause(wxCommandEvent& WXUNUSED(event)) {
    if(m_playbackState == PlaybackState::Paused) {
        // Allow shift click to ignore pause events while playback is running.
        if(wxGetKeyState(WXK_SHIFT)) {
            m_ignorePauseEvents = true;
        }

        SetPlaybackState(PlaybackState::Running);
        m_timer->Start(1000 / m_slider->GetValue());
    } else if(m_playbackState == PlaybackState::Running) {
        m_ignorePauseEvents = false;
        SetPlaybackState(PlaybackState::Paused);
        m_timer->Stop();
    } else if(m_playbackState == PlaybackState::NotAvailable) {
        wxMessageBox("You must first run an agent to obtain a simulation trace that can then be played back."
        " Either select an exercise to run the attached agent, or run an agent manually using the Agent menu item.",
        "Run an agent first", wxOK | wxCENTER | wxICON_INFORMATION);
    }
}

void SimulationFrame::OnStop(wxCommandEvent& WXUNUSED(event)) {
    // Ignore event if no playback trace is available.
    if(m_playbackState == PlaybackState::NotAvailable) return;

    // Disable step timer
    m_timer->Stop();
    m_ignorePauseEvents = false;

    // Rewind trace to initial word, and update UI
    g_activeTrace.First();
    m_worldControl->SetWorld(g_activeTrace.GetCurrentWorld());

    // Make sure the first event is selected to reflect initial world state.
    // Effectively we are pausing at the first event.
    SelectEvent(0);
    SetPlaybackState(PlaybackState::Paused);
}

void SimulationFrame::OnListItemActivated(wxListEvent& event) {
    // Ignore activation event if no playback trace is available.
    if(m_playbackState == PlaybackState::NotAvailable) return;

    int index = event.GetIndex();

    World world = g_activeTrace.Seek(index);

    m_worldControl->SetWorld(world);
}

void SimulationFrame::OnSimulationCompleted(SimulationEvent& event) {
    // If the simulation was aborted due to an error, then display the error to the user.
    if(event.HasError()) {
        wxLogError(wxString::Format("Simulation error occured at step %d\n\n%s",
            static_cast<int>(g_activeTrace.GetEventCount()),
            DescribeSimulationError(event.GetError()))
        );
    }

    // Mark whether the agent managed to complete the simulation successfully.
    // This is used to detect problematic agents, which are not automatically ran when attached to exercises.
    event.GetAgent()->hadSimulationError = event.HasError();

    // Complete the active trace. After this no further events should be added to the trace.
    g_activeTrace.Finalize();

    // (Re)populate trace list with trace of all events performed.
    m_traceList->UpdateFromActiveTrace();

    // Select first event to match trace being at initial event
    SelectEvent(0);
    SetPlaybackState(PlaybackState::Paused);

    // Unlock UI now that the simulation has completed.
    m_traceList->Enable();
    GetToolBar()->Enable();

    SetStatusText("Agent simulation completed");
}

void SimulationFrame::OnClose(wxCloseEvent& WXUNUSED(event)) {
    wxThread* thread = GetThread();

    // If the simulation watchdog thread exists and is still running we MUST wait for it to complete.
    // This is important because the thread accesses members of the simulation frame, so it cannot yet be destroyed.
    if(thread && thread->IsRunning()) {
        thread->Wait();
    }

    Destroy();
}

void SimulationFrame::OnNext(wxCommandEvent& WXUNUSED(event)) {
    // Ignore event if no playback trace is available.
    if(m_playbackState == PlaybackState::NotAvailable) return;

    if(wxGetKeyState(WXK_SHIFT)) {
        m_worldControl->SetWorld(g_activeTrace.Last());
    } else {
        m_worldControl->SetWorld(g_activeTrace.Next());
    }

    SelectEvent(g_activeTrace.GetNextEvent());
}

void SimulationFrame::OnPrevious(wxCommandEvent& WXUNUSED(event)) {
    // Ignore event if no playback trace is available.
    if(m_playbackState == PlaybackState::NotAvailable) return;

    if(wxGetKeyState(WXK_SHIFT)) {
        m_worldControl->SetWorld(g_activeTrace.First());
    } else {
        m_worldControl->SetWorld(g_activeTrace.Previous());
    }

    SelectEvent(g_activeTrace.GetNextEvent());
}

void SimulationFrame::OnNextMark(wxCommandEvent& WXUNUSED(event)) {
    // Ignore event if no playback trace is available.
    if(m_playbackState == PlaybackState::NotAvailable) return;

    if(wxGetKeyState(WXK_SHIFT)) {
        m_worldControl->SetWorld(g_activeTrace.LastMark());
    } else {
        m_worldControl->SetWorld(g_activeTrace.NextMark());
    }

    SelectEvent(g_activeTrace.GetNextEvent());
}

void SimulationFrame::OnPreviousMark(wxCommandEvent& WXUNUSED(event)) {
    // Ignore event if no playback trace is available.
    if(m_playbackState == PlaybackState::NotAvailable) return;

    if(wxGetKeyState(WXK_SHIFT)) {
        m_worldControl->SetWorld(g_activeTrace.FirstMark());
    } else {
        m_worldControl->SetWorld(g_activeTrace.PreviousMark());
    }

    SelectEvent(g_activeTrace.GetNextEvent());
}

void SimulationFrame::OnSendToFreePlay(wxCommandEvent& WXUNUSED(event)) {
    FreePlayFrame* frame = new FreePlayFrame(m_worldControl->GetWorld(), m_worldControl->GetZoomScale());

    frame->Show(true);
}

void SimulationFrame::OnSelectVariant(wxSpinEvent& event) {
    SelectVariant(event.GetInt());
}

void SimulationFrame::OnResetWorld(wxCommandEvent& WXUNUSED(event)) {
    SelectVariant(m_variantSelect->GetValue(), true);
}

void SimulationFrame::OnCaptureAsPNG(wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog dialog(this, "Save PNG file", "", "", "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if(dialog.ShowModal() == wxID_OK) {
        wxImage image = m_worldControl->PaintToPNG();

        if(!image.SaveFile(dialog.GetPath(), wxBITMAP_TYPE_PNG)) {
            wxLogError("Failed to save PNG");
        }
    }
}

void SimulationFrame::OnZoomIn(wxCommandEvent& WXUNUSED(event)) {
    m_worldControl->SetZoomScale(m_worldControl->GetZoomScale() + 1);

    FitToWorldControl();
}

void SimulationFrame::OnZoomOut(wxCommandEvent& WXUNUSED(event)) {
    int currentScale = m_worldControl->GetZoomScale();

    if(currentScale > 1) {
        m_worldControl->SetZoomScale(currentScale - 1);
    }

    FitToWorldControl();
}

void SimulationFrame::OnResetZoom(wxCommandEvent& WXUNUSED(event)) {
    m_worldControl->SetZoomScale(WorldControl::DEFAULT_ZOOM_SCALE);

    FitToWorldControl();
}