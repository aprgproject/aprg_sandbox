#include <ChessPeek/Book.hpp>
#include <ChessPeek/DatabaseDefinitions.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/StreamOperators.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(DatabaseForBooksTest, DISABLED_SavingChessDotComDatabaseWorks) {
    constexpr int MIN_NUMBER_OF_GAMES = 0;  // put a restriction if the database gets too large
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
        transformReplaceStringIfFound(nameOfLine, "é", "e");  // for Reti
        int numberOfNextMoves = convertStringToNumber<int>(
            getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NumberOfNextMoves: [", "]"));

        Board board(BoardOrientation::BlackUpWhiteDown);
        PieceColor playerColor(PieceColor::White);
        for (string const& initialMoveString : initialMoveStrings) {
            board.move(board.getMoveUsingAlgebraicNotation(initialMoveString, playerColor));
            playerColor = getOppositeColor(playerColor);
        }

        int totalNumberOfGames{};
        Book::LineDetail lineDetail{nameOfLine, playerColor, {}, {}};
        for (int i = 0; i < numberOfNextMoves; i++) {
            string nextMove =
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NextMove: [", "]");
            int numberOfGames = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "NumberOfGames: [", "]"));
            int whiteWinPercentage = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "WhiteWinPercentage: [", "]"));
            fileReader.skipLine();  // DrawPercentage;
            int blackWinPercentage = convertStringToNumber<int>(
                getStringInBetweenTwoStrings(fileReader.getLineAndIgnoreWhiteSpaces(), "BlackWinPercentage: [", "]"));
            int winPercentageForColor = (PieceColor::White == playerColor)   ? whiteWinPercentage
                                        : (PieceColor::Black == playerColor) ? blackWinPercentage
                                                                             : 0;
            Book::MoveDetail moveDetail{nextMove, winPercentageForColor};
            if (nextMove.empty()) {
                cout << "The numberOfNextMoves is in correct on site details. Please check." << endl;
                cout << "line: " << line << endl;
                cout << "nameOfLine: " << nameOfLine << endl;
                cout << "numberOfNextMoves: " << numberOfNextMoves << endl;
            }
            lineDetail.nextMoves.emplace_back(moveDetail);
            totalNumberOfGames += numberOfGames;
        }
        lineDetail.totalNumberOfGames = totalNumberOfGames;
        if (!nameOfLine.empty() && numberOfNextMoves != 0 && totalNumberOfGames > MIN_NUMBER_OF_GAMES) {
            book.addLine(board, lineDetail);
        }
    }

    // NOTE: Adjust MIN_NUMBER_OF_GAMES to keep the book size (under 10000 maybe?)
    // Also, the LoadingDatabaseWorks tests below needs to be under 100 ms.
    ASSERT_EQ(5066U, book.getSize());  // update this before writing to database
    book.saveDatabaseTo(chessDotComBookDatabase.getFullPath());
}

TEST(DatabaseForBooksTest, LoadingDatabaseWorksWithStartingPosition) {
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    book.loadDatabaseFrom(chessDotComBookDatabase.getFullPath());

    auto resultWithBUWD(book.getLine(boardWithBUWD));
    auto resultWithWUBD(book.getLine(boardWithWUBD));

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("Starting Position", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::White, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("Starting Position", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::White, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithWUBD.nextMoves.size());
}

TEST(DatabaseForBooksTest, LoadingDatabaseWorksWithE4) {
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("e4", PieceColor::White));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("e4", PieceColor::White));
    book.loadDatabaseFrom(chessDotComBookDatabase.getFullPath());
    AlbaLocalTimer timer;

    timer.resetTimer();
    auto resultWithBUWD(book.getLine(boardWithBUWD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    timer.resetTimer();
    auto resultWithWUBD(book.getLine(boardWithWUBD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("King's Pawn Opening", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("King's Pawn Opening", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithWUBD.nextMoves.size());
}

TEST(DatabaseForBooksTest, LoadingDatabaseWorksWithD4) {
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("d4", PieceColor::White));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("d4", PieceColor::White));
    book.loadDatabaseFrom(chessDotComBookDatabase.getFullPath());
    AlbaLocalTimer timer;

    timer.resetTimer();
    auto resultWithBUWD(book.getLine(boardWithBUWD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    timer.resetTimer();
    auto resultWithWUBD(book.getLine(boardWithWUBD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("Queen's Pawn Opening", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("Queen's Pawn Opening", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithWUBD.nextMoves.size());
}

TEST(DatabaseForBooksTest, LoadingDatabaseWorksWithC4) {
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("c4", PieceColor::White));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("c4", PieceColor::White));
    book.loadDatabaseFrom(chessDotComBookDatabase.getFullPath());
    AlbaLocalTimer timer;

    timer.resetTimer();
    auto resultWithBUWD(book.getLine(boardWithBUWD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    timer.resetTimer();
    auto resultWithWUBD(book.getLine(boardWithWUBD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("English Opening", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("English Opening", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::Black, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(20U, lineDetailsWithWUBD.nextMoves.size());
}

TEST(DatabaseForBooksTest, LoadingDatabaseWorksWithSicilianDefense) {
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    Board boardWithBUWD(BoardOrientation::BlackUpWhiteDown);
    Board boardWithWUBD(BoardOrientation::WhiteUpBlackDown);
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("e4", PieceColor::White));
    boardWithBUWD.move(boardWithBUWD.getMoveUsingAlgebraicNotation("c5", PieceColor::Black));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("e4", PieceColor::White));
    boardWithWUBD.move(boardWithWUBD.getMoveUsingAlgebraicNotation("c5", PieceColor::Black));
    book.loadDatabaseFrom(chessDotComBookDatabase.getFullPath());
    AlbaLocalTimer timer;

    timer.resetTimer();
    auto resultWithBUWD(book.getLine(boardWithBUWD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    timer.resetTimer();
    auto resultWithWUBD(book.getLine(boardWithWUBD));
    timer.stopTimer();
    cout << "Elapsed time for getLine: [" << timer.getElapsedTimeInMicroseconds() << " us]" << endl;

    ASSERT_TRUE(resultWithBUWD);
    auto lineDetailsWithBUWD(resultWithBUWD.value());
    EXPECT_EQ("Sicilian Defense", lineDetailsWithBUWD.nameOfLine);
    EXPECT_EQ(PieceColor::White, lineDetailsWithBUWD.colorToMove);
    EXPECT_EQ(27U, lineDetailsWithBUWD.nextMoves.size());

    ASSERT_TRUE(resultWithWUBD);
    auto lineDetailsWithWUBD(resultWithWUBD.value());
    EXPECT_EQ("Sicilian Defense", lineDetailsWithWUBD.nameOfLine);
    EXPECT_EQ(PieceColor::White, lineDetailsWithWUBD.colorToMove);
    EXPECT_EQ(27U, lineDetailsWithWUBD.nextMoves.size());
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
