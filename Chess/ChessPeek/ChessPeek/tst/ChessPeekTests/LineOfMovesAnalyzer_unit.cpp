#include <ChessPeek/LineOfMovesAnalyzer.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

namespace chess {

TEST(LineOfMovesAnalyzerTest, CheckMoveAndCommitMoveWorks) {
    Board board(Board::Orientation::BlackUpWhiteDown);
    LineOfMovesAnalyzer analyzer(board);

    analyzer.checkMove({{3, 6}, {3, 4}});
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), analyzer.getSavedPiece());

    Board::PieceMatrix expectedMatrix(8U, 8U, {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0,  0,  0,  0,  1,  1,  1,  0,  1, 1, 1, 1, 4, 2, 3, 5, 6, 3, 2, 4});
    analyzer.commitMove();
    EXPECT_EQ(expectedMatrix, analyzer.getCurrentBoard().getPieceMatrix());
}

TEST(LineOfMovesAnalyzerTest, CanPreMoveWorksOnCapture) {
    Board board(Board::Orientation::BlackUpWhiteDown);
    LineOfMovesAnalyzer analyzer(board);
    analyzer.checkMove({{3, 6}, {3, 4}});
    analyzer.commitMove();
    analyzer.checkMove({{4, 1}, {4, 3}});
    analyzer.commitMove();

    analyzer.checkMove({{3, 4}, {4, 3}});
    EXPECT_TRUE(analyzer.canPreMove());
}

}  // namespace chess

}  // namespace alba
