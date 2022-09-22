#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename BaseGraphType, typename BaseEulerPathSearchType>
class BaseHierholzerAlgorithm : public BaseEulerPathSearchType
{
public:
    using BaseClass = BaseEulerPathSearchType;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToAdjacencyVerticesMap = std::map<Vertex, Vertices>;

    BaseHierholzerAlgorithm(BaseGraphType const& graph)
        : BaseClass(graph)
        , b_graph(BaseClass::m_graph)
    {}

    Path getEulerCycle() const override
    {
        Path result;
        if(!b_graph.isEmpty() && this->hasEulerCycle()) // this is check is needed because Hierholzer algorithm does not check this
        {
            searchForEulerPath(result, this->getStartingVertexForEulerCycle());
        }
        return result;
    }

    Path getEulerPath() const override
    {
        Path result;
        if(!b_graph.isEmpty() && this->hasEulerPath()) // this is check is needed because Hierholzer algorithm does not check this
        {
            searchForEulerPath(result, this->getStartingVertexForEulerPath());
        }
        return result;
    }

protected:

    virtual void searchForEulerPath(Path & result, Vertex const& startingVertex) const = 0;

    BaseGraphType const& b_graph;
};

}

}

// Hierholzer's 1873 paper provides a different method for finding Euler cycles that is more efficient than Fleury's algorithm.

// Steps:
// Step 1) Choose any starting vertex v, and follow a trail of edges from that vertex until returning to v.
// It is not possible to get stuck at any vertex other than v, because the even degree of all vertices ensures that,
// when the trail enters another vertex w there must be an unused edge leaving w.
// The tour formed in this way is a closed tour, but may not cover all the vertices and edges of the initial graph.
// Step 2) As long as there exists a vertex u that belongs to the current tour but that has adjacent edges not part of the tour,
// start another trail from u, following unused edges until returning to u, and join the tour formed in this way to the previous tour.

// By using a data structure such as a doubly linked list to maintain the set of unused edges incident to each vertex,
// to maintain the list of vertices on the current tour that have unused edges,
// and to maintain the tour itself, the individual operations of the algorithm
// (finding unused edges exiting each vertex, finding a new starting vertex for a tour, and connecting two tours that share a vertex)
// may be performed in constant time each, so the overall algorithm takes linear time O(E).

// This algorithm may also be implemented with a deque.
// Because it is only possible to get stuck when the deque represents a closed tour, one should rotate the deque by removing edges from the tail
// and adding them to the head until unstuck, and then continue until all edges are accounted for.
// This also takes linear time O(E), as the number of rotations performed is never larger than |E|/