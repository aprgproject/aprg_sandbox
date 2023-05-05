#pragma once

#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/ChessPeekConfiguration.hpp>
#include <ChessPeek/ChessPieceRetriever.hpp>
#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/ChessEngineControllerWithUci.hpp>
#include <ChessUtilities/ChessEngineHandler.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <cstdint>

namespace alba {

namespace chess {

class ChessPeek {
public:
    using ChessCellBitValueMatrix = matrix::AlbaMatrix<uint64_t>;
    using EngineCalculationDetails = CalculationDetails;
    using BoardAndMovePair = std::pair<Board, Move>;
    using BoardAndMovePairs = std::vector<BoardAndMovePair>;

    struct PeekCalculationDetails {
        unsigned int depth;
        int scoreInCentipawns;
        unsigned int mateInNumberOfMoves;
        std::string bestMove;
        stringHelper::strings currentlySearchingMoves;
        stringHelper::strings pvMovesInBestLine;

        bool operator==(PeekCalculationDetails const& other) const;
        bool operator!=(PeekCalculationDetails const& other) const;
    };

    ChessPeek();

    void runForever();
    void runOneIteration();

    void saveBitmapOnScreen() const;
    void checkScreenAndSaveDetails();
    void startEngineAnalysisOfNewPosition();
    void calculationMonitoringCallBackForEngine(EngineCalculationDetails const& engineCalculationDetails);

private:
    bool didBoardChange(Board::PieceMatrix const& previousPieceMatrix) const;
    bool canAnalyzeBoard() const;
    bool doCorrectKingsExist() const;
    bool isPlayerKingAndOpponentKingValid() const;
    bool isOpponentKingOnCheck() const;
    bool isPlayerToMove() const;
    bool isPlayerToMoveInLichessVersus() const;

    void checkSnippetAndSaveDetails(AprgBitmap::BitmapSnippet& snippet);
    void updatePlayerColorAndOrientation(unsigned int const pieceCount);
    void updatePlayerColorIfLichessStream();
    void updatePlayerColorAndOrientationBasedOnPositionsOfTheKings(unsigned int const pieceCount);
    void setPlayerColorAndResetEngineIfNeeded(PieceColor const newColor);
    void setOrientationDependingOnBelowColor(PieceColor const belowColor);
    void setKingDetailsIfPossible(Coordinate const& chessCoordinate, Piece const& chessPiece);

    void saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails);
    void displayCalculationDetailsBasedFromTimer();
    void displayCalculationDetailsIfNotDisplayedYet();
    void printCalculationDetailsFromEngine();

    Moves getCurrentMoves(std::string const& bestMoveToDisplay) const;
    Moves getFutureMoves() const;
    std::string getBestMoveToDisplayString() const;

    void printCalculationDetails() const;
    void printMoveTables(Moves const& currentMoves, Moves const& futureMoves) const;
    void putSeparators(DisplayTable& displayTable) const;
    void putCurrentMovesTable(Moves const& currentMoves) const;
    void printFutureMovesTable(Moves const& futureMoves) const;
    std::string getChessCellForDisplay(
        Piece const& piece, unsigned int const moveNumberStart, bool const canPreMove) const;
    unsigned int getNumberOfColumnsOfDisplayTable(unsigned int const numberOfChessBoards) const;

    void initialize();

    ChessPeekConfiguration m_configuration;
    ChessPieceRetriever m_pieceRetriever;
    ChessEngineHandler m_chessEngineHandler;
    ChessEngineControllerWithUci m_chessEngineController;
    AlbaLocalUserAutomation m_userAutomation;
    AprgBitmap::Bitmap m_bitmap;
    AlbaLocalTimer m_displayTimer;
    PeekCalculationDetails m_savedCalculationDetails;
    Board m_chessBoard;
    PieceColor m_playerColor;
    Coordinate m_playerKingCoordinate;
    Coordinate m_opponentKingCoordinate;
    unsigned int m_numberOfDetectedKings;
    bool m_isEngineNewlyReseted;
    bool m_hasUnDisplayedCalculationDetails;
};

}  // namespace chess

}  // namespace alba
