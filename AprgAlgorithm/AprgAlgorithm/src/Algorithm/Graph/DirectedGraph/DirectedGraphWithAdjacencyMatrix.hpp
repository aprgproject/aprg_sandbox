#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, unsigned int MAX_VERTEX_VALUE>
class DirectedGraphWithAdjacencyMatrix : public BaseDirectedGraph<Vertex>
{
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using AdjacencyMatrix = matrix::AlbaMatrix<bool>;

    DirectedGraphWithAdjacencyMatrix()
        : m_numberOfEdges(0U)
        , m_adjacencyMatrix(MAX_VERTEX_VALUE, MAX_VERTEX_VALUE)
    {}

    bool isEmpty() const
    {
        return m_numberOfEdges==0;
    }

    bool isDirectlyConnected(Vertex const& vertex1, Vertex const& vertex2) const override
    {
        return m_adjacencyMatrix.getEntry(vertex1, vertex2);
    }

    unsigned int getNumberOfVertices() const override
    {
        return getVertices().size();
    }

    unsigned int getNumberOfEdges() const override
    {
        return m_numberOfEdges;
    }

    Vertices getAdjacentVerticesAt(Vertex const& vertex) const override
    {
        Vertices result;
        unsigned int numberOfRows(m_adjacencyMatrix.getNumberOfRows());
        for(Vertex possibleAdjacentVertex=0; possibleAdjacentVertex<numberOfRows; possibleAdjacentVertex++)
        {
            if(isDirectlyConnected(vertex, possibleAdjacentVertex))
            {
                result.emplace_back(possibleAdjacentVertex);
            }
        }
        return result;
    }

    Vertices getVertices() const override
    {
        std::array<bool, MAX_VERTEX_VALUE> isVertexIncluded{};

        unsigned int numberOfColumns(m_adjacencyMatrix.getNumberOfColumns());
        unsigned int numberOfRows(m_adjacencyMatrix.getNumberOfRows());
        for(Vertex vertex1=0; vertex1<numberOfColumns; vertex1++)
        {
            for(Vertex vertex2=0; vertex2<numberOfRows; vertex2++)
            {
                if(isDirectlyConnected(vertex1, vertex2))
                {
                    isVertexIncluded[vertex1] = true;
                    isVertexIncluded[vertex2] = true;
                }
            }
        }

        Vertices result;
        for(Vertex vertex=0; vertex<MAX_VERTEX_VALUE; vertex++)
        {
            if(isVertexIncluded.at(vertex))
            {
                result.emplace_back(vertex);
            }
        }
        return result;
    }

    Edges getEdges() const override
    {
        Edges result;
        unsigned int numberOfColumns(m_adjacencyMatrix.getNumberOfColumns());
        unsigned int numberOfRows(m_adjacencyMatrix.getNumberOfRows());
        for(Vertex vertex1=0; vertex1<numberOfColumns; vertex1++)
        {
            for(Vertex vertex2=0; vertex2<numberOfRows; vertex2++)
            {
                if(isDirectlyConnected(vertex1, vertex2))
                {
                    result.emplace_back(vertex1, vertex2);
                }
            }
        }
        return result;
    }

    std::string getDisplayableString() const override
    {
        std::string firstPartOfString("Adjacency ");
        matrix::AlbaMatrix<std::string> matrixToDisplay(MAX_VERTEX_VALUE+1, MAX_VERTEX_VALUE+1);
        stringHelper::NumberToStringConverter converter;
        matrixToDisplay.setEntry(0, 0, "X");
        for(unsigned int i=0; i<MAX_VERTEX_VALUE; i++)
        {
            matrixToDisplay.setEntry(i+1, 0, std::string("[")+converter.convert(i)+std::string("]"));
            matrixToDisplay.setEntry(0, i+1, std::string("[")+converter.convert(i)+std::string("]"));
        }
        m_adjacencyMatrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
        {
            matrixToDisplay.setEntry(x+1, y+1, converter.convert(isDirectlyConnected(x, y)));
        });
        return firstPartOfString + matrixToDisplay.getString();
    }

    AdjacencyMatrix const& getAdjacencyMatrix() const
    {
        return m_adjacencyMatrix;
    }

    void connect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        if(!isDirectlyConnected(vertex1, vertex2))        {
            m_numberOfEdges++;
            m_adjacencyMatrix.setEntry(vertex1, vertex2, true);
        }    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        if(isDirectlyConnected(vertex1, vertex2))
        {
            m_numberOfEdges--;
            m_adjacencyMatrix.setEntry(vertex1, vertex2, false);
        }
    }

    void clear()
    {
        m_numberOfEdges = 0;
        m_adjacencyMatrix.clearAndResize(MAX_VERTEX_VALUE, MAX_VERTEX_VALUE);
    }

protected:

    unsigned int m_numberOfEdges;
    AdjacencyMatrix m_adjacencyMatrix; // vertex by adjacent matrix
};

}

}
