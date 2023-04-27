#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba {

TEST(IncrementDecrementExamplesTest, PostIncrementIsAppliedOneAfterAnother) {
    int a = 1;
    cout << (a++) * (++a) << endl;  // 1*3 = 3
    int b = 1;
    cout << (b++) * (b++) << endl;  // 1*2 = 2
    int c = 1;
    cout << c++ * c++ << endl;  // 1*2 = 2

    // int x=(a++)++; // Error: lvalue required as increment operand
}

}  // namespace alba
