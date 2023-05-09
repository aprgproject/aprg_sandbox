#pragma once

#include <Common/String/AlbaStringHelper.hpp>

namespace alba {

namespace chess {

using StringAndUnsignedIntPair = std::pair<std::string, unsigned int>;
using StringAndUnsignedIntPairs = std::vector<StringAndUnsignedIntPair>;
using StringAndIntPair = std::pair<std::string, int>;
using StringAndIntPairs = std::vector<StringAndIntPair>;

struct CalculationDetails {
    unsigned int depthInPlies;           // search depth in plies
    unsigned int selectiveDepthInPlies;  // selective search depth in plies
    // Some programs also report a selective search depth beside the nominal search depth, most often much greater than
    // the nominal search depth. Some programs determine the highest distance to the root at any node, others only at
    // the horizon.
    int mateScore;  // mate in y moves, not plies.
    StringAndIntPairs currentMovesAndScores;
    int scoreInMonitoredVariation;
    stringHelper::strings monitoredVariation;  // monitored variation is set as the best line
    StringAndIntPairs commonMovesAndCountsOfEachStep;
    std::string bestMove;              // best move in position as determined by engine
    std::string responseMoveToPonder;  // move that engine is pondering after best move
};

// Ply explanation:// Source: https://en.wikipedia.org/wiki/Ply_(game_theory)
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