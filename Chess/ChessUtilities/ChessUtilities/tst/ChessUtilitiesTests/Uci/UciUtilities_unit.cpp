#include <ChessUtilities/Uci/UciUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace chess
{

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnInfoExample1)
{
    CalculationDetails actualDetails{};
    string stringFromEngine(
                "info depth 179 seldepth 2 multipv 1 score mate 1 nodes 5200 nps 57777 tbhits 0 time 90 pv b2d2");

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, stringFromEngine);

    strings expectedPv{"b2d2"};
    EXPECT_EQ(179U, actualDetails.depth);
    EXPECT_EQ(2U, actualDetails.selectiveDepth);
    EXPECT_EQ(90U, actualDetails.time);
    EXPECT_EQ(5200U, actualDetails.nodes);
    EXPECT_EQ(57777U, actualDetails.nodesPerSecond);
    EXPECT_EQ(expectedPv, actualDetails.pvMovesInBestLine);
    EXPECT_EQ(0, actualDetails.scoreInCentipawns);
    EXPECT_EQ(1U, actualDetails.mateInNumberOfMoves);
    EXPECT_TRUE(actualDetails.currentlySearchingMoves.empty());
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.ponderMove.empty());
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnInfoExample2)
{
    CalculationDetails actualDetails{};
    string stringFromEngine(
                "info depth 10 seldepth 12 multipv 1 score cp 14 nodes 20559 nps 1082052 tbhits 0 time 19 pv f6e4 b1d2 d8f6 g1e2 c7c5 d2e4 f5e4 f3f6 f8f6");

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, stringFromEngine);

    strings expectedPv{"f6e4", "b1d2", "d8f6", "g1e2", "c7c5", "d2e4", "f5e4", "f3f6", "f8f6"};
    EXPECT_EQ(10U, actualDetails.depth);
    EXPECT_EQ(12U, actualDetails.selectiveDepth);
    EXPECT_EQ(19U, actualDetails.time);
    EXPECT_EQ(20559U, actualDetails.nodes);
    EXPECT_EQ(1082052U, actualDetails.nodesPerSecond);
    EXPECT_EQ(expectedPv, actualDetails.pvMovesInBestLine);
    EXPECT_EQ(14U, actualDetails.scoreInCentipawns);
    EXPECT_EQ(0U, actualDetails.mateInNumberOfMoves);
    EXPECT_TRUE(actualDetails.currentlySearchingMoves.empty());
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.ponderMove.empty());
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnInfoExample3)
{
    CalculationDetails actualDetails{};
    string stringFromEngine(
                "info depth 23 currmove c7c5 currmovenumber 2");

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, stringFromEngine);

    strings expectedSearchMoves{"", "c7c5"};
    EXPECT_EQ(23U, actualDetails.depth);
    EXPECT_EQ(0U, actualDetails.selectiveDepth);
    EXPECT_EQ(0U, actualDetails.time);
    EXPECT_EQ(0U, actualDetails.nodes);
    EXPECT_EQ(0U, actualDetails.nodesPerSecond);
    EXPECT_TRUE(actualDetails.pvMovesInBestLine.empty());
    EXPECT_EQ(0U, actualDetails.scoreInCentipawns);
    EXPECT_EQ(0U, actualDetails.mateInNumberOfMoves);
    EXPECT_EQ(expectedSearchMoves, actualDetails.currentlySearchingMoves);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.ponderMove.empty());
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnInfoExample4)
{
    CalculationDetails actualDetails{};

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "info depth 23 currmove f8a3 currmovenumber 1");
    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "info depth 23 currmove c7c5 currmovenumber 2");
    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "info depth 23 currmove d7d6 currmovenumber 3");

    strings expectedSearchMoves{"f8a3", "c7c5", "d7d6"};
    EXPECT_EQ(23U, actualDetails.depth);
    EXPECT_EQ(0U, actualDetails.selectiveDepth);
    EXPECT_EQ(0U, actualDetails.time);
    EXPECT_EQ(0U, actualDetails.nodes);
    EXPECT_EQ(0U, actualDetails.nodesPerSecond);
    EXPECT_TRUE(actualDetails.pvMovesInBestLine.empty());
    EXPECT_EQ(0U, actualDetails.scoreInCentipawns);
    EXPECT_EQ(0U, actualDetails.mateInNumberOfMoves);
    EXPECT_EQ(expectedSearchMoves, actualDetails.currentlySearchingMoves);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.ponderMove.empty());
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnBestMoveExample1)
{
    CalculationDetails actualDetails{};

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "bestmove b4c2 ponder e1d1");

    EXPECT_EQ(0U, actualDetails.depth);
    EXPECT_EQ(0U, actualDetails.selectiveDepth);
    EXPECT_EQ(0U, actualDetails.time);
    EXPECT_EQ(0U, actualDetails.nodes);
    EXPECT_EQ(0U, actualDetails.nodesPerSecond);
    EXPECT_TRUE(actualDetails.pvMovesInBestLine.empty());
    EXPECT_EQ(0U, actualDetails.scoreInCentipawns);
    EXPECT_EQ(0U, actualDetails.mateInNumberOfMoves);
    EXPECT_TRUE(actualDetails.currentlySearchingMoves.empty());
    EXPECT_EQ("b4c2", actualDetails.bestMove);
    EXPECT_EQ("e1d1", actualDetails.ponderMove);
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksWithIgnoringStringsWithInvalidStart)
{
    CalculationDetails actualDetails{};

    retrieveCalculationDetailsOnStringFromEngine(
                actualDetails, "NOTVALIDSTART info depth 23 currmove f8a3 currmovenumber 1");
    retrieveCalculationDetailsOnStringFromEngine(
                actualDetails, "NOT VALID START info depth 179 seldepth 2 multipv 1 score mate 1 nodes 5200 nps 57777 tbhits 0 time 90 pv b2d2");
    retrieveCalculationDetailsOnStringFromEngine(
                actualDetails, "INVALIDSTART bestmove b4c2 ponder e1d1");

    // unchanged
    EXPECT_EQ(0U, actualDetails.depth);
    EXPECT_EQ(0U, actualDetails.selectiveDepth);
    EXPECT_EQ(0U, actualDetails.time);
    EXPECT_EQ(0U, actualDetails.nodes);
    EXPECT_EQ(0U, actualDetails.nodesPerSecond);
    EXPECT_TRUE(actualDetails.pvMovesInBestLine.empty());
    EXPECT_EQ(0U, actualDetails.scoreInCentipawns);
    EXPECT_EQ(0U, actualDetails.mateInNumberOfMoves);
    EXPECT_TRUE(actualDetails.currentlySearchingMoves.empty());
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.ponderMove.empty());
}

}

}


