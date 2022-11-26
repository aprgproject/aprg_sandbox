#include <Common/State/AlbaDfaUsingMatrix.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
enum class State
{
    Unknown,
    First,
    Second,
    Third,
    Fourth,
    Fifth,
    MAX
};
using DfaForTest = AlbaDfaUsingMatrix<State, unsigned int>;

std::ostream & operator<<(std::ostream & out, State const state)
{
    out << "State" << static_cast<unsigned int>(state);
    return out;
}
}

TEST(AlbaDfaUsingMatrixTest, GetNextStateTest)
{
    DfaForTest dfa(static_cast<unsigned int>(State::MAX), 6U);
    dfa.setStateTransition(State::First, State::First, 1U);
    dfa.setStateTransition(State::First, State::Second, 2U);
    dfa.setStateTransition(State::First, State::Third, 3U);
    dfa.setStateTransition(State::First, State::Fourth, 4U);
    dfa.setStateTransition(State::First, State::Fifth, 5U);

    EXPECT_EQ(State::First, dfa.getNextState(State::First, 1U));
    EXPECT_EQ(State::Second, dfa.getNextState(State::First, 2U));
    EXPECT_EQ(State::Third, dfa.getNextState(State::First, 3U));
    EXPECT_EQ(State::Fourth, dfa.getNextState(State::First, 4U));
    EXPECT_EQ(State::Fifth, dfa.getNextState(State::First, 5U));
    EXPECT_EQ(State::Unknown, dfa.getNextState(State::Second, 1U));
    EXPECT_EQ(State::Unknown, dfa.getNextState(State::Second, 2U));
    EXPECT_EQ(State::Unknown, dfa.getNextState(State::Second, 3U));
    EXPECT_EQ(State::Unknown, dfa.getNextState(State::Second, 4U));
    EXPECT_EQ(State::Unknown, dfa.getNextState(State::Second, 5U));
}

TEST(AlbaDfaUsingMatrixTest, SetStateTransitionTest)
{
    DfaForTest dfa(static_cast<unsigned int>(State::MAX), 6U);

    dfa.setStateTransition(State::First, State::First, 1U);

    EXPECT_EQ(State::First, dfa.getNextState(State::First, 1U));
    EXPECT_EQ(State::Unknown, dfa.getNextState(State::First, 2U));
}

}
