#pragma once

#include <functional>
#include <string>
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
    bool isLetterPressed (char letter) const;
    std::string getStringFromClipboard() const;
    MousePosition getMousePosition() const;
    void setMousePosition(MousePosition position) const;
    void doLeftClick() const;
    void doRightClick() const;
    void typeString(std::string const& stringToType) const;
    void typeCharacter(char character) const;
    unsigned int convertToVirtualKey(char character) const;
private:
    void doOperation(InputFunction inputFunction) const;
    const unsigned int m_realisticDelayInMilliseconds=500;
};

}