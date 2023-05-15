#include "ResultPrinter.hpp"

#include <ChessPeek/SequenceOfMovesAnalyzer.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/StreamOperators.hpp>

#include <iomanip>
#include <iostream>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr int MAX_NUMBER_OF_MOVES_FOR_PRINTING = 10;
constexpr int MAX_NUMBER_OF_BOOK_MOVES = 5;
constexpr int MAX_NUMBER_OF_MOVES_IN_A_ROW = 5;
constexpr int NEXT_OFFSET_OF_GRID = 9;
constexpr int DESIRED_HEADER_LENGTH = 31;
constexpr char SEPARATOR[] = "     ";

static string s_nameOfLine;

void saveNameOfLine(string const& nameOfLine) {
    if (!nameOfLine.empty()) {
        s_nameOfLine = nameOfLine;
    }
}

}  // namespace

namespace alba {

namespace chess {

namespace ChessPeek {

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
    MovesToPrint movesToPrint;
    movesToPrint.bookMoves = getNextMovesFromBook();
    movesToPrint.calculatedMoves = getNextMovesFromCalculation();
    movesToPrint.mostHumanMoves = movesToPrint.calculatedMoves;
    humanizeMoves(movesToPrint.mostHumanMoves);
    movesToPrint.bestLine = getMovesSequenceFromBestLine();

    if (!movesToPrint.mostHumanMoves.empty()) {
        movesToPrint.mostHumanLine = getMovesSequenceFromNextMove(movesToPrint.mostHumanMoves.front());
    }

    printCalculationDetails(movesToPrint);
    printMovesGrids(movesToPrint);
    cout << "\n\n";
    cout.flush();
}

void ResultPrinter::initialize() { saveBestAndWorstScores(); }

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

ResultPrinter::BookMoves ResultPrinter::getNextMovesFromBook() const {
    BookMoves result;
    includeBookMoves(result);
    return result;
}

void ResultPrinter::includeBookMoves(BookMoves& bookMoves) const {
    auto lineDetailOptional = m_book.getLine(m_engineBoardWithContext.getBoard());
    if (lineDetailOptional && lineDetailOptional.value().colorToMove == m_engineBoardWithContext.getPlayerColor()) {
        Book::LineDetail const& lineDetail(lineDetailOptional.value());
        saveNameOfLine(lineDetail.nameOfLine);
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
    return BookMove{move, getNameOfBookMove(move, lineDetail), bookMoveDetail.winPercentage};
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
                if (nextMoves.size() > MAX_NUMBER_OF_MOVES_FOR_PRINTING) {
                    break;
                }
            }
        }
    }
}

