#pragma once

#include <State/AlbaBaseStateMachine.hpp>

namespace alba
{

namespace FakeStateMachine
{

enum class State
{
    StateWithNoValue,
    State1,
    State2,
    State3,
    State4
};

enum class Action
{
    InitializeTo1,
    Increase,
    Decrease,
    NoAction,
    MultiplyBy2
};

ALBA_BASE_STATE_MACHINE_GENERIC_TEMPLATE_FUNCTION(StateType, State)
ALBA_BASE_STATE_MACHINE_ADD_TEMPLATE_FUNCTION(StateType, State::StateWithNoValue)
ALBA_BASE_STATE_MACHINE_ADD_TEMPLATE_FUNCTION(StateType, State::State1)
ALBA_BASE_STATE_MACHINE_ADD_TEMPLATE_FUNCTION(StateType, State::State2)
ALBA_BASE_STATE_MACHINE_ADD_TEMPLATE_FUNCTION(StateType, State::State3)
ALBA_BASE_STATE_MACHINE_ADD_TEMPLATE_FUNCTION(StateType, State::State4)

using BaseSampleStateMachine = AlbaBaseStateMachine<State, Action, std::string>;
class SampleStateMachine : public BaseSampleStateMachine
{
public:
    SampleStateMachine(State const stateIdentifier);
    void processInput(Action const& action);
private:
    void processInput(StateType<State::StateWithNoValue>, Action const& action);
    void processInput(StateType<State::State1>, Action const& action);
    void processInput(StateType<State::State2>, Action const& action);
    void processInput(StateType<State::State3>, Action const& action);
    void processInput(StateType<State::State4>, Action const& action);
    void saveActionToOutput(Action const& action);
};

}

}//namespace alba
