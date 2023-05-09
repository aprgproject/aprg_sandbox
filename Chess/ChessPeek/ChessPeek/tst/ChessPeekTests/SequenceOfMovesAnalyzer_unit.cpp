#include <ChessPeek/SequenceOfMovesAnalyzer.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(SequenceOfMovesAnalyzerTest, CheckMoveAndCommitMoveWorks) {
    Board board(Board::Orientation::BlackUpWhiteDown);
    SequenceOfMovesAnalyzer analyzer(board);

    analyzer.checkMove({{3, 6}, {3, 4}});
    EXPECT_EQ(Piece(PieceColorAndType::WhitePawn), analyzer.getPieceFromMove());

    Board::PieceMatrix expectedMatrix(8U, 8U, {12, 10, 11, 13, 14, 11, 10, 12, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0,  0,  0,  0,  1,  1,  1,  0,  1, 1, 1, 1, 4, 2, 3, 5, 6, 3, 2, 4});
    analyzer.commitMove();
    EXPECT_EQ(expectedMatrix, analyzer.getCurrentBoard().getPieceMatrix());
}

TEST(SequenceOfMovesAnalyzerTest, CanPreMoveWorksOnRecapture) {
    Board board(Board::Orientation::BlackUpWhiteDown);
    SequenceOfMovesAnalyzer analyzer(board);
    analyzer.checkMove({{4, 6}, {4, 4}});
    analyzer.commitMove();
    analyzer.checkMove({{3, 1}, {3, 3}});
    analyzer.commitMove();
    analyzer.checkMove({{4, 4}, {3, 3}});
    analyzer.commitMove();

    analyzer.checkMove({{3, 0}, {3, 3}});
    EXPECT_TRUE(analyzer.canPreMove());
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
