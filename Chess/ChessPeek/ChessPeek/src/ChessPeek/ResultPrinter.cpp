#include "ResultPrinter.hpp"

#include <ChessPeek/SequenceOfMovesAnalyzer.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <iostream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr int MINIMUM_ACCEPTABLE_DELTA_SCORE_FROM_BEST_MOVE = 100;
constexpr int MINIMUM_ACCEPTABLE_SCORE = -300;
constexpr unsigned int MIN_NUMBER_OF_MOVES_IN_TEXT = 5U;
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_TEXT = 15U;
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_TABLE = 5U;
constexpr unsigned int NEXT_OFFSET_OF_DISPLAY_TABLE = 9U;
constexpr char SEPARATOR[] = "     ";
}  // namespace

namespace alba {

namespace chess {

namespace ChessPeek {

ResultPrinter::ResultPrinter(DetailsOnTheEngine const& detailsOnTheEngine, CalculationDetails const& calculationDetails)
    : m_detailsOnTheEngine(detailsOnTheEngine), m_calculationDetails(calculationDetails) {}

void ResultPrinter::print() {
    MoveAndScorePairs moveAndScorePairs(getCurrentMoveAndScorePairs());
    Moves futureHalfMoves(getFutureHalfMoves());
    printCalculationDetails(moveAndScorePairs, futureHalfMoves);
    printMoveTables(moveAndScorePairs, futureHalfMoves);
    cout << "\n\n";
    cout.flush();
}

void ResultPrinter::printCalculationDetails(
    MoveAndScorePairs const& moveAndScorePairs, Moves const& futureHalfMoves) const {
    cout << "Player: " << m_detailsOnTheEngine.getPlayerColor() << ", Depth: " << m_calculationDetails.depthInPlies
         << ", Mate score: " << m_calculationDetails.mateScore << "\n";
    cout << "Current moves: ";
    for (MoveAndScorePair const& moveAndScorePair : moveAndScorePairs) {
        cout << m_detailsOnTheEngine.getBoard().getReadableStringForMove(moveAndScorePair.first) << " ["
             << static_cast<double>(moveAndScorePair.second) / 100 << "], ";
    }
    cout << "\n";

    Board const& boardOnTheEngine(m_detailsOnTheEngine.getBoard());
    Board updatedBoard(boardOnTheEngine);
    cout << "Monitored PV: ";
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
             << boardOnTheEngine.getReadableStringForMove(
                    boardOnTheEngine.getMoveFromTwoLetterNumberNotation(m_calculationDetails.bestMove))
             << "\n";
    }

    cout << "\n";
}

void ResultPrinter::printMoveTables(MoveAndScorePairs const& moveAndScorePairs, Moves const& futureHalfMoves) const {
    if (!moveAndScorePairs.empty()) {
        putCurrentMoves(moveAndScorePairs);
    }
    if (!futureHalfMoves.empty()) {
        printFutureHalfMoves(futureHalfMoves);
    }
}

void ResultPrinter::putCurrentMoves(MoveAndScorePairs const& moveAndScorePairs) const {
    printHorizontalBorderLine();
    printScoresHeader(moveAndScorePairs, 0);
    putCurrentMovesTable(moveAndScorePairs, 0);
    printScoresHeader(moveAndScorePairs, 5);
    putCurrentMovesTable(moveAndScorePairs, 5);
    printScoresHeader(moveAndScorePairs, 10);
    putCurrentMovesTable(moveAndScorePairs, 10);
}

void ResultPrinter::putCurrentMovesTable(
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
            putChessBoardOnDisplayTable(boardsDisplayTable, m_detailsOnTheEngine.getBoard(), xOffset);
        }
        putCurrentMovesOnDisplayTable(boardsDisplayTable, moveAndScorePairs, startIndex, numberOfMovesToDisplay);
        cout << boardsDisplayTable;
        printHorizontalBorderLine();
    }
}

void ResultPrinter::putCurrentMovesOnDisplayTable(
    DisplayTable& boardsDisplayTable, MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex,
    unsigned int const numberOfMovesToDisplay) const {
    unsigned int xOffset = 0U;
    for (unsigned int moveIndex = 0; moveIndex < numberOfMovesToDisplay; moveIndex++) {
        Move const& currentMove(moveAndScorePairs.at(startIndex + moveIndex).first);
        putMoveOnChessBoardCellsInDisplayTable(
            boardsDisplayTable, m_detailsOnTheEngine.getBoard(), currentMove, xOffset, 1U, false);
        xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE;
    }
}

