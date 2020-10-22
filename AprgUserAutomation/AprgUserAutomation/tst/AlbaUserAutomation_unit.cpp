#include <AlbaUserAutomation.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <windows.h>

using namespace alba;
using namespace std;

TEST(AlbaUserAutomationTest, DISABLED_MouseTest)
{    AlbaUserAutomation userAutomation;
    for(int x=0; x<50; x++)
    {
        MousePosition position{x,x};        userAutomation.setMousePosition(position);
    }
}

TEST(AlbaUserAutomationTest, DISABLED_KeyTest)
{
    AlbaUserAutomation userAutomation;
    for(int x=0; x<10; x++)
    {
        userAutomation.typeCharacter('q');
    }
}
TEST(AlbaUserAutomationTest, DISABLED_KeyPressTest)
{
    AlbaUserAutomation userAutomation;
    EXPECT_TRUE(userAutomation.isLetterPressed('q'));
}

TEST(AlbaUserAutomationTest, ShowMousePosition)
{
    AlbaUserAutomation userAutomation;
    while(1)
    {
        MousePosition position(userAutomation.getMousePosition());
        cout<<"X: "<<position.x<<" Y: "<<position.y<<endl;
        if(0==position.x && 0==position.y)
        {
            break;
        }
        Sleep(100);
    }
}