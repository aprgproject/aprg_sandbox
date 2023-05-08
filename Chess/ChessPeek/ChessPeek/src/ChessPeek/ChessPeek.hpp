#pragma once

#include <ChessPeek/CalculationDetails.hpp>
#include <ChessPeek/Configuration.hpp>
#include <ChessPeek/DetailsFromTheScreen.hpp>
#include <ChessPeek/DetailsOnTheEngine.hpp>
#include <ChessUtilities/ChessEngineControllerWithUci.hpp>
#include <ChessUtilities/ChessEngineHandler.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>
#include <ScreenMonitoring/AlbaLocalScreenMonitoring.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {

class ChessPeek {
public:
    using ChessCellBitValueMatrix = matrix::AlbaMatrix<uint64_t>;
    using EngineCalculationDetails = chess::CalculationDetails;

    ChessPeek();

    void runForever();
    void runOneIteration();

    void checkScreenAndSaveDetails();
    void startEngineAnalysis();
    void calculationMonitoringCallBackForEngine(EngineCalculationDetails const& engineCalculationDetails);

private:
    bool shouldAnalyzeBoard() const;
    bool didBoardFromScreenChange() const;

    void initialize();
    void saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails);

    void printCalculationDetailsWithFiltering();
    void printCalculationDetailsIfPending();
    void printCalculationDetails();

    Configuration m_configuration;
    AlbaLocalScreenMonitoring m_screenMonitoring;
    ChessEngineHandler m_engineHandler;
    ChessEngineControllerWithUci m_engineController;
    AlbaLocalTimer m_printFilteringTimer;
    DetailsFromTheScreen m_detailsFromTheScreen;
    DetailsOnTheEngine m_detailsOnTheEngine;
    CalculationDetails m_calculationDetails;
    bool m_isEngineNewlyReseted;
    bool m_hasPendingPrintAction;
};

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
