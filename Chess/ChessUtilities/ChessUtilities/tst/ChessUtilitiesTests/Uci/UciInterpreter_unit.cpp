#include <ChessUtilities/Engine/CalculationDetailsEqualityOperators.hpp>
#include <ChessUtilities/Uci/UciInterpreter.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace chess {

TEST(UciInterpreterTest, UpdateCalculationDetailsWorksWithMultiPvWithScore) {
    CalculationDetails actualDetails{};
    UciInterpreter interpreter(actualDetails);

    interpreter.updateCalculationDetails(
        "info depth 3 seldepth 3 multipv 1 score cp -69 nodes 16 nps 16000 tbhits 0 time 1 pv e8f7 e5e6 f7e6");

    Variation expectedVariation{0, -69, {"e8f7", "e5e6", "f7e6"}};
    Variations expectedVariations{expectedVariation};
    EXPECT_EQ(3U, actualDetails.depthInPlies);
    EXPECT_EQ(3U, actualDetails.selectiveDepthInPlies);    EXPECT_EQ(expectedVariations, actualDetails.variations);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.responseMoveToPonder.empty());
}

TEST(UciInterpreterTest, UpdateCalculationDetailsWorksWithMultiPvWithMate) {
    CalculationDetails actualDetails{};
    UciInterpreter interpreter(actualDetails);

    interpreter.updateCalculationDetails(
        "info depth 179 seldepth 2 multipv 1 score mate -3 nodes 5200 nps 57777 tbhits 0 time 90 pv b2d2");

    Variation expectedVariation{-3, 0, {"b2d2"}};
    Variations expectedVariations{expectedVariation};
    EXPECT_EQ(179U, actualDetails.depthInPlies);
    EXPECT_EQ(2U, actualDetails.selectiveDepthInPlies);    EXPECT_EQ(expectedVariations, actualDetails.variations);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.responseMoveToPonder.empty());
}

TEST(UciInterpreterTest, UpdateCalculationDetailsWorksWithOverwritingVariationIfSameMultiPv) {
    CalculationDetails actualDetails{};
    UciInterpreter interpreter(actualDetails);
    interpreter.updateCalculationDetails(
        "info depth 10 seldepth 12 multipv 1 score cp 14 nodes 20559 nps 1082052 tbhits 0 time 19 pv f6e4 b1d2 d8f6");
    interpreter.updateCalculationDetails(
        "info depth 10 seldepth 12 multipv 1 score cp 98 nodes 20559 nps 1082052 tbhits 0 time 19 pv g1e2 c7c5 d2e4");

    Variation expectedVariation{0, 98, {"g1e2", "c7c5", "d2e4"}};
    Variations expectedVariations{expectedVariation};
    EXPECT_EQ(10U, actualDetails.depthInPlies);
    EXPECT_EQ(12U, actualDetails.selectiveDepthInPlies);    EXPECT_EQ(expectedVariations, actualDetails.variations);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.responseMoveToPonder.empty());
}

TEST(UciInterpreterTest, UpdateCalculationDetailsWorksWithExpandingVariationsByOne) {
    CalculationDetails actualDetails{};
    UciInterpreter interpreter(actualDetails);
    interpreter.updateCalculationDetails(
        "info depth 10 seldepth 12 multipv 1 score cp 14 nodes 20559 nps 1082052 tbhits 0 time 19 pv f6e4 b1d2 d8f6");
    interpreter.updateCalculationDetails(
        "info depth 10 seldepth 12 multipv 2 score cp 98 nodes 20559 nps 1082052 tbhits 0 time 19 pv g1e2 c7c5 d2e4");

    Variation expectedVariation1{0, 14, {"f6e4", "b1d2", "d8f6"}};
    Variation expectedVariation2{0, 98, {"g1e2", "c7c5", "d2e4"}};
    Variations expectedVariations{expectedVariation1, expectedVariation2};
    EXPECT_EQ(10U, actualDetails.depthInPlies);
    EXPECT_EQ(12U, actualDetails.selectiveDepthInPlies);    EXPECT_EQ(expectedVariations, actualDetails.variations);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.responseMoveToPonder.empty());
}

