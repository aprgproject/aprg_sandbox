#include "UciUtilities.hpp"

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace chess {

constexpr int ARTIFICIAL_MATE_SCORE = 999999;

namespace {
struct InfoDetails {
    unsigned int multipv;
    int scoreInCentipawns;
    int mateScore;
    strings pvHalfMoves;
    StringPairs nameAndValuePairs;
};

bool shouldSkipTheEntireInfo(string const& token) {
    static const strings tokens{"currmove"};

    return find(tokens.cbegin(), tokens.cend(), token) != tokens.cend();
}

bool shouldBeSavedInBestLine(string const& token) {
    static const strings tokens{"depth", "seldepth"};

    return find(tokens.cbegin(), tokens.cend(), token) != tokens.cend();
}

void retrieveInfoDetailsFromInfoTokens(InfoDetails& infoDetails, strings const& tokens) {
    for (unsigned int i = 1; i < tokens.size(); i++) {
        string const& token(tokens.at(i));
        if (shouldSkipTheEntireInfo(token)) {
            break;
        } else if (shouldBeSavedInBestLine(token)) {
            infoDetails.nameAndValuePairs.emplace_back(token, tokens.at(++i));
        } else if ("multipv" == token) {
            infoDetails.multipv = convertStringToNumber<unsigned int>(tokens.at(++i));
        } else if ("cp" == token) {
            infoDetails.scoreInCentipawns = convertStringToNumber<int>(tokens.at(++i));
        } else if ("mate" == token) {
            infoDetails.mateScore = convertStringToNumber<int>(tokens.at(++i));
        } else if ("pv" == token) {
            i++;  // skip "pv"
            for (; i < tokens.size(); i++) {
                infoDetails.pvHalfMoves.emplace_back(tokens.at(i));
            }
        }
    }
}

void saveCommonDetailsOnBestLine(CalculationDetails& calculationDetails, InfoDetails const& infoDetails) {
    for (StringPair const& nameAndValuePair : infoDetails.nameAndValuePairs) {
        if (nameAndValuePair.first == "depth") {
            calculationDetails.depthInPlies = convertStringToNumber<unsigned int>(nameAndValuePair.second);
        } else if (nameAndValuePair.first == "seldepth") {
            calculationDetails.selectiveDepthInPlies = convertStringToNumber<unsigned int>(nameAndValuePair.second);
        }
    }
}

int getArtificialScore(InfoDetails const& infoDetails) {
    int result{};
    if (infoDetails.mateScore == 0) {
        result = infoDetails.scoreInCentipawns;
    } else if (infoDetails.mateScore > 0) {
        result = ARTIFICIAL_MATE_SCORE;
    } else {
        result = ARTIFICIAL_MATE_SCORE * -1;
    }
    return result;
}

void saveSearchingMoveAndScorePairsWithValidMultiPV(
    CalculationDetails& calculationDetails, InfoDetails const& infoDetails) {
    auto size = calculationDetails.searchingMoveAndScorePairs.size();
    auto possibleNewSize = infoDetails.multipv;
    auto index = infoDetails.multipv - 1;
    auto move = infoDetails.pvHalfMoves.front();
    auto artificialScore = getArtificialScore(infoDetails);
    if (possibleNewSize == size + 1) {
        calculationDetails.searchingMoveAndScorePairs.emplace_back(move, artificialScore);
    } else if (possibleNewSize > size) {
        calculationDetails.searchingMoveAndScorePairs.resize(possibleNewSize);
        calculationDetails.searchingMoveAndScorePairs[index] = {move, artificialScore};
    } else {
        calculationDetails.searchingMoveAndScorePairs[index] = {move, artificialScore};
    }
}

void savePvLineWithBestLine(CalculationDetails& calculationDetails, InfoDetails const& infoDetails) {
    calculationDetails.scoreInPvLine = infoDetails.scoreInCentipawns;
    calculationDetails.pvHalfMovesInMonitoredLine = infoDetails.pvHalfMoves;
}

void savePvLineToHaveNearEqualLine(CalculationDetails& calculationDetails, InfoDetails const& infoDetails) {
    if (getAbsoluteValue(infoDetails.scoreInCentipawns) < getAbsoluteValue(calculationDetails.scoreInPvLine)) {
        calculationDetails.scoreInPvLine = infoDetails.scoreInCentipawns;
        calculationDetails.pvHalfMovesInMonitoredLine = infoDetails.pvHalfMoves;
    }
}

void savePvDetailsWithValidMultiPV(CalculationDetails& calculationDetails, InfoDetails const& infoDetails) {
    if (!infoDetails.pvHalfMoves.empty()) {
        calculationDetails.mateScore = infoDetails.mateScore;
        saveSearchingMoveAndScorePairsWithValidMultiPV(calculationDetails, infoDetails);
        savePvLineToHaveNearEqualLine(calculationDetails, infoDetails);
    }
}

void processInfoTokens(CalculationDetails& calculationDetails, strings const& infoTokens) {
    InfoDetails infoDetails{};
    retrieveInfoDetailsFromInfoTokens(infoDetails, infoTokens);

    if (!infoDetails.pvHalfMoves.empty()) {
        if (infoDetails.multipv == 1) {
            // best line (because multipv is 1)
            saveCommonDetailsOnBestLine(calculationDetails, infoDetails);
            savePvDetailsWithValidMultiPV(calculationDetails, infoDetails);
            savePvLineWithBestLine(calculationDetails, infoDetails);  // dont remove this
        } else if (infoDetails.multipv > 1) {
            // other lines
            savePvDetailsWithValidMultiPV(calculationDetails, infoDetails);
            savePvLineToHaveNearEqualLine(calculationDetails, infoDetails);  // enable or disable
        }
    }
}

void processBestMoveTokens(CalculationDetails& calculationDetails, strings const& tokens) {
    for (unsigned int i = 0; i < tokens.size(); i++) {
        string const& token(tokens.at(i));
        if (token == "bestmove") {
            calculationDetails.bestMove = tokens.at(++i);
        } else if (token == "ponder") {
            calculationDetails.possibleResponseMove = tokens.at(++i);
        }
    }
}
}  // namespace

void retrieveCalculationDetailsOnStringFromEngine(
    CalculationDetails& calculationDetails, string const& stringFromEngine) {
    strings tokens;
    splitToStrings<SplitStringType::WithoutDelimeters>(
        tokens, getStringWithoutStartingAndTrailingWhiteSpace(stringFromEngine), " ");

    if (!tokens.empty()) {
        if ("info" == tokens.front()) {
            processInfoTokens(calculationDetails, tokens);
        } else if ("bestmove" == tokens.front()) {
            processBestMoveTokens(calculationDetails, tokens);
        }
    }
}

}  // namespace chess

}  // namespace alba
