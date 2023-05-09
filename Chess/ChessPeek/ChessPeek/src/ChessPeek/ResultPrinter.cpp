#include "ResultPrinter.hpp"

#include <ChessPeek/HumanScoreGenerator.hpp>
#include <ChessPeek/SequenceOfMovesAnalyzer.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>
#include <iostream>

using namespace alba::mathHelper;using namespace alba::stringHelper;
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
    : m_engineBoardWithContext(engineBoard), m_calculationDetails(calculationDetails), m_bestScore(), m_worstScore() {
    saveBestAndWorstScores();
}

void ResultPrinter::print() {
    CurrentMoveDetails currentMoveDetails(getCurrentMoveDetails());    FutureMoveDetails futureMoveDetails(getFutureMoveDetails());
    printCalculationDetails(currentMoveDetails, futureMoveDetails);
    printMovesGrid(currentMoveDetails, futureMoveDetails);
    cout << "\n\n";
    cout.flush();
}

void ResultPrinter::saveBestAndWorstScores() {
    Variations const& variations(m_calculationDetails.variations);
    if (!variations.empty()) {
        auto itPair = minmax_element(
            variations.cbegin(), variations.cend(), [](Variation const& variation1, Variation const& variation2) {
                return variation1.scoreInCentipawns < variation2.scoreInCentipawns;
            });
        m_bestScore = itPair.second->scoreInCentipawns;
        m_worstScore = itPair.first->scoreInCentipawns;
    }
}

