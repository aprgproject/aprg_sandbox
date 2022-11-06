#include "ChessPieceRetriever.hpp"

#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>

#include <bitset>
#include <iostream>



#include <Common/Debug/AlbaDebug.hpp>

using namespace alba::AprgBitmap;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace chess
{

ChessPieceRetriever::ChessPieceRetriever(
        ChessPeekConfiguration const& configuration)
    : m_configuration(configuration)
{
    initialize(configuration.getType());
}

Piece ChessPieceRetriever::getChessCellPiece(
        BitmapSnippet const& chessBoardSnippet,
        unsigned int const xIndex,
        unsigned int const yIndex) const
{
    return Piece(getPieceFromBitValue(m_piecesToChessCellValuesMap, getChessCellBitValue(chessBoardSnippet, xIndex, yIndex).to_ullong()));
}

ChessPieceRetriever::BitSet64 ChessPieceRetriever::getChessCellBitValue(
        BitmapSnippet const& chessBoardSnippet,
        unsigned int const xIndex,
        unsigned int const yIndex) const
{
    BitmapXY chessCellTopLeft, chessCellBottomRight;
    retrieveChessCellTopLeftAndBottomRight(chessCellTopLeft, chessCellBottomRight, chessBoardSnippet, xIndex, yIndex);

    BitSet64 result; // The object is initialized with zeros.
    unsigned int index(0U);
    for(CheckDetail const& checkDetail : m_checkDetails)
    {
        if(isBitValueAsserted(chessBoardSnippet, checkDetail, chessCellTopLeft, chessCellBottomRight))
        {
            result.set(63-index, 1U);
        }
        if(index >= 63)
        {
            break;
        }
        index++;
    }
    return result;
}

void ChessPieceRetriever::retrieveWhiteOffsetPoints(
        BitmapXYs & bitmapXYs,
        BitmapSnippet const& chessBoardSnippet,
        unsigned int const xIndex,
        unsigned int const yIndex) const
{
    retrieveOffsetPointsWithCondition(bitmapXYs, chessBoardSnippet, xIndex, yIndex, [&](double const colorIntensity)
    {
        return colorIntensity > m_configuration.getWhiteColorLimit();
    });
}

void ChessPieceRetriever::retrieveBlackOffsetPoints(
        BitmapXYs & bitmapXYs,
        BitmapSnippet const& chessBoardSnippet,
        unsigned int const xIndex,
        unsigned int const yIndex) const
{
    retrieveOffsetPointsWithCondition(bitmapXYs, chessBoardSnippet, xIndex, yIndex, [&](double const colorIntensity)
    {
        return colorIntensity < m_configuration.getBlackColorLimit();
    });
}

void ChessPieceRetriever::setLogFile(string const& logFilePath)
{
    m_logFileStreamOptional.createObjectUsingDefaultConstructor();
    m_logFileStreamOptional.getReference().open(logFilePath);

    if(!m_logFileStreamOptional.getReference().is_open())
    {
        cout << string("Cannot open log file") << logFilePath;
    }
}

void ChessPieceRetriever::initialize(ChessPeekConfigurationType const type)
{
    if(ChessPeekConfigurationType::ChessDotComUserVsUser == type
            || ChessPeekConfigurationType::ChessDotComUserVsComputer == type)
    {
        initializeConverterToChessDotCom();
    }
    else if(ChessPeekConfigurationType::LichessDotOrg == type)
    {
        initializeConverterToLichessDotOrg();
    }
}

void ChessPieceRetriever::initializeConverterToChessDotCom()
{
    m_checkMaxPoint = BitmapXY(102, 102);
    m_checkDetails = CheckDetails
    {{{17, 34}, WhiteOrBlack::White}, {{20, 40}, WhiteOrBlack::White}, {{21, 54}, WhiteOrBlack::White}, {{25, 47}, WhiteOrBlack::White},
    {{28, 42}, WhiteOrBlack::White}, {{31, 25}, WhiteOrBlack::White}, {{31, 52}, WhiteOrBlack::White}, {{32, 35}, WhiteOrBlack::White},
    {{33, 47}, WhiteOrBlack::White}, {{34, 29}, WhiteOrBlack::White}, {{35, 39}, WhiteOrBlack::White}, {{39, 60}, WhiteOrBlack::White},
    {{40, 48}, WhiteOrBlack::White}, {{41, 17}, WhiteOrBlack::White}, {{42, 42}, WhiteOrBlack::White}, {{49, 24}, WhiteOrBlack::White},
    {{49, 51}, WhiteOrBlack::White}, {{50, 42}, WhiteOrBlack::White}, {{51, 16}, WhiteOrBlack::White}, {{51, 34}, WhiteOrBlack::White},
    {{51, 76}, WhiteOrBlack::White}, {{52, 84}, WhiteOrBlack::White}, {{54, 63}, WhiteOrBlack::White}, {{58, 42}, WhiteOrBlack::White},
    {{60, 61}, WhiteOrBlack::White}, {{62, 28}, WhiteOrBlack::White}, {{62, 49}, WhiteOrBlack::White}, {{64, 18}, WhiteOrBlack::White},
    {{69, 27}, WhiteOrBlack::White}, {{79, 54}, WhiteOrBlack::White}, {{81, 39}, WhiteOrBlack::White}, {{84, 34}, WhiteOrBlack::White},
    {{19, 41}, WhiteOrBlack::Black}, {{23, 64}, WhiteOrBlack::Black}, {{24, 49}, WhiteOrBlack::Black}, {{20, 55}, WhiteOrBlack::Black},
    {{27, 23}, WhiteOrBlack::Black}, {{27, 52}, WhiteOrBlack::Black}, {{32, 37}, WhiteOrBlack::Black}, {{32, 64}, WhiteOrBlack::Black},
    {{35, 63}, WhiteOrBlack::Black}, {{38, 38}, WhiteOrBlack::Black}, {{38, 51}, WhiteOrBlack::Black}, {{41, 68}, WhiteOrBlack::Black},
    {{42, 78}, WhiteOrBlack::Black}, {{50, 32}, WhiteOrBlack::Black}, {{51, 14}, WhiteOrBlack::Black}, {{52, 50}, WhiteOrBlack::Black},
    {{52, 65}, WhiteOrBlack::Black}, {{52, 86}, WhiteOrBlack::Black}, {{55, 48}, WhiteOrBlack::Black}, {{62, 68}, WhiteOrBlack::Black},
    {{62, 78}, WhiteOrBlack::Black}, {{63, 55}, WhiteOrBlack::Black}, {{66, 16}, WhiteOrBlack::Black}, {{67, 54}, WhiteOrBlack::Black},
    {{67, 65}, WhiteOrBlack::Black}, {{73, 26}, WhiteOrBlack::Black}, {{74, 59}, WhiteOrBlack::Black}, {{76, 25}, WhiteOrBlack::Black},
    {{80, 48}, WhiteOrBlack::Black}, {{83, 39}, WhiteOrBlack::Black}, {{86, 52}, WhiteOrBlack::Black}, {{87, 33}, WhiteOrBlack::Black}};
    m_piecesToChessCellValuesMap[PieceColorAndType::Empty] = 0;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhitePawn]   = 0B0000000000000010110111010000000000000000011100000001000100000000;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteKnight] = 0B0011101111101111010111111110000000000000000000010000000000001000;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteBishop] = 0B0000001010111011001011111010000000000110000001010010000000100000;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteRook]   = 0B0000010101111001100111101000100000001001000000000000000101010000;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteQueen]  = 0B1101001000011110100011111111001100000000000000000000000000001001;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteKing]   = 0B0111100100100011111111110000011000000000000000000000000000000000;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackPawn]   = 0B0000000000000000000000000000000000000000011111011111110100000000;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackKnight] = 0B0000000000000000000000000000000000110110011111011111110110101000;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackBishop] = 0B0000000000000000000000000000000000000111111111111111110110100000;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackRook]   = 0B0000000000000000000000000000000000001011111111011111110111010000;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackQueen]  = 0B0000000000000000000000000000000010100101111110011111111110101101;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackKing]   = 0B0000000000000000000000000000000011110111110111111111100010101110;
}

