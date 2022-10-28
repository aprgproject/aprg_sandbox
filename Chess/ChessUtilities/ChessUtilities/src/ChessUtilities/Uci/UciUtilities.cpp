#include "UciUtilities.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace chess
{

namespace
{

enum class TokenState
{
    Idle,
    OneValueHeaderFound,
    InPv,
};

struct TokenProcessingData
{
    TokenState state;
    string headerToken;
    strings pvMovesInBestLine;
    string currentMove;
    string currentMoveNumber;
};

bool isOneHeaderToken(string const& token)
{
    static const strings oneHeaderTokens
    {"depth", "seldepth", "selectiveDepth", "time", "nodes", "nps", "cp", "mate", "currmove", "currmovenumber", "bestmove", "ponder"};

    return find(oneHeaderTokens.cbegin(), oneHeaderTokens.cend(), token) != oneHeaderTokens.cend();
}

void processToken(
        CalculationDetails & calculationDetails,
        TokenProcessingData & data,
        string const& token)
{
    if(TokenState::OneValueHeaderFound == data.state)
    {
        if("depth" == data.headerToken)
        {
            calculationDetails.depth = convertStringToNumber<unsigned int>(token);
        }
        else if("seldepth" == data.headerToken || "selectiveDepth" == data.headerToken)
        {
            calculationDetails.selectiveDepth = convertStringToNumber<unsigned int>(token);
        }
        else if("time" == data.headerToken)
        {
            calculationDetails.time = convertStringToNumber<unsigned int>(token);
        }
        else if("nodes" == data.headerToken)
        {
            calculationDetails.nodes = convertStringToNumber<unsigned int>(token);
        }
        else if("nps" == data.headerToken)
        {
            calculationDetails.nodesPerSecond = convertStringToNumber<unsigned int>(token);
        }
        else if("cp" == data.headerToken)
        {
            calculationDetails.scoreInCentipawns = convertStringToNumber<unsigned int>(token);
        }
        else if("mate" == data.headerToken)
        {
            calculationDetails.mateInNumberOfMoves = convertStringToNumber<unsigned int>(token);
        }
        else if("currmove" == data.headerToken)
        {
            data.currentMove = token;
        }
        else if("currmovenumber" == data.headerToken)
        {
            data.currentMoveNumber = token;
        }
        else if("bestmove" == data.headerToken)
        {
            calculationDetails.bestMove = token;
        }
        else if("ponder" == data.headerToken)
        {
            calculationDetails.ponderMove = token;
        }

        if(!data.currentMove.empty() && !data.currentMoveNumber.empty())
        {
            unsigned int index = convertStringToNumber<unsigned int>(data.currentMoveNumber) - 1;
            if(index < 100)
            {
                if(index >= calculationDetails.currentlySearchingMoves.size())
                {
                    calculationDetails.currentlySearchingMoves.resize(index+1);
                }
                calculationDetails.currentlySearchingMoves[index] = data.currentMove;
            }
            data.currentMove.clear();
            data.currentMoveNumber.clear();
        }

        data.state = TokenState::Idle;
    }
    else if(TokenState::InPv == data.state)
    {
        data.pvMovesInBestLine.emplace_back(token);
    }
    else if(isOneHeaderToken(token))
    {
        data.state = TokenState::OneValueHeaderFound;
        data.headerToken = token;
    }
    else if("pv" == token)
    {
        data.state = TokenState::InPv;
    }
}
}


void retrieveCalculationDetailsOnStringFromEngine(
        CalculationDetails & calculationDetails,
        string const& stringFromEngine)
{
    strings tokens;
    splitToStrings<SplitStringType::WithoutDelimeters>(tokens, getStringWithoutStartingAndTrailingWhiteSpace(stringFromEngine), " ");

    if(!tokens.empty())
    {
        if("info"==tokens.front() || "bestmove"==tokens.front())
        {
            TokenProcessingData tokenProcessingData{};
            for(string const& token : tokens)
            {
                processToken(calculationDetails, tokenProcessingData, token);
            }
            if(!tokenProcessingData.pvMovesInBestLine.empty())
            {
                calculationDetails.pvMovesInBestLine = tokenProcessingData.pvMovesInBestLine;
            }
        }
    }

}

}

}
