#include "ChessPeek.hpp"

#include <ChessPeek/ChessPeekPrintHelper.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>

#include <atomic>
#include <optional>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba {

namespace chess {

ChessPeek::ChessPeek()
    : m_configuration(ChessPeekConfigurationType::ChessDotComUserVsUser),
      m_pieceRetriever(m_configuration),
      m_chessEngineHandler(m_configuration.getChessEnginePath()),
      m_chessEngineController(m_chessEngineHandler, m_configuration.getUciOptionNamesAndValuePairs()),
      m_userAutomation(),
      m_bitmap(m_configuration.getScreenShotPath()),
      m_chessBoard(Board::Orientation::BlackUpWhiteDown, {}),
      m_chessBoardDetails{},
      m_playerColor(PieceColor::White),
      m_isEngineNewlyReseted(true),
      m_hasPendingPrintAction(false) {
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
    if (shouldAnalyzeBoard(previousPieceMatrix)) {
        startEngineAnalysisOfNewPosition();
    }
}

void ChessPeek::saveBitmapOnScreen() const { m_userAutomation.saveBitmapOnScreen(m_configuration.getScreenShotPath()); }

void ChessPeek::checkScreenAndSaveDetails() {
    saveBitmapOnScreen();
    BitmapSnippet snippet(
        m_bitmap.getSnippetReadFromFile(m_configuration.getTopLeftCorner(), m_configuration.getBottomRightCorner()));
    checkSnippetAndSaveDetails(snippet);

    // snippet.setPixelAt(snippet.getTopLeftCorner(), 0x00A1BA);      // for corner point debugging
    // snippet.setPixelAt(snippet.getBottomRightCorner(), 0x00A1BA);  // for corner point debugging
    // m_bitmap.setSnippetWriteToFile(snippet);  // for debugging
}

void ChessPeek::startEngineAnalysisOfNewPosition() {
    string fenString(constructFenString(m_chessBoard, m_playerColor, m_chessBoard.getCastlingFenString(), "-", 0, 1));
    m_chessEngineController.setupFenString(fenString);
    if (!m_chessEngineController.waitTillReadyAndReturnIfResetWasPerformed()) {
        m_chessEngineController.goWithPonder();
        m_isEngineNewlyReseted = false;
    } else {
        m_isEngineNewlyReseted = true;
    }
}

void ChessPeek::calculationMonitoringCallBackForEngine(EngineCalculationDetails const& calculationDetails) {
    ChessPeekCalculationDetails oldCalculationDetails = m_calculationDetails;
    saveCalculationDetails(calculationDetails);
    if (oldCalculationDetails != m_calculationDetails) {
        displayCalculationDetailsBasedFromTimer();
    }
}

void ChessPeek::initialize() {
    m_pieceRetriever.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\PieceConverter.log)");
    m_chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineHandler.log)");
    m_chessEngineController.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineController.log)");
    m_chessEngineController.setAdditionalStepsInCalculationMonitoring(
        [&](EngineCalculationDetails const& engineCalculationDetails) {
            calculationMonitoringCallBackForEngine(engineCalculationDetails);
        });
    m_chessEngineController.initializeController();
}

void ChessPeek::checkSnippetAndSaveDetails(BitmapSnippet const& snippet) {
    saveChessBoardAndItsDetails(snippet);
    updatePlayerColorAndOrientation();
}
void ChessPeek::saveChessBoardAndItsDetails(BitmapSnippet const& snippet) {
    m_chessBoardDetails = {};
    for (unsigned int j = 0; j < 8; j++) {
        for (unsigned int i = 0; i < 8; i++) {
            Piece chessPiece(m_pieceRetriever.getChessCellPiece(snippet, i, j));
            Coordinate chessCoordinate(i, j);
            m_chessBoard.setPieceAt(chessCoordinate, chessPiece);
            if (!chessPiece.isEmpty()) {
                setKingDetailsIfPossible(chessCoordinate, chessPiece);
                m_chessBoardDetails.m_pieceCount++;
            }
        }
    }
}

void ChessPeek::updatePlayerColorAndOrientation() {
    if (m_configuration.getType() == ChessPeekConfigurationType::LichessStream) {
        updatePlayerColorIfLichessStream();
    } else {
        updatePlayerColorAndOrientationBasedOnPositionsOfTheKings();
    }
}

void ChessPeek::updatePlayerColorIfLichessStream() {
    BitmapSnippet moveWidgetSnippet(m_bitmap.getSnippetReadFromFile(BitmapXY(3304, 199), BitmapXY(3636, 897)));
    constexpr auto xForWhiteSection = 3387, xForBlackSection = 3553;
    constexpr auto lastMovePixelColor = 0x2A4053U, rgbMask = 0xFFFFFFU;
    for (auto yCoordinate = 897; yCoordinate >= 199; yCoordinate -= 1) {
        auto pixelColorInWhiteSection = moveWidgetSnippet.getColorAt(BitmapXY(xForWhiteSection, yCoordinate)) & rgbMask;
        auto pixelColorInBlackSection = moveWidgetSnippet.getColorAt(BitmapXY(xForBlackSection, yCoordinate)) & rgbMask;
        if (lastMovePixelColor == pixelColorInWhiteSection) {
            setPlayerColorAndResetEngineIfNeeded(PieceColor::Black);
            break;
        } else if (lastMovePixelColor == pixelColorInBlackSection) {
            setPlayerColorAndResetEngineIfNeeded(PieceColor::White);
            break;
        }
    }
}

