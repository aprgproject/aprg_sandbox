#include "ResultPrinter.hpp"

#include <ChessPeek/SequenceOfMovesAnalyzer.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Uci/UciInterpreter.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <iostream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr int MINIMUM_ACCEPTABLE_SCORE = -300;
constexpr unsigned int MIN_NUMBER_OF_MOVES_IN_TEXT_REPORT = 5U;
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_TEXT_REPORT = 10U;
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_GRID = 5U;
constexpr unsigned int NEXT_OFFSET_OF_GRID = 9U;
constexpr char SEPARATOR[] = "     ";
}  // namespace

namespace alba {

namespace chess {

namespace ChessPeek {

ResultPrinter::ResultPrinter(BoardWithContext const& engineBoard, CalculationDetails const& calculationDetails)
    : m_engineBoardWithContext(engineBoard), m_calculationDetails(calculationDetails) {}

void ResultPrinter::print() {
    CurrentMoveDetails currentMoveDetails(getCurrentMoveDetails());
    FutureMoveDetails futureMoveDetails(getFutureMoveDetails());
    printCalculationDetails(currentMoveDetails, futureMoveDetails);
    printMovesGrid(currentMoveDetails, futureMoveDetails);
    cout << "\n\n";
    cout.flush();
}

void ResultPrinter::printCalculationDetails(
    CurrentMoveDetails const& currentMoveDetails, FutureMoveDetails const& futureMoveDetails) const {
    Board const& engineBoard(m_engineBoardWithContext.getBoard());

    cout << "Player: " << m_engineBoardWithContext.getPlayerColor() << ", Depth: " << m_calculationDetails.depthInPlies
         << ", Mate score: " << m_calculationDetails.mateScore << "\n";
    cout << "Current moves: ";
    for (CurrentMoveDetail const& currentMove : currentMoveDetails) {
        cout << engineBoard.getReadableStringForMove(currentMove.move) << " ["
             << static_cast<double>(currentMove.score) / 100 << "], ";
    }
    cout << "\n";

    Board updatedBoard(engineBoard);
    cout << "Monitored variation: ";
    for (FutureMoveDetail const& futureMoveDetail : futureMoveDetails) {
        Piece piece = updatedBoard.getPieceAt(futureMoveDetail.halfMove.first);
        cout << updatedBoard.getReadableStringForMove(futureMoveDetail.halfMove);
        cout << " by: [" << piece.getColor() << "]";
        cout << " count: [" << futureMoveDetail.commonalityCount << "]";
        cout << ", ";
        updatedBoard.move(futureMoveDetail.halfMove);
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

void ResultPrinter::printMovesGrid(
    CurrentMoveDetails const& currentMoveDetails, FutureMoveDetails const& futureMoveDetails) const {
    if (!currentMoveDetails.empty()) {
        printCurrentMovesGrid(currentMoveDetails);
    }
    if (!futureMoveDetails.empty()) {
        printFutureMovesGrid(futureMoveDetails);
    }
}

void ResultPrinter::printCurrentMovesGrid(CurrentMoveDetails const& currentMoveDetails) const {
    printHorizontalBorderLine();
    printScoresHeader(currentMoveDetails, 0);
    printARowOfCurrentMoves(currentMoveDetails, 0);
    printScoresHeader(currentMoveDetails, 5);
    printARowOfCurrentMoves(currentMoveDetails, 5);
}

void ResultPrinter::printARowOfCurrentMoves(
    CurrentMoveDetails const& currentMoveDetails, unsigned int const startIndex) const {
    constexpr unsigned int numberOfBoardDisplayRows = 8U;
    if (startIndex < currentMoveDetails.size()) {
        unsigned int rowSize =
            min(MAX_NUMBER_OF_MOVES_IN_GRID, static_cast<unsigned int>(currentMoveDetails.size() - startIndex));
        unsigned int numberOfBoardDisplayColumns = getNumberOfColumnsOfGrid(rowSize);
        DisplayTable grid(numberOfBoardDisplayColumns, numberOfBoardDisplayRows);
        grid.setVerticalBorder("|");
        setSeparatorsOnGrid(grid, NEXT_OFFSET_OF_GRID);
        for (unsigned int xOffset = 0; xOffset < numberOfBoardDisplayColumns; xOffset += NEXT_OFFSET_OF_GRID) {
            setBoardOnGrid(grid, m_engineBoardWithContext.getBoard(), xOffset);
        }
        setCurrentMovesOnGrid(grid, currentMoveDetails, startIndex, rowSize);
        cout << grid;
        printHorizontalBorderLine();
    }
}

void ResultPrinter::setCurrentMovesOnGrid(
    DisplayTable& grid, CurrentMoveDetails const& currentMoveDetails, unsigned int const startIndex,
    unsigned int const rowSize) const {
    unsigned int xOffset = 0U;
    for (unsigned int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
        Move const& currentMove(currentMoveDetails.at(startIndex + moveIndex).move);
        setMoveOnGrid(grid, m_engineBoardWithContext.getBoard(), currentMove, xOffset, 1U, optional<char>());
        xOffset += NEXT_OFFSET_OF_GRID;
    }
}

void ResultPrinter::printFutureMovesGrid(FutureMoveDetails const& futureMoveDetails) const {
    printScoreAndMoveNumbersHeader();
    printHorizontalBorderLine();
    printARowOfFutureMoves(futureMoveDetails);
    printHorizontalBorderLine();
}

void ResultPrinter::printARowOfFutureMoves(FutureMoveDetails const& futureMoveDetails) const {
    constexpr unsigned int numberOfRows = 8U;
    unsigned int rowSize =
        min(MAX_NUMBER_OF_MOVES_IN_GRID, static_cast<unsigned int>((futureMoveDetails.size() + 1U) / 2U));
    unsigned int numberOfColumns = getNumberOfColumnsOfGrid(rowSize);

    DisplayTable grid(numberOfColumns, numberOfRows);
    grid.setVerticalBorder("|");
    setSeparatorsOnGrid(grid, NEXT_OFFSET_OF_GRID);
    setFutureMovesOnGrid(grid, futureMoveDetails, rowSize);
    cout << grid;
}

void ResultPrinter::setFutureMovesOnGrid(
    DisplayTable& grid, FutureMoveDetails const& futureMoveDetails, unsigned int const rowSize) const {
    SequenceOfMovesAnalyzer analyzer(m_engineBoardWithContext);
    unsigned int movesDisplayed = 0U;
    unsigned int xOffset = 0U;
    int preMoveThreshold = 5;
    bool isUnSurePreMove = false;

    for (FutureMoveDetail const& futureMoveDetail : futureMoveDetails) {
        analyzer.analyzeMove(futureMoveDetail.halfMove);
        if (analyzer.getCurrentMoveColor() == m_engineBoardWithContext.getPlayerColor()) {
            bool isSurePreMove = analyzer.canPreMove();
            optional<char> firstChar = getFirstCharOfCell(isSurePreMove, isUnSurePreMove);

            setBoardOnGrid(grid, analyzer.getCurrentBoard(), xOffset);
            setMoveOnGrid(
                grid, analyzer.getCurrentBoard(), futureMoveDetail.halfMove, xOffset, movesDisplayed + 1, firstChar);

            xOffset += NEXT_OFFSET_OF_GRID;
            movesDisplayed++;
            if (movesDisplayed >= rowSize) {
                break;
            }
        } else {
            isUnSurePreMove = preMoveThreshold <= futureMoveDetail.commonalityCount;
        }
        analyzer.commitMove();
    }
}

void ResultPrinter::printScoresHeader(
    CurrentMoveDetails const& currentMoveDetails, unsigned int const startIndex) const {
    if (startIndex < currentMoveDetails.size()) {
        unsigned int rowSize =
            min(MAX_NUMBER_OF_MOVES_IN_GRID, static_cast<unsigned int>(currentMoveDetails.size() - startIndex));
        bool isFirst = true;
        for (unsigned int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
            if (isFirst) {
                isFirst = false;
            } else {
                cout << SEPARATOR;
            }
            cout << "|          ";
            cout << setfill(' ') << setw(9)
                 << static_cast<double>(currentMoveDetails.at(startIndex + moveIndex).score) / 100;
            cout << "            |";
        }
        cout << "\n";
        printHorizontalBorderLine();
    }
}

void ResultPrinter::printScoreAndMoveNumbersHeader() const {
    cout << "|   ";
    cout << setfill(' ') << setw(9) << static_cast<double>(m_calculationDetails.scoreInMonitoredVariation) / 100;
    cout << " -> 1st move       |     |           2nd move            |     |           3rd move            |     |   "
            "        4th move            |     |           5th move            |\n";
}

void ResultPrinter::printHorizontalBorderLine() const {
    cout << "----------------------------------------------------------------------------------------------------------"
            "-------------------------------------------------------------------------------\n";
}

void ResultPrinter::setSeparatorsOnGrid(DisplayTable& grid, unsigned int const xOffset) const {
    unsigned int const numberOfColumns = grid.getTotalColumns(), numberOfRows = grid.getTotalRows();
    for (unsigned int j = 0; j < numberOfRows; j++) {
        for (unsigned int separatorIndex = xOffset - 1; separatorIndex < numberOfColumns; separatorIndex += xOffset) {
            grid.getCellReferenceAt(separatorIndex, j).setText(SEPARATOR);
        }
    }
}

void ResultPrinter::setBoardOnGrid(DisplayTable& grid, Board const& board, unsigned int const xOffset) const {
    constexpr CoordinateDataType boardDimension = 8U;
    for (CoordinateDataType y = 0; y < boardDimension; y++) {
        for (CoordinateDataType x = 0; x < boardDimension; x++) {
            Piece piece(board.getPieceAt(Coordinate(x, y)));
            grid.getCellReferenceAt(x + xOffset, y).setText(getCellForDisplay(piece, 0U, optional<char>()));
        }
    }
}

void ResultPrinter::setMoveOnGrid(
    DisplayTable& grid, Board const& board, Move const& move, unsigned int const xOffset, unsigned int const moveNumber,
    optional<char> const& firstChar) const {
    Piece piece(board.getPieceAt(move.first));
    grid.getCellReferenceAt(move.first.getX() + xOffset, move.first.getY())
        .setText(getCellForDisplay(piece, moveNumber, firstChar));
    grid.getCellReferenceAt(move.second.getX() + xOffset, move.second.getY())
        .setText(getCellForDisplay(piece, moveNumber + 1, firstChar));
}

ResultPrinter::CurrentMoveDetails ResultPrinter::getCurrentMoveDetails() const {
    CurrentMoveDetails result;
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    for (StringAndIntPair const& currentMoveAndScorePair : m_calculationDetails.currentMovesAndScores) {
        if (result.size() >= MIN_NUMBER_OF_MOVES_IN_TEXT_REPORT &&
            currentMoveAndScorePair.second <= MINIMUM_ACCEPTABLE_SCORE) {
            break;
        }

        Move move(engineBoard.getMoveFromTwoLetterNumberNotation(currentMoveAndScorePair.first));
        if (engineBoard.isAPossibleMove(move)) {
            result.emplace_back(CurrentMoveDetail{move, currentMoveAndScorePair.second});
        }
    }

    sortForMoreHumanMoves(result);
    removeTooManyPawnMoves(result);

    if (result.size() > MAX_NUMBER_OF_MOVES_IN_TEXT_REPORT) {
        result.resize(MAX_NUMBER_OF_MOVES_IN_TEXT_REPORT);
    }
    return result;
}

ResultPrinter::FutureMoveDetails ResultPrinter::getFutureMoveDetails() const {
    FutureMoveDetails result;
    strings const& pvHalfMovesStrings(m_calculationDetails.monitoredVariation);
    Board updatedBoard(m_engineBoardWithContext.getBoard());
    PieceColor previousColor{};
    int index = 0;
    for (string const& pvHalfMoveString : pvHalfMovesStrings) {
        Move move(updatedBoard.getMoveFromTwoLetterNumberNotation(pvHalfMoveString));
        if (updatedBoard.isAPossibleMove(move)) {
            Piece piece = updatedBoard.getPieceAt(move.first);
            if (index == 0 || areOpposingColors(previousColor, piece.getColor())) {
                result.emplace_back(FutureMoveDetail{move, getCommonalityCount(move, updatedBoard, index)});
                if (result.size() >= MAX_NUMBER_OF_MOVES_IN_TEXT_REPORT) {
                    break;
                }
                updatedBoard.move(move);
                previousColor = piece.getColor();
            } else {
                break;  // colors need to alternating
            }
        } else {
            break;  // retain only line with valid moves
        }
        index++;
    }
    return result;
}

void ResultPrinter::sortForMoreHumanMoves(CurrentMoveDetails& currentMoveDetails) const {
    if (!currentMoveDetails.empty()) {
        stable_sort(
            currentMoveDetails.begin(), currentMoveDetails.end(),
            [&](CurrentMoveDetail const& detail1, CurrentMoveDetail const& detail2) {
                return isAMoreHumanMove(detail1, detail2);
            });
    }
}

void ResultPrinter::removeTooManyPawnMoves(CurrentMoveDetails& currentMoveDetails) const {
    constexpr int MAX_NUMBER_OF_PAWN_MOVES = 2;
    int numberOfPawnMoves = 0;
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    auto pastEndIt = remove_if(
        currentMoveDetails.begin(), currentMoveDetails.end(),
        [&numberOfPawnMoves, &engineBoard](CurrentMoveDetail const& currentMoveDetail) {
            Move const& move(currentMoveDetail.move);
            if (PieceType::Pawn == engineBoard.getPieceAt(move.first).getType()) {
                if (numberOfPawnMoves < MAX_NUMBER_OF_PAWN_MOVES) {
                    numberOfPawnMoves++;
                } else {
                    return true;
                }
            }
            return false;
        });
    currentMoveDetails.erase(pastEndIt, currentMoveDetails.cend());
}

bool ResultPrinter::isAMoreHumanMove(
    CurrentMoveDetail const& currentMoveDetail1, CurrentMoveDetail const& currentMoveDetail2) const {
    int scoreLevel1 = getScoreLevel(currentMoveDetail1.score);
    int scoreLevel2 = getScoreLevel(currentMoveDetail2.score);
    if (scoreLevel1 == scoreLevel2) {
        Move const& move1(currentMoveDetail1.move);
        Move const& move2(currentMoveDetail2.move);
        int distanceToKing1 = getDistanceToOpponentsKing(move1);
        int distanceToKing2 = getDistanceToOpponentsKing(move2);
        if (distanceToKing1 == distanceToKing2) {
            int yForwardCount1 = getForwardCount(move1);
            int yForwardCount2 = getForwardCount(move2);
            if (yForwardCount1 == yForwardCount2) {
                return getPieceValueOfMove(move1) > getPieceValueOfMove(move2);
            }
            return yForwardCount1 > yForwardCount2;  // offensive moves are first
        }
        return distanceToKing1 < distanceToKing2;  // moves nearest to king are first
    }
    return scoreLevel1 > scoreLevel2;  // prioritize moves that make sense
}

int ResultPrinter::getScoreLevel(int const scoreInCentipawns) const {
    if (scoreInCentipawns >= UciInterpreter::ARTIFICIAL_MATE_SCORE) {
        return 0;  // put mate as same level as best move (this is to be human and have an imperfect record on mates)
    } else if (scoreInCentipawns <= -UciInterpreter::ARTIFICIAL_MATE_SCORE) {
        return -UciInterpreter::ARTIFICIAL_MATE_SCORE;  // avoid to be mated as much as possible
    } else {
        constexpr int LEVEL_DISTANCE = 80;
        int positiveDeltaFromBestMove = m_calculationDetails.scoreInMonitoredVariation - scoreInCentipawns;
        return -1 * positiveDeltaFromBestMove / LEVEL_DISTANCE;

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
}

int ResultPrinter::getDistanceToOpponentsKing(Move const& move) const {
    Coordinate deltaToKing = m_engineBoardWithContext.getOpponentsKingCoordinate() - move.second;
    return static_cast<int>(
        round(pow(deltaToKing.getX() * deltaToKing.getX() + deltaToKing.getY() * deltaToKing.getY(), 0.5)));
}

int ResultPrinter::getForwardCount(Move const& move) const { return move.first.getY() - move.second.getY(); }

int ResultPrinter::getPieceValueOfMove(Move const& move) const {
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    return getValueOfPieceType(engineBoard.getPieceAt(move.first).getType());
}

int ResultPrinter::getCommonalityCount(Move const& move, Board const& engineBoard, int const index) const {
    int count{};
    if (index < static_cast<int>(m_calculationDetails.commonMovesAndCountsOfEachStep.size())) {
        StringAndIntPair commonMoveAndCount = m_calculationDetails.commonMovesAndCountsOfEachStep.at(index);
        if (move == engineBoard.getMoveFromTwoLetterNumberNotation(commonMoveAndCount.first)) {
            count = commonMoveAndCount.second;
        }
    }
    return count;
}

string ResultPrinter::getCellForDisplay(
    Piece const& piece, unsigned int const moveNumber, optional<char> const& firstChar) const {
    string result(3, ' ');
    if (moveNumber != 0) {
        char moveNumberCharacter = '0' + static_cast<char>(moveNumber);
        if (firstChar) {
            result[0] = firstChar.value();
        } else {
            result[0] = moveNumberCharacter;
        }
        result[2] = moveNumberCharacter;
    }
    result[1] = piece.getCharacter();
    return result;
}

optional<char> ResultPrinter::getFirstCharOfCell(bool const isSurePreMove, bool isUnsurePreMove) const {
    optional<char> result;
    if (isSurePreMove) {
        result = '*';
    } else if (isUnsurePreMove) {
        result = '~';
    }
    return result;
}

unsigned int ResultPrinter::getNumberOfColumnsOfGrid(unsigned int const numberOfBoards) const {
    return numberOfBoards == 0 ? 0U : numberOfBoards * 8U + numberOfBoards - 1;
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
