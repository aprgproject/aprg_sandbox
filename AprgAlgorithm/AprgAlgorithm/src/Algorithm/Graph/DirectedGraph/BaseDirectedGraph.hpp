#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

#include <string>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class BaseDirectedGraph : public BaseGraph<Vertex>
{
public:
    using Edges = typename GraphTypes<Vertex>::Edges;

    GraphDirectionType getGraphDirectionType() const
    {
        return GraphDirectionType::Directed;
    }

    void reverseDirections()
    {
        Edges originalEdges(this->getEdges());        this->clear();
        for(auto const& originalEdge : originalEdges)
        {
            this->connect(originalEdge.second, originalEdge.first);        }
    }
};

}

}
