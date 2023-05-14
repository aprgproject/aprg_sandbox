#pragma once

#include <ChessPeek/BoardWithContext.hpp>
#include <ChessPeek/Book.hpp>
#include <ChessPeek/CalculationDetails.hpp>
#include <ChessPeek/HumanScoreGenerator.hpp>
#include <Common/User/DisplayTable.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {
class ResultPrinter {
public:
    enum class MoveType { BookMove, CalculatedMove };

    struct NextMove {
        Move move;
        std::string moveString;
        int engineScore;
        int mateValue;
        uint32_t humanScore;
    };
    using NextMoves = std::vector<NextMove>;

    struct MovesSequence {
        int engineScore;
        int mateValue;
        std::vector<Move> halfMoves;
    };

    struct BookMove {
        Move move;
        std::string nameOfLineInBook;
        int winningPercentageInBook;
    };
    using BookMoves = std::vector<BookMove>;

    ResultPrinter() = delete;
    ResultPrinter(CalculationDetails const& calculationDetails, BoardWithContext const& engineBoard, Book const& book);

    void print();

private:
    void initialize();
    void saveBestAndWorstScores();

    BookMoves getNextMovesFromBook() const;
    void includeBookMoves(BookMoves& bookMoves) const;
    BookMove createBookMove(
        Move const& move, Book::LineDetail const& lineDetail, Book::MoveDetail const& bookMoveDetail) const;
    std::string getNameOfBookMove(Move const& move, Book::LineDetail const& lineDetail) const;
    NextMoves getNextMovesFromCalculation() const;
    void includeNextMovesFromCalculation(NextMoves& nextMoves) const;
    void sortForMoreHumanMoves(NextMoves& nextMoves) const;
    void removeTooManyPawnMoves(NextMoves& nextMoves) const;
    NextMove createNextMove(Move const& move, Variation const& variation, HumanScoreGenerator const& scorer) const;
    MovesSequence getMovesSequenceFromNextMove(NextMove const& nextMove) const;
    MovesSequence getMovesSequenceFromBestLine() const;
    void includeMovesSequenceFromVariation(MovesSequence& result, Variation const& variation) const;

    void printCalculationDetails(NextMoves const& nextMoves, MovesSequence const& movesSequence) const;
    void printMovesGrids(
        BookMoves const& bookMoves, MovesSequence const& mostHumanMoveLine, NextMoves const& calculatedMoves,
        MovesSequence const& bestMoveLine) const;

    template <typename GenericMoves>
    void printARowOfNextMoves(GenericMoves const& genericMoves, unsigned int const startIndex) const;
    template <typename GenericMoves>
    void setNextMovesOnGrid(
        DisplayTable& grid, GenericMoves const& genericMoves, unsigned int const startIndex,
        unsigned int const rowSize) const;
    template <typename GenericMoves>
    void printNextMovesHeader(GenericMoves const& genericMoves, unsigned int const startIndex) const;

    void printARowOfMovesSequence(MovesSequence const& movesSequence) const;
    void setMovesSequenceOnGrid(
        DisplayTable& grid, MovesSequence const& movesSequence, unsigned int const rowSize) const;
    void printMovesSequenceHeader(MovesSequence const& movesSequence) const;
    void printHorizontalBorderLine() const;
    void setSeparatorsOnGrid(DisplayTable& grid, unsigned int const xOffset) const;
    void setBoardOnGrid(DisplayTable& grid, Board const& board, unsigned int const xOffset) const;
    void setMoveOnGrid(
        DisplayTable& grid, Board const& board, Move const& move, unsigned int const xOffset,
        unsigned int const moveNumber, std::optional<char> const& firstChar) const;

    std::string getDisplayableString(NextMove const& nextMove, int const desiredLength) const;
    std::string getDisplayableString(BookMove const& bookMove, int const desiredLength) const;
    std::string getMovesSequenceFirstMoveHeader(int const score, int const mate) const;
    std::string getCellForDisplay(
        Piece const& piece, unsigned int const moveNumber, std::optional<char> const& firstChar) const;
    std::optional<char> getFirstCharOfCell(bool const isCertainPreMove, bool isPossiblePreMove) const;
    unsigned int getNumberOfColumnsOfGrid(unsigned int const numberOfBoards) const;

    CalculationDetails const& m_calculationDetails;
    BoardWithContext const& m_engineBoardWithContext;
    Book const& m_book;
    int m_bestScore;
    int m_worstScore;
};

}  // namespace ChessPeek

}  // namespace chess
}  // namespace alba
