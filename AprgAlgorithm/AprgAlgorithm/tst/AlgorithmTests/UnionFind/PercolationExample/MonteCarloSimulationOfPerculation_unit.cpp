#include <AlgorithmTests/UnionFind/PercolationExample/MonteCarloSimulationOfPerculation.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

namespace algorithm {

TEST(MonteCarloSimulationOfPerculationTest, DISABLED_DimensionsByEightExample) {
    MonteCarloSimulationOfPerculation<8> simulation;

    simulation.addOpenSitesUntilItPercolates();

    EXPECT_LT(0.0, simulation.getPercolationProbability());
    cout << simulation.getSitesToDisplay() << "\n";
    cout << "Percolation probability: " << simulation.getPercolationProbability() << "\n";
}

TEST(MonteCarloSimulationOfPerculationTest, DISABLED_DimensionsByTwentyExample) {
    MonteCarloSimulationOfPerculation<20> simulation;

    simulation.addOpenSitesUntilItPercolates();

    EXPECT_LT(0.0, simulation.getPercolationProbability());
    cout << simulation.getSitesToDisplay() << "\n";
    cout << "Percolation probability: " << simulation.getPercolationProbability() << "\n";
}

TEST(MonteCarloSimulationOfPerculationTest, DISABLED_DimensionsByFiftyExample) {
    MonteCarloSimulationOfPerculation<50> simulation;

    simulation.addOpenSitesUntilItPercolates();

    EXPECT_LT(0.0, simulation.getPercolationProbability());
    cout << simulation.getSitesToDisplay() << "\n";
    cout << "Percolation probability: " << simulation.getPercolationProbability() << "\n";
}

}  // namespace algorithm

}  // namespace alba
