#include <ScreenMonitoring/AlbaWindowsScreenMonitoring.hpp>

#include <gtest/gtest.h>

#include <windows.h>

#include <iostream>

using namespace std;

namespace alba {

TEST(AlbaWindowsScreenMonitoringTest, GetPixelAtWorks) {
    AlbaWindowsScreenMonitoring screenMonitoring;
    screenMonitoring.capturePixelsFromScreen();

    EXPECT_NE(0U, screenMonitoring.getColorAt(100, 100));
}

}  // namespace alba