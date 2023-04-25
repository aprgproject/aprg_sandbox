#include <Math/GameTheory/SpecificGames/MisereGame.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace math {

TEST(MisereGameTest, GetGameStateWorks) {
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({10U, 12U, 5U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({9U, 12U, 5U}));
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({8U, 12U, 5U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({8U, 12U, 4U}));
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({7U, 12U, 4U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({7U, 3U, 4U}));
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({6U, 3U, 4U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({6U, 2U, 4U}));
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({5U, 2U, 4U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({5U, 1U, 4U}));
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({4U, 1U, 4U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({4U, 0U, 4U}));
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({3U, 0U, 4U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({3U, 0U, 3U}));
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({2U, 0U, 3U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({2U, 0U, 2U}));
    EXPECT_EQ(GameState::Winning, MisereGame::getGameState({1U, 0U, 2U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({1U, 0U, 0U}));
    EXPECT_EQ(GameState::Losing, MisereGame::getGameState({0U, 0U, 0U}));
}

TEST(MisereGameTest, GetOptimalNextStateWorks) {
    EXPECT_EQ((NimState{9U, 12U, 5U}), MisereGame::getOptimalNextState({10U, 12U, 5U}));
    EXPECT_EQ((NimState{8U, 12U, 5U}), MisereGame::getOptimalNextState({9U, 12U, 5U}));
    EXPECT_EQ((NimState{8U, 12U, 4U}), MisereGame::getOptimalNextState({8U, 12U, 5U}));
    EXPECT_EQ((NimState{7U, 12U, 4U}), MisereGame::getOptimalNextState({8U, 12U, 4U}));
    EXPECT_EQ((NimState{7U, 3U, 4U}), MisereGame::getOptimalNextState({7U, 12U, 4U}));
    EXPECT_EQ((NimState{6U, 3U, 4U}), MisereGame::getOptimalNextState({7U, 3U, 4U}));
    EXPECT_EQ((NimState{6U, 2U, 4U}), MisereGame::getOptimalNextState({6U, 3U, 4U}));
    EXPECT_EQ((NimState{5U, 2U, 4U}), MisereGame::getOptimalNextState({6U, 2U, 4U}));
    EXPECT_EQ((NimState{5U, 1U, 4U}), MisereGame::getOptimalNextState({5U, 2U, 4U}));
    EXPECT_EQ((NimState{4U, 1U, 4U}), MisereGame::getOptimalNextState({5U, 1U, 4U}));
    EXPECT_EQ((NimState{4U, 0U, 4U}), MisereGame::getOptimalNextState({4U, 1U, 4U}));
    EXPECT_EQ((NimState{3U, 0U, 4U}), MisereGame::getOptimalNextState({4U, 0U, 4U}));
    EXPECT_EQ((NimState{3U, 0U, 3U}), MisereGame::getOptimalNextState({3U, 0U, 4U}));
    EXPECT_EQ((NimState{2U, 0U, 3U}), MisereGame::getOptimalNextState({3U, 0U, 3U}));
    EXPECT_EQ((NimState{2U, 0U, 2U}), MisereGame::getOptimalNextState({2U, 0U, 3U}));
    EXPECT_EQ((NimState{1U, 0U, 2U}), MisereGame::getOptimalNextState({2U, 0U, 2U}));
    EXPECT_EQ((NimState{1U, 0U, 0U}), MisereGame::getOptimalNextState({1U, 0U, 2U}));
    EXPECT_EQ((NimState{0U, 0U, 0U}), MisereGame::getOptimalNextState({1U, 0U, 0U}));
    EXPECT_EQ((NimState{0U, 0U, 0U}), MisereGame::getOptimalNextState({0U, 0U, 0U}));
}

}  // namespace math

}  // namespace alba
