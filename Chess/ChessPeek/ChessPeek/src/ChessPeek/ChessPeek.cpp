#include "ChessPeek.hpp"

#include <ChessPeek/ResultPrinter.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <atomic>
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
        shouldStillRun = !userAutomation.isKeyPressed(VK_ESCAPE);
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
        startEngineAnalysisWithBoardFromScreen();
    }
}

void ChessPeek::checkScreenAndSaveDetails() {
    m_screenMonitoring.capturePixelsFromScreen();
    m_detailsFromTheScreen.saveDetailsFromTheScreen();
}

void ChessPeek::startEngineAnalysisWithBoardFromScreen() {
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
    if (!engineCalculationDetails.variations.empty()) {
        m_calculationDetails.variations = engineCalculationDetails.variations;
    }
    if (!engineCalculationDetails.bestMove.empty()) {
        m_calculationDetails.bestMove = engineCalculationDetails.bestMove;
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

Move ChessPeek::getPerformedMove() const {
    // this is a bad idea, still cant detect if the pieces are moved manually (by a human)
    Move result{};
    Board const& oldBoard(m_detailsOnTheEngine.getBoardWithContext().getBoard());
    Board const& newBoard(m_detailsFromTheScreen.getBoardWithContext().getBoard());

    Coordinates changedCoordinates;
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            Coordinate coordinate(i, j);
            Piece oldPiece(oldBoard.getPieceAt(coordinate));
            Piece newPiece(newBoard.getPieceAt(coordinate));
            if (oldPiece != newPiece) {
                changedCoordinates.emplace_back(coordinate);
                if (changedCoordinates.size() > 4) {
                    break;
                }
            }
        }
    }
    if (changedCoordinates.size() == 2) {
        Coordinate coordinate1(changedCoordinates.front());
        Coordinate coordinate2(changedCoordinates.back());
        bool isPossibleMove1 = oldBoard.isAPossibleMove({coordinate1, coordinate2});
        bool isPossibleMove2 = oldBoard.isAPossibleMove({coordinate2, coordinate1});
        if (isPossibleMove1 && !isPossibleMove2) {
            result = {coordinate1, coordinate2};
        } else if (!isPossibleMove1 && isPossibleMove2) {
            result = {coordinate2, coordinate1};
        }
    }
    return result;
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
