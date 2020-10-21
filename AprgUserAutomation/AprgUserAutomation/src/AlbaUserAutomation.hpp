#pragma once

#include <functional>
#include <windows.h>

namespace alba
{

struct MousePosition
{
    int x;
    int y;
};

class AlbaUserAutomation
{
public:
    typedef std::function<void(INPUT&)> InputFunction;
    MousePosition getMousePosition() const;
    void setMousePosition(MousePosition position) const;
    void doLeftClick() const;
    void typeLetter(char letter) const;
    bool isLetterPressed (char letter) const;

private:
    void doOperation(InputFunction inputFunction);
    const int m_realisticDelayInMilliseconds=200;
};

}
