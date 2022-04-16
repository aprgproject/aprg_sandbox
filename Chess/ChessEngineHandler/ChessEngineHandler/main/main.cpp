#include <ChessEngineHandler/ChessEngineHandler.hpp>
#include <Common/File/AlbaFileReader.hpp>

#include <iostream>
using namespace alba;
using namespace std;

int main()
{
    // This is a repeater
    ChessEngineHandler chessEngineHandler(APRG_DIR R"(\Chess\ChessEngineHandler\FilesForTests\RybkaTest.exe)");
    chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessEngineHandler\FilesForTests\RybkaLog.log)");
    string stringReceived;
    while(1)
    {
        cin >> stringReceived; // cin has a problem on new line with arena, how to fix?
        if("xboard" != stringReceived)
        {
            chessEngineHandler.sendStringToEngine(stringReceived);
        }
    }
    return 0;
}