void ChessPieceRetriever::initializeConverterToLichessDotOrg()
{
    m_checkMaxPoint = BitmapXY(93, 93);
    m_checkDetails = CheckDetails
    {{{12, 25}, WhiteOrBlack::White}, {{16, 44}, WhiteOrBlack::White}, {{17, 59}, WhiteOrBlack::White}, {{22, 49}, WhiteOrBlack::White},
    {{26, 42}, WhiteOrBlack::White}, {{27, 25}, WhiteOrBlack::White}, {{29, 18}, WhiteOrBlack::White}, {{33, 44}, WhiteOrBlack::White},
    {{33, 53}, WhiteOrBlack::White}, {{38, 33}, WhiteOrBlack::White}, {{39, 46}, WhiteOrBlack::White}, {{41, 51}, WhiteOrBlack::White},
    {{46, 16}, WhiteOrBlack::White}, {{47, 26}, WhiteOrBlack::White}, {{47, 39}, WhiteOrBlack::White}, {{47, 49}, WhiteOrBlack::White},
    {{47, 79}, WhiteOrBlack::White}, {{54, 46}, WhiteOrBlack::White}, {{56, 33}, WhiteOrBlack::White}, {{61, 43}, WhiteOrBlack::White},
    {{61, 53}, WhiteOrBlack::White}, {{64, 19}, WhiteOrBlack::White}, {{67, 25}, WhiteOrBlack::White}, {{67, 45}, WhiteOrBlack::White},
    {{67, 62}, WhiteOrBlack::White}, {{70, 50}, WhiteOrBlack::White}, {{71, 42}, WhiteOrBlack::White}, {{71, 67}, WhiteOrBlack::White},
    {{73, 47}, WhiteOrBlack::White}, {{76, 67}, WhiteOrBlack::White}, {{77, 44}, WhiteOrBlack::White}, {{81, 25}, WhiteOrBlack::White},
    {{12, 25}, WhiteOrBlack::Black}, {{13, 59}, WhiteOrBlack::Black}, {{14, 79}, WhiteOrBlack::Black}, {{15, 32}, WhiteOrBlack::Black},
    {{20, 39}, WhiteOrBlack::Black}, {{21, 48}, WhiteOrBlack::Black}, {{23, 24}, WhiteOrBlack::Black}, {{25, 19}, WhiteOrBlack::Black},
    {{25, 54}, WhiteOrBlack::Black}, {{28, 22}, WhiteOrBlack::Black}, {{29, 19}, WhiteOrBlack::Black}, {{29, 44}, WhiteOrBlack::Black},
    {{34, 48}, WhiteOrBlack::Black}, {{39, 47}, WhiteOrBlack::Black}, {{46, 48}, WhiteOrBlack::Black}, {{46, 79}, WhiteOrBlack::Black},
    {{47, 26}, WhiteOrBlack::Black}, {{47, 38}, WhiteOrBlack::Black}, {{53, 48}, WhiteOrBlack::Black}, {{60, 48}, WhiteOrBlack::Black},
    {{64, 15}, WhiteOrBlack::Black}, {{64, 19}, WhiteOrBlack::Black}, {{68, 19}, WhiteOrBlack::Black}, {{69, 54}, WhiteOrBlack::Black},
    {{70, 50}, WhiteOrBlack::Black}, {{71, 23}, WhiteOrBlack::Black}, {{73, 64}, WhiteOrBlack::Black}, {{76, 76}, WhiteOrBlack::Black},
    {{79, 31}, WhiteOrBlack::Black}, {{79, 79}, WhiteOrBlack::Black}, {{80, 67}, WhiteOrBlack::Black}, {{81, 25}, WhiteOrBlack::Black}};
    m_piecesToChessCellValuesMap[PieceColorAndType::Empty] = 0;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhitePawn]   = 0B0000000000110111110000000000000000000000000010000001000000000000;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteKnight] = 0B0011100111100110111110011111110001001000011000110100000000010110;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteBishop] = 0B0000000101111101011100000000000000100000000100010100000000010100;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteRook]   = 0B0000010111110111111110100000000000000011001100010000011001010000;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteQueen]  = 0B1001001110001011100101000100100100011001110101001110101100001000;
    m_piecesToChessCellValuesMap[PieceColorAndType::WhiteKing]   = 0B0101100110110010110110010110101000000000000000101000000000000000;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackPawn]   = 0B0000000000000000000000000000000000000000000011111111000000000000;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackKnight] = 0B0000000000000000000000000010110001001100111111111111000110100110;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackBishop] = 0B0000000000010010000000000000000000100000000111111011000000010100;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackRook]   = 0B0000000001000000001000000000000000000011011111111111011001010000;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackQueen]  = 0B0000000000000000000000000000000010011101111111111111111110001001;
    m_piecesToChessCellValuesMap[PieceColorAndType::BlackKing]   = 0B0000000000000001000000001000000000001100100111011111000110000000;
}

