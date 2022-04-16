#include "ChessEngineControllerWithUci.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

ChessEngineControllerWithUci::ChessEngineControllerWithUci(
        ChessEngineHandler & engineHandler)
    : m_engineHandler(engineHandler)
    , m_state(ControllerState::Initializing)
{
    initialize();
}

void ChessEngineControllerWithUci::setupStartPosition()
{
    sendStopIfCalculating();
    send("position startpos");
}

void ChessEngineControllerWithUci::setupMoves(string const& moves)
{
    sendStopIfCalculating();
    string command("position startpos moves ");
    command+=moves;
    send(command);
}

void ChessEngineControllerWithUci::setupFenString(string const& fenString)
{
    sendStopIfCalculating();
    string command("position fen ");
    command+=fenString;
    send(command);
}

void ChessEngineControllerWithUci::go()
{
    sendStopIfCalculating();
    send("go");
}

void ChessEngineControllerWithUci::goWithPonder()
{
    sendStopIfCalculating();
    send("go ponder");
}

void ChessEngineControllerWithUci::goWithDepth(unsigned int const depth)
{
    sendStopIfCalculating();
    stringstream ss;
    ss << "go depth " << depth;
    send(ss.str());
}

void ChessEngineControllerWithUci::goInfinite()
{
    sendStopIfCalculating();
    send("go infinite");
}

void ChessEngineControllerWithUci::initialize()
{
    m_engineHandler.setAdditionalStepsInProcessingAStringFromEngine([&](string const& stringFromEngine)
    {
        processAStringFromEngine(stringFromEngine);
    });
    sendUci();
    m_state = ControllerState::WaitingForUciOkay;
}

void ChessEngineControllerWithUci::proceedToIdleAndProcessPendingCommands()
{
    m_state = ControllerState::Idle;
    bool hasGoCommand(false);
    while(!m_pendingCommands.empty() && !hasGoCommand)
    {
        string const& pendingCommand(m_pendingCommands.back());
        if(isStringFoundInsideTheOtherStringNotCaseSensitive(pendingCommand, "go"))
        {
            hasGoCommand=true;
        }
        send(pendingCommand);
        m_pendingCommands.pop_back();
    }
    if(hasGoCommand)
    {
        m_state = ControllerState::Calculating;
    }
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
    send("uci");
}

void ChessEngineControllerWithUci::sendStop()
{
    send("stop");
}

void ChessEngineControllerWithUci::send(string const& command)
{
    if(ControllerState::Idle == m_state || "stop" == command)
    {
        m_engineHandler.sendStringToEngine(command);
    }
    else
    {
        m_pendingCommands.emplace_back(command);
    }
}

void ChessEngineControllerWithUci::processAStringFromEngine(
        string const& stringFromEngine)
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
    string bestLine;
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
                m_currentCalculationDetails.bestMove = convertStringToNumber<unsigned int>(token);
                hasBestMove = true;
            }
            else if("ponder" == headerToken)
            {
                m_currentCalculationDetails.ponderMove = convertStringToNumber<unsigned int>(token);
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
            if(!bestLine.empty())
            {
                bestLine += " ";
            }
            bestLine += token;
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
    if(!bestLine.empty())
    {
        m_currentCalculationDetails.bestLinePv = bestLine;
    }
    if(hasBestMove)
    {
        proceedToIdleAndProcessPendingCommands();
    }
}

}
