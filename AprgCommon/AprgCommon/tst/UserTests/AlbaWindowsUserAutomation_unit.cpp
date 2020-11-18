#include <User/AlbaWindowsUserAutomation.hpp>

#include <gtest/gtest.h>
#include <windows.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetMouseTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(int x=0; x<50; x++)
    {
        MousePosition position{x,x};
        userAutomation.setMousePosition(position);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_KeyPressSmallLetterTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(char c='a'; c<='z'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_KeyPressCapitalLetterTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(char c='A'; c<='Z'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_KeyPressNumberTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(char c='0'; c<='9'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_KeyPressOtherCharacterTest)
{
    AlbaWindowsUserAutomation userAutomation;
    userAutomation.typeString(R"(.......)");
    //userAutomation.typeString(R"(`~!@#$%^&*()_+-=[]\{}|;':",./<>?)");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_IsLetterPressedTest)
{
    AlbaWindowsUserAutomation userAutomation;
    EXPECT_TRUE(userAutomation.isLetterPressed('q'));
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_ShowMousePosition)
{
    AlbaWindowsUserAutomation userAutomation;
    while(1)
    {
        MousePosition position(userAutomation.getMousePosition());
        cout<<"X: "<<position.getX()<<" Y: "<<position.getY()<<endl;
        if(0==position.getX() && 0==position.getY())
        {
            break;
        }
        Sleep(100);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_GetStringFromClipboard)
{
    AlbaWindowsUserAutomation userAutomation;
    cout <<  userAutomation.getStringFromClipboard() << endl;
}
