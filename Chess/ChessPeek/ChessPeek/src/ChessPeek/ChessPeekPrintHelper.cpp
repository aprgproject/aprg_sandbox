#include "ChessPeekPrintHelper.hpp"

#include <ChessPeek/LineOfMovesAnalyzer.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <iostream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_TEXT = 10U;
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_TABLE = 5U;
constexpr unsigned int NEXT_OFFSET_OF_DISPLAY_TABLE = 9U;
constexpr char SEPARATOR[] = "     ";
}  // namespace

namespace alba {

namespace chess {

ChessPeekPrintHelper::ChessPeekPrintHelper(
    PieceColor const& playerColor, ChessPeekCalculationDetails const& calculationDetails, Board const& board)
    : m_playerColor(playerColor), m_calculationDetails(calculationDetails), m_chessBoard(board) {}

void ChessPeekPrintHelper::print() {
    MoveAndScorePairs moveAndScorePairs(getCurrentMoveAndScorePairs());
    Moves futureHalfMoves(getFutureHalfMoves());
    printCalculationDetails(moveAndScorePairs, futureHalfMoves);
    printMoveTables(moveAndScorePairs, futureHalfMoves);
    cout << "\n\n";
    cout.flush();
}

void ChessPeekPrintHelper::printCalculationDetails(
    MoveAndScorePairs const& moveAndScorePairs, Moves const& futureHalfMoves) const {
    cout << "Player: " << m_playerColor << ", Depth: " << m_calculationDetails.depthInPlies
         << ", Mate score: " << m_calculationDetails.mateScore << "\n";
    cout << "Searching moves: ";
    for (MoveAndScorePair const& moveAndScorePair : moveAndScorePairs) {
        cout << m_chessBoard.getReadableStringForMove(moveAndScorePair.first) << " ["
             << static_cast<double>(moveAndScorePair.second) / 100 << "], ";
    }
    cout << "\n";

    Board updatedBoard(m_chessBoard);
    cout << "PV of best line: ";
    for (Move const& futureHalfMove : futureHalfMoves) {
        Piece piece = updatedBoard.getPieceAt(futureHalfMove.first);
        cout << updatedBoard.getReadableStringForMove(futureHalfMove);
        if (!piece.isEmpty()) {
            cout << " [by " << piece.getColor() << "]";
        }
        cout << ", ";
        updatedBoard.move(futureHalfMove);
    }
    cout << "\n";
    if (!m_calculationDetails.bestMove.empty()) {
        cout << "Best move: "
             << m_chessBoard.getReadableStringForMove(
                    m_chessBoard.getMoveFromTwoLetterNumberNotation(m_calculationDetails.bestMove))
             << "\n";
    }
    cout << "\n";
}

void ChessPeekPrintHelper::printMoveTables(
    MoveAndScorePairs const& moveAndScorePairs, Moves const& futureHalfMoves) const {
    if (!moveAndScorePairs.empty()) {
        putCurrentMoves(moveAndScorePairs);
    }
    if (!futureHalfMoves.empty()) {
        printFutureHalfMoves(futureHalfMoves);
    }
}

void ChessPeekPrintHelper::putCurrentMoves(MoveAndScorePairs const& moveAndScorePairs) const {
    printHorizontalBorderLine();
    printScoresHeader(moveAndScorePairs, 0);
    putCurrentMovesTable(moveAndScorePairs, 0);
    printScoresHeader(moveAndScorePairs, 5);
    putCurrentMovesTable(moveAndScorePairs, 5);
}

void ChessPeekPrintHelper::putCurrentMovesTable(
    MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const {
    constexpr unsigned int numberOfBoardDisplayRows = 8U;
    if (startIndex < moveAndScorePairs.size()) {
        unsigned int numberOfMovesToDisplay =
            min(MAX_NUMBER_OF_MOVES_IN_TABLE, static_cast<unsigned int>(moveAndScorePairs.size() - startIndex));
        unsigned int numberOfBoardDisplayColumns = getNumberOfColumnsOfBoardDisplayTable(numberOfMovesToDisplay);
        DisplayTable boardsDisplayTable(numberOfBoardDisplayColumns, numberOfBoardDisplayRows);
        boardsDisplayTable.setVerticalBorder("|");
        putSeparatorsOnDisplayTable(boardsDisplayTable, NEXT_OFFSET_OF_DISPLAY_TABLE);
        for (unsigned int xOffset = 0; xOffset < numberOfBoardDisplayColumns; xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE) {
            putChessBoardOnDisplayTable(boardsDisplayTable, m_chessBoard, xOffset);
        }
        putCurrentMovesOnDisplayTable(boardsDisplayTable, moveAndScorePairs, startIndex, numberOfMovesToDisplay);
        cout << boardsDisplayTable;
        printHorizontalBorderLine();
    }
}

void ChessPeekPrintHelper::putCurrentMovesOnDisplayTable(
    DisplayTable& boardsDisplayTable, MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex,
    unsigned int const numberOfMovesToDisplay) const {
    unsigned int xOffset = 0U;
    for (unsigned int moveIndex = 0; moveIndex < numberOfMovesToDisplay; moveIndex++) {
        Move const& currentMove(moveAndScorePairs.at(startIndex + moveIndex).first);
        putMoveOnChessBoardCellsInDisplayTable(boardsDisplayTable, m_chessBoard, currentMove, xOffset, 1U, false);
        xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE;
    }
}

void ChessPeekPrintHelper::printFutureHalfMoves(Moves const& futureHalfMoves) const {
    printScoreAndMoveNumbersHeader();
    printHorizontalBorderLine();
    printFutureHalfMovesTable(futureHalfMoves);
    printHorizontalBorderLine();
}

void ChessPeekPrintHelper::printFutureHalfMovesTable(Moves const& futureHalfMoves) const {
    constexpr unsigned int numberOfRows = 8U;
    unsigned int numberOfMovesToDisplay =
        min(MAX_NUMBER_OF_MOVES_IN_TABLE, static_cast<unsigned int>((futureHalfMoves.size() + 1U) / 2U));
    unsigned int numberOfColumns = getNumberOfColumnsOfBoardDisplayTable(numberOfMovesToDisplay);

    DisplayTable boardsDisplayTable(numberOfColumns, numberOfRows);
    boardsDisplayTable.setVerticalBorder("|");
    putSeparatorsOnDisplayTable(boardsDisplayTable, NEXT_OFFSET_OF_DISPLAY_TABLE);
    putFutureHalfMovesAndBoardsOnDisplayTable(boardsDisplayTable, futureHalfMoves, numberOfMovesToDisplay);
    cout << boardsDisplayTable;
}

void ChessPeekPrintHelper::putFutureHalfMovesAndBoardsOnDisplayTable(
    DisplayTable& boardsDisplayTable, Moves const& futureHalfMoves, unsigned int const numberOfMovesToDisplay) const {
    LineOfMovesAnalyzer analyzer(m_chessBoard);
    unsigned int movesDisplayed = 0U;
    unsigned int xOffset = 0U;

    for (Move const& futureHalfMove : futureHalfMoves) {
        analyzer.checkMove(futureHalfMove);
        if (analyzer.getSavedPiece().getColor() == m_playerColor) {
            bool canPreMove = analyzer.canPreMove();

            putChessBoardOnDisplayTable(boardsDisplayTable, analyzer.getCurrentBoard(), xOffset);
            putMoveOnChessBoardCellsInDisplayTable(
                boardsDisplayTable, analyzer.getCurrentBoard(), futureHalfMove, xOffset, movesDisplayed + 1,
                canPreMove);

            xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE;
            movesDisplayed++;
            if (movesDisplayed >= numberOfMovesToDisplay) {
                break;
            }
        }
        analyzer.commitMove();
    }
}

void ChessPeekPrintHelper::printScoresHeader(
    MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const {
    if (startIndex < moveAndScorePairs.size()) {
        unsigned int numberOfMovesToDisplay =
            min(MAX_NUMBER_OF_MOVES_IN_TABLE, static_cast<unsigned int>(moveAndScorePairs.size() - startIndex));
        bool isFirst = true;
        for (unsigned int moveIndex = 0; moveIndex < numberOfMovesToDisplay; moveIndex++) {
            if (isFirst) {
                isFirst = false;
            } else {
                cout << SEPARATOR;
            }
            cout << "|           ";
            cout << setfill(' ') << setw(9)
                 << static_cast<double>(moveAndScorePairs.at(startIndex + moveIndex).second) / 100;
            cout << "           |";
        }
        cout << "\n";
        printHorizontalBorderLine();
    }
}

void ChessPeekPrintHelper::printScoreAndMoveNumbersHeader() const {
    cout << "|   ";
    cout << setfill(' ') << setw(9) << static_cast<double>(m_calculationDetails.scoreInPvLine) / 100;
    cout << " -> 1st move       |     |           2nd move            |     |           3rd move            |     |   "
            "        4th move            |     |           5th move            |\n";
}

void ChessPeekPrintHelper::printHorizontalBorderLine() const {
    cout << "----------------------------------------------------------------------------------------------------------"
            "-------------------------------------------------------------------------------\n";
}

void ChessPeekPrintHelper::putSeparatorsOnDisplayTable(
    DisplayTable& boardsDisplayTable, unsigned int const offset) const {
    unsigned int const numberOfColumns = boardsDisplayTable.getTotalColumns(),
                       numberOfRows = boardsDisplayTable.getTotalRows();
    for (unsigned int j = 0; j < numberOfRows; j++) {
        for (unsigned int separatorIndex = offset - 1; separatorIndex < numberOfColumns; separatorIndex += offset) {
            boardsDisplayTable.getCellReferenceAt(separatorIndex, j).setText(SEPARATOR);
        }
    }
}

void ChessPeekPrintHelper::putChessBoardOnDisplayTable(
    DisplayTable& boardsDisplayTable, Board const& chessBoard, unsigned int const xOffset) const {
    constexpr CoordinateDataType chessBoardDimension = 8U;
    for (CoordinateDataType y = 0; y < chessBoardDimension; y++) {
        for (CoordinateDataType x = 0; x < chessBoardDimension; x++) {
            Piece piece(chessBoard.getPieceAt(Coordinate(x, y)));
            boardsDisplayTable.getCellReferenceAt(x + xOffset, y)
                .setText(getChessBoardCellForDisplay(piece, 0U, false));
        }
    }
}

void ChessPeekPrintHelper::putMoveOnChessBoardCellsInDisplayTable(
    DisplayTable& boardsDisplayTable, Board const& chessBoard, Move const& move, unsigned int const xOffset,
    unsigned int const moveNumberToDisplay, bool canPreMove) const {
    Piece piece(chessBoard.getPieceAt(move.first));
    boardsDisplayTable.getCellReferenceAt(move.first.getX() + xOffset, move.first.getY())
        .setText(getChessBoardCellForDisplay(piece, moveNumberToDisplay, canPreMove));
    boardsDisplayTable.getCellReferenceAt(move.second.getX() + xOffset, move.second.getY())
        .setText(getChessBoardCellForDisplay(piece, moveNumberToDisplay + 1, canPreMove));
}

string ChessPeekPrintHelper::getChessBoardCellForDisplay(
    Piece const& piece, unsigned int const moveNumber, bool const canPreMove) const {
    string result(3, ' ');
    if (moveNumber != 0) {
        char moveNumberCharacter = '0' + static_cast<char>(moveNumber);
        if (canPreMove) {
            result[0] = '*';
        } else {
            result[0] = moveNumberCharacter;
        }
        result[2] = moveNumberCharacter;
    }
    result[1] = piece.getCharacter();
    return result;
}

MoveAndScorePairs ChessPeekPrintHelper::getCurrentMoveAndScorePairs() const {
    MoveAndScorePairs result;
    for (StringAndIntPair const& searchingMoveAndScorePair : m_calculationDetails.searchingMoveAndScorePairs) {
        Move move(m_chessBoard.getMoveFromTwoLetterNumberNotation(searchingMoveAndScorePair.first));
        if (isValidMove(move)) {
            result.emplace_back(move, searchingMoveAndScorePair.second);
        }
        if (result.size() >= MAX_NUMBER_OF_MOVES_IN_TEXT) {
            break;
        }
    }
    return result;
}

Moves ChessPeekPrintHelper::getFutureHalfMoves() const {
    Moves result;
    strings const& pvHalfMovesStrings(m_calculationDetails.pvHalfMovesInMonitoredLine);
    Board updatedBoard(m_chessBoard);
    bool isFirst = true;
    PieceColor previousColor{};
    for (string const& pvHalfMoveString : pvHalfMovesStrings) {
        Move move(updatedBoard.getMoveFromTwoLetterNumberNotation(pvHalfMoveString));
        if (isValidMove(move)) {
            Piece piece = updatedBoard.getPieceAt(move.first);
            if (piece.isEmpty()) {
                break;  // piece needs to be valid
            } else {
                if (!isFirst && previousColor == piece.getColor()) {
                    break;  // colors needs to be alternating
                }
                previousColor = piece.getColor();
            }
            result.emplace_back(move);
            updatedBoard.move(move);
            if (isFirst == true) {
                isFirst = false;
            }
        } else {
            break;  // retain only line with valid moves
        }
        if (result.size() >= MAX_NUMBER_OF_MOVES_IN_TEXT) {
            break;
        }
    }
    return result;
}

unsigned int ChessPeekPrintHelper::getNumberOfColumnsOfScoreDisplayTable(unsigned int const numberOfChessBoards) const {
    return numberOfChessBoards == 0 ? 0U : numberOfChessBoards * 2 - 1;
}

unsigned int ChessPeekPrintHelper::getNumberOfColumnsOfBoardDisplayTable(unsigned int const numberOfChessBoards) const {
    return numberOfChessBoards == 0 ? 0U : numberOfChessBoards * 8U + numberOfChessBoards - 1;
}

}  // namespace chess

}  // namespace alba