TEST(UciInterpreterTest, UpdateCalculationDetailsWorksWithExpandingVariationsMoreThanOne) {
    CalculationDetails actualDetails{};
    UciInterpreter interpreter(actualDetails);
    interpreter.updateCalculationDetails(
        "info depth 10 seldepth 12 multipv 1 score cp 14 nodes 20559 nps 1082052 tbhits 0 time 19 pv f6e4 b1d2 d8f6");
    interpreter.updateCalculationDetails(
        "info depth 10 seldepth 12 multipv 5 score cp 98 nodes 20559 nps 1082052 tbhits 0 time 19 pv g1e2 c7c5 d2e4");

    Variation expectedVariation1{0, 14, {"f6e4", "b1d2", "d8f6"}};
    Variation expectedVariation2{0, 98, {"g1e2", "c7c5", "d2e4"}};
    Variations expectedVariations{expectedVariation1, {}, {}, {}, expectedVariation2};
    EXPECT_EQ(10U, actualDetails.depthInPlies);
    EXPECT_EQ(12U, actualDetails.selectiveDepthInPlies);    EXPECT_EQ(expectedVariations, actualDetails.variations);
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.responseMoveToPonder.empty());
}

TEST(UciInterpreterTest, UpdateCalculationDetailsWorksOnInfoExample4) {
    CalculationDetails actualDetails{};
    UciInterpreter interpreter(actualDetails);
    interpreter.updateCalculationDetails("info depth 23 currmove f8a3 currmovenumber 1");
    interpreter.updateCalculationDetails("info depth 23 currmove c7c5 currmovenumber 2");
    interpreter.updateCalculationDetails("info depth 23 currmove d7d6 currmovenumber 3");

    Variations expectedVariations;
    EXPECT_EQ(0U, actualDetails.depthInPlies);
    EXPECT_EQ(0U, actualDetails.selectiveDepthInPlies);
    EXPECT_TRUE(actualDetails.variations.empty());
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.responseMoveToPonder.empty());
}

TEST(UciInterpreterTest, UpdateCalculationDetailsWorksOnBestMoveExample1) {
    CalculationDetails actualDetails{};
    UciInterpreter interpreter(actualDetails);
    interpreter.updateCalculationDetails("bestmove b4c2 ponder e1d1");

    EXPECT_EQ(0U, actualDetails.depthInPlies);
    EXPECT_EQ(0U, actualDetails.selectiveDepthInPlies);
    EXPECT_TRUE(actualDetails.variations.empty());
    EXPECT_EQ("b4c2", actualDetails.bestMove);
    EXPECT_EQ("e1d1", actualDetails.responseMoveToPonder);
}

TEST(UciInterpreterTest, UpdateCalculationDetailsWorksWithIgnoringStringsWithInvalidStart) {
    CalculationDetails actualDetails{};
    UciInterpreter interpreter(actualDetails);
    interpreter.updateCalculationDetails("NOTVALIDSTART info depth 23 currmove f8a3 currmovenumber 1");
    interpreter.updateCalculationDetails(
        "NOT VALID START info depth 179 seldepth 2 multipv 1 score mate 1 time 90 pv b2d2");
    interpreter.updateCalculationDetails("INVALIDSTART bestmove b4c2 ponder e1d1");

    // unchanged
    EXPECT_EQ(0U, actualDetails.depthInPlies);
    EXPECT_EQ(0U, actualDetails.selectiveDepthInPlies);
    EXPECT_TRUE(actualDetails.variations.empty());
    EXPECT_TRUE(actualDetails.bestMove.empty());
    EXPECT_TRUE(actualDetails.responseMoveToPonder.empty());
}

}  // namespace chess

}  // namespace alba
