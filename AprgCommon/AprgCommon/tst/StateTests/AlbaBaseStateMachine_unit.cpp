#include <State/AlbaBaseStateMachine.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(AlbaBaseStateMachine, IntegerIdentifierTest)
{
    AlbaBaseStateMachine<unsigned int, unsigned int, unsigned int> stateMachine(9999u);
    EXPECT_EQ(9999u, stateMachine.getState());
    EXPECT_NO_FATAL_FAILURE(stateMachine.getOutput());
    //EXPECT_DEATH(stateMachine.processInput(0), "");
}
