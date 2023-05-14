#include <ChessPeek/Book.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(BookTest, GetSizeWorks) {
    Book book;
    Board board(BoardOrientation::BlackUpWhiteDown);
    Book::LineDetail lineDetail{"LineForTesting", PieceColor::White, {}, {}};

    EXPECT_EQ(0U, book.getSize());
    book.addLine(board, lineDetail);
    EXPECT_EQ(1U, book.getSize());
}

TEST(BookTest, GetLineWorks) {
    Book book;
    Board board(BoardOrientation::BlackUpWhiteDown);
    Book::LineDetail lineDetail{"LineForTesting", PieceColor::White, {}, {}};

    EXPECT_FALSE(book.getLine(board));
    book.addLine(board, lineDetail);

    auto actualLineDetailOptional(book.getLine(board));
    ASSERT_TRUE(actualLineDetailOptional);
    auto const& actualLineDetail(actualLineDetailOptional.value());
    EXPECT_EQ("LineForTesting", actualLineDetail.nameOfLine);
    EXPECT_EQ(PieceColor::White, actualLineDetail.colorToMove);
    EXPECT_EQ(0, actualLineDetail.totalNumberOfGames);
}

TEST(BookTest, ClearWorks) {    Book book;
    Board board(BoardOrientation::BlackUpWhiteDown);
    Book::LineDetail lineDetail{"LineForTesting", PieceColor::White, 100, {}};

    EXPECT_EQ(0U, book.getSize());

    book.addLine(board, lineDetail);
    EXPECT_EQ(1U, book.getSize());

    book.clear();
    EXPECT_EQ(0U, book.getSize());
}

TEST(BookTest, AddLineWorksOnAddingANewLine) {
    Book book;
    Board board(BoardOrientation::BlackUpWhiteDown);
    Book::LineDetail lineDetail{"LineForTesting", PieceColor::White, 100, {}};

    book.addLine(board, lineDetail);

    auto actualLineDetailOptional(book.getLine(board));
    ASSERT_TRUE(actualLineDetailOptional);
    auto const& actualLineDetail(actualLineDetailOptional.value());
    EXPECT_EQ("LineForTesting", actualLineDetail.nameOfLine);
    EXPECT_EQ(PieceColor::White, actualLineDetail.colorToMove);
    EXPECT_EQ(100, actualLineDetail.totalNumberOfGames);
}

TEST(BookTest, AddLineWorksOnNotOverwritingAnExistingLineIfLessThanTotalNumberOfGames) {
    Book book;
    Board board(BoardOrientation::BlackUpWhiteDown);
    Book::LineDetail lineDetail1{"LineForTesting", PieceColor::White, 100, {}};
    Book::LineDetail lineDetail2{"LineIsOverwritten", PieceColor::Black, 50, {}};

    book.addLine(board, lineDetail1);
    book.addLine(board, lineDetail2);

    auto actualLineDetailOptional(book.getLine(board));
    ASSERT_TRUE(actualLineDetailOptional);
    auto const& actualLineDetail(actualLineDetailOptional.value());
    EXPECT_EQ("LineForTesting", actualLineDetail.nameOfLine);
    EXPECT_EQ(PieceColor::White, actualLineDetail.colorToMove);
    EXPECT_EQ(100, actualLineDetail.totalNumberOfGames);
}

TEST(BookTest, AddLineWorksOnOverwritingAnExistingLineIfGreaterThanTotalNumberOfGames) {
    Book book;
    Board board(BoardOrientation::BlackUpWhiteDown);
    Book::LineDetail lineDetail1{"LineForTesting", PieceColor::White, 100, {}};
    Book::LineDetail lineDetail2{"LineIsOverwritten", PieceColor::Black, 200, {}};

    book.addLine(board, lineDetail1);
    book.addLine(board, lineDetail2);

    auto actualLineDetailOptional(book.getLine(board));
    ASSERT_TRUE(actualLineDetailOptional);
    auto const& actualLineDetail(actualLineDetailOptional.value());
    EXPECT_EQ("LineIsOverwritten", actualLineDetail.nameOfLine);
    EXPECT_EQ(PieceColor::Black, actualLineDetail.colorToMove);
    EXPECT_EQ(200, actualLineDetail.totalNumberOfGames);
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
