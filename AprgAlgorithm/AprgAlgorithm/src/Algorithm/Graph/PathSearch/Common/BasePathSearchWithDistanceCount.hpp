#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BasePathSearchWithDistanceCount
{
public:
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;

    BasePathSearchWithDistanceCount() = default;

    virtual ~BasePathSearchWithDistanceCount() = default;

    unsigned int getDistanceTo(Vertex const& endVertex) const
    {
        unsigned int result(0);
        auto it = m_endVertexToDistanceCountMap.find(endVertex);
        if(it != m_endVertexToDistanceCountMap.cend())
        {
            result = it->second;
        }
        return result;
    }

    VertexToUnsignedIntMap const& getEndVertexToDistanceCountMap() const
    {
        return m_endVertexToDistanceCountMap;
    }

protected:
    VertexToUnsignedIntMap m_endVertexToDistanceCountMap;
};

}

}
