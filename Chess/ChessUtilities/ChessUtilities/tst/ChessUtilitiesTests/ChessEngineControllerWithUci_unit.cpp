#include <ChessUtilities/ChessEngineControllerWithUci.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(ChessEngineControllerWithUciTest, WorksOnStartPosition)
{
    ChessEngineHandler chessEngineHandler(APRG_DIR R"(\Chess\ChessUtilities\FilesForTests\RybkaTest.exe)");
    chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessUtilities\FilesForTests\RybkaLog.log)");
    ChessEngineControllerWithUci controller(chessEngineHandler);

    controller.setupStartPosition();
    controller.go();
    Sleep(1000);

    controller.stop();
    Sleep(1000);
}

}
