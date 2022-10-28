#pragma once

#include <Common/String/AlbaStringHelper.hpp>

namespace alba
{

namespace chess
{

struct CalculationDetails
{
    unsigned int depth;
    unsigned int selectiveDepth;
    unsigned int time;
    unsigned int nodes;
    unsigned int nodesPerSecond;
    stringHelper::strings pvMovesInBestLine;
    int scoreInCentipawns;
    unsigned int mateInNumberOfMoves;
    stringHelper::strings currentlySearchingMoves;
    std::string bestMove;
    std::string ponderMove;
};

}

}
