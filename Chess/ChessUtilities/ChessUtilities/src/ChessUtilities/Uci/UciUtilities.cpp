#include "UciUtilities.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace chess {

constexpr int ARTIFICIAL_MATE_SCORE = 999999;

namespace {
struct InfoDetails {
    unsigned int multipv;
    int scoreInCentipawns;
    int mate;
    strings pvMoves;
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
            infoDetails.mate = convertStringToNumber<int>(tokens.at(++i));
        } else if ("pv" == token) {
            i++;  // skip "pv"
            for (; i < tokens.size(); i++) {
                infoDetails.pvMoves.emplace_back(tokens.at(i));
            }
        }
    }
}

void saveCalculationDetailsOnBestLine(CalculationDetails& calculationDetails, InfoDetails const& infoDetails) {
    for (StringPair const& nameAndValuePair : infoDetails.nameAndValuePairs) {
        if (nameAndValuePair.first == "depth") {
            calculationDetails.depthInPlies = convertStringToNumber<unsigned int>(nameAndValuePair.second);
        } else if (nameAndValuePair.first == "seldepth") {
            calculationDetails.selectiveDepthInPlies = convertStringToNumber<unsigned int>(nameAndValuePair.second);
        }
    }
    calculationDetails.pvMovesInBestLine = infoDetails.pvMoves;
}

int getArtificialScore(InfoDetails const& infoDetails) {
    int result{};
    if (infoDetails.mate == 0) {
        result = infoDetails.scoreInCentipawns;
    } else if (infoDetails.mate > 0) {
        result = ARTIFICIAL_MATE_SCORE;
    } else {
        result = ARTIFICIAL_MATE_SCORE * -1;
    }
    return result;
}

void saveSearchingMoveAndScoreAndMateWithValidMultiPV(
    CalculationDetails& calculationDetails, InfoDetails const& infoDetails) {
    if (!infoDetails.pvMoves.empty()) {
        calculationDetails.numberOfMovesTillMate = infoDetails.mate;

        auto size = calculationDetails.searchingMoveAndScorePairs.size();
        auto possibleNewSize = infoDetails.multipv;
        auto index = infoDetails.multipv - 1;
        auto move = infoDetails.pvMoves.front();
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
}

void processInfoTokens(CalculationDetails& calculationDetails, strings const& infoTokens) {
    InfoDetails infoDetails{};
    retrieveInfoDetailsFromInfoTokens(infoDetails, infoTokens);

    if (!infoDetails.pvMoves.empty()) {
        if (infoDetails.multipv == 1) {
            // best line (because multipv is 1)
            saveCalculationDetailsOnBestLine(calculationDetails, infoDetails);
            saveSearchingMoveAndScoreAndMateWithValidMultiPV(calculationDetails, infoDetails);
        } else if (infoDetails.multipv > 1) {
            // other lines
            saveSearchingMoveAndScoreAndMateWithValidMultiPV(calculationDetails, infoDetails);
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
    strings tokens;    splitToStrings<SplitStringType::WithoutDelimeters>(
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