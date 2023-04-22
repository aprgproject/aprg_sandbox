#pragma once

#include <Common/State/AlbaBaseStateMachine.hpp>

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

using BaseSampleStateMachine = AlbaBaseStateMachine<State, Action>;
class SampleStateMachine : public BaseSampleStateMachine
{
public:
    SampleStateMachine(State const stateIdentifier);
    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)

    void processInput(Action const& action) override;
private:
    void processStateWithNoValue(Action const action);
    void processState1(Action const action);
    void processState2(Action const action);
    void processState3(Action const action);
    void processState4(Action const action);
};

}

}//namespace alba
