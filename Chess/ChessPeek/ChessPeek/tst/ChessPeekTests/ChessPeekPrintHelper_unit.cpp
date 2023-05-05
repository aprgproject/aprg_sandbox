#include <ChessPeek/ChessPeekPrintHelper.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

namespace chess {

TEST(ChessPeekPrintHelperTest, PrintWorks) {
    PieceColor playerColor = PieceColor::White;
    ChessPeekCalculationDetails calculationDetails{};
    Board board(Board::Orientation::BlackUpWhiteDown);
    calculationDetails.depthInPlies = 21;
    calculationDetails.searchingMoveAndScorePairs = {{"d2d4", 39}, {"e2e4", 44}, {"c2c4", 39}, {"g2g3", 35},
                                                     {"g1f3", 35}, {"e2e3", 21}, {"c2c3", 8},  {"b1c3", 3},
                                                     {"b2b3", 2},  {"a2a3", 0}};
    calculationDetails.pvMovesInBestLine = {"d2d4", "g8f6", "c2c4", "g7g6", "g1f3", "f8g7", "b1c3", "d7d5",
                                            "c4d5", "f6d5", "e2e4", "d5c3", "b2c3", "c7c5", "c1e3", "d8a5",
                                            "e3d2", "e8g8", "f1e2", "c8g4", "e1g1", "f8d8", "d1c2", "g4f3"};
    ChessPeekPrintHelper printHelper(playerColor, calculationDetails, board);

    printHelper.print();
}

}  // namespace chess

}  // namespace alba
