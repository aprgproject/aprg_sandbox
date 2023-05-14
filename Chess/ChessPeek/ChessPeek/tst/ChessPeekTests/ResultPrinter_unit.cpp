#include <ChessPeek/ResultPrinter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(ResultPrinterTest, PrintWorks) {
    CalculationDetails calculationDetails{};
    BoardWithContext boardWithContext(PieceColor::White, Board(BoardOrientation::BlackUpWhiteDown));
    Book book;
    Variation variation1{14, 0, {"f6e4", "b1d2", "d8f6"}};
    Variation variation2{98, 0, {"g1e2", "c7c5", "d2e4"}};
    Variations variations{variation1, variation2};
    calculationDetails.depthInPlies = 21;
    calculationDetails.variations = variations;
    calculationDetails.bestMove = "d2d4";
    ResultPrinter printHelper(calculationDetails, boardWithContext, book);

    printHelper.print();
}

}  // namespace ChessPeek

}  // namespace chess
}  // namespace alba
