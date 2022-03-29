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
        m_foundVerticesOrderedByWeight.emplace(startVertex, Weight{}); // start vertex with weight zero for start
        while(!m_foundVerticesOrderedByWeight.empty())
        {
            auto nearestVertexIt(m_foundVerticesOrderedByWeight.cbegin());
            auto nearestVertex(*nearestVertexIt);
            m_foundVerticesOrderedByWeight.erase(nearestVertexIt);
            this->relaxAt(nearestVertex.vertex, [&](Vertex const&, Vertex const& destinationVertex, Weight const& lowestWeight)
            {
                m_foundVerticesOrderedByWeight.emplace(destinationVertex, lowestWeight);
            });
        }
    }

    SetOfVerticesWithWeight m_foundVerticesOrderedByWeight;

};

}}