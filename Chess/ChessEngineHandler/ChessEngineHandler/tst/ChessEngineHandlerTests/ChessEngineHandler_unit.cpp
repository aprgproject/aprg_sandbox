#include <ChessEngineHandler/ChessEngineHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(ChessEngineHandlerTest, ChessEngineIsRunningAfterConstruction)
{
    ChessEngineHandler chessEngineHandler(APRG_DIR R"(\Chess\ChessEngineHandler\FilesForTests\RybkaTest.exe)");
    chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessEngineHandler\FilesForTests\RybkaLog.log)");

    chessEngineHandler.sendToEngine("uci");
}

}
