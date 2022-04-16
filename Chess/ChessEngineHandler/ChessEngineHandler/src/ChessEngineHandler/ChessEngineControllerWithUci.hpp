#pragma once

#include <ChessEngineHandler/ChessEngineHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <deque>
#include <string>

namespace alba
{

class ChessEngineControllerWithUci
{
public:
    enum class ControllerState
    {
        Initializing,
        WaitingForUciOkay,
        Calculating,
        Idle
    };
    struct CalculationDetails
    {
        unsigned int depth;
        unsigned int selectiveDepth;
        unsigned int time;
        unsigned int nodes;
        unsigned int nodesPerSecond;
        std::string bestLinePv;
        unsigned int scoreInCentipawns;
        unsigned int mateInNumberOfMoves;
        stringHelper::strings currentlySearchingMoves;
        std::string bestMove;
        std::string ponderMove;
    };

    ChessEngineControllerWithUci(ChessEngineHandler & engineHandler);

    void setupStartPosition();
    void setupMoves(std::string const& moves);
    void setupFenString(std::string const& fenString);
    void go();
    void goWithPonder();
    void goWithDepth(unsigned int const depth);
    void goInfinite();

private:
    void initialize();
    void proceedToIdleAndProcessPendingCommands();

    void sendStopIfCalculating();
    void sendUci();
    void sendStop();
    void send(std::string const& command);

    void processAStringFromEngine(std::string const& stringFromEngine);
    void processInWaitingForUciOkay(std::string const& stringToProcess);
    void processInCalculating(std::string const& stringToProcess);
    ChessEngineHandler & m_engineHandler;
    ControllerState m_state;
    CalculationDetails m_currentCalculationDetails;
    std::deque<std::string> m_pendingCommands;
};

}
