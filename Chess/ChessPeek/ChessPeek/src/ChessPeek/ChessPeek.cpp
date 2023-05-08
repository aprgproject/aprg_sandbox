#include "ChessPeek.hpp"

#include <ChessPeek/ResultPrinter.hpp>
#include <ChessPeek/Utilities.hpp>
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

namespace ChessPeek {

void trackKeyPress() {
    constexpr char SPACE_BAR = ' ';
    AlbaLocalUserAutomation userAutomation;
    bool isPreviouslyPressed = false;
    while (true) {
        bool isPressed = userAutomation.isLetterPressed(SPACE_BAR);
        if (isPreviouslyPressed == false && isPressed == true) {
            haltPrinting = !haltPrinting;
        }
        isPreviouslyPressed = isPressed;
        Sleep(100);
    }
}

ChessPeek::ChessPeek()
    : m_configuration(Configuration::Type::LichessVersus),
      m_screenMonitoring(),
      m_engineHandler(m_configuration.getChessEnginePath()),
      m_engineController(m_engineHandler, m_configuration.getUciOptionNamesAndValuePairs()),
      m_detailsFromTheScreen(m_configuration, m_screenMonitoring),
      m_detailsOnTheEngine(),
      m_calculationDetails{},
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
    printCalculationDetailsIfPending();

    checkScreenAndSaveDetails();
    if (shouldAnalyzeBoard()) {
        startEngineAnalysis();
    }
}

void ChessPeek::checkScreenAndSaveDetails() {
    m_screenMonitoring.capturePixelsFromScreen();
    m_detailsFromTheScreen.saveDetailsFromTheScreen();
}

void ChessPeek::startEngineAnalysis() {
    if (m_detailsFromTheScreen.getPlayerColor() != m_detailsOnTheEngine.getPlayerColor()) {
        m_engineController.resetToNewGame();
    }

    m_detailsOnTheEngine.save(m_detailsFromTheScreen.getPlayerColor(), m_detailsFromTheScreen.getBoard());

    m_engineController.setupFenString(m_detailsOnTheEngine.getFenString());
    if (!m_engineController.waitTillReadyAndReturnIfResetWasPerformed()) {
        m_engineController.goWithPonder();
        m_isEngineNewlyReseted = false;
    } else {
        m_isEngineNewlyReseted = true;
    }
}

void ChessPeek::calculationMonitoringCallBackForEngine(EngineCalculationDetails const& calculationDetails) {
    CalculationDetails previousCalculationDetails = m_calculationDetails;
    saveCalculationDetails(calculationDetails);
    if (previousCalculationDetails != m_calculationDetails) {
        printCalculationDetailsWithFiltering();
    }
}

bool ChessPeek::shouldAnalyzeBoard() const {
    return m_detailsFromTheScreen.canAnalyzeBoard() && (m_isEngineNewlyReseted || didBoardFromScreenChange());
}

bool ChessPeek::didBoardFromScreenChange() const {
    return m_detailsFromTheScreen.getBoard() != m_detailsOnTheEngine.getBoard();
}

void ChessPeek::initialize() {
    m_engineHandler.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineHandler.log)");  // for debugging
    // m_engineController.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineController.log)");  // for debugging

    m_engineController.setAdditionalStepsInCalculationMonitoring(
        [&](EngineCalculationDetails const& engineCalculationDetails) {
            calculationMonitoringCallBackForEngine(engineCalculationDetails);
        });
    m_engineController.initialize();
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

void ChessPeek::printCalculationDetailsWithFiltering() {
    constexpr auto MINIMUM_MILLISECONDS_FOR_EACH_PRINT = 200;
    m_printFilteringTimer.stopTimer();
    if (m_printFilteringTimer.getElapsedTimeInMilliseconds() > MINIMUM_MILLISECONDS_FOR_EACH_PRINT) {
        printCalculationDetails();
        m_printFilteringTimer.resetTimer();
    } else {
        m_hasPendingPrintAction = true;
    }
}

void ChessPeek::printCalculationDetailsIfPending() {
    if (m_hasPendingPrintAction) {
        printCalculationDetails();
    }
}

void ChessPeek::printCalculationDetails() {
    static std::atomic_bool currentlyPrinting = false;
    if (!currentlyPrinting && !haltPrinting) {
        m_hasPendingPrintAction = false;
        currentlyPrinting = true;
        ResultPrinter(m_detailsOnTheEngine, m_calculationDetails).print();
        currentlyPrinting = false;
    } else {
        m_hasPendingPrintAction = true;
    }
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
