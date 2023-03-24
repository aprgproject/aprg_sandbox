#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba
{

class PrintMaximumNumberOfAs
{
public:
    using Index = unsigned int;
    using Count = unsigned int;
    using Counts = std::vector<Count>;
    enum class PressType
    {
        Unknown,
        TypeA,
        CtrlA,
        CtrlC,
        CtrlV
    };
    struct CountDetail
    {
        Count numberInScreen;
        Count numberInBuffer;
        Count numberInSelection;
    };
    using CountDetails = std::vector<CountDetail>;
    using CountDetailMatrix = matrix::AlbaMatrix<CountDetail>;
    static constexpr Count UNUSED_COUNT=std::numeric_limits<Count>::max();


    PrintMaximumNumberOfAs(Count const numberOfPresses);

    Count getMaxCountOfAOnScreenUsingNaiveRecursion() const;
    Count getMaxCountOfAOnScreenUsingMemoizationDP() const;
    Count getMaxCountOfAOnScreenUsingIterativeDP() const;
    Count getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient() const;

private:
    CountDetail getMaxCountOfAOnScreenUsingNaiveRecursion(Count const remainingNumberOfPresses, PressType const pressType) const;
    CountDetail getMaxCountOfAOnScreenUsingMemoizationDP(CountDetailMatrix & savedCounts, Count const remainingNumberOfPresses, PressType const pressType) const;
    CountDetail getBestDetailBasedOnPreviousDetails(CountDetails & previousDetails, Count const remainingNumberOfPresses, PressType const pressType) const;
    void updateDetailsBasedOnPressType(CountDetails & previousDetails, PressType const pressType) const;
    Count const m_numberOfPresses;
};

std::ostream & operator<<(std::ostream & out, PrintMaximumNumberOfAs::CountDetail const& countDetail);

}


// How to print maximum number of A’s using given four keys

// This is a famous interview question asked in Google, Paytm and many other company interviews.
// Below is the problem statement.

// Imagine you have a special keyboard with the following keys:
// Key 1:  Prints 'A' on screen
// Key 2: (Ctrl-A): Select screen
// Key 3: (Ctrl-C): Copy selection to buffer
// Key 4: (Ctrl-V): Print buffer on screen appending it
//                  after what has already been printed.

// If you can only press the keyboard for N times (with the above four
// keys), write a program to produce maximum numbers of A's. That is to
// say, the input parameter is N (No. of keys that you can press), the
// output is M (No. of As that you can produce).

// Examples:
// Input:  N = 3
// -> Output: 3
// -> We can at most get 3 A's on screen by pressing
// -> following key sequence.
// -> A, A, A
// Input:  N = 7
// -> Output: 9
// -> We can at most get 9 A's on screen by pressing
// -> following key sequence.
// -> A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
// Input:  N = 11
// -> Output: 27
// -> We can at most get 27 A's on screen by pressing
// -> following key sequence.
// -> A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V, Ctrl A,
// -> Ctrl C, Ctrl V, Ctrl V



