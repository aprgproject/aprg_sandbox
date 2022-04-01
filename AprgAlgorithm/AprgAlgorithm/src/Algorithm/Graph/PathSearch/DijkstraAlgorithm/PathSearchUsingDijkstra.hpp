#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithRelax.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparisonTemplateType>
class PathSearchUsingDijkstra : public BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparisonTemplateType>
{
public:
    using BaseClass = BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparisonTemplateType>;
    using SetOfVerticesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::SetOfVerticesWithWeight;

    PathSearchUsingDijkstra(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        searchForPathIfPossible();
    }

private:

    bool isComparisonLessThan() const
    {
        ComparisonTemplateType<unsigned int> comparisonInUnsignedInt;
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
        SetOfVerticesWithWeight foundVerticesOrderedByWeight{{this->m_startVertex, Weight{}}}; // start vertex with weight zero for start
        while(!foundVerticesOrderedByWeight.empty())
        {
            auto nearestVertexIt(foundVerticesOrderedByWeight.cbegin());
            auto nearestVertex(*nearestVertexIt);
            foundVerticesOrderedByWeight.erase(nearestVertexIt);
            this->relaxAt(nearestVertex.vertex, [&](Vertex const&, Vertex const& destinationVertex, Weight const& lowestWeight)
            {
                foundVerticesOrderedByWeight.emplace(destinationVertex, lowestWeight);
            });
        }
    }

};

}

}
