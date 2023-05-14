#pragma once

#include <ChessPeek/Book.hpp>
#include <ChessPeek/CalculationDetails.hpp>
#include <ChessPeek/Configuration.hpp>
#include <ChessPeek/DetailsFromTheScreen.hpp>
#include <ChessPeek/DetailsOnTheEngine.hpp>
#include <ChessUtilities/ChessEngineControllerWithUci.hpp>
#include <ChessUtilities/ChessEngineHandler.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

namespace alba {

namespace chess {

namespace ChessPeek {
class ChessPeek {
public:
    using EngineCalculationDetails = chess::CalculationDetails;

    ChessPeek();

    void runForever();
    void runOneIteration();
    void checkScreenAndSaveDetails();
    void startEngineAnalysisWithBoardFromScreen();
    void calculationMonitoringCallBackForEngine(EngineCalculationDetails const& engineCalculationDetails);

private:
    void initialize();
    void saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails);

    void printCalculationDetailsWithFiltering();
    void printCalculationDetailsIfPending();
    void printCalculationDetails();

    Move getPerformedMove() const;

    bool shouldAnalyzeBoard() const;
    bool didPlayerChange() const;
    bool didBoardChange() const;

    Configuration m_configuration;
    ChessEngineHandler m_engineHandler;
    ChessEngineControllerWithUci m_engineController;
    AlbaLocalTimer m_printFilteringTimer;
    DetailsFromTheScreen m_detailsFromTheScreen;
    DetailsOnTheEngine m_detailsOnTheEngine;
    Book m_book;
    CalculationDetails m_calculationDetails;
    CalculationDetails m_printCalculationDetails;
    bool m_engineWasJustReset;
    bool m_hasPendingPrintAction;
};

}  // namespace ChessPeek
}  // namespace chess

}  // namespace alba
