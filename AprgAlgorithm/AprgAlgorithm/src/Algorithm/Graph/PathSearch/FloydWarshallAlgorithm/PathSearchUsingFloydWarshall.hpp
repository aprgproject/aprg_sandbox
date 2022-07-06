#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparatorTemplateType>
class PathSearchUsingFloydWarshall
{
public:
    struct PathDetails
    {
        bool hasAPath;
        Vertex bestAdjacentVertex;
        Weight bestWeight;
    };
    using Graph = EdgeWeightedGraph;
    using Path = typename GraphTypes<Vertex>::Path;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using PathDetailsMatrix = matrix::AlbaMatrix<PathDetails>;
    using Comparator=ComparatorTemplateType<Weight>;

    PathSearchUsingFloydWarshall(EdgeWeightedGraph const& graph)
        : m_graph(graph)
        , m_pathDetailsMatrix(graph.getNumberOfVertices(), graph.getNumberOfVertices())
    {
        searchForBestPaths();
    }

    bool hasPathTo(Vertex const& startVertex, Vertex const& endVertex) const
    {
        bool result(false);
        if(m_pathDetailsMatrix.isInside(startVertex, endVertex))
        {
            result = m_pathDetailsMatrix.getEntryConstReference(startVertex, endVertex).hasAPath;
        }
        return result;
    }

    Path getPathTo(Vertex const& startVertex, Vertex const& endVertex) const
    {
        Path result;
        Vertex currentVertex = startVertex;
        bool isEndReached(false);
        bool isChanged(true);
        for(unsigned int i=0; i<m_graph.getNumberOfVertices() && currentVertex != endVertex && isChanged; i++)
        {
            isChanged=false;
            result.emplace_back(currentVertex);
            if(m_pathDetailsMatrix.isInside(currentVertex, endVertex))
            {
                PathDetails const& pathDetails(m_pathDetailsMatrix.getEntryConstReference(currentVertex, endVertex));
                if(pathDetails.hasAPath)
                {
                    if(currentVertex == pathDetails.bestAdjacentVertex)
                    {
                        result.emplace_back(endVertex);
                        isEndReached=true;
                        break;
                    }
                    else
                    {
                        currentVertex = pathDetails.bestAdjacentVertex;
                        isChanged = true;
                    }
                }
            }
        }
        if(!isEndReached)
        {
            result.clear();
        }
        return result;
    }

private:

    void searchForBestPaths()
    {
        initializePathDetailsWithEdgeWeights();
        initializePathDetailsInTheDiagonal();
        checkAllIntermediateVertices();
    }

    void initializePathDetailsWithEdgeWeights()
    {
        for(EdgeWithWeight const& edgeWithWeight : m_graph.getEdgesWithWeight())
        {
            m_pathDetailsMatrix.setEntry(edgeWithWeight.first, edgeWithWeight.second, {true, edgeWithWeight.first, edgeWithWeight.weight});
        }
    }

    void initializePathDetailsInTheDiagonal()
    {
        for(Vertex const& vertex : m_graph.getVertices())
        {
            PathDetails & diagonalPathDetails(m_pathDetailsMatrix.getEntryReference(vertex, vertex));
            diagonalPathDetails.hasAPath = true;
            diagonalPathDetails.bestAdjacentVertex = vertex;
        }
    }

    void checkAllIntermediateVertices()
    {
        Vertices vertices(m_graph.getVertices());
        for(Vertex const& intermediateVertex : vertices)
        {
            for(Vertex const& startVertex : vertices)
            {
                if(startVertex != intermediateVertex)
                {
                    PathDetails & startToIntermediateDetails(m_pathDetailsMatrix.getEntryReference(startVertex, intermediateVertex));
                    for(Vertex const& endVertex : vertices)
                    {
                        if(endVertex != intermediateVertex && startVertex != endVertex)
                        {
                            PathDetails & startToEndDetails(m_pathDetailsMatrix.getEntryReference(startVertex, endVertex));
                            PathDetails & intermediateToEndDetails(m_pathDetailsMatrix.getEntryReference(startVertex, intermediateVertex));
                            if(startToIntermediateDetails.hasAPath && intermediateToEndDetails.hasAPath)
                            {
                                Weight possibleNewWeight = startToIntermediateDetails.bestWeight + intermediateToEndDetails.bestWeight;
                                if(!startToEndDetails.hasAPath)
                                {
                                    startToEndDetails = {true, intermediateVertex, possibleNewWeight};
                                }
                                else if(m_comparator(possibleNewWeight, startToEndDetails.bestWeight))
                                {
                                    startToEndDetails.bestAdjacentVertex = intermediateVertex;
                                    startToEndDetails.bestWeight = possibleNewWeight;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Graph const& m_graph;
    Comparator m_comparator;
    PathDetailsMatrix m_pathDetailsMatrix;
};

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparatorTemplateType>
std::ostream & operator<<(std::ostream & out, typename PathSearchUsingFloydWarshall<Vertex, Weight, EdgeWeightedGraph, ComparatorTemplateType>::PathDetails const& pathDetails)
{
    out << pathDetails.hasAPath << "," << pathDetails.bestAdjacentVertex << "," << pathDetails.bestWeight;
    return out;
}


// The Floyd–Warshall algorithm4 provides an alternative way to approach the problem of finding best (shortest/longest) paths.
// The algorithm maintains a two-dimensional array that contains distances between the nodes.
// First, distances are calculated only using direct edges between the nodes, and after this, the algorithm reduces distances by using intermediate nodes in paths.

// Analysis
// The time complexity of the algorithm is O(n3), because it contains three nested loops that go through the nodes of the graph.

// Comments
// Since the implementation of the Floyd–Warshall algorithm is simple,
// the algorithm can be a good choice even if it is only needed to find a single shortest path in the graph.
// However, the algorithm can only be used when the graph is so small that a cubic time complexity is fast enough.
// And the matrix type structure makes it easier to have "start" to "end" path queries

}

}
