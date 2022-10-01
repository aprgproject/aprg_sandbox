#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

#include <map>
namespace alba
{

namespace math
{

class GameWithGraph
{
public:
    // We will focus on two-player games that do not contain random elements.
    // Our goal is to find a strategy that we can follow to win the game no matter what the opponent does, if such a strategy exists.

    using State = UnsignedInteger;
    using States = std::vector<UnsignedInteger>;
    using StateMachine = algorithm::BaseDirectedGraph<State>;
    using GraphToManipulate = algorithm::DirectedGraphWithListOfEdges<State>;
    using StateToGameStateMap = std::map<State, GameState>;
    using StateToOptimalStateMap = std::map<State, State>;

    GameWithGraph(StateMachine const& stateMachine);

    GameState getGameState(State const state) const;
    State getOptimalNextState(State const state) const;

private:
    void initialize();
    GraphToManipulate createGraphWithReverseDirections(StateMachine const& stateMachine);

    StateMachine const& m_stateMachine;
    StateToGameStateMap m_stateToGameStateMap;
    StateToOptimalStateMap m_stateToOptimalStateMap;
};

}

}
