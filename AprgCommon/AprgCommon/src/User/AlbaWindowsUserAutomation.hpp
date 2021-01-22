#pragma once

#include <Container/AlbaXY.hpp>

#include <windows.h>

#include <functional>
#include <string>

namespace alba
{

using  MousePosition = AlbaXY<int>;


class AlbaWindowsUserAutomation
{
public:
    typedef std::function<void(INPUT&)> InputFunction;
    bool isLetterPressed(char const letter) const;
    std::string getStringFromClipboard() const;
    void setStringToClipboard(std::string const& clipBoardText) const;
    MousePosition getMousePosition() const;
    void setMousePosition(MousePosition const& position) const;
    void doLeftClick() const;
    void doRightClick() const;
    void typeString(std::string const& stringToType) const;
    void typeCharacter(char const character) const;
    std::string getClassNameOfForegroundWindow() const;
    void setForegroundWindowWithClassName(std::string const& windowName) const;
    void setForegroundWindowWithWindowName(std::string const& windowName) const;
private:
    unsigned int convertToVirtualKey(char const character) const;
    void setForegroundWindowWithWindowHandle(HWND const windowHandle) const;
    void doOperation(InputFunction inputFunction) const;
    static constexpr unsigned int REALISTIC_DELAY_IN_MILLISECONDS=500;
};

}
