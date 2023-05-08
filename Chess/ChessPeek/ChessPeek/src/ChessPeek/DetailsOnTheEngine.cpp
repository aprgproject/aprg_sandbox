#include "DetailsOnTheEngine.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

DetailsOnTheEngine::DetailsOnTheEngine()
    : m_playerColor(PieceColor::White), m_board(Board::Orientation::BlackUpWhiteDown) {}

DetailsOnTheEngine::DetailsOnTheEngine(PieceColor const& playerColor, Board const& board)
    : m_playerColor(playerColor), m_board(board) {}

PieceColor DetailsOnTheEngine::getPlayerColor() const { return m_playerColor; }

Board const& DetailsOnTheEngine::getBoard() const { return m_board; }

string DetailsOnTheEngine::getFenString() const {
    return constructFenString(m_board, m_playerColor, m_board.getCastlingPartOfFenString(), "-", 0, 1);
}

void DetailsOnTheEngine::save(PieceColor const& playerColor, Board const& board) {    m_playerColor = playerColor;
    m_board = board;
}
}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
