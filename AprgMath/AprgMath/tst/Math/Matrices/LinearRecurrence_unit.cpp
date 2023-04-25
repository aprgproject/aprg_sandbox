#include <Math/Matrices/LinearRecurrence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace math {

TEST(LinearRecurrenceTest, GetNextFibonacciNumbersUsingLinearRecurrenceWorks) {
    EXPECT_EQ(UnsignedIntegerPair(1U, 1U), getNextFibonacciNumbersUsingLinearRecurrence({0U, 1U}));
    EXPECT_EQ(UnsignedIntegerPair(1U, 2U), getNextFibonacciNumbersUsingLinearRecurrence({1U, 1U}));
    EXPECT_EQ(UnsignedIntegerPair(2U, 3U), getNextFibonacciNumbersUsingLinearRecurrence({1U, 2U}));
    EXPECT_EQ(UnsignedIntegerPair(3U, 5U), getNextFibonacciNumbersUsingLinearRecurrence({2U, 3U}));
    EXPECT_EQ(UnsignedIntegerPair(5U, 8U), getNextFibonacciNumbersUsingLinearRecurrence({3U, 5U}));
    EXPECT_EQ(UnsignedIntegerPair(8U, 13U), getNextFibonacciNumbersUsingLinearRecurrence({5U, 8U}));
}

TEST(LinearRecurrenceTest, GetNextNumberOfDerangementsUsingLinearRecurrenceWorks) {
    EXPECT_EQ(UnsignedIntegerPair(0U, 0U), getNextNumberOfDerangementsUsingLinearRecurrence(0U, {0U, 0U}));
    EXPECT_EQ(UnsignedIntegerPair(0U, 0U), getNextNumberOfDerangementsUsingLinearRecurrence(1U, {0U, 0U}));
    EXPECT_EQ(UnsignedIntegerPair(0U, 0U), getNextNumberOfDerangementsUsingLinearRecurrence(2U, {0U, 0U}));
    EXPECT_EQ(UnsignedIntegerPair(1U, 2U), getNextNumberOfDerangementsUsingLinearRecurrence(3U, {0U, 1U}));
    EXPECT_EQ(UnsignedIntegerPair(2U, 9U), getNextNumberOfDerangementsUsingLinearRecurrence(4U, {1U, 2U}));
    EXPECT_EQ(UnsignedIntegerPair(9U, 44U), getNextNumberOfDerangementsUsingLinearRecurrence(5U, {2U, 9U}));
    EXPECT_EQ(UnsignedIntegerPair(44U, 265U), getNextNumberOfDerangementsUsingLinearRecurrence(6U, {9U, 44U}));
}

}  // namespace math

}  // namespace alba
