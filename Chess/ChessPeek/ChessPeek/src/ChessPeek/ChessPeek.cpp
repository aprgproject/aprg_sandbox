#include "ChessPeek.hpp"

#include <ChessPeek/ChessPeekPrintHelper.hpp>
#include <ChessPeek/Utilities.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <atomic>
#include <optional>
#include <thread>

using namespace std;

namespace {
bool haltPrinting = false;
}

namespace alba {

namespace chess {

void trackKeyPress() {
    constexpr char keyToTrack = ' ';
    AlbaLocalUserAutomation userAutomation;
    bool isPreviouslyPressed = false;
    while (true) {
        bool isPressed = userAutomation.isLetterPressed(keyToTrack);
        if (isPreviouslyPressed == false && isPressed == true) {
            haltPrinting = !haltPrinting;
        }
        isPreviouslyPressed = isPressed;
        Sleep(100);
    }
}

ChessPeek::ChessPeek()
    : m_configuration(ChessPeekConfigurationType::ChessDotComVersus),
      m_screenMonitoring(),
      m_pieceRetriever(m_configuration, m_screenMonitoring),
      m_chessEngineHandler(m_configuration.getChessEnginePath()),
      m_chessEngineController(m_chessEngineHandler, m_configuration.getUciOptionNamesAndValuePairs()),
      m_chessBoard(Board::Orientation::BlackUpWhiteDown, {}),
      m_chessBoardDetails{},
      m_playerColor(PieceColor::White),
      m_isEngineNewlyReseted(true),
      m_hasPendingPrintAction(false) {
    initialize();
}

void ChessPeek::runForever() {
    thread trackKeyPressThread(trackKeyPress);
    while (true) {
        runOneIteration();
        // Sleep(1);
    }
    trackKeyPressThread.join();
}

void ChessPeek::runOneIteration() {
    displayCalculationDetailsIfNotDisplayedYet();

    Board::PieceMatrix previousPieceMatrix(m_chessBoard.getPieceMatrix());
    checkScreenAndSaveDetails();
    if (shouldAnalyzeBoard(previousPieceMatrix)) {
        startEngineAnalysisOfNewPosition();
    }
}

void ChessPeek::checkScreenAndSaveDetails() {
    m_screenMonitoring.capturePixelsFromScreen();
    saveChessBoardAndItsDetails();
    updatePlayerColorAndOrientation();
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
    // m_chessEngineHandler.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineHandler.log)");        // for debugging
    // m_chessEngineController.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineController.log)");  // for debugging
    m_chessEngineController.setAdditionalStepsInCalculationMonitoring(
        [&](EngineCalculationDetails const& engineCalculationDetails) {
            calculationMonitoringCallBackForEngine(engineCalculationDetails);
        });
    m_chessEngineController.initializeController();
}

void ChessPeek::saveChessBoardAndItsDetails() {
    m_chessBoardDetails = {};
    for (unsigned int j = 0; j < 8; j++) {
        for (unsigned int i = 0; i < 8; i++) {
            Piece chessPiece(m_pieceRetriever.getChessCellPiece(i, j));
            Coordinate chessCoordinate(i, j);
            m_chessBoard.setPieceAt(chessCoordinate, chessPiece);
            if (!chessPiece.isEmpty()) {
                setChessBoardCountDetails(chessCoordinate, chessPiece);
                setChessBoardKingDetailsIfNeeded(chessCoordinate, chessPiece);
            }
        }
    }
}

void ChessPeek::setChessBoardCountDetails(Coordinate const& chessCoordinate, Piece const& chessPiece) {
    m_chessBoardDetails.pieceCount++;
    if (chessCoordinate.getY() <= 3) {
        if (PieceColor::White == chessPiece.getColor()) {
            m_chessBoardDetails.whiteCountInUpperHalf++;
        } else if (PieceColor::Black == chessPiece.getColor()) {
            m_chessBoardDetails.blackCountInUpperHalf++;
        }
    } else {
        if (PieceColor::White == chessPiece.getColor()) {
            m_chessBoardDetails.whiteCountInLowerHalf++;
        } else if (PieceColor::Black == chessPiece.getColor()) {
            m_chessBoardDetails.blackCountInLowerHalf++;
        }
    }
}

void ChessPeek::setChessBoardKingDetailsIfNeeded(Coordinate const& chessCoordinate, Piece const& chessPiece) {
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

void ChessPeek::updatePlayerColorAndOrientation() {
    if (m_configuration.getType() == ChessPeekConfigurationType::ChessDotComPuzzle) {
        updatePlayerColorIfChessDotComPuzzle();
    } else if (m_configuration.getType() == ChessPeekConfigurationType::LichessStream) {
        updatePlayerColorIfLichessStream();
    } else {
        updatePlayerColorAndOrientationFromChessBoardDetails();
    }
}

void ChessPeek::updatePlayerColorIfChessDotComPuzzle() {
    auto intensity = calculateColorIntensityDecimal(m_screenMonitoring.getColorAt(3337, 137));
    if (intensity < m_configuration.getBlackColorLimit()) {
        setOrientationDependingOnLowerHalfColor(PieceColor::Black);
        setPlayerColorAndResetEngineIfNeeded(PieceColor::Black);
    } else if (intensity > m_configuration.getWhiteColorLimit()) {
        setOrientationDependingOnLowerHalfColor(PieceColor::White);
        setPlayerColorAndResetEngineIfNeeded(PieceColor::White);
    }
}

void ChessPeek::updatePlayerColorIfLichessStream() {
    constexpr auto xForWhiteSection = 3387, xForBlackSection = 3553;
    constexpr auto lastMovePixelColor = 0x2A4053U, rgbMask = 0xFFFFFFU;
    for (auto yCoordinate = 897; yCoordinate >= 199; yCoordinate -= 1) {
        auto pixelColorInWhiteSection = m_screenMonitoring.getColorAt(xForWhiteSection, yCoordinate) & rgbMask;
        auto pixelColorInBlackSection = m_screenMonitoring.getColorAt(xForBlackSection, yCoordinate) & rgbMask;
        if (lastMovePixelColor == pixelColorInWhiteSection) {
            setPlayerColorAndResetEngineIfNeeded(PieceColor::Black);
            break;
        } else if (lastMovePixelColor == pixelColorInBlackSection) {
            setPlayerColorAndResetEngineIfNeeded(PieceColor::White);
            break;
        }
    }
}

void ChessPeek::updatePlayerColorAndOrientationFromChessBoardDetails() {
    constexpr unsigned int MIN_PIECE_COUNT_TO_CONSIDER = 12U;
    if (m_chessBoardDetails.pieceCount >= MIN_PIECE_COUNT_TO_CONSIDER) {
        optional<PieceColor> lowerHalfColorOptional;
        if (m_chessBoardDetails.whiteCountInLowerHalf > m_chessBoardDetails.blackCountInLowerHalf &&
            m_chessBoardDetails.blackCountInUpperHalf > m_chessBoardDetails.whiteCountInUpperHalf &&
            isInLowerHalf(m_chessBoardDetails.whiteKingCoordinate) &&
            isInUpperHalf(m_chessBoardDetails.blackKingCoordinate)) {
            lowerHalfColorOptional = PieceColor::White;
        } else if (
            m_chessBoardDetails.blackCountInLowerHalf > m_chessBoardDetails.whiteCountInLowerHalf &&
            m_chessBoardDetails.whiteCountInUpperHalf > m_chessBoardDetails.blackCountInUpperHalf &&
            isInLowerHalf(m_chessBoardDetails.blackKingCoordinate) &&
            isInUpperHalf(m_chessBoardDetails.whiteKingCoordinate)) {
            lowerHalfColorOptional = PieceColor::Black;
        }

        if (lowerHalfColorOptional) {
            setOrientationDependingOnLowerHalfColor(lowerHalfColorOptional.value());
            setPlayerColorAndResetEngineIfNeeded(lowerHalfColorOptional.value());
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

void ChessPeek::setOrientationDependingOnLowerHalfColor(PieceColor const lowerHalfColor) {
    if (PieceColor::White == lowerHalfColor) {
        m_chessBoard.setOrientation(Board::Orientation::BlackUpWhiteDown);
    } else if (PieceColor::Black == lowerHalfColor) {
        m_chessBoard.setOrientation(Board::Orientation::WhiteUpBlackDown);
    }
}

void ChessPeek::saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails) {
    m_calculationDetails.depthInPlies = engineCalculationDetails.depthInPlies;
    m_calculationDetails.mateScore = engineCalculationDetails.mateScore;
    if (!engineCalculationDetails.bestMove.empty()) {
        m_calculationDetails.bestMove = engineCalculationDetails.bestMove;
    }
    if (!engineCalculationDetails.searchingMoveAndScorePairs.empty()) {
        m_calculationDetails.searchingMoveAndScorePairs = engineCalculationDetails.searchingMoveAndScorePairs;
    }
    m_calculationDetails.scoreInPvLine = engineCalculationDetails.scoreInPvLine;
    if (!engineCalculationDetails.pvHalfMovesInMonitoredLine.empty()) {
        m_calculationDetails.pvHalfMovesInMonitoredLine = engineCalculationDetails.pvHalfMovesInMonitoredLine;
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
    if (!currentlyPrinting && !haltPrinting) {
        m_hasPendingPrintAction = false;
        currentlyPrinting = true;
        ChessPeekPrintHelper(m_playerColor, m_calculationDetails, m_chessBoard).print();
        currentlyPrinting = false;
    } else {
        m_hasPendingPrintAction = true;
    }
}

bool ChessPeek::shouldAnalyzeBoard(Board::PieceMatrix const& previousPieceMatrix) const {
    return canAnalyzeBoard() && (m_isEngineNewlyReseted || didBoardChange(previousPieceMatrix));
}

bool ChessPeek::didBoardChange(Board::PieceMatrix const& previousPieceMatrix) const {
    return previousPieceMatrix != m_chessBoard.getPieceMatrix();
}

bool ChessPeek::canAnalyzeBoard() const { return areKingsValid() && !isOpponentsKingOnCheck(); }

bool ChessPeek::areKingsValid() const {
    return m_chessBoardDetails.numberOfWhiteKings == 1 && m_chessBoardDetails.numberOfBlackKings == 1;
}

bool ChessPeek::isOpponentsKingOnCheck() const { return m_chessBoard.canBeCaptured(getOpponentsKingCoordinate()); }

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
