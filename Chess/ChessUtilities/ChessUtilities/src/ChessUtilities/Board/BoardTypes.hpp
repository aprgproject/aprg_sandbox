#pragma once

#include <ChessUtilities/Board/PieceType.hpp>
#include <Common/Container/AlbaXY.hpp>

#include <cstdint>#include <vector>

namespace alba
{
namespace chess
{

using PieceTypes = std::vector<PieceType>;
using CoordinateDataType = int8_t;
using Coordinate = AlbaXY<int8_t>;
using Coordinates = std::vector<Coordinate>;using Move = std::pair<Coordinate, Coordinate>;
using Moves = std::vector<Move>;

}
}
