#include <ChessEngineHandler/ChessEngineHandler.hpp>

#include <iostream>

using namespace alba;
using namespace std;

int main()
{
    // This is a repeater
    ChessEngineHandler engine("RybkaTest.exe");
    string stringReceived;
    while(1)
    {
        cin >> stringReceived;
        engine.sendToEngine(stringReceived);
    }
    return 0;
}
