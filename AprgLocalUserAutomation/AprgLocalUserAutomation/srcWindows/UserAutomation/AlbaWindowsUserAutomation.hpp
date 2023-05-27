#pragma once

#include <Common/Container/AlbaXY.hpp>

#include <windows.h>

#include <functional>
#include <string>

namespace alba {

using MousePosition = AlbaXY<int>;

class AlbaWindowsUserAutomation {
public:
    typedef std::function<void(INPUT&)> InputFunction;
    bool isKeyPressed(int const key) const;
    bool isLetterPressed(char const letter) const;
    MousePosition getMousePosition() const;
    void setMousePosition(MousePosition const& position) const;
    void pressLeftButtonOnMouse() const;
    void releaseLeftButtonOnMouse() const;
    void doLeftClick() const;
    void doDoubleLeftClick() const;
    void doLeftClickAt(MousePosition const& position) const;
    void doDoubleLeftClickAt(MousePosition const& position) const;
    void pressRightButtonOnMouse() const;
    void releaseRightButtonOnMouse() const;
    void doRightClick() const;
    void doRightClickAt(MousePosition const& position) const;
    void pressKey(uint16_t const key) const;
    void releaseKey(uint16_t const key) const;
    void typeKey(uint16_t const key) const;
    void typeCharacter(char const character) const;
    void typeString(std::string const& stringToType) const;
    void typeControlAndLetterSimultaneously(uint16_t const letter) const;
    std::string getClassNameOfForegroundWindow() const;
    void setForegroundWindowWithClassName(std::string const& className) const;
    void setForegroundWindowWithWindowName(std::string const& windowName) const;
    void sleepWithRealisticDelay() const;
    void sleep(int const milliseconds) const;

    void saveBitmapOnScreen(
        std::string const& filePath) const;  // Note: the difference on partially capturing the screen is negligible
    std::string getStringFromClipboard() const;
    void setStringToClipboard(std::string const& clipBoardText) const;
    void saveBitmapFromClipboard(std::string const& filePath) const;

private:
    uint16_t convertToVirtualKey(char const character) const;
    void setForegroundWindowWithWindowHandle(HWND const windowHandle) const;
    void doOperation(InputFunction const& inputFunction) const;
    void doOperationWithRealisticDelay(AlbaWindowsUserAutomation::InputFunction const& inputFunction) const;
    static constexpr int REALISTIC_DELAY_IN_MILLISECONDS = 100;
};

}  // namespace alba