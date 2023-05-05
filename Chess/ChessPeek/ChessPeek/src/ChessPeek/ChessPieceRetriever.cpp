#include "ChessPieceRetriever.hpp"

#include <ChessPeek/ColorUtilities.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <bitset>
#include <iostream>

using namespace alba::mathHelper;
using namespace std;
namespace alba {

namespace chess {

ChessPieceRetriever::ChessPieceRetriever(
    ChessPeekConfiguration const& configuration, AlbaLocalScreenMonitoring const& screenMonitoring)
    : m_configuration(configuration), m_screenMonitoring(screenMonitoring) {
    initialize(configuration.getType());
}

Piece ChessPieceRetriever::getChessCellPiece(int const xIndex, int const yIndex) const {
    return Piece(getBestPieceFromChessCellBitValue(getChessCellBitValue(xIndex, yIndex).to_ullong()));
}

ChessPieceRetriever::BitSet64 ChessPieceRetriever::getChessCellBitValue(int const xIndex, int const yIndex) const {
    XY chessCellTopLeft, chessCellBottomRight;
    retrieveChessCellTopLeftAndBottomRight(chessCellTopLeft, chessCellBottomRight, xIndex, yIndex);

    BitSet64 result;  // The object is initialized with zeros.
    int index(0U);
    for (CheckDetail const& checkDetail : m_checkDetails) {
        if (isBitValueAsserted(checkDetail, chessCellTopLeft, chessCellBottomRight)) {
            result.set(63 - index, 1U);
        }
        if (index >= 63) {            break;
        }
        index++;
    }

    return result;
}

void ChessPieceRetriever::retrieveWhiteOffsetPoints(XYs& bitmapXYs, int const xIndex, int const yIndex) const {
    retrieveOffsetPointsWithCondition(bitmapXYs, xIndex, yIndex, [&](double const colorIntensity) {
        return colorIntensity > m_configuration.getWhiteColorLimit();
    });
}

void ChessPieceRetriever::retrieveBlackOffsetPoints(XYs& bitmapXYs, int const xIndex, int const yIndex) const {
    retrieveOffsetPointsWithCondition(bitmapXYs, xIndex, yIndex, [&](double const colorIntensity) {
        return colorIntensity < m_configuration.getBlackColorLimit();
    });
}

void ChessPieceRetriever::initialize(ChessPeekConfigurationType const type) {
    switch (type) {
        case ChessPeekConfigurationType::ChessDotComVersus: {
            initializeConverterToChessDotCom();
            break;
        }
        case ChessPeekConfigurationType::ChessDotComPuzzle: {
            initializeConverterToChessDotCom();  // same with chess.com (use this as approximation)
            break;
        }        case ChessPeekConfigurationType::LichessVersus: {
            initializeConverterToLichessVersus();
            break;
        }        case ChessPeekConfigurationType::LichessStream: {
            initializeConverterToLichessVersus();  // same with lichess.org (use this as approximation)
            break;
        }
    }
}

void ChessPieceRetriever::initializeConverterToChessDotCom() {
    m_checkMaxPoint = XY(102, 102);
    m_checkDetails =
        CheckDetails{{{17, 34}, WhiteOrBlack::White}, {{20, 40}, WhiteOrBlack::White}, {{21, 54}, WhiteOrBlack::White},
                     {{25, 47}, WhiteOrBlack::White}, {{28, 42}, WhiteOrBlack::White}, {{31, 25}, WhiteOrBlack::White},                     {{31, 52}, WhiteOrBlack::White}, {{32, 35}, WhiteOrBlack::White}, {{33, 47}, WhiteOrBlack::White},
                     {{34, 29}, WhiteOrBlack::White}, {{35, 39}, WhiteOrBlack::White}, {{39, 60}, WhiteOrBlack::White},
                     {{40, 48}, WhiteOrBlack::White}, {{41, 17}, WhiteOrBlack::White}, {{42, 42}, WhiteOrBlack::White},
                     {{49, 24}, WhiteOrBlack::White}, {{49, 51}, WhiteOrBlack::White}, {{50, 42}, WhiteOrBlack::White},                     {{51, 16}, WhiteOrBlack::White}, {{51, 34}, WhiteOrBlack::White}, {{51, 76}, WhiteOrBlack::White},
                     {{52, 84}, WhiteOrBlack::White}, {{54, 63}, WhiteOrBlack::White}, {{58, 42}, WhiteOrBlack::White},
                     {{60, 61}, WhiteOrBlack::White}, {{62, 28}, WhiteOrBlack::White}, {{62, 49}, WhiteOrBlack::White},
                     {{64, 18}, WhiteOrBlack::White}, {{69, 27}, WhiteOrBlack::White}, {{79, 54}, WhiteOrBlack::White},
                     {{81, 39}, WhiteOrBlack::White}, {{84, 34}, WhiteOrBlack::White}, {{19, 41}, WhiteOrBlack::Black},
                     {{23, 64}, WhiteOrBlack::Black}, {{24, 49}, WhiteOrBlack::Black}, {{20, 55}, WhiteOrBlack::Black},
                     {{27, 23}, WhiteOrBlack::Black}, {{27, 52}, WhiteOrBlack::Black}, {{32, 37}, WhiteOrBlack::Black},
                     {{32, 64}, WhiteOrBlack::Black}, {{35, 63}, WhiteOrBlack::Black}, {{38, 38}, WhiteOrBlack::Black},
                     {{38, 51}, WhiteOrBlack::Black}, {{41, 68}, WhiteOrBlack::Black}, {{42, 78}, WhiteOrBlack::Black},
                     {{50, 32}, WhiteOrBlack::Black}, {{51, 14}, WhiteOrBlack::Black}, {{52, 50}, WhiteOrBlack::Black},
                     {{52, 65}, WhiteOrBlack::Black}, {{52, 86}, WhiteOrBlack::Black}, {{55, 48}, WhiteOrBlack::Black},
                     {{62, 68}, WhiteOrBlack::Black}, {{62, 78}, WhiteOrBlack::Black}, {{63, 55}, WhiteOrBlack::Black},
                     {{66, 16}, WhiteOrBlack::Black}, {{67, 54}, WhiteOrBlack::Black}, {{67, 65}, WhiteOrBlack::Black},
                     {{73, 26}, WhiteOrBlack::Black}, {{74, 59}, WhiteOrBlack::Black}, {{76, 25}, WhiteOrBlack::Black},
                     {{80, 48}, WhiteOrBlack::Black}, {{83, 39}, WhiteOrBlack::Black}, {{86, 52}, WhiteOrBlack::Black},
                     {{87, 33}, WhiteOrBlack::Black}};
    m_piecesToChessCellBitValuesMap[PieceColorAndType::Empty] = 0;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhitePawn] =
        0B0000000000000010110111010000000000000000011100000001000100000000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteKnight] =
        0B0011101111101111010111111110000000000000000000010000000000001000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteBishop] =
        0B0000001010111011001011111010000000000110000001010010000000100000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteRook] =
        0B0000010101111001100111101000100000001001000000000000000101010000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteQueen] =
        0B1101001000011110100011111111001100000000000000000000000000001001;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteKing] =
        0B0111100100100011111111110000011000000000000000000000000000000000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackPawn] =
        0B0000000000000000000000000000000000000000011111011111110100000000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackKnight] =
        0B0000000000000000000000000000000000110110011111011111110110101000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackBishop] =
        0B0000000000000000000000000000000000000111111111111111110110100000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackRook] =
        0B0000000000000000000000000000000000001011111111011111110111010000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackQueen] =
        0B0000000000000000000000000000000010100101111110011111111110101101;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackKing] =
        0B0000000000000000000000000000000011110111110111111111100010101110;
}

