#pragma once

#include <ChessUtilities/ChessEngineControllerWithUci.hpp>
#include <ChessUtilities/ChessEngineHandler.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

namespace alba
{

namespace chess
{

class ChessPeek
{
public:
    ChessPeek();

private:
    void initialize();
    void checkScreenForBestMove();
    ChessEngineHandler m_chessEngineHandler;
    ChessEngineControllerWithUci m_chessEngineController;
    AlbaLocalUserAutomation m_userAutomation;
};

}

}