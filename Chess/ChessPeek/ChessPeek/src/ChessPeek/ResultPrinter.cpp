#include "ResultPrinter.hpp"

#include <ChessPeek/SequenceOfMovesAnalyzer.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/StreamOperators.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>
using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_TEXT = 10U;
constexpr unsigned int MAX_NUMBER_OF_BOOK_MOVES = 5U;
constexpr unsigned int MAX_NUMBER_OF_MOVES_IN_GRID = 5U;
constexpr unsigned int NEXT_OFFSET_OF_GRID = 9U;
constexpr unsigned int DESIRED_HEADER_LENGTH = 31;
constexpr char SEPARATOR[] = "     ";
}  // namespace
namespace alba {

namespace chess {

namespace ChessPeek {

string ResultPrinter::s_nameOfLine;

ResultPrinter::ResultPrinter(
    CalculationDetails const& calculationDetails, BoardWithContext const& engineBoard, Book const& book)
    : m_calculationDetails(calculationDetails),
      m_engineBoardWithContext(engineBoard),
      m_book(book),
      m_bestScore(),
      m_worstScore() {
    initialize();
}

void ResultPrinter::print() {
    NextMoves calculatedMoves(getNextMovesFromCalculation());
    BookMoves bookMoves(getNextMovesFromBook());
    MovesSequence bestMoveLine(getMovesSequenceFromBestLine());
    MovesSequence mostHumanMoveLine{};
    if (!calculatedMoves.empty()) {
        // calculatedMoves is sorted in most human order (so we get the first one)
        mostHumanMoveLine = getMovesSequenceFromNextMove(calculatedMoves.front());
    }
    printCalculationDetails(calculatedMoves, bestMoveLine);
    printMovesGrids(bookMoves, mostHumanMoveLine, calculatedMoves, bestMoveLine);
    cout << "\n\n";
    cout.flush();
}

void ResultPrinter::initialize() { saveBestAndWorstScores(); }

void ResultPrinter::saveBestAndWorstScores() {
    Variations const& variations(m_calculationDetails.variations);
    if (!variations.empty()) {        auto itPair = minmax_element(
            variations.cbegin(), variations.cend(), [](Variation const& variation1, Variation const& variation2) {
                return variation1.scoreInCentipawns < variation2.scoreInCentipawns;
            });        m_bestScore = itPair.second->scoreInCentipawns;
        m_worstScore = itPair.first->scoreInCentipawns;
    }
}

ResultPrinter::BookMoves ResultPrinter::getNextMovesFromBook() const {
    BookMoves result;
    includeBookMoves(result);
    return result;
}

void ResultPrinter::includeBookMoves(BookMoves& bookMoves) const {
    auto lineDetailOptional = m_book.getLine(m_engineBoardWithContext.getBoard());
    if (lineDetailOptional && lineDetailOptional.value().colorToMove == m_engineBoardWithContext.getPlayerColor()) {
        Book::LineDetail const& lineDetail(lineDetailOptional.value());
        Board const& engineBoard(m_engineBoardWithContext.getBoard());
        for (Book::MoveDetail const& bookMoveDetail : lineDetail.nextMoves) {
            Move move(engineBoard.getMoveUsingAlgebraicNotation(
                bookMoveDetail.move, m_engineBoardWithContext.getPlayerColor()));
            bookMoves.emplace_back(createBookMove(move, lineDetail, bookMoveDetail));
            if (bookMoves.size() > MAX_NUMBER_OF_BOOK_MOVES) {
                break;
            }
        };
    }
}

ResultPrinter::BookMove ResultPrinter::createBookMove(
    Move const& move, Book::LineDetail const& lineDetail, Book::MoveDetail const& bookMoveDetail) const {
    PieceColor playerColor = m_engineBoardWithContext.getPlayerColor();
    int winningPercentage = PieceColor::White == playerColor   ? bookMoveDetail.whiteWinPercentage
                            : PieceColor::Black == playerColor ? bookMoveDetail.blackWinPercentage
                                                               : 0;
    return BookMove{move, getNameOfBookMove(move, lineDetail), winningPercentage};
}

string ResultPrinter::getNameOfBookMove(Move const& move, Book::LineDetail const& lineDetail) const {
    string result;
    Board nextBoard(m_engineBoardWithContext.getBoard());
    nextBoard.move(move);
    auto lineDetailOptional = m_book.getLine(nextBoard);
    if (lineDetailOptional) {
        result = lineDetailOptional.value().nameOfLine;
    }
    if (result.empty()) {
        result = lineDetail.nameOfLine;
    }
    return result;
}

ResultPrinter::NextMoves ResultPrinter::getNextMovesFromCalculation() const {
    NextMoves result;
    includeNextMovesFromCalculation(result);
    sortForMoreHumanMoves(result);
    removeTooManyPawnMoves(result);
    return result;
}

void ResultPrinter::includeNextMovesFromCalculation(NextMoves& nextMoves) const {
    HumanScoreGenerator scorer(m_engineBoardWithContext, m_bestScore, m_worstScore);
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    for (Variation const& variation : m_calculationDetails.variations) {
        if (!variation.halfMoves.empty()) {
            Move move(engineBoard.getMoveUsingUciNotation(variation.halfMoves.front()));
            if (engineBoard.isAPossibleMove(move)) {
                nextMoves.emplace_back(createNextMove(move, variation, scorer));
                if (nextMoves.size() > MAX_NUMBER_OF_MOVES_IN_TEXT) {
                    break;
                }
            }
        }
    }
}

void ResultPrinter::sortForMoreHumanMoves(NextMoves& nextMoves) const {
    if (!nextMoves.empty()) {
        stable_sort(nextMoves.begin(), nextMoves.end(), [&](NextMove const& detail1, NextMove const& detail2) {
            return detail1.humanScore > detail2.humanScore;
        });
    }
}

void ResultPrinter::removeTooManyPawnMoves(NextMoves& nextMoves) const {
    constexpr int MAX_NUMBER_OF_PAWN_MOVES = 2;
    int numberOfPawnMoves = 0;
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    auto pastEndIt =
        remove_if(nextMoves.begin(), nextMoves.end(), [&numberOfPawnMoves, &engineBoard](NextMove const& moveDetail) {
            Move const& move(moveDetail.move);
            if (PieceType::Pawn == engineBoard.getPieceAt(move.first).getType()) {
                if (numberOfPawnMoves < MAX_NUMBER_OF_PAWN_MOVES) {
                    numberOfPawnMoves++;
                } else {
                    return true;
                }
            }
            return false;
        });
    nextMoves.erase(pastEndIt, nextMoves.cend());
}

ResultPrinter::NextMove ResultPrinter::createNextMove(
    Move const& move, Variation const& variation, HumanScoreGenerator const& scorer) const {
    return NextMove{
        move, variation.halfMoves.front(), variation.scoreInCentipawns, variation.mateValue,
        scorer.getHumanScore({move, variation.scoreInCentipawns, variation.mateValue})};
}

ResultPrinter::MovesSequence ResultPrinter::getMovesSequenceFromNextMove(NextMove const& nextMove) const {
    MovesSequence result{};
    auto itVariation = find_if(
        m_calculationDetails.variations.cbegin(), m_calculationDetails.variations.cend(),
        [&](Variation const& variation) {
            return !variation.halfMoves.empty() && variation.halfMoves.front() == nextMove.moveString;
        });
    if (itVariation != m_calculationDetails.variations.cend()) {
        includeMovesSequenceFromVariation(result, *itVariation);
    }
    return result;
}

ResultPrinter::MovesSequence ResultPrinter::getMovesSequenceFromBestLine() const {
    MovesSequence result{};
    if (!m_calculationDetails.variations.empty()) {
        Variation const& bestVariation(m_calculationDetails.variations.front());
        includeMovesSequenceFromVariation(result, bestVariation);
    }
    return result;
}

void ResultPrinter::includeMovesSequenceFromVariation(MovesSequence& result, Variation const& variation) const {
    result.engineScore = variation.scoreInCentipawns;
    result.mateValue = variation.mateValue;
    Board updatedBoard(m_engineBoardWithContext.getBoard());
    PieceColor previousColor{};
    int index = 0;
    for (string const& halfMoves : variation.halfMoves) {
        Move move(updatedBoard.getMoveUsingUciNotation(halfMoves));
        if (updatedBoard.isAPossibleMove(move)) {
            Piece piece = updatedBoard.getPieceAt(move.first);
            if (index == 0 || areOpposingColors(previousColor, piece.getColor())) {
                result.halfMoves.emplace_back(move);
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

void ResultPrinter::printCalculationDetails(NextMoves const& nextMoves, MovesSequence const& movesSequence) const {
    Board const& engineBoard(m_engineBoardWithContext.getBoard());

    cout << "Player: " << m_engineBoardWithContext.getPlayerColor() << ", Depth: " << m_calculationDetails.depthInPlies
         << "\n";
    cout << "Current moves: ";
    for (NextMove const& moveDetail : nextMoves) {
        cout << engineBoard.getReadableStringOfMove(moveDetail.move) << " [" << getDisplayableString(moveDetail, 0)
             << "], ";
    }
    cout << "\n";

    Board updatedBoard(engineBoard);
    cout << "Monitored variation: ";
    for (Move const& halfMove : movesSequence.halfMoves) {
        Piece piece = updatedBoard.getPieceAt(halfMove.first);
        cout << updatedBoard.getReadableStringOfMove(halfMove);
        cout << " by " << piece.getColor() << ", ";
        updatedBoard.move(halfMove);
    }
    cout << "\n";

    if (!m_calculationDetails.bestMove.empty()) {
        cout << "Best move: "
             << engineBoard.getReadableStringOfMove(engineBoard.getMoveUsingUciNotation(m_calculationDetails.bestMove))
             << "\n";
    }

    if (!s_nameOfLine.empty()) {
        cout << "\n";
        cout << "Name of line: [" << s_nameOfLine << "]\n";
    }
    cout << "\n";
}

void ResultPrinter::printMovesGrids(
    BookMoves const& bookMoves, MovesSequence const& mostHumanMoveLine, NextMoves const& calculatedMoves,
    MovesSequence const& bestMoveLine) const {
    // top row
    if (!bookMoves.empty()) {
        printHorizontalBorderLine();
        printNextMovesHeader(bookMoves, 0);
        printHorizontalBorderLine();
        printARowOfNextMoves(bookMoves, 0);
    } else if (!mostHumanMoveLine.halfMoves.empty()) {
        printHorizontalBorderLine();
        printMovesSequenceHeader(mostHumanMoveLine);
        printHorizontalBorderLine();
        printARowOfMovesSequence(mostHumanMoveLine);
    }

    // middle row
    if (!calculatedMoves.empty()) {
        printHorizontalBorderLine();
        printNextMovesHeader(calculatedMoves, 0);
        printHorizontalBorderLine();
        printARowOfNextMoves(calculatedMoves, 0);
    }

    // bottom row
    if (!bestMoveLine.halfMoves.empty()) {
        printHorizontalBorderLine();
        printMovesSequenceHeader(bestMoveLine);
        printHorizontalBorderLine();
        printARowOfMovesSequence(bestMoveLine);
        printHorizontalBorderLine();
    }
}

template <typename GenericMoves>
void ResultPrinter::printARowOfNextMoves(GenericMoves const& genericMoves, unsigned int const startIndex) const {
    constexpr unsigned int numberOfBoardDisplayRows = 8U;
    if (startIndex < genericMoves.size()) {
        unsigned int rowSize =
            min(MAX_NUMBER_OF_MOVES_IN_GRID, static_cast<unsigned int>(genericMoves.size() - startIndex));
        unsigned int numberOfBoardDisplayColumns = getNumberOfColumnsOfGrid(rowSize);
        DisplayTable grid(numberOfBoardDisplayColumns, numberOfBoardDisplayRows);
        grid.setVerticalBorder("|");        setSeparatorsOnGrid(grid, NEXT_OFFSET_OF_GRID);
        Board const& engineBoard(m_engineBoardWithContext.getBoard());
        for (unsigned int xOffset = 0; xOffset < numberOfBoardDisplayColumns; xOffset += NEXT_OFFSET_OF_GRID) {
            setBoardOnGrid(grid, engineBoard, xOffset);
        }
        setNextMovesOnGrid(grid, genericMoves, startIndex, rowSize);
        cout << grid;
    }
}

template <typename GenericMoves>
void ResultPrinter::setNextMovesOnGrid(
    DisplayTable& grid, GenericMoves const& genericMoves, unsigned int const startIndex,
    unsigned int const rowSize) const {
    unsigned int xOffset = 0U;
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    for (unsigned int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
        Move const& nextMove(genericMoves.at(startIndex + moveIndex).move);
        setMoveOnGrid(grid, engineBoard, nextMove, xOffset, 1U, optional<char>());
        xOffset += NEXT_OFFSET_OF_GRID;
    }
}

template <typename GenericMoves>
void ResultPrinter::printNextMovesHeader(GenericMoves const& genericMoves, unsigned int const startIndex) const {
    if (startIndex < genericMoves.size()) {
        unsigned int rowSize =
            min(MAX_NUMBER_OF_MOVES_IN_GRID, static_cast<unsigned int>(genericMoves.size() - startIndex));
        bool isFirst = true;
        for (unsigned int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
            if (isFirst) {
                isFirst = false;
            } else {
                cout << SEPARATOR;
            }
            auto const& genericMove(genericMoves.at(startIndex + moveIndex));
            cout << "|" << getDisplayableString(genericMove, DESIRED_HEADER_LENGTH) << "|";
        }
        cout << "\n";
    }
}

void ResultPrinter::printARowOfMovesSequence(MovesSequence const& movesSequence) const {
    constexpr unsigned int numberOfRows = 8U;
    unsigned int rowSize =
        min(MAX_NUMBER_OF_MOVES_IN_GRID, static_cast<unsigned int>((movesSequence.halfMoves.size() + 1U) / 2U));
    unsigned int numberOfColumns = getNumberOfColumnsOfGrid(rowSize);

    DisplayTable grid(numberOfColumns, numberOfRows);
    grid.setVerticalBorder("|");
    setSeparatorsOnGrid(grid, NEXT_OFFSET_OF_GRID);
    setMovesSequenceOnGrid(grid, movesSequence, rowSize);
    cout << grid;
}

void ResultPrinter::setMovesSequenceOnGrid(
    DisplayTable& grid, MovesSequence const& movesSequence, unsigned int const rowSize) const {
    SequenceOfMovesAnalyzer analyzer(m_engineBoardWithContext);
    Board const& analyzerBoard(analyzer.getCurrentBoard());
    unsigned int movesDisplayed = 0U;
    unsigned int xOffset = 0U;
    bool isUnSurePreMove = false;

    for (Move const& halfMove : movesSequence.halfMoves) {
        analyzer.analyzeMove(halfMove);
        if (analyzer.getCurrentMoveColor() == m_engineBoardWithContext.getPlayerColor()) {
            optional<char> firstChar = getFirstCharOfCell(analyzer.canPreMove(), isUnSurePreMove);

            setBoardOnGrid(grid, analyzerBoard, xOffset);
            setMoveOnGrid(grid, analyzerBoard, halfMove, xOffset, movesDisplayed + 1, firstChar);

            xOffset += NEXT_OFFSET_OF_GRID;
            movesDisplayed++;            if (movesDisplayed >= rowSize) {
                break;
            }
        }        analyzer.commitMove();
    }
}

void ResultPrinter::printMovesSequenceHeader(MovesSequence const& movesSequence) const {
    cout << "|" << getMovesSequenceFirstMoveHeader(movesSequence.engineScore, movesSequence.mateValue);
    cout << "|     |           2nd move            |     |           3rd move            "
            "|     |           4th move            |     |           5th move            |\n";
}
void ResultPrinter::printHorizontalBorderLine() const {
    cout << "----------------------------------------------------------------------------------------------------------"
            "-------------------------------------------------------------------------------\n";}

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

string ResultPrinter::getDisplayableString(NextMove const& nextMove, int const desiredLength) const {
    stringstream ss;
    if (nextMove.mateValue == 0) {
        // ss << hex << uppercase << nextMove.humanScore << dec; // for debugging
        ss << static_cast<double>(nextMove.engineScore) / 100;
    } else {
        ss << "Mate: " << nextMove.mateValue;
    }
    return getStringWithCenterAlignment(ss.str(), desiredLength);
}

string ResultPrinter::getDisplayableString(BookMove const& bookMove, int const desiredLength) const {
    stringstream ss;
    ss << "(" << bookMove.winningPercentageInBook << "%) " << bookMove.nameOfLineInBook;
    return getStringWithCenterAlignment(ss.str(), desiredLength).substr(0, desiredLength);
}

string ResultPrinter::getMovesSequenceFirstMoveHeader(int const score, int const mate) const {
    stringstream ss;
    if (mate == 0) {
        ss << static_cast<double>(score) / 100;
    } else {
        ss << "Mate: " << mate;
    }
    ss << " -> 1st move";
    return getStringWithCenterAlignment(ss.str(), DESIRED_HEADER_LENGTH);
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
    result[1] = piece.getFenCharacter();
    return result;
}
optional<char> ResultPrinter::getFirstCharOfCell(bool const isSurePreMove, bool isUnsurePreMove) const {
    optional<char> result;
    if (isSurePreMove) {        result = '*';
    } else if (isUnsurePreMove) {
        result = '~';
    }
    return result;
}

unsigned int ResultPrinter::getNumberOfColumnsOfGrid(unsigned int const numberOfBoards) const {
    return numberOfBoards == 0 ? 0U : numberOfBoards * 8U + numberOfBoards - 1;
}

void ResultPrinter::saveNameOfLine(string const& nameOfLine) {
    if (!nameOfLine.empty()) {
        s_nameOfLine = nameOfLine;
    }
}

}  // namespace ChessPeek

}  // namespace chess
}  // namespace alba