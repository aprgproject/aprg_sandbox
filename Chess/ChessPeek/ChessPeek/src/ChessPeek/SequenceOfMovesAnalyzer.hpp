#pragma once

#include <ChessUtilities/Board/Board.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class SequenceOfMovesAnalyzer {
public:
    struct AnalyzerData {
        Board savedBoard;
        Move savedMove;
        Board previousBoard;
        Move previousMove;
    };

    SequenceOfMovesAnalyzer(Board const& board);

    void checkMove(Move const& halfMove);
    void commitMove();

    bool canPreMove() const;
    Piece getPieceFromMove() const;
    Board const& getCurrentBoard() const;

private:
    bool canPreMoveBecauseOfRecapture() const;
    bool didPreviousMoveHadOnlyOneWayToCapture() const;
    bool isARecapture() const;
    AnalyzerData m_data;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
