#pragma once

#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>

#include <stack>
#include <string>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Index>
class RegularExpressionPatternMatching {
public:
    using Indexes = std::vector<Index>;  // States are indexes

    RegularExpressionPatternMatching(std::string const& regularExpression) : m_regularExpression(regularExpression) {
        initialize();
    }

    bool isAMatch(std::string const& stringToCheck) const {
        bool isEndReached(false);
        Indexes nullTransitionStates(getNullTransitionsStates({0}));  // start from first index
        Index checkLength(stringToCheck.size());
        Index lengthOfRE(m_regularExpression.size());
        for (Index checkIndex = 0; !isEndReached && checkIndex < checkLength; checkIndex++) {
            Indexes nextStatesFromAMatch;
            for (Index const nullTransitionState : nullTransitionStates) {
                if (nullTransitionState < lengthOfRE) {
                    char charInRE(m_regularExpression.at(nullTransitionState));
                    if (charInRE == stringToCheck.at(checkIndex) || charInRE == '.')  // if there is a match
                    {
                        nextStatesFromAMatch.emplace_back(
                            nullTransitionState + 1);  // proceed to next state from nullTransitionState
                    }
                } else if (nullTransitionState == lengthOfRE)  // null transition reached the end
                {
                    isEndReached = true;
                    break;
                }
            }
            if (!isEndReached) {
                nullTransitionStates = getNullTransitionsStates(nextStatesFromAMatch);
            }
        }
        if (!isEndReached) {
            // check if any null transition state reached the end (reverse iteration order to be faster, DFS puts higher
            // vertices at the end)
            isEndReached = std::find(nullTransitionStates.crbegin(), nullTransitionStates.crend(), lengthOfRE) !=
                           nullTransitionStates.crend();
        }
        return isEndReached;
    }

private:
    Indexes getNullTransitionsStates(Indexes const statesFromAMatch) const {
        Indexes result;
        PathSearchUsingDfs<Index> nullTransitionPathSearch(m_nullTransitionsGraph, statesFromAMatch);
        for (Index const state : m_nullTransitionsGraph.getVertices()) {
            if (nullTransitionPathSearch.hasPathTo(state)) {
                result.emplace_back(state);
            }
        }
        return result;
    }

    void initialize() { buildNullTransitionsGraph(); }

    void buildNullTransitionsGraph() {
        std::stack<Index> operatorIndexes;
        Index lengthOfRE(m_regularExpression.length());
        for (Index indexOfRE = 0; indexOfRE < lengthOfRE; indexOfRE++) {
            Index startIndexOfExpression = indexOfRE;
            if (m_regularExpression.at(indexOfRE) == '(' || m_regularExpression.at(indexOfRE) == '|') {
                operatorIndexes.push(indexOfRE);  // push to stack if '(' or '|'
            } else if (m_regularExpression.at(indexOfRE) == ')') {
                Index operatorIndex(operatorIndexes.top());
                operatorIndexes.pop();
                if (m_regularExpression.at(operatorIndex) == '|')  // if stack has an or operator
                {
                    startIndexOfExpression = operatorIndexes.top();
                    operatorIndexes.pop();
                    m_nullTransitionsGraph.connect(
                        startIndexOfExpression,
                        operatorIndex + 1);  // add edge to skip the first part of the expression
                    m_nullTransitionsGraph.connect(
                        operatorIndex, indexOfRE);  // add edge to skip the second part of the expression
                } else                              // opening parenthesis goes here
                {
                    startIndexOfExpression = operatorIndex;
                }
            }
            if (indexOfRE < lengthOfRE - 1 &&
                m_regularExpression.at(indexOfRE + 1) == '*')  // do one character look ahead if its a star
            {
                m_nullTransitionsGraph.connect(
                    startIndexOfExpression,
                    indexOfRE + 1);  // add edge from first part of an expression to current state
                m_nullTransitionsGraph.connect(
                    indexOfRE + 1,
                    startIndexOfExpression);  // add edge from current state going back to first part of an expression
            }
            if (m_regularExpression.at(indexOfRE) == '(' || m_regularExpression.at(indexOfRE) == '*' ||
                m_regularExpression.at(indexOfRE) == ')') {
                m_nullTransitionsGraph.connect(
                    indexOfRE, indexOfRE + 1);  // add edge null transition to next state if its any of these operators
            }
        }
    }

