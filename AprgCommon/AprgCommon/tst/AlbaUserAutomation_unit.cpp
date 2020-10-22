#include <AlbaUserAutomation.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <windows.h>

using namespace alba;
using namespace std;

TEST(AlbaUserAutomationTest, DISABLED_SetMouseTest)
{
    AlbaUserAutomation userAutomation;
    for(int x=0; x<50; x++)
    {
        MousePosition position{x,x};
        userAutomation.setMousePosition(position);
    }
}

TEST(AlbaUserAutomationTest, DISABLED_KeyPressSmallLetterTest)
{
    AlbaUserAutomation userAutomation;
    for(char c='a'; c<='z'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaUserAutomationTest, DISABLED_KeyPressCapitalLetterTest)
{
    AlbaUserAutomation userAutomation;
    for(char c='A'; c<='Z'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaUserAutomationTest, DISABLED_KeyPressNumberTest)
{
    AlbaUserAutomation userAutomation;
    for(char c='0'; c<='9'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaUserAutomationTest, DISABLED_KeyPressOtherCharacterTest)
{
    AlbaUserAutomation userAutomation;
    userAutomation.typeString(R"(.......)");
    //userAutomation.typeString(R"(`~!@#$%^&*()_+-=[]\{}|;':",./<>?)");
}

TEST(AlbaUserAutomationTest, DISABLED_IsLetterPressedTest)
{
    AlbaUserAutomation userAutomation;
    EXPECT_TRUE(userAutomation.isLetterPressed('q'));
}

TEST(AlbaUserAutomationTest, DISABLED_ShowMousePosition)
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

TEST(AlbaUserAutomationTest, DISABLED_GetStringFromClipboard)
{
    AlbaUserAutomation userAutomation;
    cout <<  userAutomation.getStringFromClipboard() << endl;
}
