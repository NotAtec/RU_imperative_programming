#include "trace.h"

Trace g_activeTrace;

void Trace::Initialize(const World& world, size_t maxEvents) {
    m_initialWorld = world;
    m_currentWorld = world;
    m_events.clear();
    m_nextEvent = 0;
    m_maxEvents = maxEvents;
    m_hasError = false;
}

void Trace::Abort(Action action) {
    m_hasError = true;
    m_events.push_back({action, {}});
    m_nextEvent++;
}

void Trace::Finalize() {
    assert(m_nextEvent == m_events.size());

    // Mark successfull completion of simulation if no errors occured.
    // We need this pseudo event so that the trace always ends with an event that cannot be performed.
    if(!m_hasError) {
        m_events.push_back({Action::EndSimulation, {}});
    }

    m_finalWorld = m_currentWorld;
    m_currentWorld = m_initialWorld;
    m_nextEvent = 0;
}

bool Trace::AddAction(Action action) {
    // Trace must be in the final state before adding another action
    assert(m_nextEvent == m_events.size());

    // Check if performing the action pushes the trace over the maximum number of events allowed.
    if(m_nextEvent >= m_maxEvents) {
        Abort(Action::AbortSimulationMaxSteps);

        throw SimulationException(SimulationError::MaxStepsExceeded);
    }

    try {
        bool sensor = m_currentWorld.PerformAction(action);

        m_events.push_back({action, {sensor}});
        m_nextEvent++;

        return sensor;
    } catch(SimulationException& ex) {
        Abort(action);

        // Rethrow exception to notify caller.
        throw;
    }
}

void Trace::AddMark(const char* str) {
    AddAction(Action::Mark);

    // Set last event data to the mark string.
    // Note that this does not occur if AddAction throws an exception (i.e. max steps exceeded).
    m_events.back().data.mark = str;
}

const World& Trace::Seek(size_t event) {
    assert(m_events.size() >= event);

    m_currentWorld = m_initialWorld;
    m_nextEvent = event;

    for(size_t i = 0; i < event; ++i) {
        m_currentWorld.PerformAction(m_events[i].action);
    }

    return m_currentWorld;
}

const World& Trace::First() {
    m_currentWorld = m_initialWorld;
    m_nextEvent = 0;

    return m_currentWorld;
}

const World& Trace::Last() {
    m_currentWorld = m_finalWorld;
    m_nextEvent = m_events.size() - 1;

    return m_currentWorld;
}

const World& Trace::FirstMark() {
    // Seek to the first mark action encountered.
    for(size_t i = 0; i < m_events.size(); ++i) {
        if(m_events[i].action == Action::Mark) {
            return Seek(i);
        }
    }

    // If no mark action exists, then seek to first event.
    return First();
}

const World& Trace::LastMark() {
    // Seek to the last mark action encountered.
    for(size_t i = m_events.size(); i != 0; --i) {
        if(m_events[i - 1].action == Action::Mark) {
            return Seek(i - 1);
        }
    }

    // If no mark action exists, then seek to the last event.
    return Last();
}

const World& Trace::Next() {
    if(m_nextEvent < m_events.size() - 1) {
        m_currentWorld.PerformAction(m_events[m_nextEvent++].action);
    }

    return m_currentWorld;
}

const World& Trace::NextMark() {
    // If already on last event, then no next mark will exist
    if(m_nextEvent >= m_events.size() - 1) {
        return m_currentWorld;
    }

    // Skip over current next event
    m_currentWorld.PerformAction(m_events[m_nextEvent++].action);

    // Loop till last event, or till next event is a mark event
    while(m_nextEvent < m_events.size() - 1 && m_events[m_nextEvent].action != Action::Mark) {
        m_currentWorld.PerformAction(m_events[m_nextEvent++].action);
    }

    return m_currentWorld;
}

const World& Trace::Previous() {
    if(m_nextEvent == 0) {
        return m_initialWorld;
    } else {
        return Seek(m_nextEvent-1);
    }
}

const World& Trace::PreviousMark() {
    // If already on first event, then no previous mark will exist
    if(m_nextEvent == 0) {
        return m_currentWorld;
    }

    // Go back one event
    m_nextEvent--;

    // Loop till first event, or till next event is a mark event
    while(m_nextEvent > 0 && m_events[m_nextEvent].action != Action::Mark) {
        m_nextEvent--;
    }

    return Seek(m_nextEvent);
}