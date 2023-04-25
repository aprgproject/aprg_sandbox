#include "DeBruijnSequences.hpp"

#include <Algorithm/Graph/PathSearch/EulerPaths/DirectedGraph/HierholzerAlgorithmForDirectedGraph.hpp>

using namespace alba::algorithm;
using namespace std;

namespace alba {

DeBruijnSequences::DeBruijnSequences(unsigned int const substringSize, string const& alphabet)
    : m_substringSize(substringSize), m_alphabet(alphabet) {
    initialize();
}

string DeBruijnSequences::getDeBruijnString() const {
    string result;
    if (m_substringSize == 1) {
        result = m_alphabet;
    } else {
        HierholzerAlgorithmForDirectedGraph<string> eulerPathSearch(m_graph);
        auto eulerPath(eulerPathSearch.getEulerPath());
        if (!eulerPath.empty()) {
            result = eulerPath.front();
            for (auto it = eulerPath.cbegin() + 1; it != eulerPath.cend(); it++) {
                result += it->back();
            }
        }
    }
    return result;
}

void DeBruijnSequences::initialize() {
    if (m_substringSize > 1 && !m_alphabet.empty()) {
        addAllSubstringsAsVertex();
    }
}

void DeBruijnSequences::addAllSubstringsAsVertex() {
    string substring(m_substringSize - 1, m_alphabet.front());
    addSubstringAsVertex(0U, substring);
}

void DeBruijnSequences::addSubstringAsVertex(unsigned int const depth, string const& substring) {
    if (depth < m_substringSize) {
        for (char const c : m_alphabet) {
            string newSubstring = substring.substr(1, substring.length()) + c;
            addSubstringAsVertex(depth + 1, newSubstring);
            m_graph.connect(substring, newSubstring);
        }
    }
}

}  // namespace alba
