#include "NearestSamples.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>

#include <set>

using namespace std;

namespace alba {

namespace AprgAudio {

NearestSamples::NearestSamples(Samples const& samples) : m_samples(samples) { saveToValuesToIndexes(); }

Indexes NearestSamples::getNearestSamplesIndexes(double const value, int const recommendedNumberOfSamples) {
    Indexes result;
    pair<ValuesToIndexes::const_iterator, ValuesToIndexes::const_iterator> lowerAndUpperIterator(
        containerHelper::getLowerAndUpperConstIteratorsInMap(m_valuesToIndexes, value));

    set<int> indexesInOrder;
    for (ValuesToIndexes::const_iterator it = lowerAndUpperIterator.first; it != lowerAndUpperIterator.second; it++) {
        indexesInOrder.emplace(it->second);
    }
    ValuesToIndexes::const_iterator itLower = lowerAndUpperIterator.first;
    ValuesToIndexes::const_iterator itUpper = lowerAndUpperIterator.second;
    while (static_cast<int>(indexesInOrder.size()) < recommendedNumberOfSamples &&
           itLower != m_valuesToIndexes.cbegin() && itUpper != m_valuesToIndexes.cend()) {
        if (itLower != m_valuesToIndexes.cbegin()) {
            indexesInOrder.emplace(itLower->second);
            itLower--;
        }
        if (itUpper != m_valuesToIndexes.cend()) {
            indexesInOrder.emplace(itUpper->second);
            itUpper--;
        }
    }
    result.reserve(result.size());
    copy(indexesInOrder.cbegin(), indexesInOrder.cend(), back_inserter(result));
    return result;
}

void NearestSamples::saveToValuesToIndexes() {
    int i = 0;
    for (double const sample : m_samples) {
        m_valuesToIndexes.emplace(sample, i++);
    }
}

}  // namespace AprgAudio

}  // namespace alba
