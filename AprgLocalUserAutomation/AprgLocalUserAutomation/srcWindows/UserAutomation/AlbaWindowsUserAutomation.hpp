#pragma once

#include <Common/Container/AlbaXY.hpp>

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
    void doDoubleLeftClick() const;
    void doLeftClickAt(MousePosition const& position) const;
    void doDoubleLeftClickAt(MousePosition const& position) const;
    void doRightClick() const;
    void doRightClickAt(MousePosition const& position) const;
    void pressDownKey(unsigned int const key) const;
    void pressUpKey(unsigned int const key) const;
    void typeKey(unsigned int const key) const;
    void typeCharacter(char const character) const;
    void typeString(std::string const& stringToType) const;
    void typeControlAndLetterSimultaneously(unsigned int const letter) const;
    std::string getClassNameOfForegroundWindow() const;
    void setForegroundWindowWithClassName(std::string const& className) const;
    void setForegroundWindowWithWindowName(std::string const& windowName) const;
    void sleepWithRealisticDelay() const;
    void sleep(unsigned int const milliseconds) const;
private:
    unsigned int convertToVirtualKey(char const character) const;
    void setForegroundWindowWithWindowHandle(HWND const windowHandle) const;
    void doOperation(InputFunction const& inputFunction) const;
    void doOperationWithRealisticDelay(AlbaWindowsUserAutomation::InputFunction const& inputFunction) const;
    static constexpr unsigned int REALISTIC_DELAY_IN_MILLISECONDS=1000;
};

}
