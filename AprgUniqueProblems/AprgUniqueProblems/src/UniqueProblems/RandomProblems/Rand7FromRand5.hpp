#pragma once

#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

namespace alba {

class Rand7FromRand5 {
public:
    using Value = int;
    Rand7FromRand5();

    Value getRandomFrom0To6();
    Value getRandomFrom0To4();

private:
    AlbaUniformNonDeterministicRandomizer<Value> m_randomizerFrom0To4;
};

}  // namespace alba

// Rand7 from Rand5 Problem:
// ---> Implement a method rand7() given rand5().
// ---> That is, given a method that generates a random number between O and 4 (inclusive),
// ---> write a method that generates a random number between O and 6 (inclusive).

// rand5() possibilities (uniform probability):
// 0,1,2,3,4
// rand5()*5 possibilities (uniform probability):
// 0,5,10,15,20
// rand5()*5 + rand5() possibilities(uniform probability):
// 0,5,10,15,20
// 1,6,11,16,21
// 2,7,12,17,22
// 3,8,13,18,23
// 4,9,14,19,24
