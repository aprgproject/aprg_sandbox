#pragma once

#include <ChessPeek/ChessPeekConfiguration.hpp>
#include <ChessPeek/CommonTypes.hpp>
#include <ChessUtilities/Board/BoardTypes.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <ScreenMonitoring/AlbaLocalScreenMonitoring.hpp>

#include <array>
#include <bitset>#include <cstdint>
#include <fstream>
#include <functional>
#include <map>#include <optional>

namespace alba {

namespace chess {

class ChessPieceRetriever {
public:
    enum class WhiteOrBlack { White, Black };
    struct CheckDetail {
        XY pointOffset;
        WhiteOrBlack condition;
    };
    using BitSet64 = std::bitset<64>;    using Count = unsigned int;
    using PieceToChessCellBitValueMap = std::map<PieceColorAndType, uint64_t>;
    using BitValueUtilities = AlbaBitValueUtilities<uint64_t>;
    using PieceColorAndTypes = std::vector<PieceColorAndType>;    using CheckDetails = std::vector<CheckDetail>;
    using BoolFunction = std::function<bool(double const)>;

    ChessPieceRetriever() = delete;
    ChessPieceRetriever(ChessPeekConfiguration const& configuration, AlbaLocalScreenMonitoring const& screenMonitoring);

    Piece getChessCellPiece(int const xIndex, int const yIndex) const;
    BitSet64 getChessCellBitValue(int const xIndex, int const yIndex) const;

    void retrieveWhiteOffsetPoints(XYs& coordinates, int const xIndex, int const yIndex) const;
    void retrieveBlackOffsetPoints(XYs& coordinates, int const xIndex, int const yIndex) const;

private:
    void initialize(ChessPeekConfigurationType const type);    void initializeConverterToChessDotCom();
    void initializeConverterToLichessVersus();

    bool isBitValueAsserted(
        CheckDetail const& checkDetail, XY const& chessCellTopLeft, XY const& chessCellBottomRight) const;

    PieceColorAndType getBestPieceFromChessCellBitValue(uint64_t const chessCellBitValue) const;
    PieceColorAndTypes getBestFitPiecesFromChessCellBitValue(uint64_t const chessCellBitValue) const;

    void retrieveChessCellTopLeftAndBottomRight(
        XY& chessCellTopLeft, XY& chessCellBottomRight, int const xIndex, int const yIndex) const;
    void retrieveOffsetPointsWithCondition(
        XYs& coordinates, int const xIndex, int const yIndex, BoolFunction const& condition) const;

    ChessPeekConfiguration const& m_configuration;
    AlbaLocalScreenMonitoring const& m_screenMonitoring;
    XY m_checkMaxPoint;
    CheckDetails m_checkDetails;
    PieceToChessCellBitValueMap m_piecesToChessCellBitValuesMap;
};

}  // namespace chess
}  // namespace alba