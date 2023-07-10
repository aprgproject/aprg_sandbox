#pragma once

#include <Algorithm/String/Tries/TernarySearchSuffixTrie.hpp>

#include <string>

namespace alba {

namespace algorithm {

template <typename Index>
class SuffixTrieSubStringSearch {
public:
    SuffixTrieSubStringSearch(std::string const& query) : m_query(query) {}

    Index search(std::string const& searchSpace) const {
        if (!m_query.empty()) {
            return searchUsingTrie(searchSpace, m_query);
        }
        return 0;
    }

private:
    int searchUsingTrie(std::string const& searchSpace, std::string const& query) const {
        TernarySearchSuffixTrie trie(searchSpace);
        return trie.getIndexOfFirstOccurrence(query);
    }

    std::string m_query;
};

}  // namespace algorithm

}  // namespace alba
