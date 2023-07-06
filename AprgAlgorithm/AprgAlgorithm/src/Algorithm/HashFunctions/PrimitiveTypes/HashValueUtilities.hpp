#pragma once

#include <Common/Math/Helpers/PrecisionHelpers.hpp>

namespace alba {

namespace algorithm {

template <typename HashValue>
HashValue getHashUsingDivisionMethod(HashValue const hashKey, HashValue const numberOfSlots) {
    return hashKey % numberOfSlots;

    // -> In the division method, for creating hash functions,
    // ---> we map a key k into one of m numberOfSlots by taking the remainder of k divide by m.
    // ---> That is, the hashfunction is h(k) = k mod m.
    // -> When using the division method, we usually avoid certain values of divisor(m).
    // ---> For example, m should not be a power of 2, since that means that its just gonna be a the lowest-order bits
    // of a number.
    // ---> A prime, not too close to an exact power of 2 is often a good choice for m.
    // ---> This method frequently gives good results, assuming that we choose a prime number that is unrelated to
    // anypattern in the distribution of keys.
    // -> For example, we wish to allocate a hash table, with collisions resolved by chaining,
    // ---> to hold roughly n=2000 character strings, where a character has 8 bits.
    // ---> We dont mind dexamining an average of 3 elements in an unsuccessful search and so we allocate a hash table
    // of size m=701.
    // ---> We could choose m-=701 because it is a prime near 2000/3 but not near any power of 2.
    // ---> treating each key as integer, our hash function would be:
    // ---> h(k) = k mod 701.
}

template <typename HashValue>
HashValue getHashUsingMultiplicationMethod(
    HashValue const hashKey, HashValue const numberOfSlots, double const zeroToOneMutiplier) {
    return mathHelper::getFractionalPartInDouble(hashKey * zeroToOneMutiplier) * numberOfSlots;

    // -> The multiplication method for creating hash functions operates in two steps.
    // ---> First, we multiply the k by a constant A in the range of 0<A<1 and extract the fractional part of K*A.
    // ---> The we multiply this value by m and take the floor of the result.
    // ---> In short, the function is:
    // ---> h(k) = floor(m * (K * A mod 1))
    // ---> where  (K * A mod 1) means the fractional part of K * A that is, K*A = floor(K*A).
    // -> An advantage of the multiplcation method is that the value of m is not critical.
    // ---> We typlically choose it to be a power of 2(m=2^p for some integer p),
    // ---> since we can then easily implement the function on most computers.
    // -> Although this method works with any value of the constant A, it works better with some value that with others.
    // ---> The optimal choice depends on the characteristics of the data being hashed.
    // ---> Knuth[211] suggests that A ~ (sqrt(5)-1)/2 is likely to work reasonably well.
    // ---> As an example, suppose we have k=12345, p=14, m=2^14=16384 and w=32.
    // ---> Adapting Knuth;s suggestion, we choose A to be the fraction of the form x/2^32 that is closest to
    // (sqrt(5)-1)/2.
    // ---> So A = 2654435769/2^32, then 14 most significant bits for h(k) = 67.
}

template <typename HashValue>
HashValue getHashUsingMultiplicationMethod(
    HashValue const hashKey, HashValue const numberOfSlots, HashValue const numerator, HashValue const denominator) {
    // same as above but no double parameter
    return ((hashKey * numerator) % denominator) * numberOfSlots / denominator;
}

}  // namespace algorithm

}  // namespace alba

// -> What makes a good hash function
// ---> A good hash function satisfies (approximately) the assumption of simple uniform hashing:
// -----> each key is equally likely to hash to any of the m numberOfSlots, independently where any other key has hashed to
// ---> Unfortunately, we typically have no way to check this condition,
// -----> since we rarely know how the probability distribution from which the keys are drawn.
// ---> Moreover, the keys might not be drawn independently.
