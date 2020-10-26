#include "AlbaWindowsUserAutomation.hpp"

#include <String/AlbaStringHelper.hpp>

#include <windows.h>

#include <cctype>

using namespace std;

namespace alba
{

bool AlbaWindowsUserAutomation::isLetterPressed(char letter) const
{
    USHORT status = GetAsyncKeyState(::toupper(letter));
    return (( ( status & 0x8000 ) >> 15 ) == 1) || (( status & 1 ) == 1);
}

string AlbaWindowsUserAutomation::getStringFromClipboard() const
{
    string stringInClipboard;
    if(OpenClipboard(NULL))
    {
      HANDLE clipboardData = GetClipboardData(CF_TEXT);
      CloseClipboard();
      stringInClipboard = (char*)clipboardData;
    }
    return stringInClipboard;
}

MousePosition AlbaWindowsUserAutomation::getMousePosition() const
{
    MousePosition position;
    POINT mouse;
    GetCursorPos(&mouse);
    position.x = mouse.x;
    position.y = mouse.y;
    return position;
}

void AlbaWindowsUserAutomation::setMousePosition(MousePosition position) const
{
    long screenWidth = GetSystemMetrics( SM_CXSCREEN ) - 1;
    long screenHeight = GetSystemMetrics( SM_CYSCREEN ) - 1;
    float ratioInX = position.x * ( 65535.0f / screenWidth  );
    float ratioInY = position.y * ( 65535.0f / screenHeight );

    doOperation([&](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = (long)ratioInX;
        input.mi.dy = (long)ratioInY;
    });
}

void AlbaWindowsUserAutomation::doLeftClick() const
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
}

void AlbaWindowsUserAutomation::doRightClick() const
{
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    });
    doOperation([](INPUT& input)
    {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    });
}

void AlbaWindowsUserAutomation::typeString(string const& stringToType) const
{
    for(char const character : stringToType)
    {
        typeCharacter(character);
    }
}

void AlbaWindowsUserAutomation::typeCharacter(char character) const
{
    doOperation([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = convertToVirtualKey(character);
        input.ki.dwFlags = 0;
    });
    doOperation([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = convertToVirtualKey(character);
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    });
}

unsigned int AlbaWindowsUserAutomation::convertToVirtualKey(char character) const
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

void AlbaWindowsUserAutomation::doOperation(AlbaWindowsUserAutomation::InputFunction inputFunction) const
{
    INPUT input;
    memset(&input, 0, sizeof(INPUT));
    inputFunction(input);
    SendInput(1, &input, sizeof(INPUT));
    Sleep(c_realisticDelayInMilliseconds);
}

}



