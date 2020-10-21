#include <AlbaUserAutomation.hpp>

#include <gtest/gtest.h>

using namespace alba;

TEST(AlbaUserAutomationTest, DISABLED_MouseTest)
{
    AlbaUserAutomation userAutomation;
    for(int x=0; x<50; x++)
    {
        MousePosition position{x,x};
        userAutomation.setMousePosition(position);
    }
}

TEST(AlbaUserAutomationTest, DISABLED_KeyTest)
{
    AlbaUserAutomation userAutomation;
    for(int x=0; x<10; x++)
    {
        userAutomation.typeLetter('q');
    }
}

TEST(AlbaUserAutomationTest, DISABLED_KeyPressTest)
{
    AlbaUserAutomation userAutomation;
    EXPECT_TRUE(userAutomation.isLetterPressed('q'));
}
