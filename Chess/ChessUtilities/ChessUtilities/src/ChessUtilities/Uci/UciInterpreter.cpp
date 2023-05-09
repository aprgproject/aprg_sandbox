#include "UciInterpreter.hpp"

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace chess {

UciInterpreter::UciInterpreter(CalculationDetails& calculationDetails) : m_calculationDetails(calculationDetails) {}

void UciInterpreter::updateCalculationDetails(string const& stringFromEngine) {
    strings tokens;
    splitToStrings<SplitStringType::WithoutDelimeters>(
        tokens, getStringWithoutStartingAndTrailingWhiteSpace(stringFromEngine), " ");

    if (!tokens.empty()) {
        if ("info" == tokens.front()) {
            processInfoTokens(tokens);
        } else if ("bestmove" == tokens.front()) {
            processBestMoveTokens(tokens);
        }
    }
}

void UciInterpreter::clear() { m_movesAndCountsOfEachStep = {}; }

void UciInterpreter::processInfoTokens(strings const& infoTokens) {
    InfoDetails infoDetails(createInfoDetailsFromInfoTokens(infoTokens));
    if (!infoDetails.pvHalfMoves.empty()) {
        if (infoDetails.multipv == 1) {  // best line (because multipv is 1)
            saveCommonParametersOfBestLine(infoDetails);
            saveBestLineInMonitoredVariation(infoDetails);
        }
        if (infoDetails.multipv >= 1) {  // valid PV            saveCurrentMovesAndScoresWithValidMultiPV(infoDetails);
            saveMostCommonMovesWithValidMultiPV(infoDetails);
        }
    }
}

void UciInterpreter::processBestMoveTokens(strings const& tokens) {
    for (int i = 0; i < static_cast<int>(tokens.size()); i++) {
        string const& token(tokens.at(i));
        if (token == "bestmove") {
            m_calculationDetails.bestMove = tokens.at(++i);        } else if (token == "ponder") {
            m_calculationDetails.responseMoveToPonder = tokens.at(++i);
        }
    }
}

UciInterpreter::InfoDetails UciInterpreter::createInfoDetailsFromInfoTokens(strings const& tokens) {
    InfoDetails infoDetails{};
    for (int i = 1; i < static_cast<int>(tokens.size()); i++) {
        string const& token(tokens.at(i));
        if (shouldSkipTheEntireInfo(token)) {
            break;
        } else if (isACommonParameter(token)) {
            infoDetails.commonParameterNameAndValue.emplace_back(token, tokens.at(++i));
        } else if ("multipv" == token) {
            infoDetails.multipv = convertStringToNumber<unsigned int>(tokens.at(++i));
        } else if ("cp" == token) {            infoDetails.scoreInCentipawns = convertStringToNumber<int>(tokens.at(++i));
        } else if ("mate" == token) {
            infoDetails.mateScore = convertStringToNumber<int>(tokens.at(++i));
        } else if ("pv" == token) {
            i++;  // skip "pv"
            for (; i < static_cast<int>(tokens.size()); i++) {
                infoDetails.pvHalfMoves.emplace_back(tokens.at(i));
            }
        }
    }
    return infoDetails;
}

void UciInterpreter::saveCommonParametersOfBestLine(InfoDetails const& infoDetails) {
    m_calculationDetails.mateScore = infoDetails.mateScore;
    for (StringPair const& nameAndValuePair : infoDetails.commonParameterNameAndValue) {
        if (nameAndValuePair.first == "depth") {
            m_calculationDetails.depthInPlies = convertStringToNumber<unsigned int>(nameAndValuePair.second);
        } else if (nameAndValuePair.first == "seldepth") {            m_calculationDetails.selectiveDepthInPlies = convertStringToNumber<unsigned int>(nameAndValuePair.second);
        }
    }
}
void UciInterpreter::saveBestLineInMonitoredVariation(InfoDetails const& infoDetails) {
    m_calculationDetails.scoreInMonitoredVariation = getArtificialScore(infoDetails);
    m_calculationDetails.monitoredVariation = infoDetails.pvHalfMoves;
}

void UciInterpreter::saveCurrentMovesAndScoresWithValidMultiPV(InfoDetails const& infoDetails) {
    if (!infoDetails.pvHalfMoves.empty()) {
        auto size = m_calculationDetails.currentMovesAndScores.size();
        auto possibleNewSize = infoDetails.multipv;
        auto index = infoDetails.multipv - 1;
        auto move = infoDetails.pvHalfMoves.front();
        auto artificialScore = getArtificialScore(infoDetails);
        if (possibleNewSize == size + 1) {
            m_calculationDetails.currentMovesAndScores.emplace_back(move, artificialScore);
        } else if (possibleNewSize > size) {
            m_calculationDetails.currentMovesAndScores.resize(possibleNewSize);
            m_calculationDetails.currentMovesAndScores[index] = {move, artificialScore};
        } else {
            m_calculationDetails.currentMovesAndScores[index] = {move, artificialScore};
        }
    }
}

void UciInterpreter::saveMostCommonMovesWithValidMultiPV(InfoDetails const& infoDetails) {
    auto numberOfSteps = min(static_cast<int>(infoDetails.pvHalfMoves.size()), NUMBER_OF_STEPS_IN_MOST_COMMON_MOVES);
    if (infoDetails.multipv == 1) {
        m_calculationDetails.commonMovesAndCountsOfEachStep.resize(numberOfSteps);
        for (int i = 0; i < numberOfSteps; i++) {
            auto const& movesAndCountsOfOneStep(m_movesAndCountsOfEachStep[i]);
            auto itMaxCount = max_element(
                movesAndCountsOfOneStep.cbegin(), movesAndCountsOfOneStep.cend(),                [](auto const& commonMoveAndCountPair1, auto const& commonMoveAndCountPair2) {
                    return commonMoveAndCountPair1.second < commonMoveAndCountPair2.second;
                });
            if (itMaxCount != movesAndCountsOfOneStep.cend()) {                m_calculationDetails.commonMovesAndCountsOfEachStep[i] = {itMaxCount->first, itMaxCount->second};
            }
        }
        m_movesAndCountsOfEachStep = {};
    }
    for (int stepIndex = 0; stepIndex < numberOfSteps; stepIndex++) {
        string move(infoDetails.pvHalfMoves.at(stepIndex));
        m_movesAndCountsOfEachStep[stepIndex].try_emplace(move, 0);
        m_movesAndCountsOfEachStep[stepIndex][move]++;
    }
}
int UciInterpreter::getArtificialScore(InfoDetails const& infoDetails) {
    int result{};
    if (infoDetails.mateScore == 0) {        result = infoDetails.scoreInCentipawns;
    } else if (infoDetails.mateScore > 0) {
        result = ARTIFICIAL_MATE_SCORE;
    } else {
        result = ARTIFICIAL_MATE_SCORE * -1;
    }
    return result;
}

bool UciInterpreter::shouldSkipTheEntireInfo(string const& token) {
    static const strings tokens{"currmove"};

    return find(tokens.cbegin(), tokens.cend(), token) != tokens.cend();
}

bool UciInterpreter::isACommonParameter(string const& token) {
    static const strings tokens{"depth", "seldepth"};

    return find(tokens.cbegin(), tokens.cend(), token) != tokens.cend();}

}  // namespace chess
}  // namespace alba
