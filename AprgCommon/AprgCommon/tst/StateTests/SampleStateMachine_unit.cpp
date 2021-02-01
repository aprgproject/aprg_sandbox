#include <StateTests/SampleStateMachine.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace alba::FakeStateMachine;
using namespace std;

void verifyResultsOfAction(State const initialState, Action const actionToBePerformed, State const expectedState, string const& output)
{
    SampleStateMachine stateMachine(State::StateWithNoValue);
    EXPECT_EQ(State::StateWithNoValue, stateMachine.getState());
    EXPECT_TRUE(stateMachine.getOutput().empty());
}

TEST(SampleStateMachineTest, InitialValuesAreCorrect)
{
    SampleStateMachine stateMachine(State::StateWithNoValue);
    EXPECT_EQ(State::StateWithNoValue, stateMachine.getState());
    EXPECT_TRUE(stateMachine.getOutput().empty());
}

TEST(SampleStateMachineTest, GoBackToOneWorks)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::InitializeTo1, State::State1, "InitializeTo1");
    verifyResultsOfAction(State::State1, Action::InitializeTo1, State::State1, "InitializeTo1");
    verifyResultsOfAction(State::State2, Action::InitializeTo1, State::State1, "InitializeTo1");
    verifyResultsOfAction(State::State3, Action::InitializeTo1, State::State1, "InitializeTo1");
    verifyResultsOfAction(State::State4, Action::InitializeTo1, State::State1, "InitializeTo1");
}

TEST(SampleStateMachineTest, IncreaseWorks)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::Increase, State::StateWithNoValue, "Increase");
    verifyResultsOfAction(State::State1, Action::Increase, State::State2, "Increase");
    verifyResultsOfAction(State::State2, Action::Increase, State::State3, "Increase");
    verifyResultsOfAction(State::State3, Action::Increase, State::State4, "Increase");
    verifyResultsOfAction(State::State4, Action::Increase, State::StateWithNoValue, "Increase");
}

TEST(SampleStateMachineTest, DecreaseWorks)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::Decrease, State::StateWithNoValue, "Decrease");
    verifyResultsOfAction(State::State1, Action::Decrease, State::StateWithNoValue, "Decrease");
    verifyResultsOfAction(State::State2, Action::Decrease, State::State1, "Decrease");
    verifyResultsOfAction(State::State3, Action::Decrease, State::State2, "Decrease");
    verifyResultsOfAction(State::State4, Action::Decrease, State::State3, "Decrease");
}

TEST(SampleStateMachineTest, NoActionWorks)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::NoAction, State::StateWithNoValue, "NoAction");
    verifyResultsOfAction(State::State1, Action::NoAction, State::State1, "NoAction");
    verifyResultsOfAction(State::State2, Action::NoAction, State::State2, "NoAction");
    verifyResultsOfAction(State::State3, Action::NoAction, State::State3, "NoAction");
    verifyResultsOfAction(State::State4, Action::NoAction, State::State4, "NoAction");
}

TEST(SampleStateMachineTest, MultiplyBy2Works)
{
    verifyResultsOfAction(State::StateWithNoValue, Action::MultiplyBy2, State::StateWithNoValue, "MultiplyBy2");
    verifyResultsOfAction(State::State1, Action::MultiplyBy2, State::State2, "MultiplyBy2");
    verifyResultsOfAction(State::State2, Action::MultiplyBy2, State::State4, "MultiplyBy2");
    verifyResultsOfAction(State::State3, Action::MultiplyBy2, State::StateWithNoValue, "MultiplyBy2");
    verifyResultsOfAction(State::State4, Action::MultiplyBy2, State::StateWithNoValue, "MultiplyBy2");
}
