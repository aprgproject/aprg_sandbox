#include <Bitmap/Bitmap.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ScreenMonitoring/AlbaLocalScreenMonitoring.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba {

namespace chess {

TEST(ScreenMonitoringTest, ScreenCaptureCanBeSavedAsBitmap) {
    AlbaLocalScreenMonitoring screenMonitoring;
    screenMonitoring.capturePixelsFromScreen();

    AlbaLocalPathHandler outputFileForWhite(APRG_DIR R"(\Chess\ChessPeek\Files\ScreeMonitoringTest.bmp)");
    Bitmap outputBitmap(outputFileForWhite.getFullPath());
    BitmapSnippet outputSnippet(outputBitmap.getSnippetReadFromFileWholeBitmap());

    BitmapXY topLeftCorner = outputSnippet.getTopLeftCorner();
    BitmapXY bottomRightCorner = outputSnippet.getBottomRightCorner();
    for (unsigned int y = topLeftCorner.getY(); y <= bottomRightCorner.getY(); y++) {
        for (unsigned int x = topLeftCorner.getX(); x <= bottomRightCorner.getX(); x++) {
            outputSnippet.setPixelAt(BitmapXY(x, y), screenMonitoring.getColorAt(x, y));
        }
    }

    outputBitmap.setSnippetWriteToFile(outputSnippet);
}

}  // namespace chess

}  // namespace alba
