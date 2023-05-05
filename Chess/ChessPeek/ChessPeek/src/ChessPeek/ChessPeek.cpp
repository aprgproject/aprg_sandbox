#include "ChessPeek.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/User/DisplayTable.hpp>

#include <algorithm>
#include <atomic>
#include <iostream>

using namespace alba::AprgBitmap;using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace {
constexpr unsigned int offsetForNextTable = 9U;
}

namespace alba {

namespace chess {
bool ChessPeek::PeekCalculationDetails::operator==(PeekCalculationDetails const& other) const {
    return depth == other.depth && scoreInCentipawns == other.scoreInCentipawns &&
           mateInNumberOfMoves == other.mateInNumberOfMoves && bestMove == other.bestMove &&           currentlySearchingMoves == other.currentlySearchingMoves && pvMovesInBestLine == other.pvMovesInBestLine;
}

bool ChessPeek::PeekCalculationDetails::operator!=(PeekCalculationDetails const& other) const {
    return !operator==(other);
}

ChessPeek::ChessPeek()
    : m_configuration(ChessPeekConfigurationType::LichessStream),
      m_pieceRetriever(m_configuration),
      m_chessEngineHandler(m_configuration.getChessEnginePath()),
      m_chessEngineController(m_chessEngineHandler, m_configuration.getUciOptionNamesAndValuePairs()),
      m_userAutomation(),
      m_bitmap(m_configuration.getScreenShotPath()),
      m_chessBoard(Board::Orientation::BlackUpWhiteDown, {}),
      m_playerColor(PieceColor::White),
      m_playerKingCoordinate{},
      m_opponentKingCoordinate{},
      m_numberOfDetectedKings{},
      m_isEngineNewlyReseted(true),
      m_hasPendingCalculationDetailsToDisplay(false) {
    initialize();
}
void ChessPeek::runForever() {
    while (true) {
        runOneIteration();
        // Sleep(1);
    }
}
void ChessPeek::runOneIteration() {
    displayCalculationDetailsIfNotDisplayedYet();
    Board::PieceMatrix previousPieceMatrix(m_chessBoard.getPieceMatrix());
    checkScreenAndSaveDetails();
    if (canAnalyzeBoard() && (m_isEngineNewlyReseted || didBoardChange(previousPieceMatrix)) && isPlayerToMove()) {
        startEngineAnalysisOfNewPosition();
    }
}

void ChessPeek::saveBitmapOnScreen() const { m_userAutomation.saveBitmapOnScreen(m_configuration.getScreenShotPath()); }

void ChessPeek::checkScreenAndSaveDetails() {
    saveBitmapOnScreen();
    BitmapSnippet snippet(
        m_bitmap.getSnippetReadFromFile(m_configuration.getTopLeftCorner(), m_configuration.getBottomRightCorner()));
    checkSnippetAndSaveDetails(snippet);
    m_bitmap.setSnippetWriteToFile(snippet);  // for debugging
}

void ChessPeek::startEngineAnalysisOfNewPosition() {    string fenString(constructFenString(m_chessBoard, m_playerColor, m_chessBoard.getCastlingFenString(), "-", 0, 1));
    m_chessEngineController.stop();
    m_chessEngineController.setupFenString(fenString);
    if (!m_chessEngineController.waitTillReadyAndReturnIfResetWasPerformed()) {        m_chessEngineController.goWithPonder();
        m_isEngineNewlyReseted = false;
    } else {
        m_isEngineNewlyReseted = true;
    }
}

void ChessPeek::calculationMonitoringCallBackForEngine(EngineCalculationDetails const& calculationDetails) {
    PeekCalculationDetails oldCalculationDetails = m_savedCalculationDetails;
    saveCalculationDetails(calculationDetails);
    if (oldCalculationDetails != m_savedCalculationDetails) {
        displayCalculationDetailsBasedFromTimer();
    }
}

bool ChessPeek::didBoardChange(Board::PieceMatrix const& previousPieceMatrix) const {
    return previousPieceMatrix != m_chessBoard.getPieceMatrix();
}

bool ChessPeek::canAnalyzeBoard() const { return doCorrectKingsExist() && !isOpponentKingOnCheck(); }

bool ChessPeek::doCorrectKingsExist() const {
    return m_numberOfDetectedKings == 2 && isPlayerKingAndOpponentKingValid();
}

bool ChessPeek::isPlayerKingAndOpponentKingValid() const {
    Piece pieceAtPlayerKing(m_chessBoard.getPieceAt(m_playerKingCoordinate));
    Piece pieceAtOpponentKing(m_chessBoard.getPieceAt(m_opponentKingCoordinate));
    return PieceType::King == pieceAtPlayerKing.getType() && m_playerColor == pieceAtPlayerKing.getColor() &&
           PieceType::King == pieceAtOpponentKing.getType() &&
           getOppositeColor(m_playerColor) == pieceAtOpponentKing.getColor();
}

bool ChessPeek::isOpponentKingOnCheck() const { return m_chessBoard.canBeCaptured(m_opponentKingCoordinate); }

bool ChessPeek::isPlayerToMove() const {
    if (m_configuration.getType() == ChessPeekConfigurationType::LichessVersus) {
        return isPlayerToMoveInLichessVersus();
    } else {
        return true;
    }
}

bool ChessPeek::isPlayerToMoveInLichessVersus() const {
    bool result(true);
    BitmapSnippet moveWidgetSnippet(m_bitmap.getSnippetReadFromFile(BitmapXY(3326, 397), BitmapXY(3644, 500)));
    constexpr auto xForWhiteSection = 3406, xForBlackSection = 3565;
    constexpr auto lastMoveColor = 0x293A49U, rgbMask = 0xFFFFFFU;
    for (auto yCoordinate = 500; yCoordinate >= 397; yCoordinate -= 1) {
        auto colorOfMoveInWhiteSection =
            moveWidgetSnippet.getColorAt(BitmapXY(xForWhiteSection, yCoordinate)) & rgbMask;
        auto colorOfMoveInBlackSection =
            moveWidgetSnippet.getColorAt(BitmapXY(xForBlackSection, yCoordinate)) & rgbMask;
        if (lastMoveColor == colorOfMoveInWhiteSection) {
            if (m_playerColor == PieceColor::White) {
                result = false;
            }
            break;
        } else if (lastMoveColor == colorOfMoveInBlackSection) {
            if (m_playerColor == PieceColor::Black) {
                result = false;
            }
            break;
        }
    }

    return result;
}

void ChessPeek::checkSnippetAndSaveDetails(BitmapSnippet& snippet) {
    // snippet.setPixelAt(snippet.getTopLeftCorner(), 0x00A1BA);      // for corner point debugging
    // snippet.setPixelAt(snippet.getBottomRightCorner(), 0x00A1BA);  // for corner point debugging

    m_numberOfDetectedKings = 0U;
    unsigned int pieceCount = 0U;    for (unsigned int j = 0; j < 8; j++) {
        for (unsigned int i = 0; i < 8; i++) {
            Piece chessPiece(m_pieceRetriever.getChessCellPiece(snippet, i, j));
            Coordinate chessCoordinate(i, j);            m_chessBoard.setPieceAt(chessCoordinate, chessPiece);
            if (!chessPiece.isEmpty()) {
                setKingDetailsIfPossible(chessCoordinate, chessPiece);
                pieceCount++;
            }
        }
    }
    updatePlayerColorAndOrientation(pieceCount);
}

void ChessPeek::updatePlayerColorAndOrientation(unsigned int const pieceCount) {
    if (m_configuration.getType() == ChessPeekConfigurationType::LichessStream) {
        updatePlayerColorIfLichessStream();
    } else {
        updatePlayerColorAndOrientationBasedOnPositionsOfTheKings(pieceCount);
    }
}

void ChessPeek::updatePlayerColorIfLichessStream() {
    BitmapSnippet moveWidgetSnippet(m_bitmap.getSnippetReadFromFile(BitmapXY(3304, 199), BitmapXY(3636, 897)));
    constexpr auto xForWhiteSection = 3387, xForBlackSection = 3553;
    constexpr auto lastMoveColor = 0x2A4053U, rgbMask = 0xFFFFFFU;
    for (auto yCoordinate = 897; yCoordinate >= 199; yCoordinate -= 1) {
        auto lastPlayerWhiteColor = moveWidgetSnippet.getColorAt(BitmapXY(xForWhiteSection, yCoordinate)) & rgbMask;
        auto colorOfMoveInBlackSection =
            moveWidgetSnippet.getColorAt(BitmapXY(xForBlackSection, yCoordinate)) & rgbMask;
        if (lastMoveColor == lastPlayerWhiteColor) {
            setPlayerColorAndResetEngineIfNeeded(PieceColor::Black);
            break;
        } else if (lastMoveColor == colorOfMoveInBlackSection) {
            setPlayerColorAndResetEngineIfNeeded(PieceColor::White);
            break;
        }
    }
}

void ChessPeek::updatePlayerColorAndOrientationBasedOnPositionsOfTheKings(unsigned int const pieceCount) {
    Piece pieceAtKingWhiteDownPosition(m_chessBoard.getPieceAt(Coordinate(4, 7)));
    Piece pieceAtKingBlackDownPosition(m_chessBoard.getPieceAt(Coordinate(3, 7)));
    if (pieceCount >= 24U) {
        PieceColor kingColorAtDownPosition(m_playerColor);
        if (PieceType::King == pieceAtKingWhiteDownPosition.getType() &&
            PieceColor::White == pieceAtKingWhiteDownPosition.getColor()) {
            kingColorAtDownPosition = PieceColor::White;
            setOrientationDependingOnBelowColor(kingColorAtDownPosition);
        } else if (
            PieceType::King == pieceAtKingBlackDownPosition.getType() &&
            PieceColor::Black == pieceAtKingBlackDownPosition.getColor()) {
            kingColorAtDownPosition = PieceColor::Black;
            setOrientationDependingOnBelowColor(kingColorAtDownPosition);
        }
        setPlayerColorAndResetEngineIfNeeded(kingColorAtDownPosition);
    }
}

void ChessPeek::setPlayerColorAndResetEngineIfNeeded(PieceColor const newColor) {
    if (m_playerColor != newColor) {
        m_playerColor = newColor;
        m_chessEngineController.resetToNewGame();
        m_isEngineNewlyReseted = true;
    }
}

void ChessPeek::setOrientationDependingOnBelowColor(PieceColor const belowColor) {
    if (PieceColor::White == belowColor) {
        m_chessBoard.setOrientation(Board::Orientation::BlackUpWhiteDown);
    } else if (PieceColor::Black == belowColor) {
        m_chessBoard.setOrientation(Board::Orientation::WhiteUpBlackDown);
    }
}

void ChessPeek::setKingDetailsIfPossible(Coordinate const& chessCoordinate, Piece const& chessPiece) {
    if (PieceType::King == chessPiece.getType()) {
        m_numberOfDetectedKings++;
        if (m_playerColor == chessPiece.getColor()) {
            m_playerKingCoordinate = chessCoordinate;
        } else {
            m_opponentKingCoordinate = chessCoordinate;
        }
    }
}

void ChessPeek::saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails) {
    constexpr unsigned int minimumNumberOfPvMovesForUpdate = 3U;

    m_savedCalculationDetails.depth = engineCalculationDetails.depth;
    m_savedCalculationDetails.scoreInCentipawns = engineCalculationDetails.scoreInCentipawns;
    m_savedCalculationDetails.mateInNumberOfMoves = engineCalculationDetails.mateInNumberOfMoves;
    if (!engineCalculationDetails.bestMove.empty()) {
        m_savedCalculationDetails.bestMove = engineCalculationDetails.bestMove;
    }
    if (!engineCalculationDetails.currentlySearchingMoves.empty()) {
        m_savedCalculationDetails.currentlySearchingMoves = engineCalculationDetails.currentlySearchingMoves;
    }
    if (m_savedCalculationDetails.mateInNumberOfMoves > 0 ||
        engineCalculationDetails.pvMovesInBestLine.size() >= minimumNumberOfPvMovesForUpdate) {
        m_savedCalculationDetails.pvMovesInBestLine = engineCalculationDetails.pvMovesInBestLine;
    }
}

void ChessPeek::displayCalculationDetailsBasedFromTimer() {
    constexpr auto minimumMillisecondsDelayToDisplay = 200;

    m_displayTimer.stopTimer();
    if (m_displayTimer.getElapsedTimeInMilliseconds() > minimumMillisecondsDelayToDisplay) {
        m_hasPendingCalculationDetailsToDisplay = false;
        printCalculationDetailsFromEngine();
        m_displayTimer.resetTimer();
    } else {
        m_hasPendingCalculationDetailsToDisplay = true;
    }
}

void ChessPeek::displayCalculationDetailsIfNotDisplayedYet() {
    if (m_hasPendingCalculationDetailsToDisplay) {
        m_hasPendingCalculationDetailsToDisplay = false;
        printCalculationDetailsFromEngine();
    }
}

void ChessPeek::printCalculationDetailsFromEngine() {
    static std::atomic_bool currentlyPrinting = false;
    if (!currentlyPrinting) {
        currentlyPrinting = true;
        Moves currentMoves(getCurrentMoves());
        Moves futureMoves(getFutureMoves());
        printCalculationDetails(currentMoves, futureMoves);
        printMoveTables(currentMoves, futureMoves);
        cout << "\n";
        cout.flush();
        currentlyPrinting = false;
    }
}

Moves ChessPeek::getCurrentMoves() const {
    Moves result;
    strings const& searchingMovesStrings(m_savedCalculationDetails.currentlySearchingMoves);
    for (string const& searchingMoveString : searchingMovesStrings) {
        Move move(m_chessBoard.getMoveFromTwoLetterNumberNotation(searchingMoveString));
        if (isValidMove(move)) {
            result.emplace_back(move);
        }
    }

    if (result.empty()) {
        string bestMoveString(getBestMoveString());
        Move bestMove(m_chessBoard.getMoveFromTwoLetterNumberNotation(bestMoveString));
        if (isValidMove(bestMove)) {
            result.emplace_back(bestMove);
        }
    }
    return result;
}

Moves ChessPeek::getFutureMoves() const {
    Moves result;
    strings const& pvMovesStrings(m_savedCalculationDetails.pvMovesInBestLine);
    for (string const& pvMoveString : pvMovesStrings) {
        Move move(m_chessBoard.getMoveFromTwoLetterNumberNotation(pvMoveString));
        if (isValidMove(move)) {
            result.emplace_back(move);
        }
    }
    return result;
}

string ChessPeek::getBestMoveString() const {
    if (!m_savedCalculationDetails.bestMove.empty()) {
        return m_savedCalculationDetails.bestMove;
    }    if (!m_savedCalculationDetails.currentlySearchingMoves.empty()) {
        string firstMove(m_savedCalculationDetails.currentlySearchingMoves.front());
        if (!firstMove.empty()) {
            return firstMove;        }
    }
    if (!m_savedCalculationDetails.pvMovesInBestLine.empty()) {
        string firstMove(m_savedCalculationDetails.pvMovesInBestLine.front());
        if (!firstMove.empty()) {
            return firstMove;
        }
    }
    return string();
}

void ChessPeek::printCalculationDetails(Moves const& currentMoves, Moves const& futureMoves) const {
    cout << "Player: " << m_playerColor << ", Depth: " << m_savedCalculationDetails.depth
         << ", Score: " << static_cast<double>(m_savedCalculationDetails.scoreInCentipawns) / 100
         << ", Mate: " << m_savedCalculationDetails.mateInNumberOfMoves << "\n";
    cout << "Best move: [" << m_savedCalculationDetails.bestMove << "]\n";

    cout << "Searching moves: ";
    for (Move const& currentMove : currentMoves) {
        cout << m_chessBoard.getReadableStringForMove(currentMove) << ", ";
    }
    cout << "\n";

    Board temporaryBoard(m_chessBoard);
    cout << "PV: ";
    for (Move const& futureMove : futureMoves) {
        cout << temporaryBoard.getReadableStringForMove(futureMove) << ", ";
        temporaryBoard.move(futureMove);
    }
    cout << "\n\n";
}

void ChessPeek::printMoveTables(Moves const& currentMoves, Moves const& futureMoves) const {    if (!currentMoves.empty()) {
        putCurrentMovesTable(currentMoves);
        cout << "\n";
    }    if (!futureMoves.empty()) {
        printFutureMovesTable(futureMoves);
        cout << "\n";
    }
}

void ChessPeek::putCurrentMovesTable(Moves const& currentMoves) const {
    constexpr unsigned int maxNumberOfCurrentMoves = 5U;
    constexpr unsigned int numberOfRows = 8U;
    unsigned int numberOfMoves = min(maxNumberOfCurrentMoves, static_cast<unsigned int>(currentMoves.size()));
    unsigned int numberOfColumns = getNumberOfColumnsOfDisplayTable(numberOfMoves);

    DisplayTable displayTable(numberOfColumns, numberOfRows);
    displayTable.setBorders("-", "|");

    putSeparatorsOnDisplayTable(displayTable, numberOfColumns, numberOfRows);
    // put chess board
    for (unsigned int xOffset = 0; xOffset < numberOfColumns; xOffset += offsetForNextTable) {
        putChessBoardOnDisplayTable(displayTable, m_chessBoard, xOffset);
    }
    putCurrentMovesOnDisplayTable(displayTable, currentMoves, numberOfMoves);

    cout << displayTable;
}

void ChessPeek::printFutureMovesTable(Moves const& futureMoves) const {
    constexpr unsigned int maxNumberOfFuturePlayerMoves = 5U;
    constexpr unsigned int numberOfRows = 8U;
    unsigned int numberOfMoves =
        min(maxNumberOfFuturePlayerMoves, static_cast<unsigned int>((futureMoves.size() + 1U) / 2U));
    unsigned int numberOfColumns = getNumberOfColumnsOfDisplayTable(numberOfMoves);

    DisplayTable displayTable(numberOfColumns, numberOfRows);
    displayTable.setBorders("-", "|");

    putSeparatorsOnDisplayTable(displayTable, numberOfColumns, numberOfRows);
    putFutureMovesAndBoardsOnDisplayTable(displayTable, futureMoves, numberOfMoves);

    cout << displayTable;
}

void ChessPeek::putCurrentMovesOnDisplayTable(
    DisplayTable& displayTable, Moves const& currentMoves, unsigned int const numberOfMoves) const {
    unsigned int moveNumber = 1U;
    unsigned int offset = 0U;
    for (Move const& currentMove : currentMoves) {
        Piece piece(m_chessBoard.getPieceAt(currentMove.first));        displayTable.getCellReferenceAt(currentMove.first.getX() + offset, currentMove.first.getY())
            .setText(getChessCellForDisplay(piece, 1U, false));
        displayTable.getCellReferenceAt(currentMove.second.getX() + offset, currentMove.second.getY())
            .setText(getChessCellForDisplay(piece, 2U, false));
        offset += offsetForNextTable;
        moveNumber++;
        if (moveNumber > numberOfMoves) {
            break;
        }
    }
}

void ChessPeek::putFutureMovesAndBoardsOnDisplayTable(
    DisplayTable& displayTable, Moves const& futureMoves, unsigned int const numberOfMoves) const {
    unsigned int moveNumber = 1U;
    unsigned int xOffset = 0U;
    unsigned int futureMoveCount = 0U;

    Board temporaryBoard(m_chessBoard);
    PieceColor opponentColor(getOppositeColor(m_playerColor));
    Coordinate previousDestination{};
    bool hasPreviouslyOneWayOfCapture(false);
    for (Move const& futureMove : futureMoves) {
        if (isEven(futureMoveCount)) {
            putChessBoardOnDisplayTable(displayTable, temporaryBoard, xOffset);
            bool canPreMove = hasPreviouslyOneWayOfCapture && previousDestination == futureMove.second;

            Piece piece(temporaryBoard.getPieceAt(futureMove.first));            displayTable.getCellReferenceAt(futureMove.first.getX() + xOffset, futureMove.first.getY())
                .setText(getChessCellForDisplay(piece, moveNumber, canPreMove));
            displayTable.getCellReferenceAt(futureMove.second.getX() + xOffset, futureMove.second.getY())
                .setText(getChessCellForDisplay(piece, moveNumber + 1, canPreMove));

            xOffset += offsetForNextTable;
            hasPreviouslyOneWayOfCapture = false;
            moveNumber++;
            if (moveNumber > numberOfMoves) {
                break;
            }
        } else {
            previousDestination = futureMove.second;
            hasPreviouslyOneWayOfCapture =                !temporaryBoard.isEmptyAt(futureMove.second) &&
                temporaryBoard.hasOnlyOneMovePossibleToThisDestination(futureMove.second, opponentColor);
        }
        temporaryBoard.move(futureMove);
        futureMoveCount++;
    }
}

void ChessPeek::putSeparatorsOnDisplayTable(
    DisplayTable& displayTable, unsigned int const numberOfColumns, unsigned int const numberOfRows) const {
    for (unsigned int j = 0; j < numberOfRows; j++) {
        for (unsigned int separatorIndex = offsetForNextTable - 1; separatorIndex < numberOfColumns;
             separatorIndex += offsetForNextTable) {
            displayTable.getCellReferenceAt(separatorIndex, j).setText("     ");
        }
    }
}

void ChessPeek::putChessBoardOnDisplayTable(
    DisplayTable& displayTable, Board const& temporaryBoard, unsigned int const xOffset) const {
    constexpr CoordinateDataType chessBoardDimension = 8U;
    for (CoordinateDataType y = 0; y < chessBoardDimension; y++) {
        for (CoordinateDataType x = 0; x < chessBoardDimension; x++) {
            Piece piece(temporaryBoard.getPieceAt(Coordinate(x, y)));
            displayTable.getCellReferenceAt(x + xOffset, y).setText(getChessCellForDisplay(piece, 0U, false));
        }
    }
}

string ChessPeek::getChessCellForDisplay(    Piece const& piece, unsigned int const moveNumber, bool const canPreMove) const {
    string result(3, ' ');
    if (moveNumber != 0) {
        char moveNumberCharacter = '0' + static_cast<char>(moveNumber);        if (canPreMove) {
            result[0] = '*';
        } else {
            result[0] = moveNumberCharacter;
        }
        result[2] = moveNumberCharacter;
    }
    result[1] = piece.getCharacter();
    return result;
}

unsigned int ChessPeek::getNumberOfColumnsOfDisplayTable(unsigned int const numberOfChessBoards) const {
    return numberOfChessBoards == 0 ? 0U : numberOfChessBoards * 8U + numberOfChessBoards - 1;
}

void ChessPeek::initialize() {
    m_pieceRetriever.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\PieceConverter.log)");
    m_chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineHandler.log)");
    m_chessEngineController.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineController.log)");
    m_chessEngineController.setAdditionalStepsInCalculationMonitoring(
        [&](EngineCalculationDetails const& engineCalculationDetails) {
            calculationMonitoringCallBackForEngine(engineCalculationDetails);
        });
}

}  // namespace chess

}  // namespace alba
