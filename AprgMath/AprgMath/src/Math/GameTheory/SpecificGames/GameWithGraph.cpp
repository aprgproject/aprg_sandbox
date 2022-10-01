#include "GameWithGraph.hpp"

#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace math
{

GameWithGraph::GameWithGraph(
        StateMachine const& stateMachine)
    : m_stateMachine(stateMachine)
{
    initialize();
}

GameState GameWithGraph::getGameState(State const state) const
{
    GameState result(GameState::Losing);
    auto it = m_stateToGameStateMap.find(state);
    if(it != m_stateToGameStateMap.cend())
    {
        result = it->second;
    }
    return result;
}

GameWithGraph::State GameWithGraph::getOptimalNextState(State const state) const
{
    State result{};
    auto it = m_stateToOptimalStateMap.find(state);
    if(it != m_stateToOptimalStateMap.cend())
    {
        result = it->second;
    }
    return result;
}

void GameWithGraph::initialize()
{
    GraphToManipulate graphWithReverseDirections(createGraphWithReverseDirections(m_stateMachine));
    algorithm::VertexOrderingUsingDfs<State> vertexOrdering(graphWithReverseDirections);
    States statesInTopologicalOrder(vertexOrdering.getVerticesInTopologicalOrder());
    // topological sort only works when this one final losing state

    if(!statesInTopologicalOrder.empty())
    {        State previousState = statesInTopologicalOrder.front();
        for(unsigned int i=0; i<statesInTopologicalOrder.size(); i++)
        {
            State state = statesInTopologicalOrder.at(i);
            GameState gameState = isEven(i) ? GameState::Losing : GameState::Winning;
            m_stateToGameStateMap[state] = gameState;
            m_stateToOptimalStateMap[state] = previousState;
            previousState = state;
        }
    }
}

GameWithGraph::GraphToManipulate GameWithGraph::createGraphWithReverseDirections(
        StateMachine const& stateMachine)
{
    GraphToManipulate graphWithReverseDirections;
    for(auto const& edge : stateMachine.getEdges())
    {
        graphWithReverseDirections.connect(edge.second, edge.first);
    }
    return graphWithReverseDirections;
}

}

}
