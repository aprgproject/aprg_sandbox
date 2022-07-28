#pragma once

#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <string>

namespace alba
{

class DeBruijnSequences
{
public:
    // A De Bruijn sequence is a string that contains every string of length n exactly once as a substring, for a fixed alphabet of k characters.
    // The length of such a string is k^n + n - 1 characters.

    DeBruijnSequences(unsigned int const substringSize, std::string const& alphabet);

    std::string getDeBruijnString() const;

private:
    void initialize();
    void addAllSubstringsAsVertex();    void addSubstringAsVertex(unsigned int const depth, std::string const& substring);
    unsigned int const m_substringSize;
    std::string const m_alphabet;
    algorithm::DirectedGraphWithListOfEdges<std::string> m_graph;};

// An Eulerian path in this graph corresponds to a string that contains all strings of length n.
// The string contains the characters of the starting node and all characters of the edges.
// The starting node has n-1 characters and there are k^n characters in the edges, so the length of the string is k^n + n - 1.

}
