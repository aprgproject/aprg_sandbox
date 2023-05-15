#include <ChessPeek/DatabaseDefinitions.hpp>
#include <ChessPeek/ResultPrinter.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace chess {

namespace ChessPeek {

TEST(ResultPrinterTest, PrintWorks) {
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    // book.loadDatabaseFrom(chessDotComBookDatabase.getFullPath());  // comment out if needed
    CalculationDetails calculationDetails{};
    BoardWithContext boardWithContext(PieceColor::White, Board(BoardOrientation::BlackUpWhiteDown));
    Variation variation1{200, 0, {"e2e4", "c7c5", "g1f3"}};
    Variation variation2{100, 0, {"d2d4", "g8f6", "c2c4"}};
    Variation variation3{0, 0, {"g1f3", "g8f6", "d2d4"}};
    Variation variation4{-100, 0, {"c2c4", "g8f6", "d2d4"}};
    Variation variation5{-200, 0, {"g2g3", "d7d5", "g1f3"}};
    Variations variations{variation1, variation2, variation3, variation4, variation5};
    calculationDetails.depthInPlies = 21;
    calculationDetails.variations = variations;
    calculationDetails.bestMove = "e2e4";
    ResultPrinter printHelper(calculationDetails, boardWithContext, book);

    printHelper.print();}

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba
