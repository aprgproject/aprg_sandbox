#pragma once

#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/ChessPieceConverter.hpp>
#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/ChessEngineControllerWithUci.hpp>
#include <ChessUtilities/ChessEngineHandler.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <bitset>#include <cstdint>

namespace alba
{
namespace chess
{

struct CoordinateSquare
{
    unsigned int left;
    unsigned int right;
    unsigned int top;
    unsigned int bottom;
};

class ChessPeek
{
public:
    ChessPeek();
    using BitSet64 = std::bitset<64>;
    using ChessCellBitValueMatrix = matrix::AlbaMatrix<uint64_t>;
    using CalculationDetails=ChessEngineControllerWithUci::CalculationDetails;

    ChessCellBitValueMatrix const& getChessCellBitValueMatrix() const;
    void runForever();
    void runOneIteration();

    void checkScreenAndSaveDetails();
    void startNewAnalysisUsingEngine();
    void checkCalculationDetails(CalculationDetails const& calculationDetails);

private:
    void checkSnippetAndSaveDetails(AprgBitmap::BitmapSnippet & snippet);
    void updatePlayerSideAndOrientation(unsigned int const pieceCount);

    void printCalculationDetails(CalculationDetails const& calculationDetails) const;
    void printDisplayTable(alba::stringHelper::strings const& movesToDisplay) const;
    DisplayTable getDisplayTable(alba::stringHelper::strings const& movesToDisplayString) const;
    std::string getBestMoveToDisplayString(CalculationDetails const& calculationDetails) const;
    alba::stringHelper::strings getMovesToDisplayStrings(CalculationDetails const& calculationDetails, std::string const& bestMoveToDisplay) const;
    std::string getCellInDisplayTable(Coordinate const& coordinate, Move const& moveToDisplay) const;

    void retrieveChessCellBitValueAt(BitSet64 & whiteValue, BitSet64 & blackValue, AprgBitmap::BitmapSnippet & snippet, CoordinateSquare const& square) const;
    void setBitsBasedFromColor(BitSet64 & whiteValue, BitSet64 & blackValue, unsigned int const index, AprgBitmap::BitmapSnippet const& snippet, AprgBitmap::BitmapXY const& bitmapCoordinate) const;
    double calculateColorIntensityDecimal(uint32_t const color) const;    uint8_t extractRed(uint32_t const color) const;
    uint8_t extractGreen(uint32_t const color) const;
    uint8_t extractBlue(uint32_t const color) const;
    void initialize();
    ChessEngineHandler m_chessEngineHandler;
    ChessEngineControllerWithUci m_chessEngineController;
    ChessPieceConverter m_chessPieceConverter;
    AlbaLocalUserAutomation m_userAutomation;
    ChessCellBitValueMatrix m_chessCellBitValueMatrix;
    Board m_chessBoard;
    PieceColor m_playerSideColor;
    std::string m_currentBestMoveOnDisplay;
    bool m_isPreviousAnalysisNotSuccessful;
};
}

}