void ChessPieceRetriever::initializeConverterToLichessVersus() {
    m_checkMaxPoint = XY(93, 93);
    m_checkDetails =
        CheckDetails{{{12, 25}, WhiteOrBlack::White}, {{16, 44}, WhiteOrBlack::White}, {{17, 59}, WhiteOrBlack::White},
                     {{22, 49}, WhiteOrBlack::White}, {{26, 42}, WhiteOrBlack::White}, {{27, 25}, WhiteOrBlack::White},                     {{29, 18}, WhiteOrBlack::White}, {{33, 44}, WhiteOrBlack::White}, {{33, 53}, WhiteOrBlack::White},
                     {{38, 33}, WhiteOrBlack::White}, {{39, 46}, WhiteOrBlack::White}, {{41, 51}, WhiteOrBlack::White},
                     {{46, 16}, WhiteOrBlack::White}, {{47, 26}, WhiteOrBlack::White}, {{47, 39}, WhiteOrBlack::White},
                     {{47, 49}, WhiteOrBlack::White}, {{47, 79}, WhiteOrBlack::White}, {{54, 46}, WhiteOrBlack::White},                     {{56, 33}, WhiteOrBlack::White}, {{61, 43}, WhiteOrBlack::White}, {{61, 53}, WhiteOrBlack::White},
                     {{64, 19}, WhiteOrBlack::White}, {{67, 25}, WhiteOrBlack::White}, {{67, 45}, WhiteOrBlack::White},
                     {{67, 62}, WhiteOrBlack::White}, {{70, 50}, WhiteOrBlack::White}, {{71, 42}, WhiteOrBlack::White},
                     {{71, 67}, WhiteOrBlack::White}, {{73, 47}, WhiteOrBlack::White}, {{76, 67}, WhiteOrBlack::White},
                     {{77, 44}, WhiteOrBlack::White}, {{81, 25}, WhiteOrBlack::White}, {{12, 25}, WhiteOrBlack::Black},
                     {{13, 59}, WhiteOrBlack::Black}, {{14, 79}, WhiteOrBlack::Black}, {{15, 32}, WhiteOrBlack::Black},
                     {{20, 39}, WhiteOrBlack::Black}, {{21, 48}, WhiteOrBlack::Black}, {{23, 24}, WhiteOrBlack::Black},
                     {{25, 19}, WhiteOrBlack::Black}, {{25, 54}, WhiteOrBlack::Black}, {{28, 22}, WhiteOrBlack::Black},
                     {{29, 19}, WhiteOrBlack::Black}, {{29, 44}, WhiteOrBlack::Black}, {{34, 48}, WhiteOrBlack::Black},
                     {{39, 47}, WhiteOrBlack::Black}, {{46, 48}, WhiteOrBlack::Black}, {{46, 79}, WhiteOrBlack::Black},
                     {{47, 26}, WhiteOrBlack::Black}, {{47, 38}, WhiteOrBlack::Black}, {{53, 48}, WhiteOrBlack::Black},
                     {{60, 48}, WhiteOrBlack::Black}, {{64, 15}, WhiteOrBlack::Black}, {{64, 19}, WhiteOrBlack::Black},
                     {{68, 19}, WhiteOrBlack::Black}, {{69, 54}, WhiteOrBlack::Black}, {{70, 50}, WhiteOrBlack::Black},
                     {{71, 23}, WhiteOrBlack::Black}, {{73, 64}, WhiteOrBlack::Black}, {{76, 76}, WhiteOrBlack::Black},
                     {{79, 31}, WhiteOrBlack::Black}, {{79, 79}, WhiteOrBlack::Black}, {{80, 67}, WhiteOrBlack::Black},
                     {{81, 25}, WhiteOrBlack::Black}};
    m_piecesToChessCellBitValuesMap[PieceColorAndType::Empty] = 0;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhitePawn] =
        0B0000000000110111110000000000000000000000000010000001000000000000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteKnight] =
        0B0011100111100110111110011111110001001000011000110100000000010110;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteBishop] =
        0B0000000101111101011100000000000000100000000100010100000000010100;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteRook] =
        0B0000010111110111111110100000000000000011001100010000011001010000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteQueen] =
        0B1001001110001011100101000100100100011001110101001110101100001000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::WhiteKing] =
        0B0101100110110010110110010110101000000000000000101000000000000000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackPawn] =
        0B0000000000000000000000000000000000000000000011111111000000000000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackKnight] =
        0B0000000000000000000000000010110001001100111111111111000110100110;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackBishop] =
        0B0000000000010010000000000000000000100000000111111011000000010100;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackRook] =
        0B0000000001000000001000000000000000000011011111111111011001010000;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackQueen] =
        0B0000000000000000000000000000000010011101111111111111111110001001;
    m_piecesToChessCellBitValuesMap[PieceColorAndType::BlackKing] =
        0B0000000000000001000000001000000000001100100111011111000110000000;
}

