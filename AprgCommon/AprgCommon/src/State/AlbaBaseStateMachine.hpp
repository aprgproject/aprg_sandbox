#pragma once

#include <cassert>
#include <functional>
#include <map>

namespace alba
{

template <typename StateIdentifierType, typename InputType, typename OutputType> class AlbaBaseStateMachine
{
public:
    AlbaBaseStateMachine(StateIdentifierType const initialState)
        : m_stateIdentifier(initialState)
    {}
    virtual void processInput(InputType const&)
    {
        // This should not be accessed        assert(false);
    }

    OutputType getOutput() const
    {
        return m_currentOutput;
    }

    StateIdentifierType getState() const
    {
        return m_stateIdentifier;
    }
protected:
    void gotoState(StateIdentifierType const newState)
    {
        m_stateIdentifier = newState;
    }
    StateIdentifierType m_stateIdentifier;
    OutputType m_currentOutput;
};

}//namespace alba
