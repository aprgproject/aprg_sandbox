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
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;

    BasePathSearchWithDistanceCount() = default;

    unsigned int getDistanceTo(Vertex const& endVertex) const
    {
        unsigned int result(0);        auto it = m_endVertexToDistanceCountMap.find(endVertex);
        if(it != m_endVertexToDistanceCountMap.cend())
        {
            result = it->second;        }
        return result;
    }

    VertexToUnsignedIntMap const& getEndVertexToDistanceCountMap() const
    {
        return m_endVertexToDistanceCountMap;
    }

    void initializeDistances(Vertices const& vertices)
    {
        for(Vertex const& vertex : vertices)
        {
            m_endVertexToDistanceCountMap.emplace(vertex, 0U);
        }
    }

    void updateDistance(Vertex const& adjacentVertex, Vertex const& vertex)
    {
        unsigned int distanceToVertex(0U);
        auto it = this->m_endVertexToDistanceCountMap.find(vertex);
        if(it != this->m_endVertexToDistanceCountMap.cend())
        {
            distanceToVertex = it->second;
        }
        this->m_endVertexToDistanceCountMap[adjacentVertex] = distanceToVertex+1U;
    }

protected:
    // No need for virtual destructor because this class is not destroyed polymorphically.
    // Guideline #4: A base class destructor should be either public and virtual, or protected and nonvirtual.
    // Source: http://www.gotw.ca/publications/mill18.htm
    ~BasePathSearchWithDistanceCount() = default;

private:

    VertexToUnsignedIntMap m_endVertexToDistanceCountMap;};

}
}
