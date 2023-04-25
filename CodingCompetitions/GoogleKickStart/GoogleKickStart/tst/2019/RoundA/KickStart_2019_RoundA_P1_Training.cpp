// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
//#define FOR_SUBMISSION
#ifndef FOR_SUBMISSION
#include "KickStart_2019_RoundA_P1_Training.hpp"

#include <Fake/FakeNames.hpp>
//#include <Common/Debug/AlbaDebug.hpp>
#endif
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING START ~~~~~~~~~
#ifndef FOR_SUBMISSION
using namespace alba;
#endif
namespace KickStart_2019_RoundA_P1_Training {
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~

#ifndef my_cout
#define my_cout cout
#define my_cin cin
#endif

void runTestCase(unsigned int const testCaseNumber) {
    int numberOfStudents, numberOfStudentsPerTeam;
    my_cin >> numberOfStudents >> numberOfStudentsPerTeam;
    vector<int> skillsOfStudents(numberOfStudents);
    for (int i = 0; i < numberOfStudents; ++i) {
        my_cin >> skillsOfStudents[i];
    }

    sort(skillsOfStudents.begin(), skillsOfStudents.end());

    int hoursOfCoaching = 0;
    if (numberOfStudentsPerTeam <= numberOfStudents && numberOfStudents > 0 && numberOfStudentsPerTeam > 0) {
        int maxSkillOfTeam =
            *max_element(skillsOfStudents.cbegin(), skillsOfStudents.cbegin() + numberOfStudentsPerTeam);
        int i = 0;
        for (; i < numberOfStudentsPerTeam; ++i) {
            hoursOfCoaching += maxSkillOfTeam - skillsOfStudents[i];
        }

        int currentHoursOfCoaching = hoursOfCoaching;
        for (; i < numberOfStudents; ++i) {
            int maxDifference = skillsOfStudents[i] - skillsOfStudents[i - 1];
            int lastDifference = skillsOfStudents[i] - skillsOfStudents[i - numberOfStudentsPerTeam];
            currentHoursOfCoaching = currentHoursOfCoaching + maxDifference * (numberOfStudentsPerTeam)-lastDifference;
            hoursOfCoaching = min(hoursOfCoaching, currentHoursOfCoaching);
        }
    }

    my_cout << "Case #" << testCaseNumber << ": " << hoursOfCoaching << '\n';
}

void runAllTestCases() {
    unsigned int numberOfTestCases;
    my_cin >> numberOfTestCases;
    for (unsigned int testCaseNumber = 1; testCaseNumber <= numberOfTestCases; testCaseNumber++) {
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
}  // namespace KickStart_2019_RoundA_P1_Training
#undef FOR_SUBMISSION
// ~~~~~~~~~ DELETE THIS WHEN SUBMITTING END   ~~~~~~~~~
