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
    enum class DequeDirection
    {
        Front,
        Back
    };
    struct PathDetails
    {
        bool hasAPath;
        Vertex bestAdjacentVertex;
        Weight bestWeight;
    };
    using Graph = EdgeWeightedGraph;
    using Path = typename GraphTypes<Vertex>::Path;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using DequeOfVertices = typename GraphTypes<Vertex>::DequeOfVertices;
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
        if(startVertex != endVertex && m_pathDetailsMatrix.isInside(startVertex, endVertex))
        {
            PathDetails const& pathDetails(m_pathDetailsMatrix.getEntryConstReference(startVertex, endVertex));
            if(pathDetails.hasAPath)
            {
                DequeOfVertices pathInDeque;
                addToPath(pathInDeque, DequeDirection::Front, startVertex, endVertex);
                pathInDeque.emplace_front(startVertex);
                pathInDeque.emplace_back(endVertex);
                result.reserve(pathInDeque.size());
                std::copy(pathInDeque.cbegin(), pathInDeque.cend(), std::back_inserter(result));
            }
        }
        return result;
    }

private:

    void addToPath(DequeOfVertices & pathInDeque, DequeDirection const direction, Vertex const& first, Vertex const& second) const
    {
        if(first != second && m_pathDetailsMatrix.isInside(first, second) && pathInDeque.size() < 10)
        {
            PathDetails const& firstToSecond(m_pathDetailsMatrix.getEntryConstReference(first, second));
            if(firstToSecond.hasAPath)
            {
                if(first != firstToSecond.bestAdjacentVertex && second != firstToSecond.bestAdjacentVertex)
                {
                    if(DequeDirection::Front == direction)
                    {
                        pathInDeque.emplace_front(firstToSecond.bestAdjacentVertex);
                    }
                    else if(DequeDirection::Back == direction)
                    {
                        pathInDeque.emplace_back(firstToSecond.bestAdjacentVertex);
                    }
                    PathDetails const& firstToMiddle(m_pathDetailsMatrix.getEntryConstReference(first, firstToSecond.bestAdjacentVertex));
                    PathDetails const& middleToSecond(m_pathDetailsMatrix.getEntryConstReference(firstToSecond.bestAdjacentVertex, second));
                    if(firstToMiddle.hasAPath
                            && middleToSecond.hasAPath
                            && firstToMiddle.bestWeight < firstToSecond.bestWeight
                            && middleToSecond.bestWeight < firstToSecond.bestWeight)
                    {
                        addToPath(pathInDeque, DequeDirection::Front, first, firstToSecond.bestAdjacentVertex);
                        addToPath(pathInDeque, DequeDirection::Back, firstToSecond.bestAdjacentVertex, second);
                    }
                }
            }
        }
    }

    std::string getDisplayableString()
    {
        DisplayTable displayTable;
        for(unsigned int y=0; y<m_pathDetailsMatrix.getNumberOfRows(); y++)
        {
            displayTable.addRow();
            for(unsigned int x=0; x<m_pathDetailsMatrix.getNumberOfRows(); x++)
            {
                std::stringstream ss;
                ss<<m_pathDetailsMatrix.getEntryConstReference(x,y).hasAPath;
                displayTable.getLastRow().addCell(ss.str());
            }
            displayTable.getLastRow().addCell("   ");
            for(unsigned int x=0; x<m_pathDetailsMatrix.getNumberOfRows(); x++)
            {
                std::stringstream ss;
                ss<<m_pathDetailsMatrix.getEntryConstReference(x,y).bestAdjacentVertex;
                displayTable.getLastRow().addCell(ss.str());
            }
            displayTable.getLastRow().addCell("   ");
            for(unsigned int x=0; x<m_pathDetailsMatrix.getNumberOfRows(); x++)
            {
                std::stringstream ss;
                ss<<m_pathDetailsMatrix.getEntryConstReference(x,y).bestWeight;
                displayTable.getLastRow().addCell(ss.str());
            }
        }
        displayTable.setBorders("-", "|");
        return std::string("\n") + displayTable.drawOutput();
    }

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
                            PathDetails & intermediateToEndDetails(m_pathDetailsMatrix.getEntryReference(intermediateVertex, endVertex));
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
