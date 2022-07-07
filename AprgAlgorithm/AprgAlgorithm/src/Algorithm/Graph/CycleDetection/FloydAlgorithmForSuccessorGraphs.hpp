#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/SuccessorGraph/WalkInSuccessorGraph.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class FloydAlgorithmforSuccessorGraphs
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Walker = WalkInSuccessorGraph<Vertex>;
    using Path = typename GraphTypes<Vertex>::Path;

    FloydAlgorithmforSuccessorGraphs(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
        , m_walker(graph)
    {}

    bool hasACycle() const
    {
        return m_hasACycle;
    }

    Path getCycle() const
    {
        return m_cyclePath;
    }

    void reinitializeStartingFrom(Vertex const& startOfGraph)
    {
        Vertex meetingVertex(getMeetingVertexAndCheckForACycle(startOfGraph));
        m_cyclePath.clear();
        if(m_hasACycle)
        {
            saveCycle(getStartOfCycle(startOfGraph, meetingVertex));
        }
    }

private:

    Vertex getMeetingVertexAndCheckForACycle(Vertex const& startOfGraph)
    {
        Vertex turtoise(walkOne(startOfGraph));
        Vertex hare(walkTwo(startOfGraph));
        while(turtoise != hare && !isAtTheEnd(hare)) // stop if there meet or end is reached
        {
            turtoise = walkOne(turtoise); // walks one
            hare = walkTwo(hare); // walks two
        }
        m_hasACycle = turtoise == hare && !isAtTheEnd(hare); // if they meet there is a cycle, however if end is reached its not a cycle
        return hare;
    }

    Vertex getStartOfCycle(Vertex const& startOfGraph, Vertex const& meetingVertex)
    {
        Vertex vertex1 = startOfGraph;
        Vertex vertex2 = meetingVertex;
        while(vertex1 != vertex2) // if they meet again, then its the start of the cycle
        {
            vertex1 = walkOne(vertex1);
            vertex2 = walkOne(vertex2);
        }
        return vertex1;
    }

    void saveCycle(Vertex startOfCycle)
    {
        m_cyclePath.emplace_back(startOfCycle);
        Vertex vertex = walkOne(startOfCycle); // vertex traverses the cycle
        while(startOfCycle != vertex)
        {
            m_cyclePath.emplace_back(vertex); // vertex traverses the cycle
            vertex = walkOne(vertex);
        }
        m_cyclePath.emplace_back(vertex);
    }

    bool isAtTheEnd(Vertex const& vertex) const
    {
        return m_walker.isAtTheEnd(vertex);
    }

    Vertex walkOne(Vertex const& vertex)
    {
        return m_walker.walk(vertex, 1U);
    }

    Vertex walkTwo(Vertex const& vertex)
    {
        return m_walker.walk(vertex, 2U);
    }

    BaseDirectedGraphWithVertex const& m_graph;
    Walker m_walker;
    bool m_hasACycle;
    Path m_cyclePath;

};

}

}