void ResultPrinter::printFutureHalfMoves(Moves const& futureHalfMoves) const {
    printScoreAndMoveNumbersHeader();
    printHorizontalBorderLine();
    printFutureHalfMovesTable(futureHalfMoves);
    printHorizontalBorderLine();
}

void ResultPrinter::printFutureHalfMovesTable(Moves const& futureHalfMoves) const {
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

void ResultPrinter::putFutureHalfMovesAndBoardsOnDisplayTable(
    DisplayTable& boardsDisplayTable, Moves const& futureHalfMoves, unsigned int const numberOfMovesToDisplay) const {
    SequenceOfMovesAnalyzer analyzer(m_detailsOnTheEngine.getBoard());
    unsigned int movesDisplayed = 0U;
    unsigned int xOffset = 0U;

    for (Move const& futureHalfMove : futureHalfMoves) {
        analyzer.checkMove(futureHalfMove);
        if (analyzer.getPieceFromMove().getColor() == m_detailsOnTheEngine.getPlayerColor()) {
            bool canPreMove = analyzer.canPreMove();

            putChessBoardOnDisplayTable(boardsDisplayTable, analyzer.getCurrentBoard(), xOffset);            putMoveOnChessBoardCellsInDisplayTable(
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

void ResultPrinter::printScoresHeader(MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex) const {
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
            cout << "|          ";
            cout << setfill(' ') << setw(9)
                 << static_cast<double>(moveAndScorePairs.at(startIndex + moveIndex).second) / 100;
            cout << "            |";
        }
        cout << "\n";
        printHorizontalBorderLine();
    }
}

void ResultPrinter::printScoreAndMoveNumbersHeader() const {
    cout << "|   ";
    cout << setfill(' ') << setw(9) << static_cast<double>(m_calculationDetails.scoreInPvLine) / 100;
    cout << " -> 1st move       |     |           2nd move            |     |           3rd move            |     |   "
            "        4th move            |     |           5th move            |\n";
}

void ResultPrinter::printHorizontalBorderLine() const {
    cout << "----------------------------------------------------------------------------------------------------------"
            "-------------------------------------------------------------------------------\n";
}

void ResultPrinter::putSeparatorsOnDisplayTable(DisplayTable& boardsDisplayTable, unsigned int const offset) const {
    unsigned int const numberOfColumns = boardsDisplayTable.getTotalColumns(),
                       numberOfRows = boardsDisplayTable.getTotalRows();
    for (unsigned int j = 0; j < numberOfRows; j++) {
        for (unsigned int separatorIndex = offset - 1; separatorIndex < numberOfColumns; separatorIndex += offset) {
            boardsDisplayTable.getCellReferenceAt(separatorIndex, j).setText(SEPARATOR);
        }
    }
}

void ResultPrinter::putChessBoardOnDisplayTable(
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

void ResultPrinter::putMoveOnChessBoardCellsInDisplayTable(
    DisplayTable& boardsDisplayTable, Board const& chessBoard, Move const& move, unsigned int const xOffset,
    unsigned int const moveNumberToDisplay, bool canPreMove) const {
    Piece piece(chessBoard.getPieceAt(move.first));
    boardsDisplayTable.getCellReferenceAt(move.first.getX() + xOffset, move.first.getY())
        .setText(getChessBoardCellForDisplay(piece, moveNumberToDisplay, canPreMove));
    boardsDisplayTable.getCellReferenceAt(move.second.getX() + xOffset, move.second.getY())
        .setText(getChessBoardCellForDisplay(piece, moveNumberToDisplay + 1, canPreMove));
}

string ResultPrinter::getChessBoardCellForDisplay(
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

MoveAndScorePairs ResultPrinter::getCurrentMoveAndScorePairs() const {
    MoveAndScorePairs result;
    Board const& boardOnTheEngine(m_detailsOnTheEngine.getBoard());
    for (StringAndIntPair const& searchingMoveAndScorePair : m_calculationDetails.searchingMoveAndScorePairs) {
        if (result.size() >= MIN_NUMBER_OF_MOVES_IN_TEXT &&
            searchingMoveAndScorePair.second <= MINIMUM_ACCEPTABLE_SCORE) {
            break;
        }

        Move move(boardOnTheEngine.getMoveFromTwoLetterNumberNotation(searchingMoveAndScorePair.first));
        if (isMoveWithinTheBoard(move) && boardOnTheEngine.isAPossibleMove(move)) {
            result.emplace_back(move, searchingMoveAndScorePair.second);
        }
    }
    sortSoThatHumanlyMovesAreAtTheStart(result);
    if (result.size() > MAX_NUMBER_OF_MOVES_IN_TEXT) {
        result.resize(MAX_NUMBER_OF_MOVES_IN_TEXT);
    }
    return result;
}

Moves ResultPrinter::getFutureHalfMoves() const {
    Moves result;
    strings const& pvHalfMovesStrings(m_calculationDetails.pvHalfMovesInMonitoredLine);
    Board updatedBoard(m_detailsOnTheEngine.getBoard());
    bool isFirst = true;
    PieceColor previousColor{};
    for (string const& pvHalfMoveString : pvHalfMovesStrings) {
        Move move(updatedBoard.getMoveFromTwoLetterNumberNotation(pvHalfMoveString));
        if (isMoveWithinTheBoard(move) && updatedBoard.isAPossibleMove(move)) {
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

void ResultPrinter::sortSoThatHumanlyMovesAreAtTheStart(MoveAndScorePairs& moveAndScoreToBeSorted) const {
    if (!moveAndScoreToBeSorted.empty()) {
        Board const& boardOnTheEngine(m_detailsOnTheEngine.getBoard());
        stable_sort(
            moveAndScoreToBeSorted.begin(), moveAndScoreToBeSorted.end(),
            [&](MoveAndScorePair const& pair1, MoveAndScorePair const& pair2) {
                int acceptableScore1 = getAcceptableScore(pair1.second);
                int acceptableScore2 = getAcceptableScore(pair2.second);
                if (acceptableScore1 == acceptableScore2) {
                    Move const& move1(pair1.first);
                    Move const& move2(pair2.first);
                    int yMoveForwardCount1 = move1.first.getY() - move1.second.getY();
                    int yMoveForwardCount2 = move2.first.getY() - move2.second.getY();
                    if (yMoveForwardCount1 == yMoveForwardCount2) {
                        int pieceTypeValue1 = getValueOfPieceType(boardOnTheEngine.getPieceAt(move1.first).getType());
                        int pieceTypeValue2 = getValueOfPieceType(boardOnTheEngine.getPieceAt(move2.first).getType());
                        if (pieceTypeValue1 == pieceTypeValue2) {
                            int xDelta1 = getPositiveDelta(move1.first.getX(), move1.second.getX());
                            int xDelta2 = getPositiveDelta(move2.first.getX(), move2.second.getX());
                            return xDelta1 > xDelta2;  // more mobile moves are prioritized
                        }
                        return pieceTypeValue1 > pieceTypeValue2;  // higher pieces are prioritized
                    }
                    return yMoveForwardCount1 > yMoveForwardCount2;  // offensive moves are prioritized
                }
                return acceptableScore1 > acceptableScore2;  // put losing moves at the back
            });
    }
}

unsigned int ResultPrinter::getNumberOfColumnsOfScoreDisplayTable(unsigned int const numberOfChessBoards) const {
    return numberOfChessBoards == 0 ? 0U : numberOfChessBoards * 2 - 1;
}

unsigned int ResultPrinter::getNumberOfColumnsOfBoardDisplayTable(unsigned int const numberOfChessBoards) const {
    return numberOfChessBoards == 0 ? 0U : numberOfChessBoards * 8U + numberOfChessBoards - 1;
}

int ResultPrinter::getAcceptableScore(int const scoreInCentipawns) const {
    int result{};
    int deltaFromBestMove = m_calculationDetails.scoreInPvLine - scoreInCentipawns;
    if (deltaFromBestMove < MINIMUM_ACCEPTABLE_DELTA_SCORE_FROM_BEST_MOVE) {
        result = 1;  // acceptable (move still makes sense)
    } else {
        result = 0;  // not acceptable (move does not make sense)
    }
    return result;
}

int ResultPrinter::getScoreLevel(int const scoreInCentipawns) const {
    int result{};
    if (scoreInCentipawns >= 9999.99) {
        result = 5;  // mate
    } else if (scoreInCentipawns >= 200) {
        result = 4;  // clearly winning
    } else if (scoreInCentipawns > 0) {
        result = 3;  // has advantage
    } else if (scoreInCentipawns > -100) {
        result = 2;  // opponent has advantage
    } else if (scoreInCentipawns > -9999.99) {
        result = 1;  // clearly losing
    } else {
        result = 0;  // mate
    }
    return result;
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
