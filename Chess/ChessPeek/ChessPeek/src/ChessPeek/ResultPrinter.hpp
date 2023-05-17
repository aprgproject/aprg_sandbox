#pragma once

#include <ChessPeek/BoardWithContext.hpp>
#include <ChessPeek/Book.hpp>
#include <ChessPeek/CalculationDetails.hpp>
#include <ChessPeek/HumanScoreGenerator.hpp>
#include <Common/String/AlbaStringHelper.hpp>
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
        int mateValue;
        int engineScore;
        HumanScoreGenerator::Score humanScore;
    };
    using NextMoves = std::vector<NextMove>;

    struct MovesSequence {
        int mateValue;
        int engineScore;
        HumanScoreGenerator::Score humanScore;
        std::vector<Move> halfMoves;
    };
    struct BookMove {
        Move move;
        std::string nameOfLineInBook;
        int winningPercentageInBook;
    };
    using BookMoves = std::vector<BookMove>;

    struct MovesToPrint {
        BookMoves bookMoves;
        NextMoves calculatedMoves;
        NextMoves mostHumanMoves;
        MovesSequence bestLine;
        MovesSequence mostHumanLine;
    };
    using ScorePair = std::pair<int, int>;

    ResultPrinter() = delete;
    ResultPrinter(CalculationDetails const& calculationDetails, BoardWithContext const& engineBoard, Book const& book);

    void print();

private:
    void printCalculationDetails(MovesToPrint const& movesToPrint) const;
    void printMovesGrids(MovesToPrint const& movesToPrint) const;
    template <typename GenericMoves>
    void printARowOfNextMoves(GenericMoves const& genericMoves, int const startIndex) const;
    template <typename GenericMoves>
    void setNextMovesOnGrid(
        DisplayTable& grid, GenericMoves const& genericMoves, int const startIndex, int const rowSize) const;
    void printARowOfMovesSequence(MovesSequence const& movesSequence) const;
    void setMovesSequenceOnGrid(DisplayTable& grid, MovesSequence const& movesSequence, int const rowSize) const;

    void printHeadersFor2ndTo6thMostHumanMoves(NextMoves const& nextMoves) const;
    void printHeadersFor4thTo8thBestMoves(NextMoves const& nextMoves, int const startIndex) const;
    void printHeadersForBookMoves(BookMoves const& bookMoves) const;
    void printHeadersForBestLine(MovesSequence const& movesSequence) const;
    void printHeadersForMostHumanLine(MovesSequence const& movesSequence) const;
    void printHeaders(stringHelper::strings const& prefixes, stringHelper::strings const& suffixes) const;
    void printHorizontalBorder() const;
    void setSeparatorsOnGrid(DisplayTable& grid, int const xOffset) const;
    void setBoardOnGrid(DisplayTable& grid, Board const& board, int const xOffset) const;
    void setMoveOnGrid(
        DisplayTable& grid, Board const& board, Move const& move, int const xOffset, int const moveNumber,
        std::optional<char> const& firstChar) const;

    BookMoves getMovesFromBook() const;
    void fillMovesFromBook(BookMoves& bookMoves) const;
    BookMove createBookMove(
        Move const& move, Book::LineDetail const& lineDetail, Book::MoveDetail const& bookMoveDetail) const;
    std::string getNameOfBookMove(Move const& move, Book::LineDetail const& lineDetail) const;
    NextMoves getNextMovesFromCalculation() const;
    void fillNextMovesFromCalculation(NextMoves& nextMoves) const;
    void humanizeMoves(NextMoves& nextMoves) const;
    void sortForMoreHumanMoves(NextMoves& nextMoves) const;
    void removeTooManyPawnMoves(NextMoves& nextMoves) const;
    NextMove createNextMove(Move const& move, Variation const& variation) const;
    MovesSequence getMovesSequenceFromMoveString(std::string const& moveString) const;
    void fillMovesSequenceFromVariation(MovesSequence& result, Variation const& variation) const;

    stringHelper::strings getNextMovesString(NextMoves const& nextMoves, int const startIndex) const;
    stringHelper::strings getBookMovesString(BookMoves const& bookMoves) const;
    std::string getDisplayableString(NextMove const& nextMove) const;
    std::string getDisplayableString(BookMove const& bookMove) const;
    std::string getDisplayableString(MovesSequence const& movesSequence) const;
    std::string getDisplayableString(
        int const mateValue, int const engineScore, HumanScoreGenerator::Score const humanScore) const;
    std::string getDisplayableString(int const mateValue, int const engineScore) const;
    std::string formatToHeaderString(std::string const& content) const;
    std::string getDisplayableStringForABoardCell(        Piece const& piece, int const moveNumber, std::optional<char> const& firstChar) const;
    std::optional<char> getFirstCharOfABoardCell(bool const isCertainPreMove, bool isPossiblePreMove) const;
    ScorePair getBestAndWorstScores(Variations const& variations) const;
    int getNumberOfColumnsOfGrid(int const numberOfBoards) const;
    int getHorizontalBorderSize(int const numberOfBoards) const;
    int getRowSizeForHalfMoves(int const numberOfHalfMoves) const;
    int getRowSizeForFullMoves(int const numberOfFullMoves) const;

    CalculationDetails const& m_calculationDetails;
    BoardWithContext const& m_engineBoardWithContext;
    Book const& m_book;
    ScorePair m_worstAndBestScorePair;
    HumanScoreGenerator m_humanScoreGenerator;
    std::string m_horizontalBorder;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
