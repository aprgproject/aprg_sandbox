#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class CountPathsInDirectedGraph
{
public:

    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    struct VertexDetail
    {
        Vertex vertex;
        SetOfVertices dependentVertices;
    };
    using ListOfVertexDetails = std::vector<VertexDetail>;
    using VertexToIndexMap = std::map<Vertex, unsigned int>;
    using VertexPair = std::pair<Vertex, Vertex>;
    using VertexPairToCountMap = std::map<std::pair<Vertex, Vertex>, unsigned int>;

    CountPathsInDirectedGraph(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {
        initialize();
    }

    unsigned int getCount(Vertex const& start, Vertex const& end)
    {
        return getCountInternal(start, end);
    }

private:
    void initialize()
    {
        Vertices verticesInOrder(VertexOrderingUsingDfs<Vertex>(m_graph).getVerticesInTopologicalOrder());
        unsigned int index(0);
        for(Vertex const& vertexInOrder : verticesInOrder)
        {
            m_orderedVertexDetailsIndex[vertexInOrder] = index++;
            m_orderedVertexDetailsList.emplace_back(VertexDetail{vertexInOrder, {}});
        }

        for(Edge const& edge : m_graph.getEdges())
        {
            unsigned int index(m_orderedVertexDetailsIndex.at(edge.second));
            m_orderedVertexDetailsList[index].dependentVertices.emplace(edge.first);
        }
    }

    unsigned int getCountInternal(Vertex const& start, Vertex const& end)
    {
        unsigned int result(1U); // if start and end are equal, then return one count
        if(start != end)
        {
            auto it = m_pathCounts.find({start, end});
            if(it != m_pathCounts.cend())
            {
                result = it->second;
            }
            else
            {
                result = sumCounts(start, end);
                m_pathCounts.emplace(VertexPair{start, end}, result);
            }
        }
        return result;
    }

    unsigned int sumCounts(Vertex const& start, Vertex const& end)
    {
        unsigned int result(0);
        auto itStart=m_orderedVertexDetailsIndex.find(start);
        auto itEnd=m_orderedVertexDetailsIndex.find(end);
        if(itStart!=m_orderedVertexDetailsIndex.cend()
                && itEnd!=m_orderedVertexDetailsIndex.cend())
        {
            unsigned int startIndex = itStart->second;
            unsigned int endIndex = itEnd->second;
            int distanceInTopologicalOrder = static_cast<int>(endIndex) - static_cast<int>(startIndex);
            // if distanceInTopologicalOrder is positive: sum counts of dependent vertices at the end
            // if distanceInTopologicalOrder is zero: count is 1
            // if distanceInTopologicalOrder is negative: count is 0
            if(distanceInTopologicalOrder > 0)
            {
                for(Vertex const& dependentVertexAtEnd : m_orderedVertexDetailsList.at(endIndex).dependentVertices)
                {
                    result += getCountInternal(start, dependentVertexAtEnd);
                }
            }
            else if(distanceInTopologicalOrder == 0)
            {
                result = 1U;
            }
        }
        return result;
    }

    BaseDirectedGraphWithVertex const& m_graph;
    ListOfVertexDetails m_orderedVertexDetailsList;
    VertexToIndexMap m_orderedVertexDetailsIndex;
    VertexPairToCountMap m_pathCounts; // dynamic programming
};

}

}
