#include "SampleStateMachine.hpp"

using namespace std;
using namespace std::placeholders;

namespace alba
{

namespace FakeStateMachine
{

SampleStateMachine::SampleStateMachine(State const stateIdentifier)
    : AlbaBaseStateMachine(stateIdentifier)
{}

void SampleStateMachine::processInput(Action const& action)
{
    switch(m_stateIdentifier)
    {
    case State::StateWithNoValue:
        processInput(StateType<State::StateWithNoValue>(), action);
        break;
    case State::State1:
        processInput(StateType<State::State1>(), action);
        break;
    case State::State2:
        processInput(StateType<State::State2>(), action);
        break;
    case State::State3:
        processInput(StateType<State::State3>(), action);
        break;
    case State::State4:
        processInput(StateType<State::State4>(), action);
        break;
    default:
        assert(false);
        break;
    }
}

void SampleStateMachine::processInput(StateType<State::StateWithNoValue>, Action const& action)
{
    saveActionToOutput(action);
    switch(action)
    {
    case Action::InitializeTo1:
        gotoState(State::State1);
        break;
    case Action::Increase:
        gotoState(State::StateWithNoValue);
        break;
    case Action::Decrease:
        gotoState(State::StateWithNoValue);
        break;
    case Action::NoAction:
        gotoState(State::StateWithNoValue);
        break;
    case Action::MultiplyBy2:
        gotoState(State::StateWithNoValue);
        break;
    }
}

void SampleStateMachine::processInput(StateType<State::State1>, Action const& action)
{
    saveActionToOutput(action);
    switch(action)
    {
    case Action::InitializeTo1:
        gotoState(State::State1);
        break;
    case Action::Increase:
        gotoState(State::State2);
        break;
    case Action::Decrease:
        gotoState(State::StateWithNoValue);
        break;
    case Action::NoAction:
        gotoState(State::State1);
        break;
    case Action::MultiplyBy2:
        gotoState(State::State2);
        break;
    }
}

void SampleStateMachine::processInput(StateType<State::State2>, Action const& action)
{
    saveActionToOutput(action);
    switch(action)
    {
    case Action::InitializeTo1:
        gotoState(State::State1);
        break;
    case Action::Increase:
        gotoState(State::State3);
        break;
    case Action::Decrease:
        gotoState(State::State1);
        break;
    case Action::NoAction:
        gotoState(State::State2);
        break;
    case Action::MultiplyBy2:
        gotoState(State::State4);
        break;
    }
}

void SampleStateMachine::processInput(StateType<State::State3>, Action const& action)
{
    saveActionToOutput(action);
    switch(action)
    {
    case Action::InitializeTo1:
        gotoState(State::State1);
        break;
    case Action::Increase:
        gotoState(State::State4);
        break;
    case Action::Decrease:
        gotoState(State::State2);
        break;
    case Action::NoAction:
        gotoState(State::State3);
        break;
    case Action::MultiplyBy2:
        gotoState(State::StateWithNoValue);
        break;
    }
}

void SampleStateMachine::processInput(StateType<State::State4>, Action const& action)
{
    saveActionToOutput(action);
    switch(action)
    {
    case Action::InitializeTo1:
        gotoState(State::State1);
        break;
    case Action::Increase:
        gotoState(State::StateWithNoValue);
        break;
    case Action::Decrease:
        gotoState(State::State3);
        break;
    case Action::NoAction:
        gotoState(State::State4);
        break;
    case Action::MultiplyBy2:
        gotoState(State::StateWithNoValue);
        break;
    }
}

void SampleStateMachine::saveActionToOutput(Action const& action)
{
    switch(action)
    {
    case Action::InitializeTo1:
        m_currentOutput = "InitializeTo1";
        break;
    case Action::Increase:
        m_currentOutput = "Increase";
        break;
    case Action::Decrease:
        m_currentOutput = "Decrease";
        break;
    case Action::NoAction:
        m_currentOutput = "NoAction";
        break;
    case Action::MultiplyBy2:
        m_currentOutput = "MultiplyBy2";
        break;
    }
}

}


}//namespace alba
