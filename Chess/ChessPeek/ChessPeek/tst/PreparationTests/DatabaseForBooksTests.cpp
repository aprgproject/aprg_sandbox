#include <ChessPeek/Book.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

#define CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE R"(\Chess\ChessPeek\Database\ChessDotComBookDatabase.txt)"
#define CHESS_PEEK_CHESS_DOT_COM_DATA_FROM_SITE R"(\Chess\ChessPeek\Database\ChessDotComDataFromSite.txt)"

TEST(DatabaseForBooksTest, DISABLED_SavingChessDotComDatabaseWorks) {
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    AlbaLocalPathHandler chessDotComDataFromSite(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_DATA_FROM_SITE);
    ifstream inStream(chessDotComDataFromSite.getFullPath());
    AlbaFileReader fileReader(inStream);

    Book book;
    while (fileReader.isNotFinished()) {
        string line = getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "Line: [", "]");
        strings initialMoveStrings;
        splitToStrings<SplitStringType::WithoutDelimeters>(initialMoveStrings, line, ",");
        string nameOfLine =
            getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NameOfLine: [", "]");
        int numberOfNextMoves = convertStringToNumber<int>(
            getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NumberOfNextMoves: [", "]"));

        Board board(BoardOrientation::BlackUpWhiteDown);
        PieceColor playerColor(PieceColor::White);
        for (string const& initialMoveString : initialMoveStrings) {
            board.move(board.getMoveUsingAlgebraicNotation(initialMoveString, playerColor));
            playerColor = getOppositeColor(playerColor);
        }

        Book::LineDetail lineDetail{nameOfLine, {}};
        for (int i = 0; i < numberOfNextMoves; i++) {
            string nextMoveString =
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NextMove: [", "]");
            Move nextMove = board.getMoveUsingAlgebraicNotation(nextMoveString, playerColor);
            int numberOfGames = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NumberOfGames: [", "]"));
            int whiteWinPercentage = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "WhiteWinPercentage: [", "]"));
            int drawPercentage = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "DrawPercentage: [", "]"));
            int blackWinPercentage = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "BlackWinPercentage: [", "]"));
            Book::MoveDetail moveDetail{
                nextMove, numberOfGames, whiteWinPercentage, drawPercentage, blackWinPercentage};
            lineDetail.nextMoves.emplace_back(moveDetail);
        }
        if (!nameOfLine.empty() && numberOfNextMoves != 0) {
            book.addLine(board, lineDetail);
        }
    }

    book.saveDatabaseTo(chessDotComBookDatabase.getFullPath());
}

TEST(DatabaseForBooksTest, DISABLED_LoadingDatabaseWorks) {
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    AlbaLocalPathHandler chessDotComDataFromSite(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_DATA_FROM_SITE);

    Book book;
    book.loadDatabaseFrom(chessDotComBookDatabase.getFullPath());

    EXPECT_TRUE(book.getLine(Board(BoardOrientation::BlackUpWhiteDown)));
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
