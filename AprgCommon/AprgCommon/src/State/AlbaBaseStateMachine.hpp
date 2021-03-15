#pragma once

#include <cassert>
#include <functional>
#include <map>

namespace alba
{

template <typename StateIdentifierType, typename InputType> class AlbaBaseStateMachine
{
public:
    AlbaBaseStateMachine(StateIdentifierType const initialState)
        : m_state(initialState)
    {}

    virtual ~AlbaBaseStateMachine()
    {}

    virtual void processInput(InputType const&)
    {
        // This should not be accessed        assert(false);
    }

    StateIdentifierType getState() const
    {
        return m_state;
    }
protected:
    virtual void saveNextState(StateIdentifierType const newState)
    {
        m_state = newState;
    }
    StateIdentifierType m_state;
};

}//namespace alba
