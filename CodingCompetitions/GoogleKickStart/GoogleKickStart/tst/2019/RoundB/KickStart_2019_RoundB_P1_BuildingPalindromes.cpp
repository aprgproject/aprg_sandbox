// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundB_P1_BuildingPalindromes.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundB_P1_BuildingPalindromes {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

using Question = pair<int, int>;
using Questions = vector<Question>;

int32_t getPalindromeValue(string const& blocksString, Question const& question) {
    // this can be faster using dynamic programming
    int32_t result = 0;
    for (int i = question.first; i <= question.second; i++) {
        result ^= 1 << (blocksString.at(i - 1) - 'A');
    }
    return result;
}

bool canPalindrome(string const& blocksString, Question const& question) {
    int length = question.second - question.first + 1;
    if (length % 2 == 0) {
        return __builtin_popcount(getPalindromeValue(blocksString, question)) == 0;
    } else {
        return __builtin_popcount(getPalindromeValue(blocksString, question)) == 1;
    }
}

void runTestCase(int const testCaseNumber) {
    int numberOfBlocks, numberOfQuestions;
    my_cin >> numberOfBlocks >> numberOfQuestions;
    string blocksString;    my_cin >> blocksString;

    Questions questions;
    for (int y = 0; y < numberOfQuestions; ++y) {        int leftIndex, rightIndex;
        my_cin >> leftIndex >> rightIndex;
        questions.emplace_back(leftIndex, rightIndex);
    }

    int numberOfPalindromes = 0;
    for (Question const& question : questions) {
        if (canPalindrome(blocksString, question)) {
            numberOfPalindromes++;
        }
    }

    my_cout << "Case #" << testCaseNumber << ": " << numberOfPalindromes << '\n';
}

void runAllTestCases() {
    int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
        runTestCase(testCaseNumber);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    my_cin.tie(nullptr);
    runAllTestCases();

    return 0;
}

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
}  // namespace KickStart_2019_RoundB_P1_BuildingPalindromes
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
