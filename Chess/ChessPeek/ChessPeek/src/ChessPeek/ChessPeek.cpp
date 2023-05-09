#include "ChessPeek.hpp"

#include <ChessPeek/ResultPrinter.hpp>
#include <ChessPeek/Utilities.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <atomic>
#include <optional>
#include <thread>

using namespace std;

namespace {
bool shouldStillRun = true;  // USE ESCAPE KEY TO CLEANLY SHUTDOWN
}

namespace alba {

namespace chess {

namespace ChessPeek {

void trackKeyPress() {
    AlbaLocalUserAutomation userAutomation;
    while (shouldStillRun) {
        shouldStillRun = !userAutomation.isLetterPressed(VK_ESCAPE);
        Sleep(100);
    }
}

ChessPeek::ChessPeek()
    : m_configuration(Configuration::Type::ChessDotComVersus),
      m_screenMonitoring(),
      m_engineHandler(m_configuration.getChessEnginePath()),
      m_engineController(m_engineHandler, m_configuration.getUciOptionNamesAndValuePairs()),
      m_detailsFromTheScreen(m_configuration, m_screenMonitoring),
      m_detailsOnTheEngine(),
      m_calculationDetails{},
      m_engineWasJustReset(true),
      m_hasPendingPrintAction(false) {
    initialize();
}

void ChessPeek::runForever() {
    thread trackKeyPressThread(trackKeyPress);
    while (shouldStillRun) {
        runOneIteration();
        Sleep(1);
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
    if (didPlayerChange()) {
        m_engineController.resetToNewGame();
    }

    m_detailsOnTheEngine.save(m_detailsFromTheScreen.getBoardWithContext());

    m_engineController.setupFenString(m_detailsOnTheEngine.getBoardWithContext().getFenString());
    if (!m_engineController.waitTillReadyAndReturnIfResetWasPerformed()) {
        m_engineController.goWithPonder();
        m_engineWasJustReset = false;
    } else {
        m_engineWasJustReset = true;
    }
}

void ChessPeek::calculationMonitoringCallBackForEngine(EngineCalculationDetails const& calculationDetails) {
    CalculationDetails previousCalculationDetails = m_calculationDetails;
    saveCalculationDetails(calculationDetails);
    if (previousCalculationDetails != m_calculationDetails) {
        printCalculationDetailsWithFiltering();
    }
}

void ChessPeek::initialize() {
    // m_engineHandler.setLogFile(APRG_DIR R"(\Chess\ChessPeek\Files\EngineHandler.log)");  // for debugging
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
    if (!engineCalculationDetails.currentMovesAndScores.empty()) {
        m_calculationDetails.currentMovesAndScores = engineCalculationDetails.currentMovesAndScores;
    }
    m_calculationDetails.scoreInMonitoredVariation = engineCalculationDetails.scoreInMonitoredVariation;
    if (!engineCalculationDetails.monitoredVariation.empty()) {
        m_calculationDetails.monitoredVariation = engineCalculationDetails.monitoredVariation;
    }
    if (!engineCalculationDetails.commonMovesAndCountsOfEachStep.empty()) {
        m_calculationDetails.commonMovesAndCountsOfEachStep = engineCalculationDetails.commonMovesAndCountsOfEachStep;
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
    if (!currentlyPrinting) {
        m_hasPendingPrintAction = false;
        currentlyPrinting = true;
        ResultPrinter(m_detailsOnTheEngine.getBoardWithContext(), m_calculationDetails).print();
        currentlyPrinting = false;
    } else {
        m_hasPendingPrintAction = true;
    }
}

bool ChessPeek::shouldAnalyzeBoard() const {
    return m_detailsFromTheScreen.canAnalyzeBoard() && (m_engineWasJustReset || didBoardChange());
}

bool ChessPeek::didPlayerChange() const {
    return m_detailsFromTheScreen.getBoardWithContext().getPlayerColor() !=
           m_detailsOnTheEngine.getBoardWithContext().getPlayerColor();
}

bool ChessPeek::didBoardChange() const {
    return m_detailsFromTheScreen.getBoardWithContext().getBoard() !=
           m_detailsOnTheEngine.getBoardWithContext().getBoard();
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