bool ChessPieceRetriever::isBitValueAsserted(
    CheckDetail const& checkDetail, XY const& chessCellTopLeft, XY const& chessCellBottomRight) const {
    static const XYs aroundOffsets{XY(0, -1), XY(0, 1), XY(-1, 0), XY(1, 0)};

    bool result(false);
    int deltaX = chessCellBottomRight.getX() - chessCellTopLeft.getX();
    int deltaY = chessCellBottomRight.getY() - chessCellTopLeft.getY();
    int offsetInX = getIntegerAfterRoundingADoubleValue<int>(
        static_cast<double>(checkDetail.pointOffset.getX()) * deltaX / m_checkMaxPoint.getX());
    int offsetInY = getIntegerAfterRoundingADoubleValue<int>(
        static_cast<double>(checkDetail.pointOffset.getY()) * deltaY / m_checkMaxPoint.getY());
    XY pointToCheck{chessCellTopLeft.getX() + offsetInX, chessCellTopLeft.getY() + offsetInY};
    uint32_t colorToCheck(m_screenMonitoring.getColorAt(pointToCheck.getX(), pointToCheck.getY()));
    double currentIntensity(calculateColorIntensityDecimal(colorToCheck));
    if (WhiteOrBlack::White == checkDetail.condition) {
        double maximum(currentIntensity);
        for (XY const& aroundOffset : aroundOffsets) {
            XY pointWithOffset = pointToCheck + aroundOffset;
            currentIntensity = calculateColorIntensityDecimal(
                m_screenMonitoring.getColorAt(pointWithOffset.getX(), pointWithOffset.getY()));
            if (maximum < currentIntensity) {
                maximum = currentIntensity;
            }        }
        result = maximum > m_configuration.getWhiteColorLimit();
    } else if (WhiteOrBlack::Black == checkDetail.condition) {
        double minimum(currentIntensity);
        for (XY const& aroundOffset : aroundOffsets) {
            XY pointWithOffset = pointToCheck + aroundOffset;
            currentIntensity = calculateColorIntensityDecimal(
                m_screenMonitoring.getColorAt(pointWithOffset.getX(), pointWithOffset.getY()));
            if (minimum > currentIntensity) {
                minimum = currentIntensity;
            }        }
        result = minimum < m_configuration.getBlackColorLimit();
    }
    return result;}