bool ChessPieceRetriever::isBitValueAsserted(        BitmapSnippet const& chessBoardSnippet,
        CheckDetail const& checkDetail,
        BitmapXY const& chessCellTopLeft,
        BitmapXY const& chessCellBottomRight) const
{
    static const BitmapXYs aroundOffsets{BitmapXY(0, -1), BitmapXY(0, 1), BitmapXY(-1, 0), BitmapXY(1, 0)};

    bool result(false);
    unsigned int deltaX = chessCellBottomRight.getX() - chessCellTopLeft.getX();
    unsigned int deltaY = chessCellBottomRight.getY() - chessCellTopLeft.getY();
    unsigned int offsetInX = getIntegerAfterRoundingADoubleValue<unsigned int>(static_cast<double>(checkDetail.pointOffset.getX()) * deltaX / m_checkMaxPoint.getX());
    unsigned int offsetInY = getIntegerAfterRoundingADoubleValue<unsigned int>(static_cast<double>(checkDetail.pointOffset.getY()) * deltaY / m_checkMaxPoint.getY());
    BitmapXY pointToCheck{chessCellTopLeft.getX()+offsetInX, chessCellTopLeft.getY()+offsetInY};
    uint32_t colorToCheck(chessBoardSnippet.getColorAt(pointToCheck));
    double currentIntensity(calculateColorIntensityDecimal(colorToCheck));
    if(WhiteOrBlack::White == checkDetail.condition)
    {
        double maximum(currentIntensity);
        for(BitmapXY const& aroundOffset : aroundOffsets)
        {
            currentIntensity = calculateColorIntensityDecimal(chessBoardSnippet.getColorAt(pointToCheck + aroundOffset));
            if(maximum < currentIntensity)
            {
                maximum = currentIntensity;
            }
        }
        result = maximum > m_configuration.getWhiteColorLimit();
    }
    else if(WhiteOrBlack::Black == checkDetail.condition)
    {
        double minimum(currentIntensity);
        for(BitmapXY const& aroundOffset : aroundOffsets)
        {
            currentIntensity = calculateColorIntensityDecimal(chessBoardSnippet.getColorAt(pointToCheck + aroundOffset));
            if(minimum > currentIntensity)
            {
                minimum = currentIntensity;
            }
        }
        result = minimum < m_configuration.getBlackColorLimit();
    }
    //ALBA_PRINT6(result, chessCellTopLeft, chessCellBottomRight, pointToCheck, checkDetail.pointOffset, (int)checkDetail.condition);
    return result;
}

