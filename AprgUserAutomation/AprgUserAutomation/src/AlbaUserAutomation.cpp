#include "AlbaUserAutomation.hpp"

#include <cctype>

namespace alba
{

MousePosition AlbaUserAutomation::getMousePosition() const
{
    MousePosition position;
    POINT mouse;
    GetCursorPos(&mouse);
    position.x = mouse.x;
    position.y = mouse.y;
    return position;
}

void AlbaUserAutomation::setMousePosition(MousePosition position) const
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

void AlbaUserAutomation::doLeftClick() const
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

void AlbaUserAutomation::typeLetter(char letter) const
{
    doOperation([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = ::toupper(letter);
        input.ki.dwFlags = 0;
    });
    doOperation([&](INPUT& input)
    {
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = ::toupper(letter);
        input.ki.dwFlags = KEYEVENTF_KEYUP;
    });
}

bool AlbaUserAutomation::isLetterPressed(char letter) const
{
    USHORT status = GetAsyncKeyState(::toupper(letter));
    return (( ( status & 0x8000 ) >> 15 ) == 1) || (( status & 1 ) == 1);
}

void AlbaUserAutomation::doOperation(AlbaUserAutomation::InputFunction inputFunction) const
{
    INPUT input;
    memset(&input, 0, sizeof(INPUT));
    inputFunction(input);
    SendInput(1, &input, sizeof(INPUT));
    Sleep(m_realisticDelayInMilliseconds);
}

}
