#pragma once

#include <ChessPeek/BoardWithContext.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class SequenceOfMovesAnalyzer {
public:
    enum class State { NoMove, AnalyzingMove, Moved };

    struct StepDetails {
        BoardWithContext boardWithContext;
        Move move;
    };

    SequenceOfMovesAnalyzer(BoardWithContext const& boardWithContext);

    void analyzeMove(Move const& halfMove);
    void commitMove();

    bool canPreMove() const;
    State getState() const;
    Board const& getCurrentBoard() const;
    PieceColor getCurrentMoveColor() const;

private:
    bool isPreviousColorOpposite() const;
    bool canPreMoveBecauseOfRecapture() const;
    bool canPreMoveBecauseOfCheck() const;
    bool didPreviousMoveHadOnlyOneWayToCapture() const;
    bool isARecapture() const;
    State m_state;
    StepDetails m_current;
    StepDetails m_previous;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
