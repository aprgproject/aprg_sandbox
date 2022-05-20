#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithRelax.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

#include <queue>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparatorTemplateType>
class PathSearchUsingDijkstra : public BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>
{
public:
    using BaseClass = BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>;
    using VertexWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::VertexWithWeight;
    template<typename ValueType>
    struct ReverseComparator
    {
        bool operator()(ValueType const& first, ValueType const& second) const
        {
            return ComparatorTemplateType<ValueType>()(second, first);
        }
    };
    using VertexWithWeightPriorityQueue = std::priority_queue<VertexWithWeight, std::deque<VertexWithWeight>, ReverseComparator<VertexWithWeight>>;

    PathSearchUsingDijkstra(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        searchForPathIfPossible();
    }

private:

    bool isComparisonLessThan() const
    {
        ComparatorTemplateType<unsigned int> comparisonInUnsignedInt;
        return (comparisonInUnsignedInt(1U, 2U) && !comparisonInUnsignedInt(1U, 1U));
    }

    void searchForPathIfPossible()
    {
        if(isComparisonLessThan()
                || GraphUtilities::isDirectedAcyclicGraph(this->m_graph))
        {
            searchForPath();
        }
    }

    void searchForPath()
    {
        VertexWithWeightPriorityQueue foundVerticesOrderedByWeight;
        foundVerticesOrderedByWeight.emplace(this->m_startVertex, Weight{}); // start vertex with weight zero for start
        while(!foundVerticesOrderedByWeight.empty())
        {
            // loops all current best weight vertices and only updates if the weight is better
            // this essentially prims algorithm but here weight is accumulated from the start vertex (Prim just take the closest)
            VertexWithWeight vertexWithBestWeight(foundVerticesOrderedByWeight.top());
            foundVerticesOrderedByWeight.pop();
            this->relaxAt(vertexWithBestWeight.vertex, [&](Vertex const&, Vertex const& destinationVertex, Weight const& newLowestWeight)
            {
                foundVerticesOrderedByWeight.emplace(destinationVertex, newLowestWeight); // this step is after relaxation on every adjacent vertex (only if weight is changed)
            });
        }
    }

};

// Dijkstra algorithm computes a shortest path tree in any edge-weighted digraph with non negative weights,
// Proof:
// -> Each edge e=v->w is relaxed exactly once (when v is relaxed), leaving distTo[w] <= distTo[v] + e.weight()
// -> Inequality holds until algorithm terminates because:
// ---> distTo[w] cannot decrease (relax prevents this)
// ---> distTo[v] will not change at all
// ---> Thus, upon termination shortest path optimality conditions hold.

// Running time:
// depends on Indexed-PQ implementation: Total = V inserts + V deletemins + E decrease-keys
// array: insert(1), delete-min(V), decrease-key(1) -> total = V^2
// binary heap: insert(log V), delete-min(log V), decrease-key(log V) -> total = E log V
// d-way heap: insert(d logd V)), delete-min(d logd V), decrease-key(d logd V) -> total = E log(E/V) V
// Fibonacci heap: insert(1*), delete-min(log V*), decrease-key(1*) -> total = E + V log V
// * means amortized
// Bottom line:
// -> Array implementation optimal for dense graphs
// -> Binary heap is faster for sparse graphs
// -> 4 way heap is worth the trouble in performance-critical situations
// -> Fibonacci heap is best in theory, but too complicated to implement (not worth it in practice)

// Negative weights:
// Dijsktra algorithm: Does not work on negative weights


}

}
