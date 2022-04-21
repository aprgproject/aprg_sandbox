#include "ChessPieceConverter.hpp"

#include <iostream>

using namespace std;

namespace alba
{

namespace chess
{

ChessPieceConverter::ChessPieceConverter()
{
    initialize();
}

Piece ChessPieceConverter::convertBitValueToPiece(
        PieceColor const pieceColor,
        uint64_t const bitValue)
{
    PieceType pieceType;
    if(PieceColor::White == pieceColor)
    {
        pieceType = getPieceTypeFromBitValue(m_whitePiecesToBitValuesMap, bitValue);
    }
    else
    {
        pieceType = getPieceTypeFromBitValue(m_blackPiecesToBitValuesMap, bitValue);
    }
    return Piece(pieceColor, pieceType);
}

void ChessPieceConverter::setLogFile(string const& logFilePath)
{
    m_logFileStreamOptional.createObjectUsingDefaultConstructor();
    m_logFileStreamOptional.getReference().open(logFilePath);

    if(!m_logFileStreamOptional.getReference().is_open())
    {
        cout << string("Cannot open log file") << logFilePath;
    }
}

PieceType ChessPieceConverter::getPieceTypeFromBitValue(
        PieceTypeToBitValueMap const& pieceTypeToBitValueMap,
        uint64_t const bitValue)
{
    PieceTypeToBitValueMap differenceMap(getDifferenceMap(pieceTypeToBitValueMap, bitValue));
    PieceTypeToCountPerByteMap pieceTypeToDifferenceOfEachByteMap(getDifferenceOfEachByteMap(differenceMap));
    PieceTypeToCountMap pieceTypeToScoreMap(getPieceTypeToScoreMap(pieceTypeToDifferenceOfEachByteMap));
    PieceTypes bestFitTypes(getBestFitTypes(pieceTypeToScoreMap));

    PieceType result;
    if(bestFitTypes.size() == 1)
    {
        result = bestFitTypes.back();
    }
    else if(m_logFileStreamOptional)
    {
        auto & logStream(m_logFileStreamOptional.getReference());
        logStream << "Cannot determine bestFitType with bitValue: " << bitValue << endl;
        logStream << "BestFitTypes with size " << bestFitTypes.size() << " :{";
        for(PieceType const bestFit : bestFitTypes)
        {
            logStream << static_cast<unsigned int>(bestFit) << ", ";
        }
        logStream << "}" << endl;
    }

    return result;
}

ChessPieceConverter::PieceTypeToBitValueMap ChessPieceConverter::getDifferenceMap(
        PieceTypeToBitValueMap const& pieceTypeToBitValueMap,
        uint64_t const bitValue) const
{
    PieceTypeToBitValueMap differenceMap(pieceTypeToBitValueMap);
    for(auto & pieceTypeAndBitValuePair : differenceMap)
    {
        pieceTypeAndBitValuePair.second ^= bitValue;
    }
    return differenceMap;
}

ChessPieceConverter::PieceTypeToCountPerByteMap ChessPieceConverter::getDifferenceOfEachByteMap(
        PieceTypeToBitValueMap const& differenceMap) const
{
    PieceTypeToCountPerByteMap differenceOfEachByteMap;
    for(auto const& pieceTypeAndDifferencePair : differenceMap)
    {
        uint64_t difference(pieceTypeAndDifferencePair.second);
        CountPerByte & differencePerByte(differenceOfEachByteMap[pieceTypeAndDifferencePair.first]);
        differencePerByte[0] = static_cast<Count>(BitValueUtilities::getNumberOfBitsAsserted(BitManipulator::getByteAt<0>(difference)));
        differencePerByte[1] = static_cast<Count>(BitValueUtilities::getNumberOfBitsAsserted(BitManipulator::getByteAt<1>(difference)));
        differencePerByte[2] = static_cast<Count>(BitValueUtilities::getNumberOfBitsAsserted(BitManipulator::getByteAt<2>(difference)));
        differencePerByte[3] = static_cast<Count>(BitValueUtilities::getNumberOfBitsAsserted(BitManipulator::getByteAt<3>(difference)));
        differencePerByte[4] = static_cast<Count>(BitValueUtilities::getNumberOfBitsAsserted(BitManipulator::getByteAt<4>(difference)));
        differencePerByte[5] = static_cast<Count>(BitValueUtilities::getNumberOfBitsAsserted(BitManipulator::getByteAt<5>(difference)));
        differencePerByte[6] = static_cast<Count>(BitValueUtilities::getNumberOfBitsAsserted(BitManipulator::getByteAt<6>(difference)));
        differencePerByte[7] = static_cast<Count>(BitValueUtilities::getNumberOfBitsAsserted(BitManipulator::getByteAt<7>(difference)));
    }
    return differenceOfEachByteMap;
}

ChessPieceConverter::PieceTypeToCountMap ChessPieceConverter::getPieceTypeToScoreMap(
        PieceTypeToCountPerByteMap const& pieceTypeToDifferenceOfEachByteMap) const
{
    PieceTypeToCountMap pieceTypeToScoreMap
    {{PieceType::Pawn, 0U}, {PieceType::Knight, 0U}, {PieceType::Bishop, 0U}, {PieceType::Rook, 0U}, {PieceType::Queen, 0U}, {PieceType::King, 0U}};
    for(unsigned int byteIndex=0; byteIndex<8; byteIndex++)
    {
        PieceTypes pieceTypesWithMinimum;
        Count minimumDifference(9U);
        for(auto const& pieceTypeToDifferenceOfEachBytePair : pieceTypeToDifferenceOfEachByteMap)
        {
            PieceType pieceType(pieceTypeToDifferenceOfEachBytePair.first);
            CountPerByte const& differencePerByte(pieceTypeToDifferenceOfEachBytePair.second);
            Count differenceAtByte(differencePerByte.at(byteIndex));
            if(minimumDifference > differenceAtByte)
            {
                minimumDifference = differenceAtByte;
                pieceTypesWithMinimum.clear();
                pieceTypesWithMinimum.emplace_back(pieceType);
            }
            else if(minimumDifference == differenceAtByte)
            {
                pieceTypesWithMinimum.emplace_back(pieceType);
            }
        }
        for(PieceType const pieceTypeWithMinimum : pieceTypesWithMinimum)
        {
            pieceTypeToScoreMap[pieceTypeWithMinimum]++;
        }
    }
    return pieceTypeToScoreMap;
}

PieceTypes ChessPieceConverter::getBestFitTypes(
        PieceTypeToCountMap const& pieceTypeToScoreMap) const
{
    PieceTypes bestFitTypes;
    CountToPieceTypeMultiMap scoreToPieceMultimap;
    for(auto const& pieceTypeAndScorePair : pieceTypeToScoreMap)
    {
        scoreToPieceMultimap.emplace(pieceTypeAndScorePair.second, pieceTypeAndScorePair.first);
    }
    bool isFirst(true);
    Count maximumScore{};
    for(auto it = scoreToPieceMultimap.crbegin(); it!=scoreToPieceMultimap.crend(); it++)
    {
        if(isFirst)
        {
            maximumScore = it->first;
            bestFitTypes.emplace_back(it->second);
            isFirst = false;
        }
        else if(maximumScore == it->first)
        {
            bestFitTypes.emplace_back(it->second);
        }
        else
        {
            break;
        }
    }
    return bestFitTypes;
}

void ChessPieceConverter::initialize()
{
    initializeToChessDotCom();
}

void ChessPieceConverter::initializeToChessDotCom()
{
    m_whitePiecesToBitValuesMap[PieceType::Empty]  = 0;
    m_whitePiecesToBitValuesMap[PieceType::Pawn]   = 0B0000000000011000000110000001000000111100000100000011110001111110;
    m_whitePiecesToBitValuesMap[PieceType::Knight] = 0B0001000000111100001111100111111001101100001110100011111001111110;
    m_whitePiecesToBitValuesMap[PieceType::Bishop] = 0B0001100000010000001011000011110000111100001110000011110001111110;
    m_whitePiecesToBitValuesMap[PieceType::Rook]   = 0B0000000000111100001111000011010000111000001110000011110001111110;
    m_whitePiecesToBitValuesMap[PieceType::Queen]  = 0B0011110000111000101111110111111001111100001110000011111001111110;
    m_whitePiecesToBitValuesMap[PieceType::King]   = 0B0001100000011000011111101111111111111111011111000111111001111110;

    m_blackPiecesToBitValuesMap[PieceType::Empty]  = 0;
    m_blackPiecesToBitValuesMap[PieceType::Pawn]   = 0B0000000000011000000110000001100000111100000110000001110001111110;
    m_blackPiecesToBitValuesMap[PieceType::Knight] = 0B0011000000111100001111000111111001011110001111100010011001111110;
    m_blackPiecesToBitValuesMap[PieceType::Bishop] = 0B0001100000010000001111000011110000111100001111000110010001111110;
    m_blackPiecesToBitValuesMap[PieceType::Rook]   = 0B0000000000111100001111000011110000111100001111000110011001111110;
    m_blackPiecesToBitValuesMap[PieceType::Queen]  = 0B0011110000111100111111110111111001111110001111000110011001111110;
    m_blackPiecesToBitValuesMap[PieceType::King]   = 0B0001100000011000011111101101101111111111011111100110011001111110;
}

}

}
