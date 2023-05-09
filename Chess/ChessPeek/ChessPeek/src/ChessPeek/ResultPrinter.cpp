#include "ResultPrinter.hpp"

#include <ChessPeek/SequenceOfMovesAnalyzer.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Uci/UciUtilities.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>#include <Common/User/DisplayTable.hpp>

#include <iostream>
using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr int MINIMUM_ACCEPTABLE_SCORE = -300;
constexpr unsigned int MIN_NUMBER_OF_MOVES_IN_TEXT_REPORT = 5U;
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_TEXT_REPORT = 15U;
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_DISPLAY_TABLE = 5U;
constexpr unsigned int NEXT_OFFSET_OF_DISPLAY_TABLE = 9U;
constexpr char SEPARATOR[] = "     ";
}  // namespace
namespace alba {

namespace chess {

namespace ChessPeek {

ResultPrinter::ResultPrinter(BoardWithContext const& engineBoard, CalculationDetails const& calculationDetails)
    : m_engineBoardWithContext(engineBoard), m_calculationDetails(calculationDetails) {}

void ResultPrinter::print() {
    MoveAndScorePairs moveAndScorePairs(getCurrentMoveAndScorePairs());    Moves futureHalfMoves(getFutureHalfMoves());
    printCalculationDetails(moveAndScorePairs, futureHalfMoves);
    printMoveTables(moveAndScorePairs, futureHalfMoves);
    cout << "\n\n";    cout.flush();
}

void ResultPrinter::printCalculationDetails(
    MoveAndScorePairs const& moveAndScorePairs, Moves const& futureHalfMoves) const {
    cout << "Player: " << m_engineBoardWithContext.getPlayerColor() << ", Depth: " << m_calculationDetails.depthInPlies
         << ", Mate score: " << m_calculationDetails.mateScore << "\n";
    cout << "Current moves: ";
    for (MoveAndScorePair const& moveAndScorePair : moveAndScorePairs) {
        cout << m_engineBoardWithContext.getBoard().getReadableStringForMove(moveAndScorePair.first) << " ["
             << static_cast<double>(moveAndScorePair.second) / 100 << "], ";
    }
    cout << "\n";

    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    Board updatedBoard(engineBoard);
    cout << "Monitored PV: ";
    for (Move const& futureHalfMove : futureHalfMoves) {
        Piece piece = updatedBoard.getPieceAt(futureHalfMove.first);        cout << updatedBoard.getReadableStringForMove(futureHalfMove);
        if (!piece.isEmpty()) {
            cout << " [by " << piece.getColor() << "]";
        }        cout << ", ";
        updatedBoard.move(futureHalfMove);
    }
    cout << "\n";

    if (!m_calculationDetails.bestMove.empty()) {
        cout << "Best move: "
             << engineBoard.getReadableStringForMove(
                    engineBoard.getMoveFromTwoLetterNumberNotation(m_calculationDetails.bestMove))
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
            min(MAX_NUMBER_OF_MOVES_IN_DISPLAY_TABLE, static_cast<unsigned int>(moveAndScorePairs.size() - startIndex));
        unsigned int numberOfBoardDisplayColumns = getNumberOfColumnsOfBoardDisplayTable(numberOfMovesToDisplay);
        DisplayTable boardsDisplayTable(numberOfBoardDisplayColumns, numberOfBoardDisplayRows);
        boardsDisplayTable.setVerticalBorder("|");
        putSeparatorsOnDisplayTable(boardsDisplayTable, NEXT_OFFSET_OF_DISPLAY_TABLE);
        for (unsigned int xOffset = 0; xOffset < numberOfBoardDisplayColumns; xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE) {
            putChessBoardOnDisplayTable(boardsDisplayTable, m_engineBoardWithContext.getBoard(), xOffset);
        }
        putCurrentMovesOnDisplayTable(boardsDisplayTable, moveAndScorePairs, startIndex, numberOfMovesToDisplay);
        cout << boardsDisplayTable;        printHorizontalBorderLine();
    }
}
void ResultPrinter::putCurrentMovesOnDisplayTable(
    DisplayTable& boardsDisplayTable, MoveAndScorePairs const& moveAndScorePairs, unsigned int const startIndex,
    unsigned int const numberOfMovesToDisplay) const {
    unsigned int xOffset = 0U;
    for (unsigned int moveIndex = 0; moveIndex < numberOfMovesToDisplay; moveIndex++) {
        Move const& currentMove(moveAndScorePairs.at(startIndex + moveIndex).first);
        putMoveOnChessBoardCellsInDisplayTable(
            boardsDisplayTable, m_engineBoardWithContext.getBoard(), currentMove, xOffset, 1U, false);
        xOffset += NEXT_OFFSET_OF_DISPLAY_TABLE;
    }
}
void ResultPrinter::printFutureHalfMoves(Moves const& futureHalfMoves) const {
    printScoreAndMoveNumbersHeader();
    printHorizontalBorderLine();    printFutureHalfMovesTable(futureHalfMoves);
    printHorizontalBorderLine();
}

void ResultPrinter::printFutureHalfMovesTable(Moves const& futureHalfMoves) const {
    constexpr unsigned int numberOfRows = 8U;
    unsigned int numberOfMovesToDisplay =
        min(MAX_NUMBER_OF_MOVES_IN_DISPLAY_TABLE, static_cast<unsigned int>((futureHalfMoves.size() + 1U) / 2U));
    unsigned int numberOfColumns = getNumberOfColumnsOfBoardDisplayTable(numberOfMovesToDisplay);

    DisplayTable boardsDisplayTable(numberOfColumns, numberOfRows);    boardsDisplayTable.setVerticalBorder("|");
    putSeparatorsOnDisplayTable(boardsDisplayTable, NEXT_OFFSET_OF_DISPLAY_TABLE);
    putFutureHalfMovesAndBoardsOnDisplayTable(boardsDisplayTable, futureHalfMoves, numberOfMovesToDisplay);
    cout << boardsDisplayTable;}

void ResultPrinter::putFutureHalfMovesAndBoardsOnDisplayTable(
    DisplayTable& boardsDisplayTable, Moves const& futureHalfMoves, unsigned int const numberOfMovesToDisplay) const {
    SequenceOfMovesAnalyzer analyzer(m_engineBoardWithContext);
    unsigned int movesDisplayed = 0U;
    unsigned int xOffset = 0U;

    for (Move const& futureHalfMove : futureHalfMoves) {
        analyzer.analyzeMove(futureHalfMove);
        if (analyzer.getCurrentMoveColor() == m_engineBoardWithContext.getPlayerColor()) {
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
            min(MAX_NUMBER_OF_MOVES_IN_DISPLAY_TABLE, static_cast<unsigned int>(moveAndScorePairs.size() - startIndex));
        bool isFirst = true;
        for (unsigned int moveIndex = 0; moveIndex < numberOfMovesToDisplay; moveIndex++) {
            if (isFirst) {                isFirst = false;
            } else {
                cout << SEPARATOR;
            }            cout << "|          ";
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
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    for (StringAndIntPair const& searchingMoveAndScorePair : m_calculationDetails.searchingMoveAndScorePairs) {
        if (result.size() >= MIN_NUMBER_OF_MOVES_IN_TEXT_REPORT &&
            searchingMoveAndScorePair.second <= MINIMUM_ACCEPTABLE_SCORE) {
            break;
        }

        Move move(engineBoard.getMoveFromTwoLetterNumberNotation(searchingMoveAndScorePair.first));
        if (isMoveWithinTheBoard(move) && engineBoard.isAPossibleMove(move)) {
            result.emplace_back(move, searchingMoveAndScorePair.second);
        }
    }
    sortSoThatMoreHumanMovesArePrioritized(result);
    if (result.size() > MAX_NUMBER_OF_MOVES_IN_TEXT_REPORT) {
        result.resize(MAX_NUMBER_OF_MOVES_IN_TEXT_REPORT);
    }
    return result;
}
Moves ResultPrinter::getFutureHalfMoves() const {
    Moves result;
    strings const& pvHalfMovesStrings(m_calculationDetails.pvHalfMovesInMonitoredLine);
    Board updatedBoard(m_engineBoardWithContext.getBoard());
    bool isFirst = true;
    PieceColor previousColor{};
    for (string const& pvHalfMoveString : pvHalfMovesStrings) {        Move move(updatedBoard.getMoveFromTwoLetterNumberNotation(pvHalfMoveString));
        if (isMoveWithinTheBoard(move) && updatedBoard.isAPossibleMove(move)) {
            Piece piece = updatedBoard.getPieceAt(move.first);
            if (piece.isEmpty()) {
                break;  // piece needs to be valid
            } else {
                if (isFirst) {
                    isFirst = false;
                } else if (!areOpposingColors(previousColor, piece.getColor())) {
                    break;  // colors need to be alternating
                }
                previousColor = piece.getColor();
            }
            result.emplace_back(move);
            updatedBoard.move(move);

        } else {
            break;  // retain only line with valid moves
        }
        if (result.size() >= MAX_NUMBER_OF_MOVES_IN_TEXT_REPORT) {
            break;
        }
    }
    return result;
}

void ResultPrinter::sortSoThatMoreHumanMovesArePrioritized(MoveAndScorePairs& moveAndScoreToBeSorted) const {
    if (!moveAndScoreToBeSorted.empty()) {
        Board const& engineBoard(m_engineBoardWithContext.getBoard());
        Coordinate opponentsKingCoordinate = m_engineBoardWithContext.getOpponentsKingCoordinate();
        stable_sort(
            moveAndScoreToBeSorted.begin(), moveAndScoreToBeSorted.end(),
            [&](MoveAndScorePair const& pair1, MoveAndScorePair const& pair2) {
                int scoreLevel1 = getScoreLevel(pair1.second);
                int scoreLevel2 = getScoreLevel(pair2.second);
                if (scoreLevel1 == scoreLevel2) {
                    Move const& move1(pair1.first);
                    Move const& move2(pair2.first);
                    int distanceToKing1 = getDistanceToOpponentsKing(move1, opponentsKingCoordinate);
                    int distanceToKing2 = getDistanceToOpponentsKing(move2, opponentsKingCoordinate);
                    if (distanceToKing1 == distanceToKing2) {
                        int yForwardDelta1 = getForwardScore(move1);
                        int yForwardDelta2 = getForwardScore(move2);
                        if (yForwardDelta1 == yForwardDelta2) {
                            return getPieceValue(move1, engineBoard) > getPieceValue(move2, engineBoard);
                        }
                        return yForwardDelta1 > yForwardDelta2;  // offensive moves are first
                    }
                    return distanceToKing1 < distanceToKing2;  // moves nearest to king are first
                }
                return scoreLevel1 > scoreLevel2;  // prioritize moves that make sense
            });
    }
}

int ResultPrinter::getScoreLevel(int const scoreInCentipawns) const {
    int result{};
    if (scoreInCentipawns >= ARTIFICIAL_MATE_SCORE) {
        result = 0;  // put mate as same level as best move (this is to be human and have an imperfect record on mates)
    } else if (scoreInCentipawns <= -ARTIFICIAL_MATE_SCORE) {
        result = -ARTIFICIAL_MATE_SCORE;  // avoid to be mated as much as possible
    } else {
        constexpr int ONE_PAWN_SCORE = 100;
        int positiveDeltaFromBestMove = m_calculationDetails.scoreInPvLine - scoreInCentipawns;
        result = -1 * positiveDeltaFromBestMove / ONE_PAWN_SCORE;

        // The formula works like this, for example we have this scores: 300 201 200 199 100 0 -100
        // The best one is 300.
        // The value for each score respectively:
        // -> For  300: -1*(300-300)/100 =   -1/100 =  0
        // -> For  201: -1*(300-201)/100 =  -99/100 =  0
        // -> For  200: -1*(300-200)/100 = -100/100 = -1
        // -> For  199: -1*(300-199)/100 = -101/100 = -1
        // -> For  100: -1*(300-100)/100 = -200/100 = -2
        // -> For    0: -1*(300-0)/100   = -300/100 = -3
        // -> For -100: -1*(300+100)/100 = -400/100 = -4
        // Each level is one pawn distance from the best score (this is avoid "one pawn blunders" at each level).
        // Its negative so its reverse sorted.
    }
    return result;
}

int ResultPrinter::getDistanceToOpponentsKing(Move const& move, Coordinate opponentsKingCoordinate) const {
    Coordinate deltaToKing = opponentsKingCoordinate - move.second;
    return static_cast<int>(
        round(pow(deltaToKing.getX() * deltaToKing.getX() + deltaToKing.getY() * deltaToKing.getY(), 0.5)));
}

int ResultPrinter::getForwardScore(Move const& move) const { return move.first.getY() - move.second.getY(); }

int ResultPrinter::getPieceValue(Move const& move, Board const& engineBoard) const {
    return getValueOfPieceType(engineBoard.getPieceAt(move.first).getType());
}

unsigned int ResultPrinter::getNumberOfColumnsOfScoreDisplayTable(unsigned int const numberOfChessBoards) const {
    return numberOfChessBoards == 0 ? 0U : numberOfChessBoards * 2 - 1;
}

unsigned int ResultPrinter::getNumberOfColumnsOfBoardDisplayTable(unsigned int const numberOfChessBoards) const {
    return numberOfChessBoards == 0 ? 0U : numberOfChessBoards * 8U + numberOfChessBoards - 1;
}

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba