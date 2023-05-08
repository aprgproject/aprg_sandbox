#include "SequenceOfMovesAnalyzer.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

SequenceOfMovesAnalyzer::SequenceOfMovesAnalyzer(Board const& board) : m_board(board), m_analyzerData{} {}

void SequenceOfMovesAnalyzer::checkMove(Move const& halfMove) {
    if (isMoveWithinTheBoard(halfMove)) {
        m_analyzerData.previousMove = m_analyzerData.savedMove;
        m_analyzerData.previousPiece = m_analyzerData.savedPiece;
        m_analyzerData.savedMove = halfMove;
        m_analyzerData.savedPiece = m_board.getPieceAt(halfMove.first);
    }
}

void SequenceOfMovesAnalyzer::commitMove() {
    m_analyzerData.previouslyHadOnlyOnePossibleMoveToThisDestination = m_board.hasOnlyOneMovePossibleToThisDestination(
        m_analyzerData.savedMove.second, m_analyzerData.savedPiece.getColor());
    m_board.move(m_analyzerData.savedMove);
}

bool SequenceOfMovesAnalyzer::canPreMove() const { return canPreMoveBecauseOnlyOnePossibleMoveBeforeCapture(); }

Piece SequenceOfMovesAnalyzer::getSavedPiece() const { return m_analyzerData.savedPiece; }

Board const& SequenceOfMovesAnalyzer::getCurrentBoard() const { return m_board; }

bool SequenceOfMovesAnalyzer::canPreMoveBecauseOnlyOnePossibleMoveBeforeCapture() const {
    return m_analyzerData.previouslyHadOnlyOnePossibleMoveToThisDestination &&
           previousAndCurrentMoveHasSameDestination();
}

bool SequenceOfMovesAnalyzer::previousAndCurrentMoveHasSameDestination() const {
    // its a ongoing capture
    return m_analyzerData.savedMove.second == m_analyzerData.previousMove.second;
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
