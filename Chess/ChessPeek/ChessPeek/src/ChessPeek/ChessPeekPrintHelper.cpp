#include "ChessPeekPrintHelper.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <iostream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr unsigned int MAX_NUMBER_OF_MOVES = 5U;
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
    Moves futureMoves(getFutureMoves());
    printCalculationDetails(moveAndScorePairs, futureMoves);
    printMoveTables(moveAndScorePairs, futureMoves);
    cout << "\n\n";
    cout.flush();
}

void ChessPeekPrintHelper::printCalculationDetails(
    MoveAndScorePairs const& moveAndScorePairs, Moves const& futureMoves) const {
    constexpr unsigned int movesToDisplay = 10;
    cout << "Player: " << m_playerColor << ", Depth: " << m_calculationDetails.depthInPlies
         << ", Mate: " << m_calculationDetails.numberOfMovesTillMate << "\n";
    cout << "Best move: [" << m_calculationDetails.bestMove << "]\n";

    unsigned int moveCount = 1;
    cout << "Searching moves: ";
    for (MoveAndScorePair const& moveAndScorePair : moveAndScorePairs) {
        cout << m_chessBoard.getReadableStringForMove(moveAndScorePair.first) << " ["
             << static_cast<double>(moveAndScorePair.second) / 100 << "], ";
        if (moveCount++ >= movesToDisplay) {
            break;
        }
    }
    cout << "\n";

    Board temporaryBoard(m_chessBoard);
    moveCount = 1;
    cout << "PV of best line: ";
    for (Move const& futureMove : futureMoves) {
        cout << temporaryBoard.getReadableStringForMove(futureMove) << ", ";
        temporaryBoard.move(futureMove);
        if (moveCount++ >= movesToDisplay) {
            break;
        }
    }
    cout << "\n\n";
}

void ChessPeekPrintHelper::printMoveTables(MoveAndScorePairs const& moveAndScorePairs, Moves const& futureMoves) const {
    if (!moveAndScorePairs.empty()) {
        putCurrentMoves(moveAndScorePairs);
    }
    if (!futureMoves.empty()) {
        printFutureMoves(futureMoves);
    }
}

void ChessPeekPrintHelper::putCurrentMoves(MoveAndScorePairs const& moveAndScorePairs) const {
    printHorizontalBorderLine();
    printScores(moveAndScorePairs, 0);
    putCurrentMovesTable(moveAndScorePairs, 0);
    printScores(moveAndScorePairs, 5);
    putCurrentMovesTable(moveAndScorePairs, 5);
}

