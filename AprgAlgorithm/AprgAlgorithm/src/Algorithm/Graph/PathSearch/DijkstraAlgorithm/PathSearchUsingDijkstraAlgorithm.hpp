#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchForDijkstraAndDag.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class PathSearchUsingDijkstraAlgorithm : public BasePathSearchForDijkstraAndDag<Vertex, Weight, EdgeWeightedGraph>
{
public:
    using BaseClass = BasePathSearchForDijkstraAndDag<Vertex, Weight, EdgeWeightedGraph>;
    using SetOfVerticesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::SetOfVerticesWithWeight;

    PathSearchUsingDijkstraAlgorithm(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        searchForShortestPath();
    }

private:

    void searchForShortestPath()
    {
        Vertex const& startVertex(this->m_startVertex);
        SetOfVerticesWithWeight & foundVerticesOrderedByWeight(this->m_foundVerticesOrderedByWeight);
        foundVerticesOrderedByWeight.emplace(startVertex, Weight{}); // start vertex with weight zero for start
        while(!foundVerticesOrderedByWeight.empty())
        {
            auto nearestVertexIt(foundVerticesOrderedByWeight.cbegin());
            auto nearestVertex(*nearestVertexIt);
            foundVerticesOrderedByWeight.erase(nearestVertexIt);
            this->relaxAt(nearestVertex.vertex);
        }
    }

};

}
}