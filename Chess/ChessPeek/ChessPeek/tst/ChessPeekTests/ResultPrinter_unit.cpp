#include <ChessPeek/ResultPrinter.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(ResultPrinterTest, PrintWorks) {
    BoardWithContext boardWithContext(PieceColor::White, Board(Board::Orientation::BlackUpWhiteDown));
    CalculationDetails calculationDetails{};
    Variation variation1{14, 0, {"f6e4", "b1d2", "d8f6"}};
    Variation variation2{98, 0, {"g1e2", "c7c5", "d2e4"}};
    Variations variations{variation1, variation2};
    calculationDetails.depthInPlies = 21;
    calculationDetails.variations = variations;
    calculationDetails.bestMove = "d2d4";
    ResultPrinter printHelper(boardWithContext, calculationDetails);
    printHelper.print();
}
}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
