#include "SequenceOfMovesAnalyzer.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

SequenceOfMovesAnalyzer::SequenceOfMovesAnalyzer(Board const& board) : m_data{} { m_data.savedBoard = board; }

void SequenceOfMovesAnalyzer::checkMove(Move const& halfMove) {
    if (isMoveWithinTheBoard(halfMove)) {
        m_data.previousMove = m_data.savedMove;
        m_data.savedMove = halfMove;
    }
}

void SequenceOfMovesAnalyzer::commitMove() {
    m_data.previousBoard = m_data.savedBoard;
    m_data.savedBoard.move(m_data.savedMove);
}

bool SequenceOfMovesAnalyzer::canPreMove() const { return canPreMoveBecauseOfRecapture(); }

Piece SequenceOfMovesAnalyzer::getPieceFromMove() const { return m_data.savedBoard.getPieceAt(m_data.savedMove.first); }

Board const& SequenceOfMovesAnalyzer::getCurrentBoard() const { return m_data.savedBoard; }

bool SequenceOfMovesAnalyzer::canPreMoveBecauseOfRecapture() const {
    return isARecapture() && didPreviousMoveHadOnlyOneWayToCapture();
}

bool SequenceOfMovesAnalyzer::didPreviousMoveHadOnlyOneWayToCapture() const {
    Piece previousPiece = m_data.previousBoard.getPieceAt(m_data.previousMove.first);
    return m_data.previousBoard.hasOnlyOneMovePossibleToThisDestination(
        m_data.previousMove.second, previousPiece.getColor());
}

bool SequenceOfMovesAnalyzer::isARecapture() const {
    return m_data.previousMove.second == m_data.savedMove.second &&
           m_data.previousBoard.isACaptureMove(m_data.previousMove) &&
           m_data.savedBoard.isACaptureMove(m_data.savedMove);
}

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba