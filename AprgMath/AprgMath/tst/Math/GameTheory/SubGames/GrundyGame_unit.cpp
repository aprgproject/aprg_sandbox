#include <Math/GameTheory/SubGames/GrundyGame.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace math {

namespace {
using StickHeaps = GrundyGame::StickHeaps;
}

TEST(GrundyGameTest, Example1Works) {
    GrundyGame game(8U);

    EXPECT_EQ((StickHeaps{8U}), game.getStickHeaps());
    EXPECT_EQ(2U, game.getOverallGrundyNumber());
    EXPECT_EQ(GameState::Winning, game.getGameState());
    EXPECT_EQ(make_tuple(0U, 1U, 7U), game.getOptimalWayToSplit());
    EXPECT_FALSE(game.hasNoMoves());
    game.split(make_tuple(0U, 1U, 7U));

    EXPECT_EQ((StickHeaps{1U, 7U}), game.getStickHeaps());
    EXPECT_EQ(0U, game.getOverallGrundyNumber());
    EXPECT_EQ(GameState::Losing, game.getGameState());
    EXPECT_EQ(make_tuple(1U, 1U, 6U), game.getOptimalWayToSplit());
    EXPECT_FALSE(game.hasNoMoves());
    game.split(make_tuple(1U, 1U, 6U));

    EXPECT_EQ((StickHeaps{1U, 1U, 6U}), game.getStickHeaps());
    EXPECT_EQ(1U, game.getOverallGrundyNumber());
    EXPECT_EQ(GameState::Winning, game.getGameState());
    EXPECT_EQ(make_tuple(2U, 2U, 4U), game.getOptimalWayToSplit());
    EXPECT_FALSE(game.hasNoMoves());
    game.split(make_tuple(2U, 2U, 4U));

    EXPECT_EQ((StickHeaps{1U, 1U, 2U, 4U}), game.getStickHeaps());
    EXPECT_EQ(0U, game.getOverallGrundyNumber());
    EXPECT_EQ(GameState::Losing, game.getGameState());
    EXPECT_EQ(make_tuple(3U, 1U, 3U), game.getOptimalWayToSplit());
    EXPECT_FALSE(game.hasNoMoves());
    game.split(make_tuple(3U, 1U, 3U));

    EXPECT_EQ((StickHeaps{1U, 1U, 2U, 1U, 3U}), game.getStickHeaps());
    EXPECT_EQ(1U, game.getOverallGrundyNumber());
    EXPECT_EQ(GameState::Winning, game.getGameState());
    EXPECT_EQ(make_tuple(4U, 1U, 2U), game.getOptimalWayToSplit());
    EXPECT_FALSE(game.hasNoMoves());
    game.split(make_tuple(4U, 1U, 2U));

    EXPECT_EQ((StickHeaps{1U, 1U, 2U, 1U, 1U, 2U}), game.getStickHeaps());
    EXPECT_EQ(0U, game.getOverallGrundyNumber());
    EXPECT_EQ(GameState::Losing, game.getGameState());
    EXPECT_EQ(make_tuple(0U, 0U, 0U), game.getOptimalWayToSplit());
    EXPECT_TRUE(game.hasNoMoves());
}

}  // namespace math

}  // namespace alba
