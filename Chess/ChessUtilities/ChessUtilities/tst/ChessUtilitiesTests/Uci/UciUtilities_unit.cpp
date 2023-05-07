#include <ChessUtilities/Uci/UciUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace chess {

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnInfoExample1) {
    CalculationDetails actualDetails{};
    string stringFromEngine(
        "info depth 3 seldepth 3 multipv 1 score cp -69 nodes 16 nps 16000 tbhits 0 time 1 pv e8f7 e5e6 f7e6");

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, stringFromEngine);

    strings expectedPv{"e8f7", "e5e6", "f7e6"};
    StringAndIntPairs expectedMoveAndScorePairs{{"e8f7", -69}};
    EXPECT_EQ(3U, actualDetails.depthInPlies);
    EXPECT_EQ(3U, actualDetails.selectiveDepthInPlies);
    EXPECT_EQ(0, actualDetails.numberOfMovesTillMate);
    EXPECT_EQ(expectedPv, actualDetails.pvMovesInBestLine);
    EXPECT_EQ(expectedMoveAndScorePairs, actualDetails.searchingMoveAndScorePairs);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.possibleResponseMove.empty());
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnInfoExample2) {
    CalculationDetails actualDetails{};
    string stringFromEngine(
        "info depth 179 seldepth 2 multipv 1 score mate -1 nodes 5200 nps 57777 tbhits 0 time 90 pv b2d2");

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, stringFromEngine);

    strings expectedPv{"b2d2"};
    StringAndIntPairs expectedMoveAndScorePairs{{"b2d2", -999999}};
    EXPECT_EQ(179U, actualDetails.depthInPlies);
    EXPECT_EQ(2U, actualDetails.selectiveDepthInPlies);
    EXPECT_EQ(-1, actualDetails.numberOfMovesTillMate);
    EXPECT_EQ(expectedPv, actualDetails.pvMovesInBestLine);
    EXPECT_EQ(expectedMoveAndScorePairs, actualDetails.searchingMoveAndScorePairs);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.possibleResponseMove.empty());
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnInfoExample3) {
    CalculationDetails actualDetails{};
    string stringFromEngine(
        "info depth 10 seldepth 12 multipv 1 score cp 14 nodes 20559 nps 1082052 tbhits 0 time 19 pv f6e4 b1d2 d8f6 "
        "g1e2 c7c5 d2e4 f5e4 f3f6 f8f6");

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, stringFromEngine);

    strings expectedPv{"f6e4", "b1d2", "d8f6", "g1e2", "c7c5", "d2e4", "f5e4", "f3f6", "f8f6"};
    StringAndIntPairs expectedMoveAndScorePairs{{"f6e4", 14}};
    EXPECT_EQ(10U, actualDetails.depthInPlies);
    EXPECT_EQ(12U, actualDetails.selectiveDepthInPlies);
    EXPECT_EQ(0, actualDetails.numberOfMovesTillMate);
    EXPECT_EQ(expectedPv, actualDetails.pvMovesInBestLine);
    EXPECT_EQ(expectedMoveAndScorePairs, actualDetails.searchingMoveAndScorePairs);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.possibleResponseMove.empty());
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnInfoExample4) {
    CalculationDetails actualDetails{};

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "info depth 23 currmove f8a3 currmovenumber 1");
    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "info depth 23 currmove c7c5 currmovenumber 2");
    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "info depth 23 currmove d7d6 currmovenumber 3");

    EXPECT_EQ(0U, actualDetails.depthInPlies);
    EXPECT_EQ(0U, actualDetails.selectiveDepthInPlies);
    EXPECT_EQ(0, actualDetails.numberOfMovesTillMate);
    EXPECT_TRUE(actualDetails.pvMovesInBestLine.empty());
    EXPECT_TRUE(actualDetails.searchingMoveAndScorePairs.empty());
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.possibleResponseMove.empty());
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksOnBestMoveExample1) {
    CalculationDetails actualDetails{};

    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "bestmove b4c2 ponder e1d1");

    EXPECT_EQ(0U, actualDetails.depthInPlies);
    EXPECT_EQ(0U, actualDetails.selectiveDepthInPlies);
    EXPECT_EQ(0, actualDetails.numberOfMovesTillMate);
    EXPECT_TRUE(actualDetails.pvMovesInBestLine.empty());
    EXPECT_TRUE(actualDetails.searchingMoveAndScorePairs.empty());
    EXPECT_EQ("b4c2", actualDetails.bestMove);
    EXPECT_EQ("e1d1", actualDetails.possibleResponseMove);
}

TEST(UciUtilitiesTest, RetrieveCalculationDetailsOnStringFromEngineWorksWithIgnoringStringsWithInvalidStart) {
    CalculationDetails actualDetails{};

    retrieveCalculationDetailsOnStringFromEngine(
        actualDetails, "NOTVALIDSTART info depth 23 currmove f8a3 currmovenumber 1");
    retrieveCalculationDetailsOnStringFromEngine(
        actualDetails,
        "NOT VALID START info depth 179 seldepth 2 multipv 1 score mate 1 nodes 5200 nps 57777 tbhits 0 time 90 pv "
        "b2d2");
    retrieveCalculationDetailsOnStringFromEngine(actualDetails, "INVALIDSTART bestmove b4c2 ponder e1d1");

    // unchanged
    EXPECT_EQ(0U, actualDetails.depthInPlies);
    EXPECT_EQ(0U, actualDetails.selectiveDepthInPlies);
    EXPECT_EQ(0, actualDetails.numberOfMovesTillMate);
    EXPECT_TRUE(actualDetails.pvMovesInBestLine.empty());
    EXPECT_TRUE(actualDetails.searchingMoveAndScorePairs.empty());
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.possibleResponseMove.empty());
}

}  // namespace chess

}  // namespace alba
