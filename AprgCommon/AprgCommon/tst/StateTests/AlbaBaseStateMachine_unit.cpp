#include <State/AlbaBaseStateMachine.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaBaseStateMachine, IntegerIdentifierTest)
{
    AlbaBaseStateMachine<unsigned int, unsigned int> stateMachine(9999u);
    EXPECT_EQ(9999u, stateMachine.getState());
    //EXPECT_DEATH(stateMachine.processInput(0), "");
}

}

