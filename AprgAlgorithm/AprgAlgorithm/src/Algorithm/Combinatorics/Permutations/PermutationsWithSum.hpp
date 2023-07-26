#pragma once

#include <algorithm>
#include <set>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Values>
class PermutationsWithSum {
public:
    using Value = typename Values::value_type;
    using Permutation = std::vector<Value>;
    using Permutations = std::set<Permutation>;
    using VectorOfPermutations = std::vector<Permutations>;

    PermutationsWithSum(Values const& values) : m_inputValues(values) {}

    Permutations getPermutationsWithSumUsingLoops(Value const total) {
        // using loops
        if (total >= static_cast<Value>(m_permutations.size())) {
            Value initialValue = m_permutations.size();
            auto&& [minIt, maxIt] = std::minmax_element(m_inputValues.cbegin(), m_inputValues.cend());
            Value newSize = std::max(total + 1, *maxIt);
            m_permutations.resize(newSize);

            for (Value const inputValue : m_inputValues) {
                if (m_permutations[inputValue].empty()) {
                    m_permutations[inputValue].emplace(Permutation{inputValue});
                }
            }

            for (Value partialValue = initialValue; partialValue < newSize; partialValue++) {
                Permutations& permutations(m_permutations[partialValue]);
                for (Value const inputValue : m_inputValues) {
                    if (partialValue > inputValue) {
                        for (Permutation const& permutationWithoutValue : m_permutations[partialValue - inputValue]) {
                            Permutation permutationWithValue(permutationWithoutValue);
                            permutationWithValue.emplace_back(inputValue);
                            permutations.emplace(permutationWithValue);
                        }
                    }
                }
            }
        }
        return m_permutations[total];
    }

private:
    Values const& m_inputValues;
    VectorOfPermutations m_permutations;  // dynamic programming
};

}  // namespace algorithm

}  // namespace alba