PieceColorAndType ChessPieceRetriever::getPieceFromBitValue(
        PieceToBitValueMap const& pieceToBitValueMap,
        uint64_t const bitValue) const
{
    PieceToBitValueMap differenceMap(getDifferenceMap(pieceToBitValueMap, bitValue));
    PieceToCountPerByteMap pieceToDifferenceOfEachByteMap(getDifferenceOfEachByteMap(differenceMap));
    PieceToCountMap pieceToScoreMap(getPieceToScoreMap(pieceToDifferenceOfEachByteMap));
    PieceColorAndTypes bestFitPieces(getBestFitPieces(pieceToScoreMap));

    PieceColorAndType result{};
    if(bestFitPieces.size() == 1)
    {
        result = bestFitPieces.back();
    }
    /*else if(m_logFileStreamOptional)
    {
        auto & logStream(m_logFileStreamOptional.getReference());
        bitset<64> bitsetValue(bitValue);
        logStream << "Cannot determine bestFitType with bitValue: " << bitsetValue.to_string() << endl;
        logStream << "BestFitTypes with size " << bestFitPieces.size() << " :{";
        for(PieceColorAndType const bestFitPiece : bestFitPieces)
        {
            logStream << getEnumString(bestFitPiece) << ", ";
        }
        logStream << "}" << endl;
    }*/
    return result;
}

