#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename BaseGraphType, typename BaseEulerPathSearchType>
class BaseHierholzerAlgorithm : public BaseEulerPathSearchType
{
public:
    using BaseClass = BaseEulerPathSearchType;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;

    BaseHierholzerAlgorithm(BaseGraphType const& graph)
        : BaseClass(graph)
        , b_graph(BaseClass::m_graph)
    {}

    Path getEulerCycle() const override
    {
        Path result;
        if(this->hasEulerCycle()) // this is check is needed because Hierholzer algorithm does not check this
        {
            searchForEulerPath(result, this->getStartingVertexForEulerCycle());
        }
        return result;
    }

    Path getEulerPath() const override
    {
        Path result;
        if(this->hasEulerPath()) // this is check is needed because Hierholzer algorithm does not check this
        {
            searchForEulerPath(result, this->getStartingVertexForEulerPath());
        }
        return result;
    }

protected:

    virtual void searchForEulerPath(Path & result, Vertex const& startingVertex) const = 0;

    BaseGraphType const& b_graph;
};

}

}
