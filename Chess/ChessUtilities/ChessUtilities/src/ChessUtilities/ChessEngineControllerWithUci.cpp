#include "ChessEngineControllerWithUci.hpp"

#include <ChessUtilities/Uci/UciUtilities.hpp>
#include <Common/Macros/AlbaMacros.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimeHelper.hpp>

#include <iostream>
#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace chess
{

ChessEngineControllerWithUci::ChessEngineControllerWithUci(
        ChessEngineHandler & engineHandler,
        stringHelper::StringPairs const& uciOptionNamesAndValuePairs)
    : m_engineHandler(engineHandler)
    , m_uciOptionNamesAndValuePairs(uciOptionNamesAndValuePairs)
    , m_additionalStepsInCalculationMonitoring()
    , m_logFileStreamOptional()
    , m_state(ControllerState::Initializing)
    , m_waitingForReadyOkay(false)
    , m_currentCalculationDetails{}
    , m_pendingCommands()
{
    initialize();
}

void ChessEngineControllerWithUci::resetToNewGame()
{
    log("Resetting to a new game");
    sendStopIfCalculating();
    send(CommandType::Position, "ucinewgame");
}

void ChessEngineControllerWithUci::setupStartPosition()
{
    log("Setting start position");
    sendStopIfCalculating();
    send(CommandType::Position, "position startpos");
}

void ChessEngineControllerWithUci::setupMoves(string const& moves)
{
    log("Setting position with moves");
    sendStopIfCalculating();
    string command("position startpos moves ");
    command+=moves;
    send(CommandType::Position, command);
}

void ChessEngineControllerWithUci::setupFenString(string const& fenString)
{
    log("Setting position with FEN string");
    sendStopIfCalculating();
    string command("position fen ");
    command+=fenString;
    send(CommandType::Position, command);
}

void ChessEngineControllerWithUci::go()
{
    log("Go!");
    sendStopIfCalculating();
    send(CommandType::Go, "go");
}

void ChessEngineControllerWithUci::goWithPonder()
{
    log("Go with ponder!");
    sendStopIfCalculating();
    send(CommandType::Go, "go ponder");
}

void ChessEngineControllerWithUci::goWithDepth(unsigned int const depth)
{
    log("Go with depth!");
    sendStopIfCalculating();
    stringstream ss;
    ss << "go depth " << depth;
    send(CommandType::Go, ss.str());
}

void ChessEngineControllerWithUci::goInfinite()
{
    log("Go infinite!");
    sendStopIfCalculating();
    send(CommandType::Go, "go infinite");
}

bool ChessEngineControllerWithUci::waitTillReadyAndReturnIfResetWasPerformed()
{
    log("Sending \"isready\" and waiting for response");
    forceSend("isready");
    m_waitingForReadyOkay = true;

    bool shouldReset(false);
    unsigned int count(0U);
    while(m_waitingForReadyOkay)
    {
        if(count > 10) // 1 second elapsed so engine is stuck, lets reset
        {
            shouldReset = true;
            break;
        }
        count++;
        sleepFor(100);
    }

    if(shouldReset)
    {
        log("Engine is stuck, resetting engine");
        resetEngine();
    }

    return shouldReset;
}

void ChessEngineControllerWithUci::stop()
{
    sendStop();
}

void ChessEngineControllerWithUci::setAdditionalStepsInCalculationMonitoring(
        StepsInCalculationMonitoring const& additionalSteps)
{
    m_additionalStepsInCalculationMonitoring = additionalSteps;
}

void ChessEngineControllerWithUci::setLogFile(string const& logFilePath)
{
    m_logFileStreamOptional.emplace();
    m_logFileStreamOptional->open(logFilePath);

    if(!m_logFileStreamOptional->is_open())
    {
        cout << "Cannot open log file" << logFilePath;
    }
}

void ChessEngineControllerWithUci::initialize()
{
    m_engineHandler.setAdditionalStepsInProcessingAStringFromEngine([&](string const& stringFromEngine)
    {
        processAStringFromEngine(stringFromEngine);
    });
    sendUciAndUciOptions();
}

void ChessEngineControllerWithUci::resetEngine()
{
    log("Resetting engine");
    clearData();
    m_engineHandler.reset();
    sendUciAndUciOptions();
}

void ChessEngineControllerWithUci::clearData()
{
    changeState(ControllerState::Initializing);
    m_waitingForReadyOkay = false;
    m_currentCalculationDetails = {};
    m_pendingCommands.clear();
}

void ChessEngineControllerWithUci::clearCalculationDetails()
{
    m_currentCalculationDetails = CalculationDetails{};
}

void ChessEngineControllerWithUci::changeState(
        ControllerState const state)
{
    if(m_logFileStreamOptional)
    {
        m_logFileStreamOptional.value()
                << "Changing state from " << getEnumString(m_state)
                << " to " << getEnumString(state) << "\n";
    }
    m_state = state;
}

void ChessEngineControllerWithUci::proceedToIdleStateAndProcessPendingCommands()
{
    changeState(ControllerState::Idle);
    bool hasGoOnPendingCommand(false);
    while(!m_pendingCommands.empty() && !hasGoOnPendingCommand)
    {
        Command pendingCommand(m_pendingCommands.front());
        m_pendingCommands.pop_front();
        hasGoOnPendingCommand = CommandType::Go == pendingCommand.commandType;
        send(pendingCommand);
    }
}

void ChessEngineControllerWithUci::log(string const& logString)
{
    if(m_logFileStreamOptional)
    {
        m_logFileStreamOptional.value() << logString << "\n";
    }
}

void ChessEngineControllerWithUci::forceSend(
        string const& commandString)
{
    m_engineHandler.sendStringToEngine(commandString);
}

void ChessEngineControllerWithUci::sendStopIfCalculating()
{
    if(ControllerState::Calculating == m_state)
    {
        sendStop();
    }
}

void ChessEngineControllerWithUci::sendUciAndUciOptions()
{
    sendUci();
    sendUciOptions();
}

void ChessEngineControllerWithUci::sendUci()
{
    send(CommandType::Uci, "uci");
}

void ChessEngineControllerWithUci::sendStop()
{
    send(CommandType::Stop, "stop");
}

void ChessEngineControllerWithUci::sendUciOptions()
{
    for(StringPair const& namesAndValuePair : m_uciOptionNamesAndValuePairs)
    {
        send(CommandType::UciOption, constructUciOptionCommand(namesAndValuePair.first, namesAndValuePair.second));
    }
}

void ChessEngineControllerWithUci::send(
        CommandType const& commandType,
        string const& commandString)
{
    send(Command{commandType, commandString});
}

void ChessEngineControllerWithUci::send(
        Command const& command)
{
    log(string("Sending command: ") + command.commandString);

    // all the logic are here lol
    switch(m_state)
    {
    case ControllerState::Initializing:
    {
        if(CommandType::Uci == command.commandType)
        {
            m_engineHandler.sendStringToEngine(command.commandString);
            changeState(ControllerState::WaitingForUciOkay);
        }
        else
        {
            m_pendingCommands.emplace_back(command);
        }
        break;
    }
    case ControllerState::WaitingForUciOkay:
    {
        m_pendingCommands.emplace_back(command);
        break;
    }
    case ControllerState::Calculating:
    {
        if(CommandType::Stop == command.commandType)
        {
            m_engineHandler.sendStringToEngine(command.commandString);
            changeState(ControllerState::Idle);
        }
        else
        {
            m_pendingCommands.emplace_back(command);
        }
        break;
    }
    case ControllerState::Idle:
    {
        if(CommandType::Go == command.commandType)
        {
            clearCalculationDetails();
            changeState(ControllerState::Calculating);
        }
        m_engineHandler.sendStringToEngine(command.commandString);
        break;
    }
    }
}

void ChessEngineControllerWithUci::processAStringFromEngine(
        string const& stringFromEngine)
{
    if(m_waitingForReadyOkay)
    {
        processInWaitingForReadyOkay(stringFromEngine);
    }
    else
    {
        switch(m_state)
        {
        case ControllerState::WaitingForUciOkay:
        {
            processInWaitingForUciOkay(stringFromEngine);
            break;
        }
        case ControllerState::Calculating:
        {
            processInCalculating(stringFromEngine);
            break;
        }
        default:
        {
            // idle and and other states are ignored
            break;
        }
        }
    }
}

void ChessEngineControllerWithUci::processInWaitingForReadyOkay(
        string const& stringFromEngine)
{
    string stringToProcess(getStringWithoutStartingAndTrailingWhiteSpace(stringFromEngine));
    if("readyok" == stringToProcess)
    {
        m_waitingForReadyOkay = false;
    }
}

void ChessEngineControllerWithUci::processInWaitingForUciOkay(
        string const& stringFromEngine)
{
    string stringToProcess(getStringWithoutStartingAndTrailingWhiteSpace(stringFromEngine));
    if("uciok" == stringToProcess)
    {
        proceedToIdleStateAndProcessPendingCommands();
    }
}

void ChessEngineControllerWithUci::processInCalculating(
        string const& stringFromEngine)
{
    retrieveCalculationDetailsOnStringFromEngine(m_currentCalculationDetails, stringFromEngine);

    if(!m_currentCalculationDetails.bestMove.empty())
    {
        proceedToIdleStateAndProcessPendingCommands();
    }

    if(m_additionalStepsInCalculationMonitoring)
    {
        m_additionalStepsInCalculationMonitoring.value()(m_currentCalculationDetails);
    }
}

string ChessEngineControllerWithUci::constructUciOptionCommand(
        string const& name,
        string const& value)
{
    return "setoption name " + name + " value " + value;
}

string getEnumString(
        ChessEngineControllerWithUci::ControllerState const state)
{
    switch(state)
    {
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(ChessEngineControllerWithUci::ControllerState::Initializing, "Initializing,")
    ALBA_MACROS_CASE_ENUM_SHORT_STRING(ChessEngineControllerWithUci::ControllerState::WaitingForUciOkay, "WaitingForUciOkay")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(ChessEngineControllerWithUci::ControllerState::Idle, "Idle")
            ALBA_MACROS_CASE_ENUM_SHORT_STRING(ChessEngineControllerWithUci::ControllerState::Calculating, "Calculating")
            default:
        return "default";
    }
}

ostream & operator<<(
        ostream & out,
        ChessEngineControllerWithUci::ControllerState const state)
{
    out << getEnumString(state);
    return out;
}

}

}
