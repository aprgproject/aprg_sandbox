#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithRelax.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparatorTemplateType>
class PathSearchForDirectedAcyclicGraph : public BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>
{
public:
    using BaseClass = BasePathSearchWithRelax<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexOrderingUsingDfsWithVertex = VertexOrderingUsingDfs<Vertex>;

    PathSearchForDirectedAcyclicGraph(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : BaseClass(graph, startVertex)
    {
        searchForPathIfPossible();
    }

private:

    void searchForPathIfPossible()
    {
        if(GraphUtilities::isDirectedAcyclicGraph(this->m_graph))
        {
            searchForPath();
        }
    }

    void searchForPath()
    {
        VertexOrderingUsingDfsWithVertex vertexOrdering(this->m_graph);
        Vertices verticesInTopologicalOrder(vertexOrdering.getVerticesInTopologicalOrder()); // Uses topological sort
        // Since dependency is in order, we are assured we are getting best weight path for each vertex
        // This works even with negative weights
        for(Vertex const& vertex : verticesInTopologicalOrder)
        {
            this->relaxAt(vertex);
        }
    }

};

// Applications:
// -> Content-aware resizing. Seam carving: Resize an image without distortion for display on cell phones and web browsers.
// ---> how to find seams: less weighted (energy function) path from top to bottom (horizontal scaling) or left to right (vertical scaling)
// ---> and just remove the seams
// -> Parallel job scheduling
// ---> How to find the minimum completion time? Longest path in the graph. This is critical path method (CPM).

}

}
