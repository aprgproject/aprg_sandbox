#pragma once

namespace alba {

namespace chess {

namespace EngineConstants {

constexpr int NUMBER_OF_THREADS = 4;  // Desktop computer at home has four threads

constexpr int NUMBER_OF_VARIATIONS = 20;

}  // namespace EngineConstants
// Basis: https://github.com/official-stockfish/Stockfish
// In threads: For best performance, set this equal to the number of CPU cores available.
}  // namespace chess

}  // namespace alba
