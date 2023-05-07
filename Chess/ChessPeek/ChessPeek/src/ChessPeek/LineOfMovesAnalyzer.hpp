#pragma once

#include <ChessUtilities/Board/Board.hpp>

namespace alba {

namespace chess {

class LineOfMovesAnalyzer {
public:
    struct AnalyzerData {
        Move previousMove;
        Piece previousPiece;
        Move savedMove;
        Piece savedPiece;
        bool previouslyHadOnlyOnePossibleMoveToThisDestination;
    };

    LineOfMovesAnalyzer(Board const& board);

    void checkMove(Move const& halfMove);
    void commitMove();

    bool canPreMove() const;
    Piece getSavedPiece() const;
    Board const& getCurrentBoard() const;

private:
    bool canPreMoveBecauseOnlyOnePossibleMoveBeforeCapture() const;
    bool previousAndCurrentMoveHasSameDestination() const;
    Board m_board;
    AnalyzerData m_analyzerData;
};

}  // namespace chess

}  // namespace alba
