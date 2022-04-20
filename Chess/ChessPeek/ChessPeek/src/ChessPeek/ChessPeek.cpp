#include "ChessPeek.hpp"

#define SCREEN_SHOT_PATH APRG_DIR R"(\Chess\ChessPeek\Files\ScreenShot.bmp)"

namespace alba
{

namespace chess
{

ChessPeek::ChessPeek()
    : m_chessEngineHandler(APRG_DIR R"(\Chess\ChessPeek\Files\stockfish13.exe)")
    , m_chessEngineController(m_chessEngineHandler)
{}

void ChessPeek::initialize()
{
    m_chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\Engine.log)");
}

void ChessPeek::checkScreenForBestMove()
{
    m_userAutomation.saveBitmapOnScreen(SCREEN_SHOT_PATH);

}

}

}