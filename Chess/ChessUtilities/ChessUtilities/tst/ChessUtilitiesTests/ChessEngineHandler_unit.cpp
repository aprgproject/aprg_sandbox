#include <ChessUtilities/ChessEngineHandler.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

TEST(ChessEngineHandlerTest, DISABLED_ChessEngineIsRunningAfterConstruction)
{
    ChessEngineHandler chessEngineHandler(APRG_DIR R"(\Chess\ChessUtilities\FilesForTests\RybkaTest.exe)");
    chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessUtilities\FilesForTests\RybkaLog.log)");

    chessEngineHandler.sendStringToEngine("uci");
    Sleep(1000);
}

TEST(ChessEngineHandlerTest, DISABLED_ChessEngineIsAbleToSendBestMove)
{
    ChessEngineHandler chessEngineHandler(APRG_DIR R"(\Chess\ChessUtilities\FilesForTests\RybkaTest.exe)");
    chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessUtilities\FilesForTests\RybkaLog.log)");

    chessEngineHandler.sendStringToEngine("uci");
    Sleep(1000);
    chessEngineHandler.sendStringToEngine("position startpos");
    chessEngineHandler.sendStringToEngine("go");
    Sleep(1000);
    chessEngineHandler.sendStringToEngine("stop");
    Sleep(1000);
}

}