void ResultPrinter::humanizeMoves(NextMoves& nextMoves) const {
    sortForMoreHumanMoves(nextMoves);
    removeTooManyPawnMoves(nextMoves);
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

void ResultPrinter::printCalculationDetails(MovesToPrint const& movesToPrint) const {
    Board const& engineBoard(m_engineBoardWithContext.getBoard());

    cout << "Player: " << m_engineBoardWithContext.getPlayerColor() << ", Depth: " << m_calculationDetails.depthInPlies
         << "\n";
    cout << "Calculated moves: ";
    for (NextMove const& moveDetail : movesToPrint.calculatedMoves) {
        cout << engineBoard.getReadableStringOfMove(moveDetail.move) << " [" << getDisplayableString(moveDetail)
             << "], ";
    }
    cout << "\n";

    Board updatedBoard(engineBoard);
    cout << "Best variation: ";
    for (Move const& halfMove : movesToPrint.bestLine.halfMoves) {
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

void ResultPrinter::printMovesGrids(MovesToPrint const& movesToPrint) const {
    bool isSomethingPrinted(false);
    if (!movesToPrint.mostHumanLine.halfMoves.empty()) {
        printHorizontalBorderLine();
        printHeadersForMostHumanLine(movesToPrint.mostHumanLine);
        printHorizontalBorderLine();
        printARowOfMovesSequence(movesToPrint.mostHumanLine);
        isSomethingPrinted = true;
    }

    if (!movesToPrint.mostHumanMoves.empty()) {
        printHorizontalBorderLine();
        printHeadersForMostHumanMoves(movesToPrint.mostHumanMoves, 0);
        printHorizontalBorderLine();
        printARowOfNextMoves(movesToPrint.mostHumanMoves, 0);
        isSomethingPrinted = true;
    }

    if (!movesToPrint.bookMoves.empty()) {
        printHorizontalBorderLine();
        printHeadersForBookMoves(movesToPrint.bookMoves);
        printHorizontalBorderLine();
        printARowOfNextMoves(movesToPrint.bookMoves, 0);
        isSomethingPrinted = true;
    } else if (!movesToPrint.bestLine.halfMoves.empty()) {
        printHorizontalBorderLine();
        printHeadersForBestLine(movesToPrint.bestLine);
        printHorizontalBorderLine();
        printARowOfMovesSequence(movesToPrint.bestLine);
        isSomethingPrinted = true;
    }

    if (isSomethingPrinted) {
        printHorizontalBorderLine();
    }

    /*if (movesToPrint.calculatedMoves.size() > 3) {
        printHorizontalBorderLine();
        printHeadersFor4thTo8thBestMoves(movesToPrint.calculatedMoves, 3);
        printHorizontalBorderLine();
        printARowOfNextMoves(movesToPrint.calculatedMoves, 3);
        printHorizontalBorderLine();
    }*/
}

template <typename GenericMoves>
void ResultPrinter::printARowOfNextMoves(GenericMoves const& genericMoves, int const startIndex) const {
    if (startIndex < static_cast<int>(genericMoves.size())) {
        int rowSize = getRowSizeForFullMoves(static_cast<int>(genericMoves.size()) - startIndex);
        int numberOfBoardDisplayColumns = getNumberOfColumnsOfGrid(rowSize);
        DisplayTable grid(numberOfBoardDisplayColumns, Board::CHESS_SIDE_SIZE);
        grid.setVerticalBorder("|");
        setSeparatorsOnGrid(grid, NEXT_OFFSET_OF_GRID);
        Board const& engineBoard(m_engineBoardWithContext.getBoard());
        for (int xOffset = 0; xOffset < numberOfBoardDisplayColumns; xOffset += NEXT_OFFSET_OF_GRID) {
            setBoardOnGrid(grid, engineBoard, xOffset);
        }
        setNextMovesOnGrid(grid, genericMoves, startIndex, rowSize);
        cout << grid;
    }
}

template <typename GenericMoves>
void ResultPrinter::setNextMovesOnGrid(
    DisplayTable& grid, GenericMoves const& genericMoves, int const startIndex, int const rowSize) const {
    int xOffset = 0;
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    for (int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
        Move const& nextMove(genericMoves.at(startIndex + moveIndex).move);
        setMoveOnGrid(grid, engineBoard, nextMove, xOffset, 1, optional<char>());
        xOffset += NEXT_OFFSET_OF_GRID;
    }
}

void ResultPrinter::printARowOfMovesSequence(MovesSequence const& movesSequence) const {
    int rowSize = getRowSizeForHalfMoves(movesSequence.halfMoves.size());
    int numberOfColumns = getNumberOfColumnsOfGrid(rowSize);
    DisplayTable grid(numberOfColumns, Board::CHESS_SIDE_SIZE);
    grid.setVerticalBorder("|");
    setSeparatorsOnGrid(grid, NEXT_OFFSET_OF_GRID);
    setMovesSequenceOnGrid(grid, movesSequence, Board::CHESS_SIDE_SIZE);
    cout << grid;
}

void ResultPrinter::setMovesSequenceOnGrid(
    DisplayTable& grid, MovesSequence const& movesSequence, int const rowSize) const {
    SequenceOfMovesAnalyzer analyzer(m_engineBoardWithContext);
    Board const& analyzerBoard(analyzer.getCurrentBoard());
    int numberOfBoardDisplayColumns = static_cast<int>(grid.getTotalColumns());
    int movesDisplayed = 0;
    int xOffset = 0;
    bool isUnSurePreMove = false;

    for (Move const& halfMove : movesSequence.halfMoves) {
        if (xOffset < numberOfBoardDisplayColumns) {
            analyzer.analyzeMove(halfMove);
            if (analyzer.getCurrentMoveColor() == m_engineBoardWithContext.getPlayerColor()) {
                optional<char> firstChar = getFirstCharOfABoardCell(analyzer.canPreMove(), isUnSurePreMove);

                setBoardOnGrid(grid, analyzerBoard, xOffset);
                setMoveOnGrid(grid, analyzerBoard, halfMove, xOffset, movesDisplayed + 1, firstChar);

                xOffset += NEXT_OFFSET_OF_GRID;
                movesDisplayed++;
                if (movesDisplayed >= rowSize) {
                    break;
                }
            }
            analyzer.commitMove();
        } else {
            break;
        }
    }
}

void ResultPrinter::printHeadersForMostHumanMoves(NextMoves const& nextMoves, int const startIndex) const {
    int rowSize = getRowSizeForFullMoves(static_cast<int>(nextMoves.size()) - startIndex);
    strings prefixes = getNextMovesString(nextMoves, startIndex);
    strings suffixes{
        " -> 1st most human move", " -> 2nd most human move", " -> 3rd most human move", " -> 4th most human move",
        " -> 5th most human move"};
    prefixes.resize(min(static_cast<int>(prefixes.size()), rowSize));
    suffixes.resize(min(static_cast<int>(suffixes.size()), rowSize));
    printHeaders(prefixes, suffixes);
}

void ResultPrinter::printHeadersFor4thTo8thBestMoves(NextMoves const& nextMoves, int const startIndex) const {
    int rowSize = getRowSizeForFullMoves(static_cast<int>(nextMoves.size()) - startIndex);
    strings prefixes = getNextMovesString(nextMoves, startIndex);
    strings suffixes{
        " -> 4th best move", " -> 5th best move", " -> 6th best move", " -> 7th best move", " -> 8th best move"};
    prefixes.resize(min(static_cast<int>(prefixes.size()), rowSize));
    suffixes.resize(min(static_cast<int>(suffixes.size()), rowSize));
    printHeaders(prefixes, suffixes);
}

void ResultPrinter::printHeadersForBookMoves(BookMoves const& bookMoves) const {
    strings prefixes = getBookMovesString(bookMoves);
    strings suffixes;
    printHeaders(prefixes, suffixes);
}

void ResultPrinter::printHeadersForBestLine(MovesSequence const& movesSequence) const {
    int rowSize = getRowSizeForHalfMoves(movesSequence.halfMoves.size());
    strings prefixes{getDisplayableString(movesSequence)};
    strings suffixes{
        " -> best line move 1", "best line move 2", "best line move 3", "best line move 4", "best line move 5"};
    prefixes.resize(min(static_cast<int>(prefixes.size()), rowSize));
    suffixes.resize(min(static_cast<int>(suffixes.size()), rowSize));
    printHeaders(prefixes, suffixes);
}

void ResultPrinter::printHeadersForMostHumanLine(MovesSequence const& movesSequence) const {
    int rowSize = getRowSizeForHalfMoves(movesSequence.halfMoves.size());
    strings prefixes{getDisplayableString(movesSequence)};
    strings suffixes{
        " -> most human line move 1", "most human line move 2", "most human line move 3", "most human line move 4",
        "most human line move 5"};
    prefixes.resize(min(static_cast<int>(prefixes.size()), rowSize));
    suffixes.resize(min(static_cast<int>(suffixes.size()), rowSize));
    printHeaders(prefixes, suffixes);
}

void ResultPrinter::printHeaders(strings const& prefixes, strings const& suffixes) const {
    if (!prefixes.empty() || !suffixes.empty()) {
        int rowSize = static_cast<int>(max(prefixes.size(), suffixes.size()));
        bool isFirst = true;
        for (int i = 0; i < rowSize; i++) {
            if (isFirst) {
                isFirst = false;
            } else {
                cout << SEPARATOR;
            }
            string headerString;
            if (i < static_cast<int>(prefixes.size())) {
                headerString += prefixes.at(i);
            }
            if (i < static_cast<int>(suffixes.size())) {
                headerString += suffixes.at(i);
            }
            cout << "|" << formatToHeaderString(headerString) << "|";
        }
        cout << "\n";
    }
}

void ResultPrinter::printHorizontalBorderLine() const {
    cout << "----------------------------------------------------------------------------------------------------------"
            "-------------------------------------------------------------------------------\n";
}

void ResultPrinter::setSeparatorsOnGrid(DisplayTable& grid, int const xOffset) const {
    int const numberOfColumns = grid.getTotalColumns(), numberOfRows = grid.getTotalRows();
    for (int j = 0; j < numberOfRows; j++) {
        for (int separatorIndex = xOffset - 1; separatorIndex < numberOfColumns; separatorIndex += xOffset) {
            grid.getCellReferenceAt(separatorIndex, j).setText(SEPARATOR);
        }
    }
}

void ResultPrinter::setBoardOnGrid(DisplayTable& grid, Board const& board, int const xOffset) const {
    for (CoordinateDataType y = 0; y < Board::CHESS_SIDE_SIZE; y++) {
        for (CoordinateDataType x = 0; x < Board::CHESS_SIDE_SIZE; x++) {
            Piece piece(board.getPieceAt(Coordinate(x, y)));
            grid.getCellReferenceAt(x + xOffset, y)
                .setText(getDisplayableStringForABoardCell(piece, 0, optional<char>()));
        }
    }
}

void ResultPrinter::setMoveOnGrid(
    DisplayTable& grid, Board const& board, Move const& move, int const xOffset, int const moveNumber,
    optional<char> const& firstChar) const {
    Piece piece(board.getPieceAt(move.first));
    grid.getCellReferenceAt(move.first.getX() + xOffset, move.first.getY())
        .setText(getDisplayableStringForABoardCell(piece, moveNumber, firstChar));
    grid.getCellReferenceAt(move.second.getX() + xOffset, move.second.getY())
        .setText(getDisplayableStringForABoardCell(piece, moveNumber + 1, firstChar));
}

string ResultPrinter::getDisplayableString(NextMove const& nextMove) const {
    return getDisplayableString(nextMove.engineScore, nextMove.mateValue);
}

string ResultPrinter::getDisplayableString(BookMove const& bookMove) const {
    stringstream ss;
    ss << "(" << bookMove.winningPercentageInBook << "%) " << bookMove.nameOfLineInBook;
    return ss.str();
}

strings ResultPrinter::getNextMovesString(NextMoves const& nextMoves, int const startIndex) const {
    strings result;
    if (startIndex < static_cast<int>(nextMoves.size())) {
        int rowSize = min(MAX_NUMBER_OF_MOVES_IN_A_ROW, static_cast<int>(nextMoves.size() - startIndex));
        for (int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
            auto const& nextMove(nextMoves.at(startIndex + moveIndex));
            result.emplace_back(formatToHeaderString(getDisplayableString(nextMove)));
        }
    }
    return result;
}

strings ResultPrinter::getBookMovesString(BookMoves const& bookMoves) const {
    strings result;
    int rowSize = min(MAX_NUMBER_OF_MOVES_IN_A_ROW, static_cast<int>(bookMoves.size()));
    for (int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
        auto const& bookMove(bookMoves.at(moveIndex));
        result.emplace_back(formatToHeaderString(getDisplayableString(bookMove)));
    }
    return result;
}

string ResultPrinter::getDisplayableString(MovesSequence const& movesSequence) const {
    return getDisplayableString(movesSequence.engineScore, movesSequence.mateValue);
}

string ResultPrinter::getDisplayableString(int const score, int const mateValue) const {
    stringstream ss;
    if (mateValue == 0) {
        // ss << hex << uppercase << nextMove.humanScore << dec;  // for debugging
        ss << fixed << setprecision(2) << setfill('0') << static_cast<double>(score) / 100;
    } else {
        ss << "Mate: " << mateValue;
    }
    return ss.str();
}

string ResultPrinter::formatToHeaderString(string const& content) const {
    return getStringWithCenterAlignment(content, DESIRED_HEADER_LENGTH).substr(0, DESIRED_HEADER_LENGTH);
}

string ResultPrinter::getDisplayableStringForABoardCell(
    Piece const& piece, int const moveNumber, optional<char> const& firstChar) const {
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
    result[1] = piece.getFenCharacter();
    return result;
}

optional<char> ResultPrinter::getFirstCharOfABoardCell(bool const isSurePreMove, bool isUnsurePreMove) const {
    optional<char> result;
    if (isSurePreMove) {
        result = '*';
    } else if (isUnsurePreMove) {
        result = '~';
    }
    return result;
}

int ResultPrinter::getNumberOfColumnsOfGrid(int const numberOfBoards) const {
    return numberOfBoards == 0 ? 0 : (numberOfBoards * Board::CHESS_SIDE_SIZE) + numberOfBoards - 1;
}

int ResultPrinter::getRowSizeForHalfMoves(int const numberOfHalfMoves) const {
    return min(MAX_NUMBER_OF_MOVES_IN_A_ROW, static_cast<int>((numberOfHalfMoves + 1) / 2));
}

int ResultPrinter::getRowSizeForFullMoves(int const numberOfFullMoves) const {
    return min(MAX_NUMBER_OF_MOVES_IN_A_ROW, static_cast<int>(numberOfFullMoves));
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
