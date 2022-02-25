#pragma once

#include <Algorithm/Graph/GraphTypes.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

namespace alba
{

namespace algorithm
{

template <unsigned int MAX_VERTEX_VALUE>
class UndirectedGraphWithAdjacencyMatrix : public BaseUndirectedGraph
{
public:
    using AdjacencyMatrix = matrix::AlbaMatrix<bool>;

    UndirectedGraphWithAdjacencyMatrix()
        : m_numberOfVertices(0U)
        , m_numberOfEdges(0U)
        , m_adjacencyMatrix(MAX_VERTEX_VALUE, MAX_VERTEX_VALUE)
    {}

    bool isConnected(Vertex const vertex1, Vertex const vertex2) const override
    {
        return m_adjacencyMatrix.getEntry(vertex1, vertex2);
    }

    unsigned int getNumberOfVertices() const override
    {
        return m_numberOfVertices;
    }

    unsigned int getNumberOfEdges() const override
    {
        return m_numberOfEdges;
    }

    Vertices getAdjacentVerticesAt(Vertex const vertex) const override
    {
        Vertices result;
        unsigned int numberOfRows(m_adjacencyMatrix.getNumberOfRows());
        for(unsigned int possibleAdjacentVertex=0; possibleAdjacentVertex<numberOfRows; possibleAdjacentVertex++)
        {
            if(isConnected(vertex, possibleAdjacentVertex))
            {
                result.emplace_back(possibleAdjacentVertex);
            }
        }
        return result;
    }

    Vertices getVertices() const override
    {
        Vertices result;
        unsigned int numberOfColumns(m_adjacencyMatrix.getNumberOfColumns());
        for(Vertex vertex=0; vertex<numberOfColumns; vertex++)
        {
            if(isAnyVertexConnectedAtThisVertex(vertex))
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
            for(Vertex vertex2=vertex1; vertex2<numberOfRows; vertex2++)
            {
                if(m_adjacencyMatrix.getEntry(vertex1, vertex2))
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
            matrixToDisplay.setEntry(x+1, y+1, converter.convert(m_adjacencyMatrix.getEntry(x, y)));
        });
        return firstPartOfString + matrixToDisplay.getString();
    }

    void connect(Vertex const vertex1, Vertex const vertex2) override
    {
        if(!isConnected(vertex1, vertex2))
        {
            if(!isAnyVertexConnectedAtThisVertex(vertex1))
            {
                m_numberOfVertices++;
            }
            if(!isAnyVertexConnectedAtThisVertex(vertex2))
            {
                m_numberOfVertices++;
            }
            m_numberOfEdges++;
            m_adjacencyMatrix.setEntry(vertex1, vertex2, true);
            m_adjacencyMatrix.setEntry(vertex2, vertex1, true);
        }
    }

    void disconnect(Vertex const vertex1, Vertex const vertex2) override
    {
        if(isConnected(vertex1, vertex2))
        {
            m_numberOfEdges--;
            m_adjacencyMatrix.setEntry(vertex1, vertex2, false);
            m_adjacencyMatrix.setEntry(vertex2, vertex1, false);
            if(!isAnyVertexConnectedAtThisVertex(vertex1))
            {
                m_numberOfVertices--;
            }
            if(!isAnyVertexConnectedAtThisVertex(vertex2))
            {
                m_numberOfVertices--;
            }
        }
    }

private:

    bool isAnyVertexConnectedAtThisVertex(Vertex const vertex) const
    {
        AdjacencyMatrix::MatrixData column;
        m_adjacencyMatrix.retrieveColumn(column, vertex);
        return std::any_of(column.cbegin(), column.cend(), [](bool const isConnected)
        {
            return isConnected;
        });
    }
    unsigned int m_numberOfVertices;
    unsigned int m_numberOfEdges;
    AdjacencyMatrix m_adjacencyMatrix;
};

}

}
