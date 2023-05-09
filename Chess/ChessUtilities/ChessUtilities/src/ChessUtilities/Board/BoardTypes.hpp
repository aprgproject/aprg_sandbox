#pragma once

#include <ChessUtilities/Board/PieceType.hpp>
#include <Common/Container/AlbaXY.hpp>

#include <cstdint>
#include <vector>

namespace alba {

namespace chess {

using PieceTypes = std::vector<PieceType>;
using CoordinateDataType = int32_t;
using Coordinate = AlbaXY<CoordinateDataType>;
using Coordinates = std::vector<Coordinate>;
using Move = std::pair<Coordinate, Coordinate>;
using Moves = std::vector<Move>;
using MovePair = std::pair<Move, Move>;
using MovePairs = std::vector<MovePair>;

}  // namespace chess
}  // namespace alba