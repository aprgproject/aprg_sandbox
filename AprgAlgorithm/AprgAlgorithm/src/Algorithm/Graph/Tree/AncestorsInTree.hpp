#pragma once

#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class AncestorsInTree
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using VertexAndCountPair = std::pair<Vertex, unsigned int>;
    using VertexAndCountPairToVertexMap = std::map<VertexAndCountPair, Vertex>;
    using Dfs = PathSearchUsingDfs<Vertex>;

    AncestorsInTree(BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree)
        : m_graph(graph)
        , m_rootOfTree(rootOfTree)
        , m_dfs(m_graph, m_rootOfTree)
    {
        initializeIfNeeded();
    }

    Vertex getAncestor(Vertex const& child, unsigned int const distance) const
    {
        return getAncestorInternal(child, distance);
    }

private:

    Vertex getAncestorInternal(Vertex const& vertex, unsigned int const distance) const
    {
        Vertex result(vertex);
        if(distance > 0)
        {
            if(distance%2 == 0 || distance == 1) // is power of two but not zero
            {
                auto it = m_startAndDistancePairToDestinationMap.find({vertex, distance});
                if(it != m_startAndDistancePairToDestinationMap.cend())
                {
                    result = it->second;
                }
            }
            else
            {
                unsigned int halfDistance = distance/2;
                result = getAncestorInternal(getAncestorInternal(vertex, distance-halfDistance), halfDistance);
            }
        }
        return result;
    }

    void initializeIfNeeded()
    {
        if(GraphUtilities::isATree(m_graph))
        {
            initialize();
        }
    }

    void initialize()
    {
        VertexToVertexMap const& vertexToPreviousVertexMap(m_dfs.getVertexToPreviousVertexMap());
        for(Vertex const& child : m_graph.getVertices())
        {
            unsigned int distanceFromChild(0);
            Vertex currentParent = child;
            while(m_rootOfTree != currentParent)
            {
                updateDestinationMap(child, distanceFromChild, currentParent);
                auto it = vertexToPreviousVertexMap.find(currentParent);
                if(it != vertexToPreviousVertexMap.cend())
                {
                    currentParent = it->second;
                    distanceFromChild++;
                }
                else
                {
                    break;
                }
            }
            if(m_rootOfTree == currentParent)
            {
                updateDestinationMap(child, distanceFromChild, currentParent);
            }
        }
    }

    void updateDestinationMap(Vertex const& child, unsigned int const distanceFromChild, Vertex const& parent)
    {
        if(distanceFromChild>0 && (distanceFromChild%2==0 || distanceFromChild==1)) // is power of two but not zero
        {
            m_startAndDistancePairToDestinationMap[VertexAndCountPair(child, distanceFromChild)] = parent;
        }
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    Dfs m_dfs;
    VertexAndCountPairToVertexMap m_startAndDistancePairToDestinationMap;
};

}

}
