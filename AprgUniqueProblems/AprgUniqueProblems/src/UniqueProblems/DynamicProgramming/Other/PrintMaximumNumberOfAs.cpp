#include "PrintMaximumNumberOfAs.hpp"

#include <algorithm>

using namespace std;

namespace alba {

PrintMaximumNumberOfAs::PrintMaximumNumberOfAs(Count const numberOfPresses) : m_numberOfPresses(numberOfPresses) {}

PrintMaximumNumberOfAs::Count PrintMaximumNumberOfAs::getMaxCountOfAOnScreenUsingNaiveRecursion() const {
    // Time Complexity: O(4^n)
    // Auxiliary Space: O(1)

    CountDetails countDetails{
        getMaxCountOfAOnScreenUsingNaiveRecursion(m_numberOfPresses, PressType::TypeA),
        getMaxCountOfAOnScreenUsingNaiveRecursion(m_numberOfPresses, PressType::CtrlA),
        getMaxCountOfAOnScreenUsingNaiveRecursion(m_numberOfPresses, PressType::CtrlC),
        getMaxCountOfAOnScreenUsingNaiveRecursion(m_numberOfPresses, PressType::CtrlV)};

    auto it = max_element(
        countDetails.cbegin(), countDetails.cend(), [](CountDetail const& first, CountDetail const& second) {
            return first.numberInScreen < second.numberInScreen;
        });
    return it->numberInScreen;
}

PrintMaximumNumberOfAs::Count PrintMaximumNumberOfAs::getMaxCountOfAOnScreenUsingMemoizationDP() const {
    // Time Complexity: O(n^2) same as iterative DP.
    // Auxiliary Space: O(n^2).

    CountDetailMatrix savedCounts(
        m_numberOfPresses + 1, static_cast<Count>(PressType::CtrlV) + 1,
        CountDetail{UNUSED_COUNT, UNUSED_COUNT, UNUSED_COUNT});
    CountDetails countDetails{
        getMaxCountOfAOnScreenUsingMemoizationDP(savedCounts, m_numberOfPresses, PressType::TypeA),
        getMaxCountOfAOnScreenUsingMemoizationDP(savedCounts, m_numberOfPresses, PressType::CtrlA),
        getMaxCountOfAOnScreenUsingMemoizationDP(savedCounts, m_numberOfPresses, PressType::CtrlC),
        getMaxCountOfAOnScreenUsingMemoizationDP(savedCounts, m_numberOfPresses, PressType::CtrlV)};

    auto it = max_element(
        countDetails.cbegin(), countDetails.cend(), [](CountDetail const& first, CountDetail const& second) {
            return first.numberInScreen < second.numberInScreen;
        });
    return it->numberInScreen;
}

PrintMaximumNumberOfAs::Count PrintMaximumNumberOfAs::getMaxCountOfAOnScreenUsingIterativeDP() const {
    // Time Complexity: O(n^2).
    // Auxiliary Space: O(n^2).

    CountDetailMatrix savedCounts(m_numberOfPresses + 1, static_cast<Count>(PressType::CtrlV) + 1, CountDetail{});
    for (Count remainingNumberOfPresses = 1; remainingNumberOfPresses <= m_numberOfPresses;
         remainingNumberOfPresses++) {
        for (Count pressTypeValue = static_cast<Count>(PressType::TypeA);
             pressTypeValue <= static_cast<Count>(PressType::CtrlV); pressTypeValue++) {
            CountDetails previousDetails{
                savedCounts.getEntryConstReference(remainingNumberOfPresses - 1, static_cast<Count>(PressType::TypeA)),
                savedCounts.getEntryConstReference(remainingNumberOfPresses - 1, static_cast<Count>(PressType::CtrlA)),
                savedCounts.getEntryConstReference(remainingNumberOfPresses - 1, static_cast<Count>(PressType::CtrlC)),
                savedCounts.getEntryConstReference(remainingNumberOfPresses - 1, static_cast<Count>(PressType::CtrlV))};
            savedCounts.setEntry(
                remainingNumberOfPresses, pressTypeValue,
                getBestDetailBasedOnPreviousDetails(
                    previousDetails, remainingNumberOfPresses, static_cast<PressType>(pressTypeValue)));
        }
    }

    Count result(0);
    for (Count pressTypeValue = static_cast<Count>(PressType::TypeA);
         pressTypeValue <= static_cast<Count>(PressType::CtrlV); pressTypeValue++) {
        result = max(result, savedCounts.getEntryConstReference(m_numberOfPresses, pressTypeValue).numberInScreen);
    }
    return result;
}

PrintMaximumNumberOfAs::Count PrintMaximumNumberOfAs::getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient() const {
    // Time Complexity: O(n^2).
    // Auxiliary Space: O(n).

    if (m_numberOfPresses <= 6) {
        return m_numberOfPresses;
    } else {
        Counts countsOnScreen(m_numberOfPresses, 0);
        for (Count remainingNumberOfPresses = 1; remainingNumberOfPresses <= 6; remainingNumberOfPresses++) {
            countsOnScreen[remainingNumberOfPresses - 1] = remainingNumberOfPresses;
        }
        for (Count remainingNumberOfPresses = 7; remainingNumberOfPresses <= m_numberOfPresses;
             remainingNumberOfPresses++) {
            // break point will start ctrl-a, ctrl-c and then only ctrl-v all the way.
            for (Count breakPoint = remainingNumberOfPresses - 3; breakPoint >= 1; breakPoint--) {
                Count countIfBreakPoint = (remainingNumberOfPresses - breakPoint - 1) * countsOnScreen[breakPoint - 1];
                if (countIfBreakPoint > countsOnScreen[remainingNumberOfPresses - 1]) {
                    countsOnScreen[remainingNumberOfPresses - 1] = countIfBreakPoint;
                }
            }
        }
        return countsOnScreen.back();
    }
}

PrintMaximumNumberOfAs::CountDetail PrintMaximumNumberOfAs::getMaxCountOfAOnScreenUsingNaiveRecursion(
    Count const remainingNumberOfPresses, PressType const pressType) const {
    CountDetail result{0, 0, 0};
    if (remainingNumberOfPresses > 0) {
        CountDetails previousDetails{
            getMaxCountOfAOnScreenUsingNaiveRecursion(remainingNumberOfPresses - 1, PressType::TypeA),
            getMaxCountOfAOnScreenUsingNaiveRecursion(remainingNumberOfPresses - 1, PressType::CtrlA),
            getMaxCountOfAOnScreenUsingNaiveRecursion(remainingNumberOfPresses - 1, PressType::CtrlC),
            getMaxCountOfAOnScreenUsingNaiveRecursion(remainingNumberOfPresses - 1, PressType::CtrlV)};
        result = getBestDetailBasedOnPreviousDetails(previousDetails, remainingNumberOfPresses, pressType);
    }
    return result;
}

PrintMaximumNumberOfAs::CountDetail PrintMaximumNumberOfAs::getMaxCountOfAOnScreenUsingMemoizationDP(
    CountDetailMatrix& savedCounts, Count const remainingNumberOfPresses, PressType const pressType) const {
    CountDetail result = savedCounts.getEntryConstReference(remainingNumberOfPresses, static_cast<Count>(pressType));
    if (UNUSED_COUNT == result.numberInScreen) {
        result = {0, 0, 0};
        if (remainingNumberOfPresses > 0) {
            CountDetails previousDetails{
                getMaxCountOfAOnScreenUsingMemoizationDP(savedCounts, remainingNumberOfPresses - 1, PressType::TypeA),
                getMaxCountOfAOnScreenUsingMemoizationDP(savedCounts, remainingNumberOfPresses - 1, PressType::CtrlA),
                getMaxCountOfAOnScreenUsingMemoizationDP(savedCounts, remainingNumberOfPresses - 1, PressType::CtrlC),
                getMaxCountOfAOnScreenUsingMemoizationDP(savedCounts, remainingNumberOfPresses - 1, PressType::CtrlV)};
            result = getBestDetailBasedOnPreviousDetails(previousDetails, remainingNumberOfPresses, pressType);
        }
        savedCounts.setEntry(remainingNumberOfPresses, static_cast<Count>(pressType), result);
    }
    return result;
}

PrintMaximumNumberOfAs::CountDetail PrintMaximumNumberOfAs::getBestDetailBasedOnPreviousDetails(
    CountDetails& previousDetails, Count const remainingNumberOfPresses, PressType const pressType) const {
    updateDetailsBasedOnPressType(previousDetails, pressType);

    if (remainingNumberOfPresses == m_numberOfPresses) {
        auto it = max_element(
            previousDetails.cbegin(), previousDetails.cend(), [](CountDetail const& first, CountDetail const& second) {
                return first.numberInScreen < second.numberInScreen;
            });
        return *it;
    } else if (remainingNumberOfPresses + 1 == m_numberOfPresses) {
        auto it = max_element(
            previousDetails.cbegin(), previousDetails.cend(), [](CountDetail const& first, CountDetail const& second) {
                return first.numberInScreen + first.numberInBuffer < second.numberInScreen + second.numberInBuffer;
            });
        return *it;
    } else {
        auto it = max_element(
            previousDetails.cbegin(), previousDetails.cend(), [](CountDetail const& first, CountDetail const& second) {
                return first.numberInScreen + max(first.numberInBuffer, first.numberInSelection) <
                       second.numberInScreen + max(second.numberInBuffer, second.numberInSelection);
            });
        return *it;
    }
}

void PrintMaximumNumberOfAs::updateDetailsBasedOnPressType(
    CountDetails& previousDetails, PressType const pressType) const {
    switch (pressType) {
        case PressType::TypeA: {
            for (auto& previousDetail : previousDetails) {
                previousDetail.numberInScreen++;
            }
            break;
        }
        case PressType::CtrlA: {
            for (auto& previousDetail : previousDetails) {
                previousDetail.numberInSelection = previousDetail.numberInScreen;
            }
            break;
        }
        case PressType::CtrlC: {
            for (auto& previousDetail : previousDetails) {
                previousDetail.numberInBuffer = previousDetail.numberInSelection;
            }
            break;
        }
        case PressType::CtrlV: {
            for (auto& previousDetail : previousDetails) {
                previousDetail.numberInScreen += previousDetail.numberInBuffer;
            }
            break;
        }
        case PressType::Unknown: {
            break;
        }
    }
}

ostream& operator<<(ostream& out, PrintMaximumNumberOfAs::CountDetail const& countDetail) {
    out << (int)countDetail.numberInScreen << ":" << (int)countDetail.numberInBuffer << ":"
        << (int)countDetail.numberInSelection;
    return out;
}

}  // namespace alba
