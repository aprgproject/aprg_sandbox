#pragma once

#include <Algorithm/UnionFind/WeightedQuickUnionWithArray.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/User/DisplayTable.hpp>

#include <string>
#include <vector>

using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

template <int DIMENSION>
class MonteCarloSimulationOfPerculation {
public:
    MonteCarloSimulationOfPerculation()
        : m_sites{}, m_unionFindOfIndexes(), m_numberOfOpenSites(0), m_randomizer(0, getDimensionsSquared() - 1) {}

    bool isPercolated() const {
        return m_unionFindOfIndexes.isConnected(getVirtualTopIndex(), getVirtualBottomIndex());
    }

    double getPercolationProbability() const {
        return static_cast<double>(m_numberOfOpenSites) / getDimensionsSquared();
    }

    std::string getSitesToDisplay() const {
        DisplayTable displayTable;
        for (int y = 0; y < DIMENSION; y++) {
            displayTable.addRow();
            for (int x = 0; x < DIMENSION; x++) {
                std::string cell = isSiteOpen(getIndex(x, y)) ? " " : "X";
                displayTable.getLastRow().addCell(cell);
            }
        }
        displayTable.setBorders("-", "|");
        return convertToString(displayTable);
    }

    void addOpenSitesUntilItPercolates() {
        while (!isPercolated()) {
            addOpenSite();
        }
    }

    void addOpenSite() {
        while (true) {
            int newOpenSiteIndex(m_randomizer.getRandomValue());
            if (!isSiteOpen(newOpenSiteIndex)) {
                m_sites[newOpenSiteIndex] = true;
                connectNeighboringSitesAt(newOpenSiteIndex);
                connectToVirtualTopOrBottomIfNeeded(newOpenSiteIndex);
                m_numberOfOpenSites++;
                break;
            }
        }
    }

private:
    static constexpr int getDimensionsSquared() {
        constexpr int DIMENSION_SQUARED = DIMENSION * DIMENSION;
        return DIMENSION_SQUARED;
    }

    static constexpr int getVirtualTopIndex() { return getDimensionsSquared(); }

    static constexpr int getVirtualBottomIndex() { return getDimensionsSquared() + 1; }

    bool isSiteOpen(int const index) const { return m_sites[index]; }

    int getIndex(int const x, int const y) const { return y * DIMENSION + x; }

    void retrieveCoordinates(int const index, int& x, int& y) const {
        x = index % DIMENSION;
        y = index / DIMENSION;
    }

    void connectNeighboringSitesAt(int const index) {
        int x, y;
        retrieveCoordinates(index, x, y);
        if (x > 0) {
            connectNeighborSites(index, getIndex(x - 1, y));
        }
        if (y > 0) {
            connectNeighborSites(index, getIndex(x, y - 1));
        }
        if (x < DIMENSION - 1) {
            connectNeighborSites(index, getIndex(x + 1, y));
        }
        if (y < DIMENSION - 1) {
            connectNeighborSites(index, getIndex(x, y + 1));
        }
    }

    void connectNeighborSites(int const mainIndex, int const neighborIndex) {
        if (isSiteOpen(neighborIndex)) {
            m_unionFindOfIndexes.connect(mainIndex, neighborIndex);
        }
    }

    void connectToVirtualTopOrBottomIfNeeded(int const indexToCheck) {
        int x, y;
        retrieveCoordinates(indexToCheck, x, y);
        if (y == 0) {
            m_unionFindOfIndexes.connect(getVirtualTopIndex(), indexToCheck);
        } else if (y == DIMENSION - 1) {
            m_unionFindOfIndexes.connect(getVirtualBottomIndex(), indexToCheck);
        }
    }

    std::array<bool, getDimensionsSquared()> m_sites;
    WeightedQuickUnionWithArray<int, getDimensionsSquared() + 2>
        m_unionFindOfIndexes;  //+2 because of virtual top site and bottom site
    int m_numberOfOpenSites;
    AlbaUniformNonDeterministicRandomizer<int> m_randomizer;
};

}  // namespace algorithm

}  // namespace alba
