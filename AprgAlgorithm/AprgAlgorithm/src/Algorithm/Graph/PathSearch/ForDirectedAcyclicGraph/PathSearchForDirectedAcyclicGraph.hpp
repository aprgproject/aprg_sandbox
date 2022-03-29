#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchForDijkstraAndDag.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparisonTemplateType>
class PathSearchForDirectedAcyclicGraph : public BasePathSearchForDijkstraAndDag<Vertex, Weight, EdgeWeightedGraph, ComparisonTemplateType>
{
public:
    using BaseClass = BasePathSearchForDijkstraAndDag<Vertex, Weight, EdgeWeightedGraph, ComparisonTemplateType>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using GraphUtilitiesWithVertex = GraphUtilities<Vertex>;
    using VertexOrderingUsingDfsWithVertex = VertexOrderingUsingDfs<Vertex>;

    PathSearchForDirectedAcyclicGraph(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        searchForPathIfPossible();
    }

private:

    void searchForPathIfPossible()
    {
        if(GraphUtilitiesWithVertex::isDirectedAcyclicGraph(this->m_graph))
        {
            searchForPath();
        }
    }

    void searchForPath()
    {
        VertexOrderingUsingDfsWithVertex vertexOrdering(this->m_graph);
        Vertices verticesInTopologicalOrder(vertexOrdering.getVerticesInTopologicalOrder());
        for(Vertex const& vertex : verticesInTopologicalOrder)
        {
            this->relaxAt(vertex);
        }
    }

};

}

}
