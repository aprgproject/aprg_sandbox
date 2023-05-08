#pragma once

#include <ChessPeek/CalculationDetails.hpp>
#include <ChessPeek/DetailsOnTheEngine.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class ResultPrinter {
public:
    using BoardAndMovePair = std::pair<Board, Move>;
    using BoardAndMovePairs = std::vector<BoardAndMovePair>;

    ResultPrinter() = delete;
    ResultPrinter(DetailsOnTheEngine const& detailsOnTheEngine, CalculationDetails const& calculationDetails);

    void print();

private:
    void printCalculationDetails(MoveAndScorePairs const& moveAndScorePairs, Moves const& futureHalfMoves) const;
    void printMoveTables(MoveAndScorePairs const& moveAndScorePairs, Moves const& futureHalfMoves) const;

    void putCurrentMoves(MoveAndScorePairs const& moveAndScorePairs) const;
    void putCurrentMovesTable(MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const;
    void putCurrentMovesOnDisplayTable(
        DisplayTable& boardsDisplayTable, MoveAndScorePairs const& moveAndScorePairs, unsigned int const start,
        unsigned int const numberOfMovesToDisplay) const;

    void printFutureHalfMoves(Moves const& futureHalfMoves) const;
    void printFutureHalfMovesTable(Moves const& futureHalfMoves) const;
    void putFutureHalfMovesAndBoardsOnDisplayTable(
        DisplayTable& boardsDisplayTable, Moves const& futureHalfMoves,
        unsigned int const numberOfMovesToDisplay) const;

    void printScoresHeader(MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const;
    void printScoreAndMoveNumbersHeader() const;
    void printHorizontalBorderLine() const;
    void putSeparatorsOnDisplayTable(DisplayTable& boardsDisplayTable, unsigned int const offset) const;
    void putChessBoardOnDisplayTable(
        DisplayTable& boardsDisplayTable, Board const& chessBoard, unsigned int const xOffset) const;
    void putMoveOnChessBoardCellsInDisplayTable(
        DisplayTable& boardsDisplayTable, Board const& chessBoard, Move const& move, unsigned int const xOffset,
        unsigned int const moveNumberToDisplay, bool canPreMove) const;

    std::string getChessBoardCellForDisplay(
        Piece const& piece, unsigned int const moveNumberStart, bool const canPreMove) const;
    MoveAndScorePairs getCurrentMoveAndScorePairs() const;
    Moves getFutureHalfMoves() const;
    void sortSoThatHumanlyMovesAreAtTheStart(MoveAndScorePairs& moveAndScoreToBeSorted) const;

    unsigned int getNumberOfColumnsOfScoreDisplayTable(unsigned int const numberOfChessBoards) const;
    unsigned int getNumberOfColumnsOfBoardDisplayTable(unsigned int const numberOfChessBoards) const;
    int getAcceptableScore(int const scoreInCentipawns) const;
    int getScoreLevel(int const scoreInCentipawns) const;

    DetailsOnTheEngine const& m_detailsOnTheEngine;
    CalculationDetails const& m_calculationDetails;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
