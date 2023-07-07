#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename DataType>
class SuffixArray {
public:
    SuffixArray(std::string const& mainString) { initialize(mainString); }

    DataType getSize() const { return m_suffixes.size(); }

    DataType getIndexOnMainStringOfSuffixAt(DataType const index) const {
        return getSize() - m_suffixes[index].length();
    }

    DataType getRank(std::string const& key) const {
        DataType low = 0, high = getSize() - 1;
        while (low <= high) {
            DataType mid = getMidpointOfIndexes(low, high);
            auto compareValue = key.compare(m_suffixes[mid]);
            if (compareValue < 0) {
                high = mid - 1;
            } else if (compareValue > 0) {
                low = mid + 1;
            } else {
                low = mid;
                break;
            }
        }
        return low;
    }

    std::string const& getSuffixAt(DataType const index) const { return m_suffixes[index]; }

    std::string getLongestCommonPrefixOfTwoSuffixes(DataType const index1, DataType const index2) const {
        return stringHelper::getLongestCommonPrefix(m_suffixes[index1], m_suffixes[index2]);
    }

private:
    void initialize(std::string const& mainString) {
        for (DataType i = 0; i < static_cast<DataType>(mainString.length()); i++) {
            m_suffixes.emplace_back(mainString.substr(i));
        }
        std::sort(m_suffixes.begin(), m_suffixes.end());
    }

    stringHelper::strings m_suffixes;
};

}  // namespace algorithm

}  // namespace alba

// Check Manber-Myers MSD is really efficient
