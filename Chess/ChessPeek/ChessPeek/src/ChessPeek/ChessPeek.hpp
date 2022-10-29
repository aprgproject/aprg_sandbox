#pragma once

#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/ChessPeekConfiguration.hpp>
#include <ChessPeek/ChessPieceConverter.hpp>
#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/ChessEngineControllerWithUci.hpp>#include <ChessUtilities/ChessEngineHandler.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <bitset>
#include <cstdint>

namespace alba
{

namespace chess
{

class ChessPeek
{
public:
    using BitSet64 = std::bitset<64>;
    using ChessCellBitValueMatrix = matrix::AlbaMatrix<uint64_t>;
    using EngineCalculationDetails=CalculationDetails;    using BoardAndMovePair = std::pair<Board, Move>;
    using BoardAndMovePairs = std::vector<BoardAndMovePair>;

    struct ChessCellCoordinates
    {
        unsigned int left;
        unsigned int right;
        unsigned int top;
        unsigned int bottom;
    };

    struct PeekCalculationDetails
    {
        unsigned int depth;
        int scoreInCentipawns;
        unsigned int mateInNumberOfMoves;
        std::string bestMove;
        stringHelper::strings currentlySearchingMoves;
        stringHelper::strings pvMovesInBestLine;
    };

    ChessPeek();

    void runForever();
    void runOneIteration();

    void checkScreenAndSaveDetails();
    void startEngineAnalysisOfNewPosition();
    void calculationMonitoringCallBackForEngine(EngineCalculationDetails const& engineCalculationDetails);

private:
    bool didBoardChange(Board::PieceMatrix const& previousPieceMatrix) const;
    bool canAnalyzeBoard() const;
    bool doCorrectKingsExist() const;
    bool isPlayerKingAndOpponentKingValid() const;
    bool isOpponentKingOnCheck() const;

    void checkSnippetAndSaveDetails(AprgBitmap::BitmapSnippet & snippet);
    ChessCellCoordinates getChessCellCoordinates(unsigned int const i,  unsigned int const j, double const startX, double const startY, double const deltaX, double const deltaY);    Piece getChessPieceIfPossible(BitSet64 const& blackValue, BitSet64 const& whiteValue);
    void updatePlayerSideAndOrientation(unsigned int const pieceCount);
    void setOrientationDependingOnPlayerColor(PieceColor const newColor);
    void setKingDetailsIfPossible(Coordinate const& chessCoordinate, Piece const& chessPiece);

    void saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails);
    void checkCalculationDetailsFromEngine();

    Moves getCurrentMoves(std::string const& bestMoveToDisplay) const;
    Moves getFutureMoves() const;
    std::string getBestMoveToDisplayString() const;

    void printCalculationDetails() const;
    void printMoveTables(Moves const& currentMoves, Moves const& futureMoves) const;
    void putSeparators(DisplayTable & displayTable) const;
    void putCurrentMovesTable(Moves const& currentMoves) const;
    void printFutureMovesTable(Moves const& futureMoves) const;
    std::string getChessCellForDisplay(Piece const& piece, unsigned int const moveNumberStart) const;
    unsigned int getNumberOfColumnsOfDisplayTable(unsigned int const numberOfChessBoards) const;

    void retrieveChessCellDataBasedFromPixels(BitSet64 & whiteValue, BitSet64 & blackValue, AprgBitmap::BitmapSnippet & snippet, ChessCellCoordinates const& square) const;
    void retrieveDataBasedFromPixel(BitSet64 & whiteValue, BitSet64 & blackValue, unsigned int const index, AprgBitmap::BitmapSnippet const& snippet, AprgBitmap::BitmapXY const& bitmapCoordinate) const;    double calculateColorIntensityDecimal(uint32_t const color) const;
    uint8_t extractRed(uint32_t const color) const;
    uint8_t extractGreen(uint32_t const color) const;
    uint8_t extractBlue(uint32_t const color) const;
    void initialize();

    ChessPeekConfiguration m_configuration;
    ChessPieceConverter m_chessPieceConverter;
    ChessEngineHandler m_chessEngineHandler;
    ChessEngineControllerWithUci m_chessEngineController;
    AlbaLocalUserAutomation m_userAutomation;
    PeekCalculationDetails m_savedCalculationDetails;
    Board m_chessBoard;    PieceColor m_playerColor;
    Coordinate m_playerKingCoordinate;
    Coordinate m_opponentKingCoordinate;
    unsigned int m_numberOfDetectedKings;
    bool m_isEngineNewlyReseted;
};

}

}
