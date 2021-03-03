#include "AlbaWindowsUserAutomation.hpp"

#include <String/AlbaStringHelper.hpp>
#include <Windows/AlbaWindowsHelper.hpp>

#include <windows.h>

#include <iostream>
#include <cctype>

using namespace std;

namespace alba
{

bool AlbaWindowsUserAutomation::isLetterPressed(char const letter) const
{
    USHORT status = GetAsyncKeyState(::toupper(letter));
    return (( ( status & 0x8000 ) >> 15 ) == 1); //|| (( status & 1 ) == 1);

    /*
     https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getasynckeystate
If the function succeeds, the return value specifies whether the key was pressed since the last call to GetAsyncKeyState,
and whether the key is currently up or down. I
f the most significant bit is set, the key is down, and if the least significant bit is set, the key was pressed after the previous call to GetAsyncKeyState.
However, you should not rely on this last behavior; for more information, see the Remarks.
*/
}

void AlbaWindowsUserAutomation::setStringToClipboard(std::string const& clipBoardText) const
{
    HANDLE hData;
    char *pointerData = NULL;//pointer to allow char copying

    hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE,clipBoardText.length() + 1);//get handle to memory to hold phrase
    pointerData = (char*)GlobalLock(hData);//get pointer from handle
    memcpy(pointerData,clipBoardText.c_str(),clipBoardText.length() + 1);//copy over the phrase
    GlobalUnlock(hData);//free the handle
    OpenClipboard(NULL);//allow you to work with clipboard
    EmptyClipboard();//clear previous contents
    SetClipboardData(CF_TEXT,hData);//set our data
    CloseClipboard();//finished!!
}

string AlbaWindowsUserAutomation::getStringFromClipboard() const
{
    string stringInClipboard;
    if(OpenClipboard(NULL))
    {
        HANDLE clipboardData = GetClipboardData(CF_TEXT);
        stringInClipboard = (char*)clipboardData;
        CloseClipboard();
    }
    return stringInClipboard;
}

MousePosition AlbaWindowsUserAutomation::getMousePosition() const
{
    MousePosition position;
    POINT mouse;
    GetCursorPos(&mouse);
    return MousePosition(mouse.x, mouse.y);
}

void AlbaWindowsUserAutomation::setMousePosition(MousePosition const& position) const
{
    long screenWidth = GetSystemMetrics( SM_CXSCREEN ) - 1;
    long screenHeight = GetSystemMetrics( SM_CYSCREEN ) - 1;
    float ratioInX = position.getX() * ( 65535.0f / screenWidth  );
    float ratioInY = position.getY() * ( 65535.0f / screenHeight );

    doOperationWithRealisticDelay([&](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = (long)ratioInX;
        input.mi.dy = (long)ratioInY;
    });
}

void AlbaWindowsUserAutomation::doLeftClick() const
{
    doOperationWithRealisticDelay([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    });
    doOperationWithRealisticDelay([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    });
}

void AlbaWindowsUserAutomation::doDoubleLeftClick() const
{
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    });
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    });
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    });
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    });
    sleepWithRealisticDelay();
}

void AlbaWindowsUserAutomation::doLeftClickAt(MousePosition const& position) const
{
    setMousePosition(position);
    doLeftClick();
}

void AlbaWindowsUserAutomation::doDoubleLeftClickAt(MousePosition const& position) const
{
    setMousePosition(position);
    doDoubleLeftClick();
}

void AlbaWindowsUserAutomation::doRightClickAt(MousePosition const& position) const
{
    setMousePosition(position);
    doRightClick();
}


void AlbaWindowsUserAutomation::doRightClick() const
{
    doOperationWithRealisticDelay([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    });
    doOperationWithRealisticDelay([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    });
}

void AlbaWindowsUserAutomation::pressDownKey(unsigned int const key) const
{
    doOperation([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = (WORD)key;
        input.ki.dwFlags = 0;
    });
}

