#include "AddTwoNumbersWithoutUsingArithmeticOperators.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>

using namespace std;

namespace alba {

AddTwoNumbersWithoutUsingArithmeticOperators::AddTwoNumbersWithoutUsingArithmeticOperators() {}

AddTwoNumbersWithoutUsingArithmeticOperators::Value AddTwoNumbersWithoutUsingArithmeticOperators::getSum(
    Value const value1, Value const value2) const {
    Value carry = value1 & value2;
    Value sum = value1 ^ value2;
    while (carry > 0) {
        carry <<= 1;
        int newCarry = sum & carry;
        sum = sum ^ carry;
        carry = newCarry;
    }
    return sum;
}

}  // namespace alba
