#pragma once

#include <cassert>

namespace alba {

template <typename State, typename Input>
class AlbaBaseStateMachine {
public:
    AlbaBaseStateMachine(State const initialState) : m_state(initialState) {}
    virtual ~AlbaBaseStateMachine() = default;  // virtual destructor because of virtual functions (vtable exists)
    // rule of zero

    virtual void processInput(Input const&) = 0;

    State getState() const { return m_state; }

protected:
    virtual void saveNextState(State const newState) { m_state = newState; }
    State m_state;
};

// This different from the "State" design pattern.

}  // namespace alba
