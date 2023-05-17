#include "UciInterpreter.hpp"

#include <algorithm>

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

void UciInterpreter::processInfoTokens(strings const& infoTokens) {
    InfoDetails infoDetails(createInfoDetailsFromInfoTokens(infoTokens));
    if (!infoDetails.pvHalfMoves.empty()) {
        if (infoDetails.multipv == 1) {  // best line (because multipv is 1)
            saveCommonParametersOfBestLine(infoDetails);
        }
        saveVariation(infoDetails);
    }
}

void UciInterpreter::processBestMoveTokens(strings const& tokens) {
    for (int i = 0; i < static_cast<int>(tokens.size()); i++) {
        string const& token(tokens.at(i));
        if (token == "bestmove") {
            m_calculationDetails.bestMove = tokens.at(++i);
        } else if (token == "ponder") {
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
        } else if ("cp" == token) {
            infoDetails.scoreInCentipawns = convertStringToNumber<int>(tokens.at(++i));
        } else if ("mate" == token) {
            infoDetails.mateValue = convertStringToNumber<int>(tokens.at(++i));
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
    for (StringPair const& nameAndValuePair : infoDetails.commonParameterNameAndValue) {
        if (nameAndValuePair.first == "depth") {
            m_calculationDetails.depthInPlies = convertStringToNumber<unsigned int>(nameAndValuePair.second);
        } else if (nameAndValuePair.first == "seldepth") {
            m_calculationDetails.selectiveDepthInPlies = convertStringToNumber<unsigned int>(nameAndValuePair.second);
        }
    }
}

void UciInterpreter::saveVariation(InfoDetails const& infoDetails) {
    if (infoDetails.multipv > 0 && !infoDetails.pvHalfMoves.empty()) {
        auto size = m_calculationDetails.variations.size();
        auto possibleNewSize = infoDetails.multipv;
        auto index = infoDetails.multipv - 1;
        Variation variation{infoDetails.mateValue, infoDetails.scoreInCentipawns, infoDetails.pvHalfMoves};
        if (possibleNewSize <= size) {
            m_calculationDetails.variations[index] = variation;
        } else if (possibleNewSize == size + 1) {            m_calculationDetails.variations.emplace_back(variation);
        } else {
            m_calculationDetails.variations.resize(possibleNewSize);
            m_calculationDetails.variations[index] = variation;
        }
    }
}

bool UciInterpreter::shouldSkipTheEntireInfo(string const& token) {
    static const strings tokens{"currmove"};

    return find(tokens.cbegin(), tokens.cend(), token) != tokens.cend();
}

bool UciInterpreter::isACommonParameter(string const& token) {
    static const strings tokens{"depth", "seldepth"};

    return find(tokens.cbegin(), tokens.cend(), token) != tokens.cend();
}

}  // namespace chess

}  // namespace alba
