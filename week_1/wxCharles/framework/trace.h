#pragma once

#include "world.h"

struct Event {
    Action action;
    union {
        bool sensor;
        const char* mark;
    } data;
};

// NOTE: Trace contains a list of events (actions) that are executed in sequence on the initial world
// The nextEvent index points to the next event that will be executed
// This means current world is the state of the world -before- executing nextEvent
// The last event can never be executed, as it is either:
// - a pseudo simulation end, in case of successful simulation
// - a pseudo simulation aborted, in case of max step exceeded or timeout of agent thread
// - an action that triggered a simulation error, such as stepping into a wall
class Trace {
public:
    Trace() {
        Initialize(World(), 0);
    }

    Trace(const World& initialWorld, size_t maxEvents) {
        Initialize(initialWorld, maxEvents);
    }

    // Trace construction.
    void Initialize(const World& world, size_t maxEvents);
    void Abort(Action action);
    void Finalize();
    bool AddAction(Action action);
    void AddMark(const char* str);

    // Trace seeking.
    const World& First();
    const World& Last();
    const World& FirstMark();
    const World& LastMark();
    const World& Next();
    const World& Previous();
    const World& NextMark();
    const World& PreviousMark();
    const World& Seek(size_t event);

    // General getters.
    const World& GetInitialWorld() const { return m_initialWorld; }
    const World& GetCurrentWorld() const { return m_currentWorld; }
    const World& GetFinalWorld() const { return m_finalWorld; }
    size_t GetEventCount() const { return m_events.size(); }
    size_t GetNextEvent() const { return m_nextEvent; }
    Action GetAction(size_t index) const { return m_events[index].action; }
    Action GetNextAction() const { return GetAction(m_nextEvent); }
    Event GetEvent(size_t index) const { return m_events[index]; }
    bool HasError() const { return m_hasError; }
    bool AtFinalEvent() const { return m_nextEvent >= m_events.size() - 1; }

private:
    World m_initialWorld;
    World m_finalWorld;
    World m_currentWorld;
    std::vector<Event> m_events;
    size_t m_nextEvent;
    size_t m_maxEvents;
    bool m_hasError;
};

// Trace used to perform step() etc actions on
extern Trace g_activeTrace;