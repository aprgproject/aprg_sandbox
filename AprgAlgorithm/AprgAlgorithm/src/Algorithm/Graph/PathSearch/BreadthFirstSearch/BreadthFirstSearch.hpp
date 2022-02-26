#pragma once

#include <Algorithm/Graph/PathSearch/BasePathSearch.hpp>

namespace alba
{

namespace algorithm
{

class BreadthFirstSearch : public BasePathSearch
{
public:

    BreadthFirstSearch(BaseUndirectedGraph const& graph, Vertex const startVertex);

    Path getShortestPathTo(Vertex const endVertex) const;

    void reinitializeStartingFrom(Vertex const startVertex) override;
};

}

}