ChessPieceRetriever::PieceToBitValueMap ChessPieceRetriever::getDifferenceMap(
        PieceToBitValueMap const& pieceToBitValueMap,
        uint64_t const bitValue) const
{
    PieceToBitValueMap differenceMap(pieceToBitValueMap);
    for(auto & pieceAndBitValuePair : differenceMap)
    {
        pieceAndBitValuePair.second ^= bitValue;
    }
    return differenceMap;
}

ChessPieceRetriever::PieceToCountPerByteMap ChessPieceRetriever::getDifferenceOfEachByteMap(
        PieceToBitValueMap const& differenceMap) const
{
    PieceToCountPerByteMap differenceOfEachByteMap;
    for(auto const& pieceAndDifferencePair : differenceMap)
    {
        uint64_t difference(pieceAndDifferencePair.second);
        CountPerByte & differencePerByte(differenceOfEachByteMap[pieceAndDifferencePair.first]);
        differencePerByte[0] = static_cast<Count>(BitValueUtilities::getNumberOfOnes(BitManipulator::getByteAt<0>(difference)));
        differencePerByte[1] = static_cast<Count>(BitValueUtilities::getNumberOfOnes(BitManipulator::getByteAt<1>(difference)));
        differencePerByte[2] = static_cast<Count>(BitValueUtilities::getNumberOfOnes(BitManipulator::getByteAt<2>(difference)));
        differencePerByte[3] = static_cast<Count>(BitValueUtilities::getNumberOfOnes(BitManipulator::getByteAt<3>(difference)));
        differencePerByte[4] = static_cast<Count>(BitValueUtilities::getNumberOfOnes(BitManipulator::getByteAt<4>(difference)));
        differencePerByte[5] = static_cast<Count>(BitValueUtilities::getNumberOfOnes(BitManipulator::getByteAt<5>(difference)));
        differencePerByte[6] = static_cast<Count>(BitValueUtilities::getNumberOfOnes(BitManipulator::getByteAt<6>(difference)));
        differencePerByte[7] = static_cast<Count>(BitValueUtilities::getNumberOfOnes(BitManipulator::getByteAt<7>(difference)));
    }
    return differenceOfEachByteMap;
}

ChessPieceRetriever::PieceToCountMap ChessPieceRetriever::getPieceToScoreMap(
        PieceToCountPerByteMap const& pieceToDifferenceOfEachByteMap) const
{
    PieceToCountMap pieceToScoreMap
    {{PieceColorAndType::WhitePawn, 0U}, {PieceColorAndType::WhiteKnight, 0U}, {PieceColorAndType::WhiteBishop, 0U},
        {PieceColorAndType::WhiteRook, 0U}, {PieceColorAndType::WhiteQueen, 0U}, {PieceColorAndType::WhiteKing, 0U},
        {PieceColorAndType::BlackPawn, 0U}, {PieceColorAndType::BlackKnight, 0U}, {PieceColorAndType::BlackBishop, 0U},
        {PieceColorAndType::BlackRook, 0U}, {PieceColorAndType::BlackQueen, 0U}, {PieceColorAndType::BlackKing, 0U}};
    for(unsigned int byteIndex=0; byteIndex<8; byteIndex++)
    {
        PieceColorAndTypes piecesWithMinimum;
        Count minimumDifference(9U);
        for(auto const& pieceToDifferenceOfEachBytePair : pieceToDifferenceOfEachByteMap)
        {
            PieceColorAndType piece(pieceToDifferenceOfEachBytePair.first);
            CountPerByte const& differencePerByte(pieceToDifferenceOfEachBytePair.second);
            Count differenceAtByte(differencePerByte.at(byteIndex));
            if(minimumDifference > differenceAtByte)
            {
                minimumDifference = differenceAtByte;
                piecesWithMinimum.clear();
                piecesWithMinimum.emplace_back(piece);
            }
            else if(minimumDifference == differenceAtByte)
            {
                piecesWithMinimum.emplace_back(piece);
            }
        }
        for(PieceColorAndType const pieceWithMinimum : piecesWithMinimum)
        {
            pieceToScoreMap[pieceWithMinimum]++;
        }
    }
    return pieceToScoreMap;
}

