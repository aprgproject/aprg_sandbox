#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <bitset>
#include <deque>
#include <map>
#include <numeric>
#include <string>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Index>
class AhoCorasickMultipleSubstringsSearch {
public:
    static_assert(typeHelper::isIntegralType<Index>(), "Index must be signed (to handle UNUSED_STATE)");
    static constexpr Index MAX_NUMBER_OF_QUERIES = 64;
    static constexpr Index RADIX = 256;
    static constexpr Index UNUSED_STATE = -1;
    static constexpr Index START_STATE_ZERO = 0;
    using Strings = std::vector<std::string>;
    using Indexes = std::vector<Index>;
    using DequeOfIndexes = std::deque<Index>;
    using States = Indexes;
    using MatchBits = std::bitset<MAX_NUMBER_OF_QUERIES>;
    using StateToMatchBits = std::vector<MatchBits>;
    using StateMatrix = matrix::AlbaMatrix<Index>;
    using SearchResult = std::map<std::string, Indexes>;

    AhoCorasickMultipleSubstringsSearch(Strings const& queries)
        : m_queries(queries),
          m_maxNumberOfStates(getTotalLength(queries) + 1),
          m_trieTransitions(m_maxNumberOfStates, RADIX, UNUSED_STATE),
          m_trieArtificialConnections(m_maxNumberOfStates, UNUSED_STATE),
          m_stateToMatchBits(m_maxNumberOfStates, MatchBits{}) {
        initialize();
    }

    SearchResult search(std::string const& searchSpace) { return searchUsingTransitions(searchSpace); }

private:
    inline bool isUsedState(Index const state) const { return state != UNUSED_STATE; }
    inline bool isUnusedState(Index const state) const { return state == UNUSED_STATE; }

    Index getTotalLength(Strings const& queries) const {
        return std::accumulate(
            queries.cbegin(), queries.cend(), 0,
            [](Index const partialLength, std::string const& query) { return partialLength + query.length(); });
    }

    SearchResult searchUsingTransitions(std::string const& searchSpace) const {
        SearchResult result;
        Index currentState = START_STATE_ZERO;
        for (Index searchIndex = 0; searchIndex < static_cast<Index>(searchSpace.size()) && isUsedState(currentState);
             ++searchIndex) {
            currentState = getNextState(currentState, searchSpace[searchIndex]);
            auto const& matchBits(m_stateToMatchBits[currentState]);
            if (!matchBits.none()) {
                for (int queryIndex = 0; queryIndex < static_cast<Index>(m_queries.size()); ++queryIndex) {
                    if (matchBits[queryIndex]) {
                        auto const& query = m_queries[queryIndex];
                        result[query].emplace_back(searchIndex - query.length() + 1);
                    }
                }
            }
        }
        return result;
    }

    Index getNextState(Index const state, char const character) const {
        // Use failure transition if next transition is not defined
        Index currentState = state;
        while (isUnusedState(m_trieTransitions.getEntry(currentState, character)) &&
               isUsedState(m_trieArtificialConnections[currentState])) {
            currentState = m_trieArtificialConnections[currentState];
        }
        return m_trieTransitions.getEntry(currentState, character);
    }

    void initialize() {
        removeEmptyQueries();
        assert(m_queries.size() < MAX_NUMBER_OF_QUERIES);
        constructTransitions();
    }

    void removeEmptyQueries() {
        m_queries.erase(
            std::remove_if(m_queries.begin(), m_queries.end(), [](auto const& query) { return query.empty(); }),
            m_queries.end());
    }

    void constructTransitions() {
        constructTrieTransitionsAndMatchBits();
        constructBackTransitionsFromStartStateForUnhandledCharacters();

        DequeOfIndexes nearestStates;  // for BFS
        initializeNearestStatesAndConnectionsBasedFromStartState(nearestStates);
        updateConnectionsAndMatchBitsOfEquivalentStatesThruBfs(nearestStates);
    }

    void constructTrieTransitionsAndMatchBits() {
        Index lastAvailableState = 1;
        for (int queryIndex = 0; queryIndex < static_cast<Index>(m_queries.size()); ++queryIndex) {
            Index currentState = START_STATE_ZERO;
            // Trie like traversal
            for (auto const& characterInQuery : m_queries[queryIndex]) {
                Index& nextState(m_trieTransitions.getEntryReference(currentState, characterInQuery));
                if (isUnusedState(nextState)) {
                    nextState = lastAvailableState++;
                }
                currentState = nextState;
            }
            m_stateToMatchBits[currentState].set(queryIndex, true);
        }
    }

