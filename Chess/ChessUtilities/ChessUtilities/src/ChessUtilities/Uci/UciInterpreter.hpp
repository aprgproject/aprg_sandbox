#pragma once

#include <ChessUtilities/Engine/CalculationDetails.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <array>
#include <unordered_map>

namespace alba {

namespace chess {

class UciInterpreter {
public:
    struct InfoDetails {
        unsigned int multipv;
        int scoreInCentipawns;
        int mateScore;
        stringHelper::strings pvHalfMoves;
        stringHelper::StringPairs nameAndValuePairs;
    };

    static constexpr int ARTIFICIAL_MATE_SCORE = 999999;
    static constexpr int NUMBER_OF_MOST_COMMON_MOVES = 10;

    UciInterpreter(CalculationDetails& calculationDetails);

    void clear();
    void updateCalculationDetails(std::string const& stringFromEngine);

private:
    void processInfoTokens(stringHelper::strings const& infoTokens);
    void processBestMoveTokens(stringHelper::strings const& tokens);

    void saveInfoDetailsFromInfoTokens(InfoDetails& infoDetails, stringHelper::strings const& tokens);
    void saveCommonDetailsOnBestLine(InfoDetails const& infoDetails);
    void saveCurrentMovesAndScoresWithValidMultiPV(InfoDetails const& infoDetails);
    void saveBestLineInMonitoredVariation(InfoDetails const& infoDetails);
    void saveMostCommonMovesWithValidMultiPV(InfoDetails const& infoDetails);

    int getArtificialScore(InfoDetails const& infoDetails);
    bool shouldSkipTheEntireInfo(std::string const& token);
    bool shouldBeSavedInBestLine(std::string const& token);

    CalculationDetails& m_calculationDetails;
    std::array<std::unordered_map<std::string, int>, NUMBER_OF_MOST_COMMON_MOVES> m_movesAndCountsOfEachStep;
};

}  // namespace chess

}  // namespace alba
