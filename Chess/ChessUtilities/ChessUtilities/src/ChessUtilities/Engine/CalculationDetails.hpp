#pragma once

#include <Common/String/AlbaStringHelper.hpp>

namespace alba {

namespace chess {

struct Variation {
    int mateValue;  // number of mate moves, can be negative if player is about to be mated
    int scoreInCentipawns;
    stringHelper::strings halfMoves;
};

using Variations = std::vector<Variation>;

struct CalculationDetails {
    int depthInPlies;           // search depth in plies
    int selectiveDepthInPlies;  // selective search depth in plies
    // Some programs also report a selective search depth beside the nominal search depth, most often much greater than
    // the nominal search depth. Some programs determine the highest distance to the root at any node, others only at
    // the horizon.
    Variations variations;
    std::string bestMove;              // best move in position as determined by engine
    std::string responseMoveToPonder;  // move that engine is pondering after best move
};

// Ply explanation:
// Source: https://en.wikipedia.org/wiki/Ply_(game_theory)
// For example, in standard chess terminology, one move consists of a turn by each player; therefore a ply in chess is a
// half-move. Thus, after 20 moves in a chess game, 40 plies have been completed—20 by white and 20 by black.

// PV means "Principal variation"
// Source: https://www.chessprogramming.org/Principal_Variation
// The Principal variation (PV) is a sequence of moves that programs consider best and therefore expect to be played.
// All the nodes included by the PV are PV-nodes.
// Inside an iterative deepening framework, it is the most important move ordering consideration to play the PV
// collected during the current iteration, as the very first left moves of the next iteration

}  // namespace chess

}  // namespace alba