    std::string m_regularExpression;
    DirectedGraphWithListOfEdges<Index> m_nullTransitionsGraph;
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

// Bottom line: REs are amazing powerful and expressive, but using them in applications can be amazingly complex and
// error prone. -> Mark: Thank you!

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
// ---> One state per RE character in the string (start=0, accept=M). Same to KMP where one state represents an index in
// the string
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

// NFA simulation: analysis
// Proposition: Determining whether an N-character text is recognized
// by the NFA corresponding to an M-character pattern takes time proportional to MN in worst case.
// Proof: For each of the N text characters, we iterate through a set of states of size no more than M and run DFS on
// the graph of null transitions.

// Building an NFA corresponding to an RE
// -> [Concatenation]: Add "match transition" edge from state corresponding to characters in the alphabet to next state
// -> [Parentheses]: Add "epsilon/null transition" edge from parentheses to next state
// -> [Closure]: Add three "epsilon/null transition" edge for each * operator.
// ---> There is a need to have current <-> previous transitions to be able to get back as much as want for finding a
// match.
// ---> Single character closure:
// -----> Add edge from current state going back to previous state
// -----> Add edge from previous state to current state
// -----> Add edge from current state to next state
// ---> Closure expression:
// -----> Add edge from current state going back to first opening parenthesis
// -----> Add edge from first opening parenthesis to current state
// -----> Add edge from current state to next state
// -> [Or]: Add two "epsilon/null transition" edge for each | operator.
// ---> Add edge to skip the first part of the expression
// -----> From start of first expression to after | operator
// ---> Add edge to skip the second part of the expression
// -----> From | operator to the end of second part of expression

// NFA construction: implementation
// -> Goal: Write a program to build the "epsilon/null transition" digraph
// -> Challenges: Remember operator locations
// ---> Solution: Maintain a stack:
// -----> '(' symbol: push '(' onto stack
// -----> '|' symbol: push '|' onto stack
// -----> ')' symbol: pop corresponding '(' and possibly intervening '|' add null transitions edges for closure/or.

// NFA construction: analysis
// Proposition: Building the NFA corresponding to an M-character RE takes time and space proportional to M.
// Proof: For each of the M characters in the RE, we add at most three null transitions and execute at most two stack
// operations.

// Applications
// -> GREP: Generalized regular expression print
// ---> Take a RE as command-line argument and print the lines from standard input having some substring that is matched
// by the RE.
// ---> Bottom line: Worst case for grep (proportional to MN) is the same as for brute-force substring search.
// ---> Typical grep application: crossword puzzles.
// ---> Industrial-strength grep implementation:
// -----> Add character classes
// -----> Handle meta characters
// -----> Add capturing capabilities
// -----> Extend the closure operator
// -----> Error checking and recovery
// -----> Greedy vs reluctant matching
// -> Regular expression in other languages
// ---> Broadly applicable programmers tool
// -----> Originated in Unix in the 1970s
// -----> Many languages support extended regular expression
// -----> Built into grep, awk, emacs, Perl, PHP, Python, JavaScript
// ---> Regular expression in java
// -----> Validity checking: Does the input match the regexp?
// -----> Java string libary. Use input.matches(regexp) for basic RE matching.
// -> Harvesting information
// ---> Goal: Print all substring of input that match a RE.

// Algorithmic complexity attacks
// -> Typical implementions do not guarantee performance (unix, perl, java implementation) -> sometimes it takes
// exponential time!

// Not so regular expressions
// -> Back references
// ---> \1 notation matches subexpression that was matched earlier
// ---> Supported by typical RE implementations
// ---> Pattern matching with back-references is intractable

// Context:
// -> Abstract machines, langurages and nondeterminism
// ---> Basis of the theory of computation
// ---> intensively studies since the 1930s
// ---> Basis of programming languages
// -> Compiler: A program that translates a program to machine code.
// ---> KMP: string to DFA
// ---> grep: RE to NFA
// ---> javac: java language to java byte code

// Summary:
// -> Programmer
// ---> Implement a substring search via DFA simulation
// ---> Implement RE pattern matching via NFA simulation
// -> Theoretician
// ---> RE is a compact description of a set of strings.
// ---> NFA is an abstract machine equivalent in power to RE.
// ---> DFAs and REs have limitations
// -> Example of essential paradigms in computer science
// ---> Build interrmediate abstractions
// ---> Pick the right ones!
// ---> Solve important practical problems

}  // namespace algorithm

}  // namespace alba
