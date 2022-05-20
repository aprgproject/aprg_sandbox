#pragma once

#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>

#include <stack>
#include <string>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Index>
class RegularExpressionPatternMatching
{
public:
    using Indexes = std::vector<Index>; // States are indexes

    RegularExpressionPatternMatching(std::string const& regularExpression)
        : m_regularExpression(regularExpression)    {
        initialize();
    }

    bool isAMatch(std::string const& stringToCheck) const
    {
        bool result(false);
        Indexes nullTransitionStates(getNextStatesBasedFromNullTransitions({0})); // start from first index
        Index checkLength(stringToCheck.size());
        Index lengthOfRE(m_regularExpression.size());
        for(Index checkIndex=0; checkIndex<checkLength; checkIndex++)
        {
            Indexes matchTransitionStates;
            for(Index const nullTransitionState : nullTransitionStates)
            {
                if(nullTransitionState < lengthOfRE)
                {
                    char charInRE(m_regularExpression.at(nullTransitionState));
                    if(charInRE == stringToCheck.at(checkIndex) || charInRE == '.')
                    {
                        matchTransitionStates.emplace_back(nullTransitionState+1);
                    }
                }
            }
            if(!matchTransitionStates.empty())
            {
                nullTransitionStates = getNextStatesBasedFromNullTransitions(matchTransitionStates);
            }
        }
        for(Index const nullTransitionState : nullTransitionStates)
        {
            if(nullTransitionState == lengthOfRE)
            {
                result = true;
                break;            }
        }
        return result;
    }

private:

    Indexes getNextStatesBasedFromNullTransitions(Indexes const matchTransitionStates) const
    {
        Indexes result;
        PathSearchUsingDfs<Index> pathSearch(m_nfaGraph, matchTransitionStates);
        for(Index const index : m_nfaGraph.getVertices())
        {
            if(pathSearch.hasPathTo(index))
            {
                result.emplace_back(index);
            }
        }
        return result;
    }

    void initialize()    {
        std::stack<Index> operatorIndexes;
        Index regularExpressionLength(m_regularExpression.length());
        for(Index i=0; i<regularExpressionLength; i++)        {
            Index lp = i;
            if(m_regularExpression.at(i) == '(' || m_regularExpression.at(i) == '|')
            {
                operatorIndexes.push(i);
            }
            else if(m_regularExpression.at(i) == ')')
            {
                Index operatorIndex(operatorIndexes.top());
                operatorIndexes.pop();
                if(m_regularExpression.at(operatorIndex) == '|')
                {
                    lp = operatorIndexes.top();
                    operatorIndexes.pop();
                    m_nfaGraph.connect(lp, operatorIndex+1);
                    m_nfaGraph.connect(operatorIndex, i);
                }
                else
                {
                    lp = operatorIndex;
                }
            }
            if(i < regularExpressionLength-1 && m_regularExpression.at(i+1) == '*')
            {
                m_nfaGraph.connect(lp, i+1);
                m_nfaGraph.connect(i+1, lp);
            }
            if(m_regularExpression.at(i) == '(' || m_regularExpression.at(i) == '*' || m_regularExpression.at(i) == ')')
            {
                m_nfaGraph.connect(i, i+1);
            }
        }
    }

    std::string m_regularExpression;
    DirectedGraphWithListOfEdges<Index> m_nfaGraph;
};

// Pattern matching
// -> Substring search. Find a single string in text.
// -> Pattern matching. Find one of a specified set of string in text.

// Example:
// -> Fragile X syndrome is a common cause of mental retardation
// -> Human genome contains triple repeat of CGG or AGG,
//    bracketed by GCG at the beginning and CTG at the end.
// -> Number of repeats is variable, and correlated with syndrome.
// -> So pattern: GCG(CGG|AGG)*CTG
// -> Text: GCGGCGTGTGTGCGAGAGAGTGGGTTTAAAGCTG[GCGCGGAGGCGGCTG]GCGCGGAGGCTG

// Applications:
// -> Syntax highlighting
// -> Google code search -> can use regex
// -> Test if a string matches some pattern
// -> Process natural language.
// -> Scan for virus signature.
// -> Specify a programming language
// -> Access information in digiral libaries
// -> Search genome using PROSITE patterns
// -> Filter text (spam, NetNanny, Carnivore, malware)
// -> Validate data-entry fields (dates, email, URL, credit card)

// Parse text files:
// -> Compile a java program
// -> Crawl and index the web
// -> Read in data stored in ad hov input file format
// -> Create java documentation from Javadoc comments

