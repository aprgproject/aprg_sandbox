#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchForDijkstraAndDag.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparisonTemplateType>
class PathSearchUsingDijkstraAlgorithm : public BasePathSearchForDijkstraAndDag<Vertex, Weight, EdgeWeightedGraph, ComparisonTemplateType>
{
public:
    using BaseClass = BasePathSearchForDijkstraAndDag<Vertex, Weight, EdgeWeightedGraph, ComparisonTemplateType>;
    using SetOfVerticesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::SetOfVerticesWithWeight;
    using GraphUtilitiesWithVertex = GraphUtilities<Vertex>;

    PathSearchUsingDijkstraAlgorithm(EdgeWeightedGraph const& graph, Vertex const& startVertex)
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
                || GraphUtilitiesWithVertex::isDirectedAcyclicGraph(this->m_graph))
        {
            searchForPath();
        }
    }

    void searchForPath()
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

}

}
