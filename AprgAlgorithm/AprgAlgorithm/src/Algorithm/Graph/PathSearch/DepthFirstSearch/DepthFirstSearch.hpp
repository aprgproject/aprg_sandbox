#pragma once

#include <Algorithm/Graph/PathSearch/BasePathSearch.hpp>

namespace alba
{
namespace algorithm
{

class DepthFirstSearch : public BasePathSearch
{
public:
    DepthFirstSearch(BaseUndirectedGraph const& graph, Vertex const startVertex);

    Path getOrderedPathTo(Vertex const endVertex);

    void reinitializeStartingFrom(Vertex const startVertex) override;

private:
    void continueTraversal(Vertex const vertex);
};

}
}
