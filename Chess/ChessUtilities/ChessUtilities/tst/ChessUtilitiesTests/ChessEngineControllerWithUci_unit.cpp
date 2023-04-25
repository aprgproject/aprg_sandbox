#include <ChessUtilities/ChessEngineControllerWithUci.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

TEST(ChessEngineControllerWithUciTest, DISABLED_WorksOnStartPosition) {
    ChessEngineHandler chessEngineHandler(APRG_DIR R"(\Chess\ChessUtilities\FilesForTests\RybkaTest.exe)");
    chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessUtilities\FilesForTests\RybkaLog.log)");
    ChessEngineControllerWithUci controller(chessEngineHandler);

    controller.setupStartPosition();
    controller.go();
    Sleep(1000);

    controller.stop();
    Sleep(1000);
}

}  // namespace chess

}  // namespace alba
