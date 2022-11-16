#pragma once

#include <ChessUtilities/ChessEngineHandler.hpp>
#include <ChessUtilities/Engine/CalculationDetails.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <deque>
#include <fstream>
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
        UciOption,
        Position,
        Go,
        Stop,
    };

    struct Command
    {
        CommandType commandType;
        std::string commandString;
    };

    using StepsInCalculationMonitoring = std::function<void(CalculationDetails const&)> ;

    ChessEngineControllerWithUci(
            ChessEngineHandler & engineHandler,
            stringHelper::StringPairs const& uciOptionNamesAndValuePairs = {});

    void resetToNewGame();
    void setupStartPosition();
    void setupMoves(std::string const& moves);
    void setupFenString(std::string const& fenString);
    void go();
    void goWithPonder();
    void goWithDepth(unsigned int const depth);
    void goInfinite();
    bool waitTillReadyAndReturnIfResetWasPerformed();
    void stop();

    void setAdditionalStepsInCalculationMonitoring(StepsInCalculationMonitoring const& additionalSteps);
    void setLogFile(std::string const& logFilePath);

private:

    void initialize();
    void resetEngine();

    // clear functions
    void clearData();
    void clearCalculationDetails();

    // state functions
    void changeState(ControllerState const state);
    void proceedToIdleStateAndProcessPendingCommands();

    // log functions
    void log(std::string const& logString);

    // send functions
    void forceSend(std::string const& commandString);
    void sendStopIfCalculating();
    void sendUciAndUciOptions();
    void sendUci();
    void sendStop();
    void sendUciOptions();
    void send(CommandType const& commandType, std::string const& commandString);
    void send(Command const& command);

    // process functions
    void processInWaitingForReadyOkay(std::string const& stringFromEngine);
    void processAStringFromEngine(std::string const& stringFromEngine);
    void processInWaitingForUciOkay(std::string const& stringToProcess);
    void processInCalculating(std::string const& stringToProcess);

    std::string constructUciOptionCommand(std::string const& name, std::string const& value);

    ChessEngineHandler & m_engineHandler;
    stringHelper::StringPairs m_uciOptionNamesAndValuePairs;
    AlbaOptional<StepsInCalculationMonitoring> m_additionalStepsInCalculationMonitoring;
    AlbaOptional<std::ofstream> m_logFileStreamOptional;
    ControllerState m_state;
    bool m_waitingForReadyOkay;
    CalculationDetails m_currentCalculationDetails;
    std::deque<Command> m_pendingCommands;
};

std::string getEnumString(ChessEngineControllerWithUci::ControllerState const state);
std::ostream & operator<<(std::ostream & out, ChessEngineControllerWithUci::ControllerState const state);


}

}
