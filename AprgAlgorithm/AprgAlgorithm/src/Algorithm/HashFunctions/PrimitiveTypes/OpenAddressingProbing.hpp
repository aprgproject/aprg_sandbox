#pragma once

#include <Common/Memory/AlbaCast.hpp>

#include <functional>

namespace alba {

namespace algorithm {

template <typename HashValue>
using HashingFunction = std::function<HashValue(HashValue)>;

template <typename HashValue>
HashValue getHashForLinearProbing(
    HashValue const key, HashValue const numberOfSlots, HashingFunction<HashValue> const& originalHashFunction,
    HashValue const offset) {
    return (originalHashFunction(key) + offset) % numberOfSlots;

    // Linear probing is easy to implement, but it suffers from a problem known as primary clustering.
    // Long runs of occupied slots build up, increasing the average search time.
    // Clusters arise because an empty slot preced by i full slots gets filled next with probability i+1/m.
    // Long runs of occupied slots tend to get longer, and the average search time increases.
}

template <typename HashValue>
HashValue getHashForQuadraticProbing(
    HashValue const key, HashValue const numberOfSlots, HashingFunction<HashValue> const& originalHashFunction,
    HashValue const offset, HashValue const coefficient1, HashValue const coefficient2) {
    return (originalHashFunction(key) + coefficient1 * offset + coefficient2 * offset * offset) % numberOfSlots;

    // Quadratic probing causes a milder form of clustering, called secondary clustering.
    // As in linear probing, the initial probe determines the entire sequence,
    // and so only m distinct probe sequence are used.
}

template <typename HashValue>
HashValue getHashForDoubleHash(
    HashValue const key, HashValue const numberOfSlots, HashingFunction<HashValue> const& originalHashFunction,
    HashingFunction<HashValue> const& offsetHashFunction, HashValue const offset) {
    return (originalHashFunction(key) + offsetHashFunction(key) * offset) % numberOfSlots;

    // Double hashing offers one of the best methods available for open addressing
    // because the permutations produced have many of characteristics of randomly chosen permutations.
    // Unlike the case  of linear or quadratic probing, the probe sequence here depends in two ways upon the k,
    // since the initial probe position, the offset or both may vary.
}

}  // namespace algorithm

}  // namespace alba

// Check other discussion in other files as well, they are understandable insights (BaseLinearProbingHash).

// We will examine three commonly used techniques to compute the probe sequences required to open addressing:
// -> Linear probing, quadratic probing and double hashing.
// These techniques all guarantee that the hashes geenerated fits the number of slots for each key.
// None of There techniques fulfills the assumption of uniform hashing,
// -> however, since none of them is capable of generating more than m^2 different probe sequences* (instead of the m!
// that uniform hashing requires). Double hashing has the greatest number of probe sequences and as one might expect,
// seems to give the best results.
