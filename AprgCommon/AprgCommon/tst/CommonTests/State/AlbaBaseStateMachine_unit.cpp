#include <Common/State/AlbaBaseStateMachine.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaBaseStateMachineTest, IntegerIdentifierTest)
{
    AlbaBaseStateMachine<unsigned int, unsigned int> stateMachine(9999U);
    EXPECT_EQ(9999U, stateMachine.getState());    //EXPECT_DEATH(stateMachine.processInput(0), string());
}

}