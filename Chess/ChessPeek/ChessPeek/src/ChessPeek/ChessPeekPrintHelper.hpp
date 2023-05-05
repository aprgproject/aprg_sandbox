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
    void printCalculationDetails(MoveAndScorePairs const& moveAndScorePairs, Moves const& futureMoves) const;
    void printMoveTables(MoveAndScorePairs const& moveAndScorePairs, Moves const& futureMoves) const;
    void putCurrentMoves(MoveAndScorePairs const& moveAndScorePairs) const;
    void printScores(MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const;
    void putCurrentMovesTable(MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const;
    void printFutureMoves(Moves const& futureMoves) const;
    void printFutureMovesTable(Moves const& futureMoves) const;
    void putCurrentMovesOnDisplayTable(
        DisplayTable& displayTable, MoveAndScorePairs const& moveAndScorePairs, unsigned int const start,
        unsigned int const end) const;
    void putFutureMovesAndBoardsOnDisplayTable(
        DisplayTable& displayTable, Moves const& futureMoves, unsigned int const numberOfMoves) const;
    void putSeparatorsOnDisplayTable(DisplayTable& displayTable, unsigned int const offset) const;
    void putChessBoardOnDisplayTable(
        DisplayTable& displayTable, Board const& temporaryBoard, unsigned int const xOffset) const;
    void printPvMoveNumbers() const;
    void printHorizontalBorderLine() const;
    std::string getChessBoardCellForDisplay(
        Piece const& piece, unsigned int const moveNumberStart, bool const canPreMove) const;

    MoveAndScorePairs getCurrentMoveAndScorePairs() const;
    Moves getFutureMoves() const;
    unsigned int getNumberOfColumnsOfScoreDisplayTable(unsigned int const numberOfChessBoards) const;
    unsigned int getNumberOfColumnsOfBoardDisplayTable(unsigned int const numberOfChessBoards) const;

    PieceColor const& m_playerColor;
    ChessPeekCalculationDetails const& m_calculationDetails;
    Board const& m_chessBoard;
};

}  // namespace chess

}  // namespace alba
