#include <StateTests/SampleStateMachine.hpp>

#include <gtest/gtest.h>

using namespace alba::FakeStateMachine;
using namespace std;

namespace alba
{

void verifyResultsOfAction(State const initialState, Action const actionToBePerformed, State const expectedState)
{
    SampleStateMachine stateMachine(initialState);
    stateMachine.processInput(actionToBePerformed);
    EXPECT_EQ(expectedState, stateMachine.getState());
}

TEST(SampleStateMachineTest, InitialValuesAreCorrect)
{
    SampleStateMachine stateMachine(State::StateWithNoValue);
    EXPECT_EQ(State::StateWithNoValue, stateMachine.getState());
}

TEST(SampleStateMachineTest, GoBackToOneWorks)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::InitializeTo1, State::State1);
    verifyResultsOfAction(State::State1, Action::InitializeTo1, State::State1);
    verifyResultsOfAction(State::State2, Action::InitializeTo1, State::State1);
    verifyResultsOfAction(State::State3, Action::InitializeTo1, State::State1);
    verifyResultsOfAction(State::State4, Action::InitializeTo1, State::State1);
}

TEST(SampleStateMachineTest, IncreaseWorks)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::Increase, State::StateWithNoValue);
    verifyResultsOfAction(State::State1, Action::Increase, State::State2);
    verifyResultsOfAction(State::State2, Action::Increase, State::State3);
    verifyResultsOfAction(State::State3, Action::Increase, State::State4);
    verifyResultsOfAction(State::State4, Action::Increase, State::StateWithNoValue);
}

TEST(SampleStateMachineTest, DecreaseWorks)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::Decrease, State::StateWithNoValue);
    verifyResultsOfAction(State::State1, Action::Decrease, State::StateWithNoValue);
    verifyResultsOfAction(State::State2, Action::Decrease, State::State1);
    verifyResultsOfAction(State::State3, Action::Decrease, State::State2);
    verifyResultsOfAction(State::State4, Action::Decrease, State::State3);
}

TEST(SampleStateMachineTest, NoActionWorks)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::NoAction, State::StateWithNoValue);
    verifyResultsOfAction(State::State1, Action::NoAction, State::State1);
    verifyResultsOfAction(State::State2, Action::NoAction, State::State2);
    verifyResultsOfAction(State::State3, Action::NoAction, State::State3);
    verifyResultsOfAction(State::State4, Action::NoAction, State::State4);
}

TEST(SampleStateMachineTest, MultiplyBy2Works)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::MultiplyBy2, State::StateWithNoValue);
    verifyResultsOfAction(State::State1, Action::MultiplyBy2, State::State2);
    verifyResultsOfAction(State::State2, Action::MultiplyBy2, State::State4);
    verifyResultsOfAction(State::State3, Action::MultiplyBy2, State::StateWithNoValue);
    verifyResultsOfAction(State::State4, Action::MultiplyBy2, State::StateWithNoValue);
}

}
