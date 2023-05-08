#include "LineOfMovesAnalyzer.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba {

namespace chess {

LineOfMovesAnalyzer::LineOfMovesAnalyzer(Board const& board) : m_board(board), m_analyzerData{} {}

void LineOfMovesAnalyzer::checkMove(Move const& halfMove) {
    if (isMoveWithinTheBoard(halfMove)) {
        m_analyzerData.previousMove = m_analyzerData.savedMove;
        m_analyzerData.previousPiece = m_analyzerData.savedPiece;
        m_analyzerData.savedMove = halfMove;        m_analyzerData.savedPiece = m_board.getPieceAt(halfMove.first);
    }
}
void LineOfMovesAnalyzer::commitMove() {
    m_analyzerData.previouslyHadOnlyOnePossibleMoveToThisDestination = m_board.hasOnlyOneMovePossibleToThisDestination(
        m_analyzerData.savedMove.second, m_analyzerData.savedPiece.getColor());
    m_board.move(m_analyzerData.savedMove);
}

bool LineOfMovesAnalyzer::canPreMove() const { return canPreMoveBecauseOnlyOnePossibleMoveBeforeCapture(); }

Piece LineOfMovesAnalyzer::getSavedPiece() const { return m_analyzerData.savedPiece; }

Board const& LineOfMovesAnalyzer::getCurrentBoard() const { return m_board; }

bool LineOfMovesAnalyzer::canPreMoveBecauseOnlyOnePossibleMoveBeforeCapture() const {
    return m_analyzerData.previouslyHadOnlyOnePossibleMoveToThisDestination &&
           previousAndCurrentMoveHasSameDestination();
}

bool LineOfMovesAnalyzer::previousAndCurrentMoveHasSameDestination() const {
    // its a ongoing capture
    return m_analyzerData.savedMove.second == m_analyzerData.previousMove.second;
}

}  // namespace chess

}  // namespace alba
