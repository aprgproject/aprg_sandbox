#include <ChessEngineHandler/ChessEngineHandler.hpp>

using namespace alba;
using namespace std;

int main()
{
    // This is a mirror
    ChessEngineHandler engine("RybkaTest.exe");
    string stringReceived;
    while(1)
    {
        cin>>stringReceived;
        engine.sendToEngine(stringReceived);
        Sleep(1);
    }
    return 0;
}