void ChessPeekPrintHelper::printScores(
    MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const {
    if (startIndex < moveAndScorePairs.size()) {
        unsigned int numberOfMoves =
            min(MAX_NUMBER_OF_MOVES, static_cast<unsigned int>(moveAndScorePairs.size() - startIndex));
        bool isFirst = true;
        for (unsigned int moveIndex = 0; moveIndex < numberOfMoves; moveIndex++) {
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

void ChessPeekPrintHelper::putCurrentMovesTable(
    MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const {
    constexpr unsigned int numberOfBoardDisplayRows = 8U;
    if (startIndex < moveAndScorePairs.size()) {
        unsigned int numberOfMoves =
            min(MAX_NUMBER_OF_MOVES, static_cast<unsigned int>(moveAndScorePairs.size() - startIndex));
        unsigned int numberOfBoardDisplayColumns = getNumberOfColumnsOfBoardDisplayTable(numberOfMoves);
        DisplayTable boardDisplayTable(numberOfBoardDisplayColumns, numberOfBoardDisplayRows);
        boardDisplayTable.setVerticalBorder("|");
        putSeparatorsOnDisplayTable(boardDisplayTable, NEXT_OFFSET_OF_DISPLAY_TABLE);
        for (unsigned int xOffset = 0; xOffset < numberOfBoardDisplayColumns; xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE) {
            putChessBoardOnDisplayTable(boardDisplayTable, m_chessBoard, xOffset);
        }
        putCurrentMovesOnDisplayTable(boardDisplayTable, moveAndScorePairs, startIndex, numberOfMoves);
        cout << boardDisplayTable;
        printHorizontalBorderLine();
    }
}

void ChessPeekPrintHelper::printFutureMoves(Moves const& futureMoves) const {
    printPvMoveNumbers();
    printHorizontalBorderLine();
    printFutureMovesTable(futureMoves);
    printHorizontalBorderLine();
}

void ChessPeekPrintHelper::printFutureMovesTable(Moves const& futureMoves) const {
    constexpr unsigned int numberOfRows = 8U;
    unsigned int numberOfMoves = min(MAX_NUMBER_OF_MOVES, static_cast<unsigned int>((futureMoves.size() + 1U) / 2U));
    unsigned int numberOfColumns = getNumberOfColumnsOfBoardDisplayTable(numberOfMoves);

    DisplayTable boardDisplayTable(numberOfColumns, numberOfRows);
    boardDisplayTable.setVerticalBorder("|");
    putSeparatorsOnDisplayTable(boardDisplayTable, NEXT_OFFSET_OF_DISPLAY_TABLE);
    putFutureMovesAndBoardsOnDisplayTable(boardDisplayTable, futureMoves, numberOfMoves);
    cout << boardDisplayTable;
}

void ChessPeekPrintHelper::putCurrentMovesOnDisplayTable(
    DisplayTable& boardDisplayTable, MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex,
    unsigned int const numberOfMoves) const {
    unsigned int xOffset = 0U;
    for (unsigned int moveIndex = 0; moveIndex < numberOfMoves; moveIndex++) {
        Move const& currentMove(moveAndScorePairs.at(startIndex + moveIndex).first);
        Piece piece(m_chessBoard.getPieceAt(currentMove.first));
        boardDisplayTable.getCellReferenceAt(currentMove.first.getX() + xOffset, currentMove.first.getY())
            .setText(getChessBoardCellForDisplay(piece, 1U, false));
        boardDisplayTable.getCellReferenceAt(currentMove.second.getX() + xOffset, currentMove.second.getY())
            .setText(getChessBoardCellForDisplay(piece, 2U, false));
        xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE;
    }
}

void ChessPeekPrintHelper::putFutureMovesAndBoardsOnDisplayTable(
    DisplayTable& boardDisplayTable, Moves const& futureMoves, unsigned int const numberOfMoves) const {
    unsigned int moveNumberToDisplay = 1U;
    unsigned int xOffset = 0U;
    unsigned int moveIndex = 0U;

    Board temporaryBoard(m_chessBoard);
    PieceColor opponentColor(getOppositeColor(m_playerColor));
    Coordinate previousDestination{};
    bool hasPreviouslyOneWayOfCapture(false);
    for (Move const& futureMove : futureMoves) {
        if (isEven(moveIndex)) {
            putChessBoardOnDisplayTable(boardDisplayTable, temporaryBoard, xOffset);
            bool canPreMove = hasPreviouslyOneWayOfCapture && previousDestination == futureMove.second;

            Piece piece(temporaryBoard.getPieceAt(futureMove.first));
            boardDisplayTable.getCellReferenceAt(futureMove.first.getX() + xOffset, futureMove.first.getY())
                .setText(getChessBoardCellForDisplay(piece, moveNumberToDisplay, canPreMove));
            boardDisplayTable.getCellReferenceAt(futureMove.second.getX() + xOffset, futureMove.second.getY())
                .setText(getChessBoardCellForDisplay(piece, moveNumberToDisplay + 1, canPreMove));

            xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE;
            hasPreviouslyOneWayOfCapture = false;
            moveNumberToDisplay++;
            if (moveNumberToDisplay > numberOfMoves) {
                break;
            }
        } else {
            previousDestination = futureMove.second;
            hasPreviouslyOneWayOfCapture =
                !temporaryBoard.isEmptyAt(futureMove.second) &&
                temporaryBoard.hasOnlyOneMovePossibleToThisDestination(futureMove.second, opponentColor);
        }
        temporaryBoard.move(futureMove);
        moveIndex++;
    }
}

void ChessPeekPrintHelper::putSeparatorsOnDisplayTable(
    DisplayTable& boardDisplayTable, unsigned int const offset) const {
    unsigned int const numberOfColumns = boardDisplayTable.getTotalColumns(),
                       numberOfRows = boardDisplayTable.getTotalRows();
    for (unsigned int j = 0; j < numberOfRows; j++) {
        for (unsigned int separatorIndex = offset - 1; separatorIndex < numberOfColumns; separatorIndex += offset) {
            boardDisplayTable.getCellReferenceAt(separatorIndex, j).setText(SEPARATOR);
        }
    }
}

void ChessPeekPrintHelper::putChessBoardOnDisplayTable(
    DisplayTable& boardDisplayTable, Board const& board, unsigned int const xOffset) const {
    constexpr CoordinateDataType chessBoardDimension = 8U;
    for (CoordinateDataType y = 0; y < chessBoardDimension; y++) {
        for (CoordinateDataType x = 0; x < chessBoardDimension; x++) {
            Piece piece(board.getPieceAt(Coordinate(x, y)));
            boardDisplayTable.getCellReferenceAt(x + xOffset, y).setText(getChessBoardCellForDisplay(piece, 0U, false));
        }
    }
}

void ChessPeekPrintHelper::printPvMoveNumbers() const {
    cout << "|           1st move            |     |           2nd move            |     |           3rd move          "
            "  |     |           4th move            |     |           5th move            |\n";
}

void ChessPeekPrintHelper::printHorizontalBorderLine() const {
    cout << "----------------------------------------------------------------------------------------------------------"
            "-------------------------------------------------------------------------------\n";
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
    }
    return result;
}

Moves ChessPeekPrintHelper::getFutureMoves() const {
    Moves result;
    strings const& pvMovesStrings(m_calculationDetails.pvMovesInBestLine);
    for (string const& pvMoveString : pvMovesStrings) {
        Move move(m_chessBoard.getMoveFromTwoLetterNumberNotation(pvMoveString));
        if (isValidMove(move)) {
            result.emplace_back(move);
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
