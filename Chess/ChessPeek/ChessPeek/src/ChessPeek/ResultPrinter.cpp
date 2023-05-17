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
constexpr int MAX_NUMBER_OF_BOARDS_IN_A_ROW = 3;  // make it 2 if bullet (for less boards and quicker responses)
constexpr int NEXT_OFFSET_OF_GRID = 9;
constexpr int DESIRED_HEADER_LENGTH = 31;
constexpr char SEPARATOR[] = "     ";

static string s_nameOfLine;

}  // namespace

namespace alba {
namespace chess {

namespace ChessPeek {

ResultPrinter::ResultPrinter(
    CalculationDetails const& calculationDetails, BoardWithContext const& engineBoard, Book const& book)
    : m_calculationDetails(calculationDetails),
      m_engineBoardWithContext(engineBoard),
      m_book(book),
      m_worstAndBestScorePair(getBestAndWorstScores(m_calculationDetails.variations)),
      m_humanScoreGenerator(m_engineBoardWithContext, m_worstAndBestScorePair.first, m_worstAndBestScorePair.second),
      m_horizontalBorder(getHorizontalBorderSize(MAX_NUMBER_OF_BOARDS_IN_A_ROW), '-') {}

void ResultPrinter::print() {
    MovesToPrint movesToPrint;
    movesToPrint.bookMoves = getMovesFromBook();
    movesToPrint.calculatedMoves = getNextMovesFromCalculation();
    movesToPrint.mostHumanMoves = movesToPrint.calculatedMoves;
    humanizeMoves(movesToPrint.mostHumanMoves);

    if (!m_calculationDetails.variations.empty()) {
        Variation const& bestVariation(m_calculationDetails.variations.front());
        if (!bestVariation.halfMoves.empty()) {
            movesToPrint.bestLine = getMovesSequenceFromMoveString(bestVariation.halfMoves.front());
        }
    }

    if (!movesToPrint.mostHumanMoves.empty()) {
        movesToPrint.mostHumanLine = getMovesSequenceFromMoveString(movesToPrint.mostHumanMoves.front().moveString);
    }

    printCalculationDetails(movesToPrint);
    printMovesGrids(movesToPrint);
    cout << "\n\n";
    cout.flush();
}

void ResultPrinter::printCalculationDetails(MovesToPrint const& movesToPrint) const {
    Board const& engineBoard(m_engineBoardWithContext.getBoard());

    cout << "Player: " << m_engineBoardWithContext.getPlayerColor() << ", Depth: " << m_calculationDetails.depthInPlies
         << "\n";
    cout << "Calculated moves: ";
    for (NextMove const& nextMove : movesToPrint.calculatedMoves) {
        cout << engineBoard.getReadableStringOfMove(nextMove.move) << " ["
             << getDisplayableString(nextMove.mateValue, nextMove.engineScore) << "], ";
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
    if (!movesToPrint.mostHumanLine.halfMoves.empty()) {
        printHeadersForMostHumanLine(movesToPrint.mostHumanLine);
        printARowOfMovesSequence(movesToPrint.mostHumanLine);
    }

    if (!movesToPrint.mostHumanMoves.empty()) {
        printHeadersFor2ndTo6thMostHumanMoves(movesToPrint.mostHumanMoves);
        printARowOfNextMoves(movesToPrint.mostHumanMoves, 1);
    }

    if (!movesToPrint.bookMoves.empty()) {
        printHeadersForBookMoves(movesToPrint.bookMoves);
        printARowOfNextMoves(movesToPrint.bookMoves, 0);
        printHorizontalBorder();
    } else if (!movesToPrint.bestLine.halfMoves.empty()) {
        printHeadersForBestLine(movesToPrint.bestLine);
        printARowOfMovesSequence(movesToPrint.bestLine);
        printHorizontalBorder();
    }
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

void ResultPrinter::printHeadersFor2ndTo6thMostHumanMoves(NextMoves const& nextMoves) const {
    int rowSize = getRowSizeForFullMoves(static_cast<int>(nextMoves.size()) - 1);
    if (rowSize > 0) {
        strings prefixes = getNextMovesString(nextMoves, 1);
        strings suffixes{
            " -> 2nd most human move", " -> 3rd most human move", " -> 4th most human move", " -> 5th most human move",
            " -> 6th most human move"};
        prefixes.resize(min(static_cast<int>(prefixes.size()), rowSize));
        suffixes.resize(min(static_cast<int>(suffixes.size()), rowSize));
        printHorizontalBorder();
        printHeaders(prefixes, suffixes);
        printHorizontalBorder();
    }
}

void ResultPrinter::printHeadersFor4thTo8thBestMoves(NextMoves const& nextMoves, int const startIndex) const {
    int rowSize = getRowSizeForFullMoves(static_cast<int>(nextMoves.size()) - startIndex);
    if (rowSize > 0) {
        strings prefixes = getNextMovesString(nextMoves, startIndex);
        strings suffixes{
            " -> 4th best move", " -> 5th best move", " -> 6th best move", " -> 7th best move", " -> 8th best move"};
        prefixes.resize(min(static_cast<int>(prefixes.size()), rowSize));
        suffixes.resize(min(static_cast<int>(suffixes.size()), rowSize));
        printHorizontalBorder();
        printHeaders(prefixes, suffixes);
        printHorizontalBorder();
    }
}

void ResultPrinter::printHeadersForBookMoves(BookMoves const& bookMoves) const {
    strings prefixes = getBookMovesString(bookMoves);
    strings suffixes;
    printHorizontalBorder();
    printHeaders(prefixes, suffixes);
    printHorizontalBorder();
}

void ResultPrinter::printHeadersForBestLine(MovesSequence const& movesSequence) const {
    int rowSize = getRowSizeForHalfMoves(movesSequence.halfMoves.size());
    if (rowSize > 0) {
        strings prefixes{getDisplayableString(movesSequence)};
        strings suffixes{
            " -> best line move 1", "best line move 2", "best line move 3", "best line move 4", "best line move 5"};
        prefixes.resize(min(static_cast<int>(prefixes.size()), rowSize));
        suffixes.resize(min(static_cast<int>(suffixes.size()), rowSize));
        printHorizontalBorder();
        printHeaders(prefixes, suffixes);
        printHorizontalBorder();
    }
}

void ResultPrinter::printHeadersForMostHumanLine(MovesSequence const& movesSequence) const {
    int rowSize = getRowSizeForHalfMoves(movesSequence.halfMoves.size());
    if (rowSize > 0) {
        strings prefixes{getDisplayableString(movesSequence)};
        strings suffixes{
            " -> most human line move 1", "most human line move 2", "most human line move 3", "most human line move 4",
            "most human line move 5"};
        prefixes.resize(min(static_cast<int>(prefixes.size()), rowSize));
        suffixes.resize(min(static_cast<int>(suffixes.size()), rowSize));
        printHorizontalBorder();
        printHeaders(prefixes, suffixes);
        printHorizontalBorder();
    }
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

void ResultPrinter::printHorizontalBorder() const { cout << m_horizontalBorder << "\n"; }

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

ResultPrinter::BookMoves ResultPrinter::getMovesFromBook() const {
    BookMoves result;
    fillMovesFromBook(result);
    return result;
}

void ResultPrinter::fillMovesFromBook(BookMoves& bookMoves) const {
    auto lineDetailOptional = m_book.getLine(m_engineBoardWithContext.getBoard());
    if (lineDetailOptional && lineDetailOptional.value().colorToMove == m_engineBoardWithContext.getPlayerColor()) {
        Book::LineDetail const& lineDetail(lineDetailOptional.value());
        if (!lineDetail.nameOfLine.empty()) {
            s_nameOfLine = lineDetail.nameOfLine;
            Board const& engineBoard(m_engineBoardWithContext.getBoard());
            for (Book::MoveDetail const& bookMoveDetail : lineDetail.nextMoves) {
                Move move(engineBoard.getMoveUsingAlgebraicNotation(
                    bookMoveDetail.move, m_engineBoardWithContext.getPlayerColor()));
                bookMoves.emplace_back(createBookMove(move, lineDetail, bookMoveDetail));
                if (bookMoves.size() > MAX_NUMBER_OF_BOARDS_IN_A_ROW) {
                    break;
                }
            };
        }
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
    fillNextMovesFromCalculation(result);
    return result;
}

void ResultPrinter::fillNextMovesFromCalculation(NextMoves& nextMoves) const {
    Board const& engineBoard(m_engineBoardWithContext.getBoard());
    for (Variation const& variation : m_calculationDetails.variations) {
        if (!variation.halfMoves.empty()) {
            Move move(engineBoard.getMoveUsingUciNotation(variation.halfMoves.front()));
            if (engineBoard.isAPossibleMove(move)) {
                nextMoves.emplace_back(createNextMove(move, variation));
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

ResultPrinter::NextMove ResultPrinter::createNextMove(Move const& move, Variation const& variation) const {
    return NextMove{
        move, variation.halfMoves.front(), variation.mateValue, variation.scoreInCentipawns,
        m_humanScoreGenerator.getHumanScore({move, variation.mateValue, variation.scoreInCentipawns})};
}

ResultPrinter::MovesSequence ResultPrinter::getMovesSequenceFromMoveString(string const& moveString) const {
    MovesSequence result{};
    auto itVariation = find_if(
        m_calculationDetails.variations.cbegin(), m_calculationDetails.variations.cend(),
        [&](Variation const& variation) {
            return !variation.halfMoves.empty() && variation.halfMoves.front() == moveString;
        });
    if (itVariation != m_calculationDetails.variations.cend()) {
        fillMovesSequenceFromVariation(result, *itVariation);
    }
    return result;
}

void ResultPrinter::fillMovesSequenceFromVariation(MovesSequence& result, Variation const& variation) const {
    result.mateValue = variation.mateValue;
    result.engineScore = variation.scoreInCentipawns;
    if (!variation.halfMoves.empty()) {
        Move move(m_engineBoardWithContext.getBoard().getMoveUsingUciNotation(variation.halfMoves.front()));
        result.humanScore =
            m_humanScoreGenerator.getHumanScore({move, variation.mateValue, variation.scoreInCentipawns});
    }
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

strings ResultPrinter::getNextMovesString(NextMoves const& nextMoves, int const startIndex) const {
    strings result;
    if (startIndex < static_cast<int>(nextMoves.size())) {
        int rowSize = min(MAX_NUMBER_OF_BOARDS_IN_A_ROW, static_cast<int>(nextMoves.size() - startIndex));
        for (int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
            auto const& nextMove(nextMoves.at(startIndex + moveIndex));
            result.emplace_back(formatToHeaderString(getDisplayableString(nextMove)));
        }
    }
    return result;
}

strings ResultPrinter::getBookMovesString(BookMoves const& bookMoves) const {
    strings result;
    int rowSize = min(MAX_NUMBER_OF_BOARDS_IN_A_ROW, static_cast<int>(bookMoves.size()));
    for (int moveIndex = 0; moveIndex < rowSize; moveIndex++) {
        auto const& bookMove(bookMoves.at(moveIndex));
        result.emplace_back(formatToHeaderString(getDisplayableString(bookMove)));
    }
    return result;
}

string ResultPrinter::getDisplayableString(NextMove const& nextMove) const {
    return getDisplayableString(nextMove.mateValue, nextMove.engineScore, nextMove.humanScore);
}

string ResultPrinter::getDisplayableString(BookMove const& bookMove) const {
    stringstream ss;
    ss << "(" << bookMove.winningPercentageInBook << "%) " << bookMove.nameOfLineInBook;
    return ss.str();
}

string ResultPrinter::getDisplayableString(MovesSequence const& movesSequence) const {
    return getDisplayableString(movesSequence.mateValue, movesSequence.engineScore, movesSequence.humanScore);
}

string ResultPrinter::getDisplayableString(
    int const mateValue, int const engineScore, HumanScoreGenerator::Score const humanScore) const {
    stringstream ss;
    if (mateValue == 0) {
        ss << fixed << setprecision(2) << setfill('0') << static_cast<double>(engineScore) / 100;    } else {
        ss << "Mate: " << mateValue;
    }
    ss << " (" << hex << uppercase << humanScore << dec << ")";
    return ss.str();
}

string ResultPrinter::getDisplayableString(int const mateValue, int const engineScore) const {
    stringstream ss;
    if (mateValue == 0) {
        ss << fixed << setprecision(2) << setfill('0') << static_cast<double>(engineScore) / 100;
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

ResultPrinter::ScorePair ResultPrinter::getBestAndWorstScores(Variations const& variations) const {
    if (!variations.empty()) {
        auto itPair = minmax_element(
            variations.cbegin(), variations.cend(), [](Variation const& variation1, Variation const& variation2) {
                return variation1.scoreInCentipawns < variation2.scoreInCentipawns;
            });
        return ScorePair{itPair.first->scoreInCentipawns, itPair.second->scoreInCentipawns};
    }
    return {};
}

int ResultPrinter::getNumberOfColumnsOfGrid(int const numberOfBoards) const {
    return numberOfBoards <= 0 ? 0 : (numberOfBoards * Board::CHESS_SIDE_SIZE) + numberOfBoards - 1;
}

int ResultPrinter::getHorizontalBorderSize(int const numberOfBoards) const {
    constexpr int CELL_SIZE = 3;
    constexpr int BORDER_SIZE = 1;
    constexpr int SEPARATOR_SIZE = 5;
    return numberOfBoards <= 0 ? 0
                               : (numberOfBoards * Board::CHESS_SIDE_SIZE * CELL_SIZE) +
                                     (numberOfBoards * (Board::CHESS_SIDE_SIZE + 1) * BORDER_SIZE) +
                                     (numberOfBoards - 1) * SEPARATOR_SIZE;
}

int ResultPrinter::getRowSizeForHalfMoves(int const numberOfHalfMoves) const {
    return min(MAX_NUMBER_OF_BOARDS_IN_A_ROW, static_cast<int>((numberOfHalfMoves + 1) / 2));
}

int ResultPrinter::getRowSizeForFullMoves(int const numberOfFullMoves) const {
    return min(MAX_NUMBER_OF_BOARDS_IN_A_ROW, static_cast<int>(numberOfFullMoves));
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