PieceColorAndType ChessPieceRetriever::getBestPieceFromChessCellBitValue(uint64_t const chessCellBitValue) const {
    PieceColorAndTypes bestFitPieces(getBestFitPiecesFromChessCellBitValue(chessCellBitValue));

    PieceColorAndType result{};
    if (bestFitPieces.size() == 1) {
        result = bestFitPieces.back();
    }
    /*if (chessCellBitValue == 0b1001001100001011100101000100100100011001110101001010101100001000) {
        bitset<64> bitsetValue(chessCellBitValue);
        cout << "Cannot determine bestFitType with bitValue: " << bitsetValue.to_string() << "\n";
        cout << "BestFitTypes with size " << bestFitPieces.size() << " :{";
        for (PieceColorAndType const bestFitPiece : bestFitPieces) {
            cout << getEnumString(bestFitPiece) << ", ";
        }
        cout << "}\n";
    }*/
    return result;
}
ChessPieceRetriever::PieceColorAndTypes ChessPieceRetriever::getBestFitPiecesFromChessCellBitValue(
    uint64_t const chessCellBitValue) const {
    PieceColorAndTypes result;    Count minimumDifferenceCount(65U);
    for (auto& pieceAndChessCellBitValuePair : m_piecesToChessCellBitValuesMap) {
        PieceColorAndType piece(pieceAndChessCellBitValuePair.first);
        uint64_t pieceChessCellBitValue(pieceAndChessCellBitValuePair.second);
        Count differenceCount =
            static_cast<Count>(BitValueUtilities::getNumberOfOnes(pieceChessCellBitValue ^ chessCellBitValue));
        if (minimumDifferenceCount > differenceCount) {
            minimumDifferenceCount = differenceCount;
            result.clear();
            result.emplace_back(piece);
        } else if (minimumDifferenceCount == differenceCount) {
            result.emplace_back(piece);
        }
    }
    return result;
}

void ChessPieceRetriever::retrieveChessCellTopLeftAndBottomRight(
    XY& chessCellTopLeft, XY& chessCellBottomRight, int const xIndex, int const yIndex) const {
    double startX = m_configuration.getBoardTopLeft().getX();
    double startY = m_configuration.getBoardTopLeft().getY();
    double endX = m_configuration.getBoardBottomRight().getX();
    double endY = m_configuration.getBoardBottomRight().getY();
    double deltaX = (endX - startX) / 8;
    double deltaY = (endY - startY) / 8;
    chessCellTopLeft =
        XY{static_cast<int>(round(startX + deltaX * xIndex)), static_cast<int>(round(startY + deltaY * yIndex))};
    chessCellBottomRight =
        XY{static_cast<int>(round(startX + deltaX * (xIndex + 1))),
           static_cast<int>(round(startY + deltaY * (yIndex + 1)))};
}

void ChessPieceRetriever::retrieveOffsetPointsWithCondition(
    XYs& bitmapXYs, int const xIndex, int const yIndex, BoolFunction const& condition) const {
    double startX = m_configuration.getBoardTopLeft().getX();
    double startY = m_configuration.getBoardTopLeft().getY();
    double endX = m_configuration.getBoardBottomRight().getX();
    double endY = m_configuration.getBoardBottomRight().getY();
    double deltaX = (endX - startX) / 8;
    double deltaY = (endY - startY) / 8;
    XY chessCellTopLeft{
        static_cast<int>(round(startX + deltaX * xIndex)), static_cast<int>(round(startY + deltaY * yIndex))};
    XY chessCellBottomRight{
        static_cast<int>(round(startX + deltaX * (xIndex + 1))),
        static_cast<int>(round(startY + deltaY * (yIndex + 1)))};

    int xLimit = chessCellBottomRight.getX() - chessCellTopLeft.getX();
    int yLimit = chessCellBottomRight.getY() - chessCellTopLeft.getY();
    for (int x = 0U; x < xLimit; x++) {
        for (int y = 0U; y < yLimit; y++) {
            if (condition(calculateColorIntensityDecimal(
                    m_screenMonitoring.getColorAt(chessCellTopLeft.getX() + x, chessCellTopLeft.getY() + y)))) {
                bitmapXYs.emplace_back(x, y);
            }
        }
    }
}

}  // namespace chess

}  // namespace alba