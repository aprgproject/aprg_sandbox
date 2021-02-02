#pragma once

#include <cassert>
#include <functional>
#include <map>

namespace alba
{

#define ALBA_BASE_STATE_MACHINE_GENERIC_TEMPLATE_FUNCTION(GeneratedStateType, StateIdentifierType)   \
template <StateIdentifierType id>                                                           \
struct GeneratedStateType                                                                        \
{                                                                                                      \
    static_assert((unsigned int)id==-1, "State is not implemented.");                                                \
};                                                                                                     \
/**/

#define ALBA_BASE_STATE_MACHINE_ADD_TEMPLATE_FUNCTION(GeneratedStateType, id)           \
template <>                                                                               \
struct GeneratedStateType<id>                                                           \
{                                                                                         \
};                                                                                        \
/**/


template <typename StateIdentifierType, typename InputType, typename OutputType> class AlbaBaseStateMachine
{
public:
    using ProcessFunction = std::function<void(InputType const& action)>;

    AlbaBaseStateMachine(StateIdentifierType const initialState)
        : m_stateIdentifier(initialState)
    {}

    virtual void processInput(InputType const&)
    {
        // This should not be accessed
        assert(false);
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
