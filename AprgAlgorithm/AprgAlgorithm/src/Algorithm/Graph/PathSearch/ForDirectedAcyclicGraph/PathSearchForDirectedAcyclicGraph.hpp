#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchForDijkstraAndDag.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class PathSearchForDirectedAcyclicGraph : public BasePathSearchForDijkstraAndDag<Vertex, Weight, EdgeWeightedGraph>
{
public:
    using BaseClass = BasePathSearchForDijkstraAndDag<Vertex, Weight, EdgeWeightedGraph>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using GraphUtilitiesWithVertex = GraphUtilities<Vertex>;
    using VertexOrderingUsingDfsWithVertex = VertexOrderingUsingDfs<Vertex>;

    PathSearchForDirectedAcyclicGraph(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        searchForShortestPathIfPossible();
    }

private:

    void searchForShortestPathIfPossible()
    {
        if(GraphUtilitiesWithVertex::isDirectedAcyclicGraph(this->m_graph))
        {
            searchForShortestPath();
        }
    }

    void searchForShortestPath()
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
