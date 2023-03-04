#pragma once

#include <Algorithm/UnionFind/WeightedQuickUnionWithArray.hpp>
#include <Common/Randomizer/AlbaSimpleRandomizer.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <string>
#include <vector>

using namespace alba::stringHelper;

namespace alba
{

namespace algorithm
{

template <unsigned int DIMENSION>
class MonteCarloSimulationOfPerculation
{
public:

    MonteCarloSimulationOfPerculation()
        : m_sites{} // all are blocked
        , m_unionFindOfIndexes()
        , m_numberOfOpenSites(0U)
        , m_randomizer()
    {}

    bool isPercolated() const
    {
        return m_unionFindOfIndexes.isConnected(getVirtualTopIndex(), getVirtualBottomIndex());
    }

    double getPercolationProbability() const
    {
        return static_cast<double>(m_numberOfOpenSites) / getDimensionsSquared();
    }

    std::string getSitesToDisplay() const
    {
        DisplayTable displayTable;
        for(unsigned int y=0; y<DIMENSION; y++)
        {
            displayTable.addRow();
            for(unsigned int x=0; x<DIMENSION; x++)
            {
                std::string cell = isSiteOpen(getIndex(x, y)) ? " " : "X";
                displayTable.getLastRow().addCell(cell);
            }
        }
        displayTable.setBorders("-", "|");
        return convertToString(displayTable);
    }

    void addOpenSitesUntilItPercolates()
    {
        while(!isPercolated())
        {
            addOpenSite();
        }
    }

    void addOpenSite()
    {
        while(true)
        {
            unsigned int newOpenSiteIndex(m_randomizer.getRandomIntegerInUniformDistribution(0, getDimensionsSquared()-1));
            if(!isSiteOpen(newOpenSiteIndex))
            {
                m_sites[newOpenSiteIndex] = true;                connectNeighboringSitesAt(newOpenSiteIndex);
                connectToVirtualTopOrBottomIfNeeded(newOpenSiteIndex);
                m_numberOfOpenSites++;
                break;            }
        }
    }

private:

    static constexpr unsigned int getDimensionsSquared()
    {
        constexpr unsigned int DIMENSION_SQUARED = DIMENSION*DIMENSION;
        return DIMENSION_SQUARED;
    }

    static constexpr unsigned int getVirtualTopIndex()
    {
        return getDimensionsSquared();
    }

    static constexpr unsigned int getVirtualBottomIndex()
    {
        return getDimensionsSquared()+1;
    }

    bool isSiteOpen(
            unsigned int const index) const
    {
        return m_sites.at(index);
    }

    unsigned int getIndex(
            unsigned int const x,
            unsigned int const y) const
    {
        return y*DIMENSION + x;
    }

    void retrieveCoordinates(
            unsigned int const index,
            unsigned int & x,
            unsigned int & y) const
    {
        x = index % DIMENSION;
        y = index / DIMENSION;
    }

    void connectNeighboringSitesAt(
            unsigned int const index)
    {
        unsigned int x, y;
        retrieveCoordinates(index, x, y);
        if(x > 0)
        {
            connectNeighborSites(index, getIndex(x-1, y));
        }
        if(y > 0)
        {
            connectNeighborSites(index, getIndex(x, y-1));
        }
        if(x < DIMENSION-1)
        {
            connectNeighborSites(index, getIndex(x+1, y));
        }
        if(y < DIMENSION-1)
        {
            connectNeighborSites(index, getIndex(x, y+1));
        }
    }

    void connectNeighborSites(
            unsigned int const mainIndex,
            unsigned int const neighborIndex)
    {
        if(isSiteOpen(neighborIndex))
        {
            m_unionFindOfIndexes.connect(mainIndex, neighborIndex);
        }
    }

    void connectToVirtualTopOrBottomIfNeeded(
            unsigned int const indexToCheck)
    {
        unsigned int x, y;
        retrieveCoordinates(indexToCheck, x, y);
        if(y == 0)
        {
            m_unionFindOfIndexes.connect(getVirtualTopIndex(), indexToCheck);
        }
        else if(y == DIMENSION-1)
        {
            m_unionFindOfIndexes.connect(getVirtualBottomIndex(), indexToCheck);
        }
    }

    std::array<bool, getDimensionsSquared()> m_sites;
    WeightedQuickUnionWithArray<unsigned int, getDimensionsSquared()+2> m_unionFindOfIndexes; //+2 because of virtual top site and bottom site
    unsigned int m_numberOfOpenSites;
    AlbaSimpleRandomizer m_randomizer;
};

}

}