// What is regular expression?
// ->A regular expression is a notation to specify a set of strings.
// operation     | order | example RE | matches           | does not match
// concatenation | 3     | AABAAB     | AABAAB            | every other string
// or            | 4     | AA | BAAB  | AA BAAB           | every other string
// closure       | 2     | AB*A       | AA, ABBBBBBA, etc | AB ABABA
// parentheses   | 1     | (AB)*A     | A ABABABABABABABA | AA ABBA

// Regular expression shortcuts
// -> Additional operations are often added for convenience
// operation       | example RE        | matches               | does not match
// wildcard        | .U.U.U            | CUMULUS JUGULUM       | SUCCUBUS TUMULTUOUS
// character class | [A-Za-z][a-z]*    | word Capitalized      | camelCase 4illegal
// at least 1      | A(BC)+(DE)        | ABCDE ABCBCDE         | ADE BCDE
// exactly k       | [0-9]{5}-[0-9]{4} | 08540-1321 19072-5541 | 111111111111 166-54-111
// -> Example: [A-E]+ is shorthand for (A|B|C|D|E)(A|B|C|D|E)*

// RE notation is surprising expressive
// Regular expression examples:
// Problem                 | Regular expression          | matches                 | does not match
// substring search        | .*SPB.*                     | RASPBERRY CRIPSBREAD    | SUBSPACE SUBSPECIES
// social security numbers | [0-9]{3}-[0-9]{2}-[0-9]{4}  | 166-11-4433 166-45-1111 | 11-55555555555 8675309
// email addresses         | [a-z]+@([a-z]+\.)+(edu|com) | wayne@princeton.edu     | spam@nowhere
// java identifier         | [$_A-Aa-z][$_A-Aa-z0-9]*    | ident3 patternmatcher   | 3a ident#3

// REs play a well understood role in the theory of computation

// Google. Supports * for full word wildcard and | for union

// Writing a RE is like writing a program
// -> Need to understand programming model.
// -> Can be easier to write than read
// -> Can be difficult to debug

// Bottom line: REs are amazing powerful and expressive, but using them in applications can be amazingly complex and error prone. -> Mark: Thank you!

// Duality between REs and DFAs

// RE: Concise way to describe a set of strings
// DFA: Machine to recognize whether a given string is in a given set.

// Kleene's theorem
// -> For any DFA, there exists a RE that describes the same set of strings.
// -> For any RE, there exists a DFA that recognizes the same set of strings.
// -> Stephen Kleene -> Princeton PHD 1934.

// Pattern matching implementation:

// Basic plan (first attempt):
// -> Overview is the same as for KMP
// ---> No backup in text input stream
// ---> Linear time guarantee
// ---> Underlying abstraction: DFA
// -> Basic plan (first attempt)
// ---> Build DFA from RE
// ---> Simulate DFA with text as input
// ---> Bad news: Basic plan is infeasible (DFA may have exponential # of states).

// Basic plan (revised):
// -> Overview is the same as for KMP
// ---> No backup in text input stream
// ---> quadratic time guarantee (linear-time typical)
// ---> Underlying abstraction: NFA
// -> Basic plan (first attempt)
// ---> Build NFA from RE
// ---> Simulate NFA with text as input


// NFA
// -> Regular expression matching NFA
// ---> RE enclosed in parentheses
// ---> One state per RE character in the string (start=0, accept=M). Same to KMP where one state represents an index in the string
// ---> Transitions:
// -----> Epsilon/Null transition (change state, but don't scan text)
// -----> Match transition (change state, and scan to next text char).
// ---> Accept if any sequence of transitions ends in accept state.

// Nondeterminism
// -> One view: machine can guess the proper sequence of state transitions
// -> Another view: sequence is a proof that machine accepts the text
// -> Mark's view: you have to power to try them all

// How to determine whether a string is matched by an automaton?
// -> Deterministic ->  easy because exactly one applicable transition
// -> Non deterministic -> can be several applicable transitions; need to select the right one!

// How to simulate NFA?
// -> Systematically consider all possible transition sequences.

// NFA representation
// -> State names: Indexes from 0 to M
// -> Match transitions: Keep regular expression in a string.
// -> Epsilon/Null transitions: Store in a digraph G.

// NFA simulation:
// Q: How to efficiently simulate an NFA?
// -> Maintain set of all possible states that NFA could be in after reading in the first i text characters.
// -> Steps:
// ---> 1) get all states reachable after reading i symbols
// ---> 2) get all possible match transitions on reading (i+1)st symbol c
// ---> 3) get all possible null transitions before read next symbol
// ---> 4) check all states reachable after reading i+1 symbols

// Digraph reachability
// -> Find all vertices reachable from a given source or set of vertices
// ---> Solution: Run DFS from each source, without unmarking vertices.
// ---> Performance: Runs in time proportional to E+V.
// ---> Mark: Or better yet use transitive closure!

}

}