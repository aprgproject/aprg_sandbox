#include "ChessEngineControllerWithUci.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace chess
{

ChessEngineControllerWithUci::ChessEngineControllerWithUci(
        ChessEngineHandler & engineHandler)
    : m_engineHandler(engineHandler)
    , m_state(ControllerState::Initializing)
    , m_waitingForReadyOkay(false)
{
    initialize();
}

void ChessEngineControllerWithUci::resetToNewGame()
{
    sendStopIfCalculating();
    send(CommandType::Position, "ucinewgame");
}

void ChessEngineControllerWithUci::setupStartPosition()
{
    sendStopIfCalculating();
    send(CommandType::Position, "position startpos");
}

void ChessEngineControllerWithUci::setupMoves(string const& moves)
{
    sendStopIfCalculating();
    string command("position startpos moves ");
    command+=moves;
    send(CommandType::Position, command);
}

void ChessEngineControllerWithUci::setupFenString(string const& fenString)
{
    sendStopIfCalculating();
    string command("position fen ");
    command+=fenString;
    send(CommandType::Position, command);
}

void ChessEngineControllerWithUci::go()
{
    sendStopIfCalculating();
    send(CommandType::Go, "go");
}

void ChessEngineControllerWithUci::goWithPonder()
{
    sendStopIfCalculating();
    send(CommandType::Go, "go ponder");
}

void ChessEngineControllerWithUci::goWithDepth(unsigned int const depth)
{
    sendStopIfCalculating();
    stringstream ss;
    ss << "go depth " << depth;
    send(CommandType::Go, ss.str());
}

void ChessEngineControllerWithUci::goInfinite()
{
    sendStopIfCalculating();
    send(CommandType::Go, "go infinite");
}

void ChessEngineControllerWithUci::sendIsReadyAndWaitOrResetIfNeeded()
{
    forceSend("isready");
    m_waitingForReadyOkay = true;

    bool shouldReset(false);
    AlbaLocalTimer timer;
    unsigned int count(0U);
    while(m_waitingForReadyOkay)
    {
        if(count > 10) // 1 second elapsed so engine is stuck, lets reset
        {
            shouldReset = true;
            break;
        }
        count++;
        timer.sleep(100);
    }

    if(shouldReset)
    {
        resetEngine();
    }
}

void ChessEngineControllerWithUci::stop()
{
    sendStop();
}

void ChessEngineControllerWithUci::setAdditionalStepsInCalculationMonitoring(
        StepsInCalculationMonitoring const& additionalSteps)
{
    m_additionalStepsInCalculationMonitoring.setConstReference(additionalSteps);
}

void ChessEngineControllerWithUci::initialize()
{
    m_engineHandler.setAdditionalStepsInProcessingAStringFromEngine([&](string const& stringFromEngine)
    {
        processAStringFromEngine(stringFromEngine);
    });
    sendUci();
}

void ChessEngineControllerWithUci::resetEngine()
{
    m_engineHandler.reset();
    m_waitingForReadyOkay = false;
    m_state = ControllerState::Initializing;
    sendUci();
}

void ChessEngineControllerWithUci::proceedToIdleAndProcessPendingCommands()
{
    m_state = ControllerState::Idle;
    bool hasGoOnPendingCommand(false);
    while(!m_pendingCommands.empty() && !hasGoOnPendingCommand)
    {
        Command pendingCommand(m_pendingCommands.front());
        m_pendingCommands.pop_front();
        hasGoOnPendingCommand = CommandType::Go == pendingCommand.commandType;
        send(pendingCommand);
    }
}

void ChessEngineControllerWithUci::clearCalculationDetails()
{
    m_currentCalculationDetails = CalculationDetails{};
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

void ChessEngineControllerWithUci::sendUci()
{
    send(CommandType::Uci, "uci");
}

void ChessEngineControllerWithUci::sendStop()
{
    send(CommandType::Stop, "stop");
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
    // all the logic are here lol
    switch(m_state)
    {
    case ControllerState::Initializing:
    {
        if(CommandType::Uci == command.commandType)
        {
            m_engineHandler.sendStringToEngine(command.commandString);
            m_state = ControllerState::WaitingForUciOkay;
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
            m_state = ControllerState::Idle;
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
            m_state = ControllerState::Calculating;
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
            // started and idle are ignored
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
        proceedToIdleAndProcessPendingCommands();
    }
}

void ChessEngineControllerWithUci::processInCalculating(
        string const& stringFromEngine)
{
    strings tokens;
    splitToStrings<SplitStringType::WithoutDelimeters>(tokens, getStringWithoutStartingAndTrailingWhiteSpace(stringFromEngine), " ");

    enum class TokenState
    {
        OneValueHeaderFound,
        Idle,
        PvLineFound,
    };

    bool hasBestMove(false);
    TokenState state;
    string headerToken;
    strings movesInBestLine;
    string currentMove;
    string currentMoveNumber;
    for(string const& token : tokens)
    {
        if(TokenState::OneValueHeaderFound == state)
        {
            if("depth" == headerToken)
            {
                m_currentCalculationDetails.depth = convertStringToNumber<unsigned int>(token);
            }
            else if("selectiveDepth" == headerToken)
            {
                m_currentCalculationDetails.selectiveDepth = convertStringToNumber<unsigned int>(token);
            }
            else if("time" == headerToken)
            {
                m_currentCalculationDetails.time = convertStringToNumber<unsigned int>(token);
            }
            else if("nodes" == headerToken)
            {
                m_currentCalculationDetails.nodes = convertStringToNumber<unsigned int>(token);
            }
            else if("nps" == headerToken)
            {
                m_currentCalculationDetails.nodesPerSecond = convertStringToNumber<unsigned int>(token);
            }
            else if("cp" == headerToken)
            {
                m_currentCalculationDetails.scoreInCentipawns = convertStringToNumber<unsigned int>(token);
            }
            else if("mate" == headerToken)
            {
                m_currentCalculationDetails.mateInNumberOfMoves = convertStringToNumber<unsigned int>(token);
            }
            else if("currmove" == headerToken)
            {
                currentMove = token;
            }
            else if("currmovenumber" == headerToken)
            {
                currentMoveNumber = token;
            }
            else if("bestmove" == headerToken)
            {
                m_currentCalculationDetails.bestMove = token;
                hasBestMove = true;
            }
            else if("ponder" == headerToken)
            {
                m_currentCalculationDetails.ponderMove = token;
            }
            if(!currentMove.empty() && !currentMoveNumber.empty())
            {
                unsigned int index = convertStringToNumber<unsigned int>(currentMoveNumber) - 1;
                if(index < 100)
                {
                    if(index >= m_currentCalculationDetails.currentlySearchingMoves.size())
                    {
                        m_currentCalculationDetails.currentlySearchingMoves.resize(index+1);
                    }
                    m_currentCalculationDetails.currentlySearchingMoves[index] = currentMove;
                }
                currentMove.clear();
                currentMoveNumber.clear();
            }

            state = TokenState::Idle;
        }
        else if(TokenState::PvLineFound == state)
        {
            if(!token.empty())
            {
                movesInBestLine.emplace_back(token);
            }
        }
        else if("depth" == token || "selectiveDepth" == token || "time" == token || "nodes" == token
                || "nps" == token || "cp" == token || "mate" == token || "currmove" == token || "currmovenumber" == token
                || "bestmove" == token || "ponder" == token)
        {
            state = TokenState::OneValueHeaderFound;
            headerToken = token;
        }
        else if("pv" == token)
        {
            state = TokenState::PvLineFound;
        }
    }
    if(!movesInBestLine.empty())
    {
        m_currentCalculationDetails.pvMovesInBestLine = movesInBestLine;
    }
    if(hasBestMove)
    {
        proceedToIdleAndProcessPendingCommands();
    }

    if(m_additionalStepsInCalculationMonitoring)
    {
        m_additionalStepsInCalculationMonitoring.getConstReference()(m_currentCalculationDetails);
    }
}

}

}
