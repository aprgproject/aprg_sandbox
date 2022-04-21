#pragma once

#include <ChessUtilities/ChessEngineHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <deque>
#include <string>

namespace alba
{

namespace chess
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

    enum class CommandType
    {
        Uci,
        Position,
        Go,
        Stop,
    };

    struct CalculationDetails
    {
        unsigned int depth;
        unsigned int selectiveDepth;
        unsigned int time;
        unsigned int nodes;
        unsigned int nodesPerSecond;
        stringHelper::strings pvMovesInBestLine;
        int scoreInCentipawns;
        unsigned int mateInNumberOfMoves;
        stringHelper::strings currentlySearchingMoves;
        std::string bestMove;
        std::string ponderMove;
    };

    struct Command
    {
        CommandType commandType;
        std::string commandString;
    };

    using StepsInCalculationMonitoring = std::function<void(CalculationDetails const&)> ;

    ChessEngineControllerWithUci(ChessEngineHandler & engineHandler);

    void resetToNewGame();
    void setupStartPosition();
    void setupMoves(std::string const& moves);
    void setupFenString(std::string const& fenString);
    void go();
    void goWithPonder();
    void goWithDepth(unsigned int const depth);
    void goInfinite();
    void sendIsReadyAndWaitOrResetIfNeeded();
    void stop();

    void setAdditionalStepsInCalculationMonitoring(StepsInCalculationMonitoring const& additionalSteps);
private:

    void initialize();
    void resetEngine();
    void proceedToIdleAndProcessPendingCommands();
    void clearCalculationDetails();

    void forceSend(std::string const& commandString);
    void sendStopIfCalculating();
    void sendUci();
    void sendStop();    void send(CommandType const& commandType, std::string const& commandString);
    void send(Command const& command);

    void processInWaitingForReadyOkay(std::string const& stringFromEngine);
    void processAStringFromEngine(std::string const& stringFromEngine);
    void processInWaitingForUciOkay(std::string const& stringToProcess);
    void processInCalculating(std::string const& stringToProcess);
    ChessEngineHandler & m_engineHandler;
    ControllerState m_state;
    bool m_waitingForReadyOkay;
    CalculationDetails m_currentCalculationDetails;
    std::deque<Command> m_pendingCommands;
    AlbaOptional<StepsInCalculationMonitoring> m_additionalStepsInCalculationMonitoring;};

}
}
