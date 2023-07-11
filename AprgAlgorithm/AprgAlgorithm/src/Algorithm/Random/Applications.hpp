#pragma once

namespace alba {

namespace algorithm {}  // namespace algorithm

}  // namespace alba

// Applications and Scope:
// -> Consider a tool that basically does sorting.
// ---> Let the tool be used by many users and there are few users who always use tool for already sorted array.
// ---> If the tool uses a Non-Randomized QuickSort,
// then those few users are always going to face worst case situation.
// ---> On the other hand if the tool uses Randomized QuickSort, then there is no user that always gets worst case.
// ---> Everybody gets expected O(n Log n) time.
// -> Randomized algorithms have huge applications in Cryptography.
// -> Load Balancing.
// -> Number-Theoretic Applications:
// ---> Primality Testing
// -> Data Structures:
// ---> Hashing, Sorting, Searching, Order Statistics and Computational Geometry.
// -> Algebraic identities:
// ---> Polynomial and matrix identity verification. Interactive proof systems.
// -> Mathematical programming:
// ---> Faster algorithms for linear programming, Rounding linear program solutions to integer program solutions
// -> Graph algorithms:
// ---> Minimum spanning trees, shortest paths, minimum cuts.
// -> Counting and enumeration:
// ---> Matrix permanent Counting combinatorial structures.
// -> Parallel and distributed computing:
// ---> Deadlock avoidance distributed consensus.
// -> Probabilistic existence proofs:
// ---> Show that a combinatorial object arises with non-zero probability
// among objects drawn from a suitable probability space.
// -> Derandomization:
// ---> First devise a randomized algorithm then argue that it can be derandomized to yield a deterministic algorithm.
