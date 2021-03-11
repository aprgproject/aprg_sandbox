#include <User/AlbaWindowsUserAutomation.hpp>

#include <gtest/gtest.h>
#include <windows.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(AlbaWindowsUserAutomationTest, DISABLED_DeleteThisTestDontGoToSleepSetMouseTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(int x=0; x<300; x+=10)    {
        MousePosition position{x,x};
        userAutomation.setMousePosition(position);
        userAutomation.sleep(10000);        if(x==290)
        {
            x=0;
        }
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetMouseTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(int x=0; x<50; x++)
    {
        MousePosition position{x,x};
        userAutomation.setMousePosition(position);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_KeyPressDownAndUpSmallLetterTest)
{
#define VK_CONTROL 0x11
    AlbaWindowsUserAutomation userAutomation;
    userAutomation.pressDownKey(VK_CONTROL);
    userAutomation.pressDownKey('A');
    userAutomation.pressUpKey(VK_CONTROL);
    userAutomation.pressUpKey('A');
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeSmallLetterTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(char c='a'; c<='z'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeCapitalLetterTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(char c='A'; c<='Z'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeNumberTest)
{
    AlbaWindowsUserAutomation userAutomation;
    for(char c='0'; c<='9'; c++)
    {
        userAutomation.typeCharacter(c);
    }
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_TypeString)
{
    AlbaWindowsUserAutomation userAutomation;
    userAutomation.typeString(R"(.......)");
    //userAutomation.typeString(R"(`~!@#$%^&*()_+-=[]\{}|;':",./<>?)");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_IsLetterPressedTest)
{
    AlbaWindowsUserAutomation userAutomation;
    while(1)
    {
        char letter = 'q';
        bool isPressed = userAutomation.isLetterPressed(letter);
        cout<<"letter: "<<letter<<" isPressed: "<<isPressed<<endl;
        if(isPressed)
        {
            break;
        }
        Sleep(100);
    }
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

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetStringFromClipboard)
{
    AlbaWindowsUserAutomation userAutomation;
    userAutomation.setStringToClipboard("TestString");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_GetClassNameOfForegroundWindow)
{
    AlbaWindowsUserAutomation userAutomation;
    cout<<userAutomation.getClassNameOfForegroundWindow()<<endl;
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetActiveWindowBasedClassName)
{
    AlbaWindowsUserAutomation userAutomation;
    userAutomation.setForegroundWindowWithClassName("Notepad");
}

TEST(AlbaWindowsUserAutomationTest, DISABLED_SetActiveWindowBasedWindowName)
{
    AlbaWindowsUserAutomation userAutomation;
    userAutomation.setForegroundWindowWithWindowName("Untitled - Notepad");
}
