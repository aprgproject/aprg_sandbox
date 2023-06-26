#include "MultipleGamesWithMaze.hpp"

#include <Math/GameTheory/Common/GameUtilities.hpp>

#include <sstream>

using namespace std;

namespace alba {

namespace math {

bool MultipleGamesWithMaze::hasNoMoves() const {
    bool result(true);
    for (UnsignedInteger gameIndex = 0; gameIndex < m_games.size(); gameIndex++) {
        if (!m_games[gameIndex].hasNoMoves(m_coordinateInGames[gameIndex])) {
            result = false;
            break;
        }    }
    return result;
}
UnsignedInteger MultipleGamesWithMaze::getOverallGrundyNumber() { return getCombinedGrundyNumber(); }

GameState MultipleGamesWithMaze::getGameState() { return getGameStateFromGrundyNumber(getOverallGrundyNumber()); }

MultipleGamesWithMaze::GameIndexAndCoordinatePair MultipleGamesWithMaze::getOptimalNextGameAndCoordinate() {
    GameIndexAndCoordinatePair result{};
    UnsignedInteger overallGrundyNumber = getOverallGrundyNumber();
    GameState gameState = getGameStateFromGrundyNumber(overallGrundyNumber);
    if (GameState::Losing == gameState) {
        for (UnsignedInteger gameIndex = 0; gameIndex < m_games.size(); gameIndex++) {
            Game& game(m_games[gameIndex]);
            Coordinate const& coordinate(m_coordinateInGames[gameIndex]);
            if (!game.hasNoMoves(coordinate)) {
                result = {gameIndex, game.getOptimalNextCoordinateAt(coordinate)};
                break;            }
        }
    } else if (GameState::Winning == gameState) {
        for (UnsignedInteger gameIndex = 0; gameIndex < m_games.size(); gameIndex++) {
            Game& game(m_games[gameIndex]);
            Coordinate const& coordinate(m_coordinateInGames[gameIndex]);
            UnsignedInteger grundyNumberAtGame = game.getGrundyNumberAt(coordinate);
            UnsignedInteger hammingDistance = grundyNumberAtGame ^ overallGrundyNumber;
            if (hammingDistance < grundyNumberAtGame) {                result = {gameIndex, m_games[gameIndex].getNextCoordinateWithGrundyNumber(coordinate, hammingDistance)};
                break;
            }
        }    }
    return result;
}

string MultipleGamesWithMaze::getString() {
    stringstream result;
    for (UnsignedInteger gameIndex = 0; gameIndex < m_games.size(); gameIndex++) {
        result << "Game " << gameIndex << ":";
        result << m_games[gameIndex].getString();
    }
    return result.str();
}

void MultipleGamesWithMaze::setCoordinateAtGame(UnsignedInteger const gameIndex, Coordinate const& newCoordinate) {
    if (gameIndex < m_games.size()) {
        m_coordinateInGames[gameIndex] = newCoordinate;
    }
}

void MultipleGamesWithMaze::addGameWithMaze(
    BooleanMatrix const& isBlockedMatrix, Coordinate const& startingCoordinate) {
    m_games.emplace_back(isBlockedMatrix);
    m_coordinateInGames.emplace_back(startingCoordinate);
}

UnsignedInteger MultipleGamesWithMaze::getCombinedGrundyNumber() {
    UnsignedInteger result(0U);
    for (UnsignedInteger gameIndex = 0; gameIndex < m_games.size(); gameIndex++) {
        result = math::getCombinedGrundyNumber(
            result, m_games[gameIndex].getGrundyNumberAt(m_coordinateInGames[gameIndex]));
    }
    return result;
}
}  // namespace math

}  // namespace alba