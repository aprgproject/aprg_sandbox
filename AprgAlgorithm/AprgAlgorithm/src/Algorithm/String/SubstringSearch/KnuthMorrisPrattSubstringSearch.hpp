#pragma once

#include <Common/State/AlbaDfaUsingMatrix.hpp>

#include <string>

namespace alba {

namespace algorithm {

template <typename Index>
class KnuthMorrisPrattSubstringSearch {
public:
    using RadixType = int;
    using Dfa = AlbaDfaUsingMatrix<Index, RadixType>;
    static constexpr RadixType RADIX = 256;

    KnuthMorrisPrattSubstringSearch(std::string const& query) : m_query(query), m_nextIndexDfa(query.length(), RADIX) {
        // In m_nextIndexDfa, x coordinate is character and y coordinate is the next state (which is index)
        initialize();
    }

    Index search(std::string const& searchSpace) {
        Index result(static_cast<Index>(std::string::npos));
        Index searchSpaceLength(searchSpace.length());
        Index queryLength(m_query.length());
        Index searchIndex = 0, matchIndex = 0;
        for (; searchIndex < searchSpaceLength && matchIndex < queryLength; searchIndex++) {
            // use DFA to determine next state
            matchIndex = m_nextIndexDfa.getNextState(matchIndex, searchSpace[searchIndex]);
        }
        if (matchIndex == queryLength) {
            result = searchIndex - queryLength;
        }
        return result;
    }

private:
    void initialize() {
        if (!m_query.empty()) {
            // put initial transition of: from first index go to second index (if character is encountered)
            m_nextIndexDfa.setStateTransition(0, 1, m_query[0]);
            Index queryLength(m_query.length());
            Index delayedState(0);  // this state tracks if input is one tempo delayed
            // The delayedState is useful because if there is a mismatch, we could track where that state would go
            // (as it already have previous matches)
            // -> Mismatch transition is tricky:
            // ---> If in state j and next char c != pattern.charAt(j), then the last j-1 of input are pattern[1 ...
            // j-1], followed by c
            // ---> Reason for this is salvaging previous matches from mismatches only occurs on indexes [1 ... j-1]

            for (Index i = 1; i < queryLength; i++) {
                for (RadixType c = 0; c < RADIX; c++) {
                    // assign mismatch state as the "delayedState with inputed c"
                    Index mismatchState(m_nextIndexDfa.getNextState(delayedState, c));
                    // put transition: if there is a mismatch go back to
                    // "delayedState with inputed c" (mismatch state)
                    m_nextIndexDfa.setStateTransition(i, mismatchState, c);
                }
                // put transition (overwrite): if match go to the next state
                m_nextIndexDfa.setStateTransition(i, i + 1, m_query[i]);
                // update delayed state (one tempo delayed)
                delayedState = m_nextIndexDfa.getNextState(delayedState, m_query[i]);
            }
        }
    }

    std::string m_query;
    Dfa m_nextIndexDfa;
};

}  // namespace algorithm

}  // namespace alba

// Sedgewick: This is one of the coolest algorithm.

// Intuition: Suppose we are searching in text for pattern: "BAAAAAAAAA"
// -> Suppose we match 5 chars in pattern, with mismatch on 6th char (suppose BAAAAB).
// -> We know previous 6 chars in text are BAAAAB
// -> Dont need to back up text pointer!

// Knuth-Morris-Pratt algorithm: Clever method to always avoid backup.
// DFA is abstract string searching machine
// -> Finite number of states (including start and halt)
// -> Exactly one transition for each char in alphabet
// -> Accept if sequence of transition leads to halt state.

// What is the interpretation of DFA state?
// -> State = number of characters in pattern that have been matched

// Key difference from brute-force implementation
// -> Need to precompute dfa[][] from pattern
// -> Text pointer i never decrements
// -> Could use input stream
// -> Running time: Simulate DFA on text: at most N character accesses.

// Transitions:
// -> Match transition is easy
// ---> If in state j and next char c == pattern.charAt(j), go to j+1
// -> Mismatch transition is tricky
// ---> If in state j and next char c != pattern.charAt(j), then the last j-1 of input are pattern[1 ... j-1], followed
// by c
// ---> To compute dfa[c][j]: Simulate pattern[1 ... j-1] on DFA and take transition c.
// -> Running time: Construction of DFA: seems to require j steps. No! It would only take constant time if we maintain
// state X (delayedState).
// -> Final running time: M character access (but space/time proportional to R M)

// Proposition:
// -> KMP search accesses no more than M+N characters to search for a pattern of length M in a test of length N.
// -> Proof: Each pattern char accessed once when constructin the DFA each text char accessed once (in the worst case),
// when simulating the DFA.

// Proposition KMP constructs dfa[][] in time and space proportional to R*M

// Improvements:
// -> Larger alphabets. Improved version of KMP constructs nfa[] in time and space proportional to M.

// History:
// -> Independently discovered by two thoereticians and a practitioner.
// ---> Knuth: inspired by esoteric theorem, discovered linear algorithm.
// ---> Pratt: made running time independent of alphabet size
// ---> Morris: built a text editor for the CDC 6400 computer (typewriters were used stil)

// Other Discussions:
// The KMP matching algorithm uses degenerating property (pattern having same sub-patterns appearing more than once in
// the pattern) of the pattern and improves the worst case complexity to O(n).
// The basic idea behind KMP’s algorithm is: whenever we detect a mismatch (after some matches),
// we already know some of the characters in the text of the next window.
// We take advantage of this information to avoid matching the characters that we know will anyway match