void AlbaWindowsUserAutomation::pressUpKey(unsigned int const key) const
{
    doOperation([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = (WORD)key;
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    });
}

void AlbaWindowsUserAutomation::typeCharacter(char const character) const
{
    doOperationWithRealisticDelay([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = (WORD)convertToVirtualKey(character);
        input.ki.dwFlags = 0;
    });
    doOperationWithRealisticDelay([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = (WORD)convertToVirtualKey(character);
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    });
}

void AlbaWindowsUserAutomation::typeString(string const& stringToType) const
{
    for(char const character : stringToType)
    {
        typeCharacter(character);
    }
}

void AlbaWindowsUserAutomation::typeControlAndLetterSimultaneously(unsigned int const letter) const
{
    pressDownKey(VK_CONTROL);
    pressDownKey(letter);
    sleepWithRealisticDelay();
    pressUpKey(letter);
    pressUpKey(VK_CONTROL);
}

string AlbaWindowsUserAutomation::getClassNameOfForegroundWindow() const
{
    int const LENGTH = 1000;
    char className[LENGTH];
    GetClassName (GetForegroundWindow(), className, LENGTH);
    return string(className);
}

void AlbaWindowsUserAutomation::setForegroundWindowWithClassName(std::string const& className) const
{
    Sleep(2000);
    int const LENGTH = 1000;
    char classNameTemp[LENGTH];
    GetClassName (GetForegroundWindow(), classNameTemp, LENGTH);
    cout<<"ClassName:["<<classNameTemp<<"]"<<endl;

    HWND windowHandle = FindWindowEx(nullptr, nullptr, className.c_str(), nullptr);
    cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
    setForegroundWindowWithWindowHandle(windowHandle);
}

void AlbaWindowsUserAutomation::setForegroundWindowWithWindowName(std::string const& windowName) const
{
    HWND windowHandle = FindWindowEx(nullptr, nullptr, nullptr, windowName.c_str());
    setForegroundWindowWithWindowHandle(windowHandle);
}

void AlbaWindowsUserAutomation::sleepWithRealisticDelay() const
{
    Sleep(REALISTIC_DELAY_IN_MILLISECONDS);
}

void AlbaWindowsUserAutomation::sleep(unsigned int const milliseconds) const
{
    Sleep(milliseconds);
}

unsigned int AlbaWindowsUserAutomation::convertToVirtualKey(char const character) const
{
    int virtualKey = character;
    if(stringHelper::isLetter(character))
    {
        virtualKey = ::toupper(character);
    }
    else if('.' == character)
    {
        virtualKey = VK_OEM_PERIOD;
    }
    return virtualKey;
}

void AlbaWindowsUserAutomation::setForegroundWindowWithWindowHandle(HWND const windowHandle) const
{
    bool isSuccessful(false);
    if(windowHandle != nullptr)
    {
        isSuccessful = (bool)SetWindowPos(windowHandle,       // handle to window
                                          HWND_TOPMOST,  // placement-order handle
                                          0,     // horizontal position
                                          0,      // vertical position
                                          0,  // width
                                          0, // height
                                          SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE// window-positioning options
                                          );
    }
    if(!isSuccessful)
    {
        cout<<"Error in AlbaWindowsUserAutomation::setActiveWindow()"<<endl;
        cout<<AlbaWindowsHelper::getLastFormattedErrorMessage()<<endl;
    }
}

void AlbaWindowsUserAutomation::doOperation(AlbaWindowsUserAutomation::InputFunction const& inputFunction) const
{
    INPUT input;
    memset(&input, 0, sizeof(INPUT));
    inputFunction(input);
    SendInput(1, &input, sizeof(INPUT));
}

void AlbaWindowsUserAutomation::doOperationWithRealisticDelay(AlbaWindowsUserAutomation::InputFunction const& inputFunction) const
{
    doOperation(inputFunction);
    sleepWithRealisticDelay();
}
}
