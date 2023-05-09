#include "SequenceOfMovesAnalyzer.hpp"

#include <ChessPeek/BoardWithContext.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

SequenceOfMovesAnalyzer::SequenceOfMovesAnalyzer(BoardWithContext const& boardWithContext)
    : m_state(State::NoMove), m_current{boardWithContext, {}}, m_previous{} {}

void SequenceOfMovesAnalyzer::analyzeMove(Move const& halfMove) {
    if (areCoordinatesValid(halfMove)) {
        m_previous.move = m_current.move;
        m_current.move = halfMove;
        PieceColor moveColor = m_current.boardWithContext.getBoard().getPieceAt(m_current.move.first).getColor();
        m_current.boardWithContext.setPlayerColor(moveColor);
        m_state = State::AnalyzingMove;
    }
}

void SequenceOfMovesAnalyzer::commitMove() {
    m_previous.boardWithContext = m_current.boardWithContext;
    m_current.boardWithContext.move(m_current.move);
    m_state = State::Moved;
}

bool SequenceOfMovesAnalyzer::canPreMove() const {
    bool result(false);
    if (State::AnalyzingMove == m_state && isPreviousColorOpposite()) {
        result = canPreMoveBecauseOfRecapture() || canPreMoveBecauseOfCheck();
    }
    return result;
}

SequenceOfMovesAnalyzer::State SequenceOfMovesAnalyzer::getState() const { return m_state; }

Board const& SequenceOfMovesAnalyzer::getCurrentBoard() const { return m_current.boardWithContext.getBoard(); }

PieceColor SequenceOfMovesAnalyzer::getCurrentMoveColor() const { return m_current.boardWithContext.getPlayerColor(); }

bool SequenceOfMovesAnalyzer::isPreviousColorOpposite() const {
    return areOpposingColors(m_current.boardWithContext.getPlayerColor(), m_previous.boardWithContext.getPlayerColor());
}

bool SequenceOfMovesAnalyzer::canPreMoveBecauseOfRecapture() const {
    return isARecapture() && didPreviousMoveHadOnlyOneWayToCapture();
}

bool SequenceOfMovesAnalyzer::canPreMoveBecauseOfCheck() const {
    BoardWithContext const& currentContext(m_current.boardWithContext);
    BoardWithContext const& previousContext(m_previous.boardWithContext);

    if (previousContext.isPlayersKingOnCheck()) {
        Coordinate kingCoordinate = previousContext.getPlayerKingCoordinate();
        Board const& analysisBoard(previousContext.getBoard());
        Moves attacksOnKing = analysisBoard.getAttacksToThis(kingCoordinate, currentContext.getPlayerColor());
        auto numberOfKingEscapes = analysisBoard.getMovesFromThis(kingCoordinate, 2).size();
        auto numberOfBlocks = analysisBoard.getNumberOfWaysToBlockAttacks(attacksOnKing, 2);
        auto numberOfLegalMoves = numberOfKingEscapes + numberOfBlocks;
        return numberOfLegalMoves == 1;
    }
    return false;
}

bool SequenceOfMovesAnalyzer::didPreviousMoveHadOnlyOneWayToCapture() const {
    Board const& previousBoard(m_previous.boardWithContext.getBoard());
    return previousBoard.hasOnlyOneMoveToThis(
        m_previous.move.second, previousBoard.getPieceAt(m_previous.move.first).getColor());
}

bool SequenceOfMovesAnalyzer::isARecapture() const {
    Board const& previousBoard(m_previous.boardWithContext.getBoard());
    Board const& currentBoard(m_current.boardWithContext.getBoard());

    return m_previous.move.second == m_current.move.second && previousBoard.isACaptureMove(m_previous.move) &&
           currentBoard.isACaptureMove(m_current.move);
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