void ResultPrinter::printCalculationDetails(
    CurrentMoveDetails const& currentMoveDetails, FutureMoveDetails const& futureMoveDetails) const {
    Board const& engineBoard(m_engineBoardWithContext.getBoard());

    cout << "Player: " << m_engineBoardWithContext.getPlayerColor() << ", Depth: " << m_calculationDetails.depthInPlies
         << "\n";
    cout << "Current moves: ";
    for (CurrentMoveDetail const& moveDetail : currentMoveDetails) {
        cout << engineBoard.getReadableStringForMove(moveDetail.move) << " ["
             << getDisplayedScore(moveDetail.engineScore, moveDetail.mateValue) << "], ";
    }
    cout << "\n";

    Board updatedBoard(engineBoard);
    cout << "Monitored variation: ";
    for (FutureMoveDetail const& moveDetail : futureMoveDetails) {
        Piece piece = updatedBoard.getPieceAt(moveDetail.halfMove.first);
        cout << updatedBoard.getReadableStringForMove(moveDetail.halfMove);
        cout << " by " << piece.getColor() << ", ";
        updatedBoard.move(moveDetail.halfMove);
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
    if (!currentMoveDetails.empty()) {        printCurrentMovesGrid(currentMoveDetails);
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
        Board const& engineBoard(m_engineBoardWithContext.getBoard());
        for (unsigned int xOffset = 0; xOffset < numberOfBoardDisplayColumns; xOffset += NEXT_OFFSET_OF_GRID) {
            setBoardOnGrid(grid, engineBoard, xOffset);
        }
        setCurrentMovesOnGrid(grid, currentMoveDetails, startIndex, rowSize);
        cout << grid;        printHorizontalBorderLine();
    }
}
void ResultPrinter::setCurrentMovesOnGrid(
    DisplayTable& grid, CurrentMoveDetails const& currentMoveDetails, unsigned int const startIndex,
    unsigned int const rowSize) const {
    unsigned int xOffset = 0U;
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    for (unsigned int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
        Move const& currentMove(currentMoveDetails.at(startIndex + moveIndex).move);
        setMoveOnGrid(grid, engineBoard, currentMove, xOffset, 1U, optional<char>());
        xOffset += NEXT_OFFSET_OF_GRID;
    }
}

void ResultPrinter::printFutureMovesGrid(FutureMoveDetails const& futureMoveDetails) const {
    printBestMoveScoreAndMoveNumbersHeader();
    printHorizontalBorderLine();
    printARowOfFutureMoves(futureMoveDetails);
    printHorizontalBorderLine();}

void ResultPrinter::printARowOfFutureMoves(FutureMoveDetails const& futureMoveDetails) const {
    constexpr unsigned int numberOfRows = 8U;    unsigned int rowSize =
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
    Board const& analyzerBoard(analyzer.getCurrentBoard());
    unsigned int movesDisplayed = 0U;
    unsigned int xOffset = 0U;
    bool isUnSurePreMove = false;

    for (FutureMoveDetail const& moveDetail : futureMoveDetails) {
        analyzer.analyzeMove(moveDetail.halfMove);
        if (analyzer.getCurrentMoveColor() == m_engineBoardWithContext.getPlayerColor()) {
            optional<char> firstChar = getFirstCharOfCell(analyzer.canPreMove(), isUnSurePreMove);

            setBoardOnGrid(grid, analyzerBoard, xOffset);
            setMoveOnGrid(grid, analyzerBoard, moveDetail.halfMove, xOffset, movesDisplayed + 1, firstChar);

            xOffset += NEXT_OFFSET_OF_GRID;
            movesDisplayed++;
            if (movesDisplayed >= rowSize) {
                break;
            }
        }
        analyzer.commitMove();
    }}

void ResultPrinter::printScoresHeader(
    CurrentMoveDetails const& currentMoveDetails, unsigned int const startIndex) const {    if (startIndex < currentMoveDetails.size()) {
        unsigned int rowSize =
            min(MAX_NUMBER_OF_MOVES_IN_GRID, static_cast<unsigned int>(currentMoveDetails.size() - startIndex));
        bool isFirst = true;
        for (unsigned int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
            if (isFirst) {
                isFirst = false;
            } else {
                cout << SEPARATOR;
            }
            CurrentMoveDetail const& moveDetail(currentMoveDetails.at(startIndex + moveIndex));
            cout << "|" << getDisplayedScore(moveDetail.engineScore, moveDetail.mateValue, 31) << "|";
        }
        cout << "\n";
        printHorizontalBorderLine();
    }
}

void ResultPrinter::printBestMoveScoreAndMoveNumbersHeader() const {
    Variation const& variation(m_calculationDetails.variations.front());
    cout << "|" << getDisplayedScore(variation.scoreInCentipawns, variation.mateValue, 31, " -> 1st move");
    cout << "|     |           2nd move            |     |           3rd move            "
            "|     |           4th move            |     |           5th move            |\n";
}

void ResultPrinter::printHorizontalBorderLine() const {    cout << "----------------------------------------------------------------------------------------------------------"
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
    HumanScoreGenerator scorer(m_engineBoardWithContext, m_bestScore, m_worstScore);
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    for (Variation const& variation : m_calculationDetails.variations) {
        if (result.size() >= MIN_NUMBER_OF_MOVES_IN_TEXT_REPORT &&
            variation.scoreInCentipawns <= MINIMUM_ACCEPTABLE_SCORE) {
            break;
        }
        if (!variation.halfMoves.empty()) {
            Move move(engineBoard.getMoveFromTwoLetterNumberNotation(variation.halfMoves.front()));
            if (engineBoard.isAPossibleMove(move)) {
                CurrentMoveDetail moveDetail{
                    move, variation.scoreInCentipawns, variation.mateValue,
                    scorer.getHumanScore({move, variation.scoreInCentipawns, variation.mateValue})};
                result.emplace_back(moveDetail);
            }
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
    if (!m_calculationDetails.variations.empty()) {
        Variation const& bestVariation(m_calculationDetails.variations.front());
        if (!bestVariation.halfMoves.empty()) {
            strings const& bestHalfMoves(bestVariation.halfMoves);
            Board updatedBoard(m_engineBoardWithContext.getBoard());
            PieceColor previousColor{};
            int index = 0;
            for (string const& bestHalfMove : bestHalfMoves) {
                Move move(updatedBoard.getMoveFromTwoLetterNumberNotation(bestHalfMove));
                if (updatedBoard.isAPossibleMove(move)) {
                    Piece piece = updatedBoard.getPieceAt(move.first);
                    if (index == 0 || areOpposingColors(previousColor, piece.getColor())) {
                        result.emplace_back(FutureMoveDetail{move});
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
        }
    }
    return result;
}
void ResultPrinter::sortForMoreHumanMoves(CurrentMoveDetails& currentMoveDetails) const {
    if (!currentMoveDetails.empty()) {
        stable_sort(
            currentMoveDetails.begin(), currentMoveDetails.end(),
            [&](CurrentMoveDetail const& detail1, CurrentMoveDetail const& detail2) {
                return detail1.humanScore > detail2.humanScore;
            });
    }
}
void ResultPrinter::removeTooManyPawnMoves(CurrentMoveDetails& currentMoveDetails) const {
    constexpr int MAX_NUMBER_OF_PAWN_MOVES = 2;
    int numberOfPawnMoves = 0;
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    auto pastEndIt = remove_if(
        currentMoveDetails.begin(), currentMoveDetails.end(),
        [&numberOfPawnMoves, &engineBoard](CurrentMoveDetail const& moveDetail) {
            Move const& move(moveDetail.move);
            if (PieceType::Pawn == engineBoard.getPieceAt(move.first).getType()) {
                if (numberOfPawnMoves < MAX_NUMBER_OF_PAWN_MOVES) {
                    numberOfPawnMoves++;                } else {
                    return true;
                }
            }            return false;
        });
    currentMoveDetails.erase(pastEndIt, currentMoveDetails.cend());
}

string ResultPrinter::getDisplayedScore(
    int const score, int const mate, size_t const desiredLength, std::string const& lastPart) const {
    stringstream ss;
    if (mate == 0) {
        ss << static_cast<double>(score) / 100;
    } else {
        ss << "Mate: " << mate;
    }
    ss << lastPart;
    return getStringWithCenterAlignment(ss.str(), desiredLength);
}

string ResultPrinter::getCellForDisplay(    Piece const& piece, unsigned int const moveNumber, optional<char> const& firstChar) const {
    string result(3, ' ');
    if (moveNumber != 0) {
        char moveNumberCharacter = '0' + static_cast<char>(moveNumber);        if (firstChar) {
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