ChessPieceRetriever::PieceColorAndTypes ChessPieceRetriever::getBestFitPieces(
        PieceToCountMap const& pieceToScoreMap) const
{
    PieceColorAndTypes bestFitTypes;
    CountToPieceMultiMap scoreToPieceMultimap;
    for(auto const& pieceAndScorePair : pieceToScoreMap)
    {
        scoreToPieceMultimap.emplace(pieceAndScorePair.second, pieceAndScorePair.first);
    }
    if(!scoreToPieceMultimap.empty())
    {
        auto it = scoreToPieceMultimap.crbegin();
        Count maximumScore = it->first;
        bestFitTypes.emplace_back(it->second);
        it++;
        for(; it!=scoreToPieceMultimap.crend(); it++)
        {
            if(maximumScore == it->first)
            {
                bestFitTypes.emplace_back(it->second);
            }
            else
            {
                break;
            }
        }
    }
    return bestFitTypes;
}

void ChessPieceRetriever::retrieveChessCellTopLeftAndBottomRight(
        BitmapXY & chessCellTopLeft,
        BitmapXY & chessCellBottomRight,
        BitmapSnippet const& chessBoardSnippet,
        unsigned int const xIndex,
        unsigned int const yIndex) const
{
    double startX = chessBoardSnippet.getTopLeftCorner().getX();
    double startY = chessBoardSnippet.getTopLeftCorner().getY();
    double endX = chessBoardSnippet.getBottomRightCorner().getX();
    double endY = chessBoardSnippet.getBottomRightCorner().getY();
    double deltaX = (endX-startX)/8;
    double deltaY = (endY-startY)/8;
    chessCellTopLeft = BitmapXY{static_cast<unsigned int>(round(startX + deltaX*xIndex)), static_cast<unsigned int>(round(startY + deltaY*yIndex))};
    chessCellBottomRight = BitmapXY{static_cast<unsigned int>(round(startX + deltaX*(xIndex+1))), static_cast<unsigned int>(round(startY + deltaY*(yIndex+1)))};
}

void ChessPieceRetriever::retrieveOffsetPointsWithCondition(
        BitmapXYs & bitmapXYs,
        BitmapSnippet const& chessBoardSnippet,
        unsigned int const xIndex,
        unsigned int const yIndex,
        BoolFunction const& condition) const
{
    double startX = chessBoardSnippet.getTopLeftCorner().getX();
    double startY = chessBoardSnippet.getTopLeftCorner().getY();
    double endX = chessBoardSnippet.getBottomRightCorner().getX();
    double endY = chessBoardSnippet.getBottomRightCorner().getY();
    double deltaX = (endX-startX)/8;
    double deltaY = (endY-startY)/8;
    BitmapXY chessCellTopLeft{static_cast<unsigned int>(round(startX + deltaX*xIndex)), static_cast<unsigned int>(round(startY + deltaY*yIndex))};
    BitmapXY chessCellBottomRight{static_cast<unsigned int>(round(startX + deltaX*(xIndex+1))), static_cast<unsigned int>(round(startY + deltaY*(yIndex+1)))};

    int xLimit = chessCellBottomRight.getX()-chessCellTopLeft.getX();
    int yLimit = chessCellBottomRight.getY()-chessCellTopLeft.getY();
    for(int x=0U; x<xLimit; x++)
    {
        for(int y=0U; y<yLimit; y++)
        {
            if(condition(calculateColorIntensityDecimal(chessBoardSnippet.getColorAt({chessCellTopLeft.getX()+x, chessCellTopLeft.getY()+y}))))
            {
                bitmapXYs.emplace_back(x, y);
            }
        }
    }
}

double ChessPieceRetriever::calculateColorIntensityDecimal(uint32_t const color) const
{
    return (((double)extractRed(color)+extractGreen(color)+extractBlue(color))/0xFF)/3;
}

uint8_t ChessPieceRetriever::extractRed(uint32_t const color) const
{
    return (AlbaBitManipulation<uint32_t>::getByteAt<2>(color));
}

uint8_t ChessPieceRetriever::extractGreen(uint32_t const color) const
{
    return (AlbaBitManipulation<uint32_t>::getByteAt<1>(color));
}

uint8_t ChessPieceRetriever::extractBlue(uint32_t const color) const
{
    return (AlbaBitManipulation<uint32_t>::getByteAt<0>(color));
}

}

}
