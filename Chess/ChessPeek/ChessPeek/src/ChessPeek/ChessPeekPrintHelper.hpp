#pragma once

#include <ChessPeek/ChessPeekCalculationDetails.hpp>
#include <ChessUtilities/Board/Board.hpp>

namespace alba {

namespace chess {

class ChessPeekPrintHelper {
public:
    using BoardAndMovePair = std::pair<Board, Move>;
    using BoardAndMovePairs = std::vector<BoardAndMovePair>;

    ChessPeekPrintHelper() = delete;
    ChessPeekPrintHelper(
        PieceColor const& playerColor, ChessPeekCalculationDetails const& calculationDetails, Board const& board);

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

    PieceColor const& m_playerColor;    ChessPeekCalculationDetails const& m_calculationDetails;
    Board const& m_chessBoard;
};
}  // namespace chess

}  // namespace alba
