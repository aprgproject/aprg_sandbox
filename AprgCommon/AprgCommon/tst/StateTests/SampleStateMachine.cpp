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
    switch(m_state)
    {
    case State::StateWithNoValue:
        processStateWithNoValue(action);
        break;
    case State::State1:
        processState1(action);
        break;
    case State::State2:
        processState2(action);
        break;
    case State::State3:
        processState3(action);
        break;
    case State::State4:
        processState4(action);
        break;
    default:
        assert(false);
        break;
    }
}

void SampleStateMachine::processStateWithNoValue(Action const& action)
{
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

void SampleStateMachine::processState1(Action const& action)
{
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

void SampleStateMachine::processState2(Action const& action)
{
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

void SampleStateMachine::processState3(Action const& action)
{
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

void SampleStateMachine::processState4(Action const& action)
{
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

}


}//namespace alba
