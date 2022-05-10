#include <AlgorithmTests/UnionFind/PercolationExample/MonteCarloSimulationOfPerculation.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

namespace algorithm
{

TEST(MonteCarloSimulationOfPerculationTest, DISABLED_DimensionsByEightExample)
{
    MonteCarloSimulationOfPerculation<8U> simulation;

    simulation.addOpenSitesUntilItPercolates();

    EXPECT_LT(0.0, simulation.getPercolationProbability());
    cout << simulation.getSitesToDisplay() << endl;
    cout << "Percolation probability: " << simulation.getPercolationProbability() << endl;
}

TEST(MonteCarloSimulationOfPerculationTest, DISABLED_DimensionsByTwentyExample)
{
    MonteCarloSimulationOfPerculation<20U> simulation;

    simulation.addOpenSitesUntilItPercolates();

    EXPECT_LT(0.0, simulation.getPercolationProbability());
    cout << simulation.getSitesToDisplay() << endl;
    cout << "Percolation probability: " << simulation.getPercolationProbability() << endl;
}

TEST(MonteCarloSimulationOfPerculationTest, DISABLED_DimensionsByFiftyExample)
{
    MonteCarloSimulationOfPerculation<50U> simulation;

    simulation.addOpenSitesUntilItPercolates();

    EXPECT_LT(0.0, simulation.getPercolationProbability());
    cout << simulation.getSitesToDisplay() << endl;
    cout << "Percolation probability: " << simulation.getPercolationProbability() << endl;
}

}

}
