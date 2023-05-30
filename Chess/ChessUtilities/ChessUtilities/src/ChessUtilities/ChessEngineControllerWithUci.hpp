#pragma once

#include <ChessUtilities/ChessEngineHandler.hpp>
#include <ChessUtilities/Engine/CalculationDetails.hpp>
#include <ChessUtilities/Uci/UciInterpreter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <deque>
#include <fstream>
#include <string>

namespace alba {

namespace chess {

class ChessEngineControllerWithUci {
public:
    enum class ControllerState { Initializing, WaitingForUciOkay, Calculating, Idle, Quitted };

    enum class CommandType {
        Uci,
        UciOption,
        Position,
        Go,
        Stop,
    };

    struct Command {
        CommandType commandType;
        std::string commandString;
    };

    using StepsInCalculationMonitoring = std::function<void(CalculationDetails const&)>;

    ChessEngineControllerWithUci(
        ChessEngineHandler& engineHandler, stringHelper::StringPairs const& uciOptionNamesAndValuePairs = {});

    void initialize();
    void quit();
    void resetEngine();

    void resetToNewGame();
    void setupStartPosition();
    void setupMoves(std::string const& moves);
    void setupFenString(std::string const& fenString);
    void go();
    void goWithPonder();
    void goWithDepth(int const depth);
    void goInfinite();
    bool waitTillReadyAndReturnIfResetWasPerformed();
    void stop();

    void setAdditionalStepsInCalculationMonitoring(StepsInCalculationMonitoring const& additionalSteps);
    void setLogFile(std::string const& logFilePath);

private:
    // clear functions
    void resetData();
    void clearCalculationDetails();

    // state functions
    void changeState(ControllerState const state);
    void proceedToIdleStateAndProcessPendingCommands();
    void processPendingCommands();

    // log functions
    void log(std::string const& logString);

    // send functions
    void sendUci();
    void sendQuit();
    void sendStop();
    void sendUciAndUciOptions();
    void sendUciOptions();
    void sendStopIfCalculating();
    void send(CommandType const& commandType, std::string const& commandString);
    void send(Command const& command);
    void forceSend(std::string const& commandString);

    // process functions
    void processAStringFromEngine(std::string const& stringFromEngine);
    void processInWaitingForUciOkay(std::string const& stringToProcess);
    void processInCalculating(std::string const& stringToProcess);

    std::string constructUciOptionCommand(std::string const& name, std::string const& value);
    std::string getEnumString(ControllerState const state);
    void putStringProcessingFunctionAsCallBack();

    ChessEngineHandler& m_engineHandler;
    stringHelper::StringPairs m_uciOptionNamesAndValuePairs;
    std::optional<StepsInCalculationMonitoring> m_additionalStepsInCalculationMonitoring;
    std::optional<std::ofstream> m_logFileStreamOptional;
    ControllerState m_state;
    bool m_waitingForReadyOkay;
    CalculationDetails m_calculationDetails;
    UciInterpreter m_uciInterpreter;
    std::deque<Command> m_pendingCommands;
};

}  // namespace chess

}  // namespace alba
