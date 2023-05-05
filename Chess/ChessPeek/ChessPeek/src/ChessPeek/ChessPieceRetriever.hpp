#pragma once

#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/ChessPeekConfiguration.hpp>
#include <ChessUtilities/Board/BoardTypes.hpp>
#include <ChessUtilities/Board/Piece.hpp>
#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <array>
#include <bitset>
#include <cstdint>
#include <fstream>
#include <functional>
#include <map>
#include <optional>

namespace alba {

namespace chess {

class ChessPieceRetriever {
public:
    enum class WhiteOrBlack { White, Black };
    struct CheckDetail {
        AprgBitmap::BitmapXY pointOffset;
        WhiteOrBlack condition;
    };
    using BitSet64 = std::bitset<64>;
    using Count = unsigned int;
    using PieceToChessCellBitValueMap = std::map<PieceColorAndType, uint64_t>;
    using BitValueUtilities = AlbaBitValueUtilities<uint64_t>;
    using PieceColorAndTypes = std::vector<PieceColorAndType>;
    using CheckDetails = std::vector<CheckDetail>;
    using BoolFunction = std::function<bool(double const)>;

    ChessPieceRetriever() = delete;
    ChessPieceRetriever(ChessPeekConfiguration const& configuration);

    Piece getChessCellPiece(
        AprgBitmap::BitmapSnippet const& chessBoardSnippet, unsigned int const xIndex, unsigned int const yIndex) const;
    BitSet64 getChessCellBitValue(
        AprgBitmap::BitmapSnippet const& chessBoardSnippet, unsigned int const xIndex, unsigned int const yIndex) const;

    void retrieveWhiteOffsetPoints(
        AprgBitmap::BitmapXYs& bitmapXYs, AprgBitmap::BitmapSnippet const& chessBoardSnippet, unsigned int const xIndex,
        unsigned int const yIndex) const;
    void retrieveBlackOffsetPoints(
        AprgBitmap::BitmapXYs& bitmapXYs, AprgBitmap::BitmapSnippet const& chessBoardSnippet, unsigned int const xIndex,
        unsigned int const yIndex) const;

    void setLogFile(std::string const& logFilePath);

private:
    void initialize(ChessPeekConfigurationType const type);
    void initializeConverterToChessDotCom();
    void initializeConverterToLichessVersus();

    bool isBitValueAsserted(
        AprgBitmap::BitmapSnippet const& chessBoardSnippet, CheckDetail const& checkDetail,
        AprgBitmap::BitmapXY const& chessCellTopLeft, AprgBitmap::BitmapXY const& chessCellBottomRight) const;

    PieceColorAndType getBestPieceFromChessCellBitValue(uint64_t const chessCellBitValue) const;
    PieceColorAndTypes getBestFitPiecesFromChessCellBitValue(uint64_t const chessCellBitValue) const;

    void retrieveChessCellTopLeftAndBottomRight(
        AprgBitmap::BitmapXY& chessCellTopLeft, AprgBitmap::BitmapXY& chessCellBottomRight,
        AprgBitmap::BitmapSnippet const& chessBoardSnippet, unsigned int const xIndex, unsigned int const yIndex) const;
    void retrieveOffsetPointsWithCondition(
        AprgBitmap::BitmapXYs& bitmapXYs, AprgBitmap::BitmapSnippet const& chessBoardSnippet, unsigned int const xIndex,
        unsigned int const yIndex, BoolFunction const& condition) const;

    double calculateColorIntensityDecimal(uint32_t const color) const;
    uint8_t extractRed(uint32_t const color) const;
    uint8_t extractGreen(uint32_t const color) const;
    uint8_t extractBlue(uint32_t const color) const;

    ChessPeekConfiguration m_configuration;
    AprgBitmap::BitmapXY m_checkMaxPoint;
    CheckDetails m_checkDetails;
    PieceToChessCellBitValueMap m_piecesToChessCellBitValuesMap;
    std::optional<std::ofstream> m_logFileStreamOptional;
};

}  // namespace chess

}  // namespace alba
