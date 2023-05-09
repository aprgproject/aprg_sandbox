#pragma once

#include <ChessPeek/BoardWithContext.hpp>
#include <ChessPeek/CalculationDetails.hpp>

#include <optional>

namespace alba {

namespace chess {

namespace ChessPeek {

class ResultPrinter {
public:
    struct CurrentMoveDetail {
        Move move;
        int score;
    };

    struct FutureMoveDetail {
        Move halfMove;
        int commonalityCount;
    };

    using CurrentMoveDetails = std::vector<CurrentMoveDetail>;
    using FutureMoveDetails = std::vector<FutureMoveDetail>;

    ResultPrinter() = delete;
    ResultPrinter(BoardWithContext const& engineBoard, CalculationDetails const& calculationDetails);

    void print();

private:
    void printCalculationDetails(
        CurrentMoveDetails const& currentMoveDetails, FutureMoveDetails const& futureMoveDetails) const;
    void printMovesGrid(CurrentMoveDetails const& currentMoveDetails, FutureMoveDetails const& futureMoveDetails) const;

    void printCurrentMovesGrid(CurrentMoveDetails const& currentMoveDetails) const;
    void printARowOfCurrentMoves(CurrentMoveDetails const& currentMoveDetails, unsigned int const startIndex) const;
    void setCurrentMovesOnGrid(
        DisplayTable& grid, CurrentMoveDetails const& currentMoveDetails, unsigned int const startIndex,
        unsigned int const rowSize) const;

    void printFutureMovesGrid(FutureMoveDetails const& futureMoveDetails) const;
    void printARowOfFutureMoves(FutureMoveDetails const& futureMoveDetails) const;
    void setFutureMovesOnGrid(
        DisplayTable& grid, FutureMoveDetails const& futureMoveDetails, unsigned int const rowSize) const;

    void printScoresHeader(CurrentMoveDetails const& currentMoveDetails, unsigned int const startIndex) const;
    void printScoreAndMoveNumbersHeader() const;
    void printHorizontalBorderLine() const;

    void setSeparatorsOnGrid(DisplayTable& grid, unsigned int const xOffset) const;
    void setBoardOnGrid(DisplayTable& grid, Board const& board, unsigned int const xOffset) const;
    void setMoveOnGrid(
        DisplayTable& grid, Board const& board, Move const& move, unsigned int const xOffset,
        unsigned int const moveNumber, std::optional<char> const& firstChar) const;

    CurrentMoveDetails getCurrentMoveDetails() const;
    FutureMoveDetails getFutureMoveDetails() const;
    void sortForMoreHumanMoves(CurrentMoveDetails& currentMoveDetails) const;
    void removeTooManyPawnMoves(CurrentMoveDetails& currentMoveDetails) const;

    bool isAMoreHumanMove(CurrentMoveDetail const& detail1, CurrentMoveDetail const& detail2) const;
    int getScoreLevel(int const scoreInCentipawns) const;
    int getDistanceToOpponentsKing(Move const& move) const;
    int getForwardCount(Move const& move) const;
    int getPieceValueOfMove(Move const& move) const;
    int getCommonalityCount(Move const& move, Board const& engineBoard, int const index) const;
    std::string getCellForDisplay(
        Piece const& piece, unsigned int const moveNumber, std::optional<char> const& firstChar) const;
    std::optional<char> getFirstCharOfCell(bool const isCertainPreMove, bool isPossiblePreMove) const;    unsigned int getNumberOfColumnsOfGrid(unsigned int const numberOfBoards) const;

    BoardWithContext const& m_engineBoardWithContext;
    CalculationDetails const& m_calculationDetails;};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
