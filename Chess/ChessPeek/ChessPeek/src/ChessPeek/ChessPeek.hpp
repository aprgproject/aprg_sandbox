#pragma once

#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/ChessPieceConverter.hpp>
#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/ChessEngineControllerWithUci.hpp>
#include <ChessUtilities/ChessEngineHandler.hpp>
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
    ChessPeek();
    using BitSet64 = std::bitset<64>;
    using ChessCellBitValueMatrix = matrix::AlbaMatrix<uint64_t>;
    using EngineCalculationDetails=CalculationDetails;
    using BoardAndMovePair = std::pair<Board, Move>;
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

    void runForever();
    void runOneIteration();

    void checkScreenAndSaveDetails();
    void startAnalysisUsingEngine();
    void calculationMonitoringCallBack(EngineCalculationDetails const& engineCalculationDetails);

    void setKingDetailsIfPossible(Coordinate chessCoordinate, Piece chessPiece, PieceColor opponentColor);

private:
    bool canAnalyzeBoard() const;
    bool doCorrectKingsExist() const;
    bool isPlayerKingAndOpponentKingValid() const;
    bool isOpponentKingOnCheck() const;
    void saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails);
    void checkCalculationDetails();

    void checkSnippetAndSaveDetails(AprgBitmap::BitmapSnippet & snippet);
    ChessCellCoordinates getChessCellCoordinates(unsigned int const i,  unsigned int const j, double const startX, double const startY, double const deltaX, double const deltaY);
    Piece getChessPieceIfPossible(BitSet64 const& blackValue, BitSet64 const& whiteValue);
    void updatePlayerSideAndOrientation(unsigned int const pieceCount);
    void setOrientationDependingOnPlayerColor(PieceColor const newColor);
    void setKingDetailsIfPossible(Coordinate const& chessCoordinate, Piece const& chessPiece);

    void printCalculationDetails() const;
    void printCurrentMovesIfNeeded(Moves const& currentMoves) const;
    void printFutureMovesIfNeeded(BoardAndMovePairs const& futureBoardsAndMoves) const;
    std::string getBestMoveToDisplayString() const;
    Moves getCurrentMoves(std::string const& bestMoveToDisplay) const;
    BoardAndMovePairs getFutureBoardsAndMoves() const;
    DisplayTable getDisplayTableForCurrentMoves(Moves const& currentMoves) const;
    DisplayTable getDisplayTableForFutureMoves(BoardAndMovePairs const& futureBoardsAndMoves) const;
    void addCellForSpaceIfNotFirst(bool & isFirst, DisplayTable & displayTable) const;
    std::string getCellInDisplayTable(
            Board const& chessBoard,
            Coordinate const& coordinate,
            Move const& moveToDisplay,
            unsigned int const moveNumberStart) const;

    void retrieveChessCellDataBasedFromPixels(BitSet64 & whiteValue, BitSet64 & blackValue, AprgBitmap::BitmapSnippet & snippet, ChessCellCoordinates const& square) const;
    void retrieveDataBasedFromPixel(BitSet64 & whiteValue, BitSet64 & blackValue, unsigned int const index, AprgBitmap::BitmapSnippet const& snippet, AprgBitmap::BitmapXY const& bitmapCoordinate) const;
    double calculateColorIntensityDecimal(uint32_t const color) const;
    uint8_t extractRed(uint32_t const color) const;
    uint8_t extractGreen(uint32_t const color) const;
    uint8_t extractBlue(uint32_t const color) const;
    void initialize();

    ChessEngineHandler m_chessEngineHandler;
    ChessEngineControllerWithUci m_chessEngineController;
    ChessPieceConverter m_chessPieceConverter;
    AlbaLocalUserAutomation m_userAutomation;
    PeekCalculationDetails m_savedCalculationDetails;
    Board m_chessBoard;
    PieceColor m_playerColor;
    Coordinate m_playerKingCoordinate;
    Coordinate m_opponentKingCoordinate;
    unsigned int m_numberOfDetectedKings;
    bool m_isEngineNewlyReseted;
};

}

}
