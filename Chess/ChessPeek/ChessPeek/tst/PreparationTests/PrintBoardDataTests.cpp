#include <ChessPeek/DetailsFromTheScreen.hpp>
#include <ChessUtilities/Board/StreamOperators.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(PrintBoardDataTest, PrintBoardData) {
    Configuration configuration(Configuration::Type::ChessDotComVersus);
    DetailsFromTheScreen detailsFromScreen(configuration);
    detailsFromScreen.saveDetailsFromTheScreen();

    Board const& board(detailsFromScreen.getBoardWithContext().getBoard());
    cout << "\n" << board << "\n";
    printHexValuesInBoard(cout, board);
    cout << "\n";
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
