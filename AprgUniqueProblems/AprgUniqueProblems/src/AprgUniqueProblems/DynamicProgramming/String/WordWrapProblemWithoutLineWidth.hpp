#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <limits>
#include <string>

namespace alba {

class WordWrapProblemWithoutLineWidth {
public:
    using Index = unsigned int;
    using Cost = unsigned int;
    using Indices = std::vector<Index>;
    using Costs = std::vector<Cost>;
    struct RecursionDetails {
        Index maxLength;
        Indices lengths;
    };
    static constexpr Cost MAX_COST = std::numeric_limits<Cost>::max();

    WordWrapProblemWithoutLineWidth(stringHelper::strings const& words);

    Cost getOptimizedCostUsingNaiveRecursion() const;
    Cost getOptimizedCostByTryingAllLengths() const;

private:
    Cost getOptimizedCostUsingNaiveRecursion(RecursionDetails const& recursionDetails, Index const wordIndex) const;
    Cost getTotalLength() const;
    Cost getCost(Index const maxLength, Indices const& lengths) const;
    Cost getCostFromExtraSpaces(Index const numberOfExtraSpaces) const;
    stringHelper::strings m_words;
};

}  // namespace alba

// Given a sequence of words put line breaks in the given sequence such that the lines are printed neatly.
// Assume that the length of each word is smaller than the line width.