void ChessPeek::updatePlayerColorAndOrientationBasedOnPositionsOfTheKings() {
    if (m_chessBoardDetails.m_pieceCount >= 24U) {
        optional<PieceColor> kingColorAtTheBottomOptional;
        if (m_chessBoardDetails.whiteKingCoordinate.getY() == 7U) {
            kingColorAtTheBottomOptional = PieceColor::White;  // bottom row has a white king
        } else if (m_chessBoardDetails.blackKingCoordinate.getY() == 7U) {
            kingColorAtTheBottomOptional = PieceColor::Black;  // bottom row has a black king
        } else if (m_chessBoardDetails.whiteKingCoordinate.getY() == 0U) {
            kingColorAtTheBottomOptional = PieceColor::Black;  // top row has a white king
        } else if (m_chessBoardDetails.blackKingCoordinate.getY() == 0U) {
            kingColorAtTheBottomOptional = PieceColor::White;  // top row has a black king
        }
        if (kingColorAtTheBottomOptional) {
            setOrientationDependingOnBelowColor(kingColorAtTheBottomOptional.value());
            setPlayerColorAndResetEngineIfNeeded(kingColorAtTheBottomOptional.value());
        }
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
        if (PieceColor::White == chessPiece.getColor()) {
            m_chessBoardDetails.numberOfWhiteKings++;
            m_chessBoardDetails.whiteKingCoordinate = chessCoordinate;
        } else {
            m_chessBoardDetails.numberOfBlackKings++;
            m_chessBoardDetails.blackKingCoordinate = chessCoordinate;
        }
    }
}

void ChessPeek::saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails) {
    m_calculationDetails.depthInPlies = engineCalculationDetails.depthInPlies;
    m_calculationDetails.numberOfMovesTillMate = engineCalculationDetails.numberOfMovesTillMate;
    if (!engineCalculationDetails.bestMove.empty()) {
        m_calculationDetails.bestMove = engineCalculationDetails.bestMove;
    }
    if (!engineCalculationDetails.searchingMoveAndScorePairs.empty()) {
        m_calculationDetails.searchingMoveAndScorePairs = engineCalculationDetails.searchingMoveAndScorePairs;
    }
    if (!engineCalculationDetails.pvMovesInBestLine.empty()) {
        m_calculationDetails.pvMovesInBestLine = engineCalculationDetails.pvMovesInBestLine;
    }
}

void ChessPeek::displayCalculationDetailsBasedFromTimer() {
    constexpr auto minimumMillisecondsDelayToDisplay = 200;

    m_displayTimer.stopTimer();
    if (m_displayTimer.getElapsedTimeInMilliseconds() > minimumMillisecondsDelayToDisplay) {
        printCalculationDetails();
        m_displayTimer.resetTimer();
    } else {
        m_hasPendingPrintAction = true;
    }
}

void ChessPeek::displayCalculationDetailsIfNotDisplayedYet() {
    if (m_hasPendingPrintAction) {
        printCalculationDetails();
    }
}

void ChessPeek::printCalculationDetails() {
    static std::atomic_bool currentlyPrinting = false;
    if (!currentlyPrinting) {
        m_hasPendingPrintAction = false;
        currentlyPrinting = true;
        ChessPeekPrintHelper(m_playerColor, m_calculationDetails, m_chessBoard).print();
        currentlyPrinting = false;
    } else {
        m_hasPendingPrintAction = true;
    }
}

bool ChessPeek::shouldAnalyzeBoard(Board::PieceMatrix const& previousPieceMatrix) const {
    return canAnalyzeBoard() && (m_isEngineNewlyReseted || didBoardChange(previousPieceMatrix)) && isPlayerToMove();
}

bool ChessPeek::didBoardChange(Board::PieceMatrix const& previousPieceMatrix) const {
    return previousPieceMatrix != m_chessBoard.getPieceMatrix();
}

bool ChessPeek::canAnalyzeBoard() const { return areKingsValid() && !isOpponentsKingOnCheck(); }

bool ChessPeek::areKingsValid() const {
    return m_chessBoardDetails.numberOfWhiteKings == 1 && m_chessBoardDetails.numberOfBlackKings == 1;
}

bool ChessPeek::isOpponentsKingOnCheck() const { return m_chessBoard.canBeCaptured(getOpponentsKingCoordinate()); }

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

Coordinate ChessPeek::getOpponentsKingCoordinate() const {
    Coordinate result = {};
    if (m_playerColor == PieceColor::White) {
        result = m_chessBoardDetails.blackKingCoordinate;
    } else if (m_playerColor == PieceColor::Black) {
        result = m_chessBoardDetails.whiteKingCoordinate;
    }
    return result;
}

}  // namespace chess

}  // namespace alba