    void constructBackTransitionsFromStartStateForUnhandledCharacters() {
        for (Index character = 0; character < RADIX; ++character) {
            Index& nextStateFromStart(m_trieTransitions.getEntryReference(START_STATE_ZERO, character));
            if (isUnusedState(nextStateFromStart)) {
                nextStateFromStart = START_STATE_ZERO;  // move back to zero
            }
        }
    }

    void initializeNearestStatesAndConnectionsBasedFromStartState(DequeOfIndexes& nearestStates) {
        for (Index character = 0; character < RADIX; ++character) {
            Index nextStateFromStart(m_trieTransitions.getEntryReference(START_STATE_ZERO, character));
            if (nextStateFromStart != START_STATE_ZERO) {
                m_trieArtificialConnections[nextStateFromStart] = START_STATE_ZERO;
                nearestStates.emplace_front(nextStateFromStart);
            }
        }
    }

    Index getNextStateByArtificialConnection(Index const currentState, Index const character) {
        Index nextState = m_trieArtificialConnections[currentState];
        while (isUnusedState(m_trieTransitions.getEntry(nextState, character))) {
            nextState = m_trieArtificialConnections[nextState];
        }
        nextState = m_trieTransitions.getEntry(nextState, character);
        return nextState;
    }

    void updateConnectionsAndMatchBitsOfEquivalentStatesThruBfs(DequeOfIndexes& nearestStates) {
        while (nearestStates.size()) {
            Index currentState = nearestStates.back();
            nearestStates.pop_back();
            for (Index character = 0; character < RADIX; ++character) {
                Index nextState(m_trieTransitions.getEntry(currentState, character));
                if (isUsedState(nextState)) {
                    Index equivalentNextState = getNextStateByArtificialConnection(currentState, character);
                    m_trieArtificialConnections[nextState] = equivalentNextState;
                    m_stateToMatchBits[nextState] |= m_stateToMatchBits[equivalentNextState];
                    if (nextState < m_maxNumberOfStates) {
                        nearestStates.emplace_front(nextState);
                    }
                }
            }
        }
    }

    Strings m_queries;
    Index m_maxNumberOfStates;
    StateMatrix m_trieTransitions;
    States m_trieArtificialConnections;  // this is used to connect trie nodes
    StateToMatchBits m_stateToMatchBits;
};

}  // namespace algorithm

}  // namespace alba

// Notes:
// In computer science, the Aho–Corasick algorithm is a string-searching algorithm.
// This is dictionary-matching algorithm that locates elements of a finite set of strings
// (the "dictionary") within an input text.
// It matches all strings simultaneously.
// The complexity of the algorithm is linear in the length of the strings plus
// the length of the searched text plus the number of output matches.
// Note that because all matches are found, there can be a quadratic number of matches if every substring matches
// (e.g. dictionary = a, aa, aaa, aaaa and input string is aaaa).
//
// Informally, the algorithm constructs a finite-state machine that resembles a trie
// with additional links between the various internal nodes.
// These extra internal links allow fast transitions between failed string matches
// (e.g. asearch for cat in a trie that does not contain cat,
// but contains cart, and thus would fail at the node prefixed by ca),
// to other branches of the trie that share a common prefix
// (e.g., in the previous case, a branch for attribute might be the best lateral transition).
// This allows the automaton to transition between string matches without the need for backtracking.
//
// When the string dictionary is known in advance (e.g. a computer virus database),
// the construction of the automaton can be performed once off-line and the compiled automaton stored for later use.
// In this case, its run time is linear in the length of the input plus the number of matched entries.
//
// The Aho–Corasick string-matching algorithm formed the basis of the original Unix command fgrep.
// This is invented by Alfred V. Aho and Margaret J. Corasick in 1975.
//
// Example:
// Input: text = "ahishers"
//        arr[] = {"he", "she", "hers", "his"}
// Output:
//    Word his appears from 1 to 3
//    Word he appears from 4 to 5
//    Word she appears from 3 to 5
//    Word hers appears from 4 to 7
//
// If we use a linear time searching algorithm like KMP, then we need to one by one search all words in text[].
// This gives us total time complexity as O(n + length(word[0]) + O(n + length(word[1]) + O(n + length(word[2]) + … O(n
// + length(word[k-1]).
// This time complexity can be written as O(n*k + m).
//
// Aho-Corasick Algorithm finds all words in O(n + m + z) time where z is total number of occurrences of words in text.
// The Aho–Corasick string matching algorithm formed the basis of the original Unix command fgrep.
