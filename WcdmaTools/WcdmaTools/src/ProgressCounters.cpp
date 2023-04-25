#include "ProgressCounters.hpp"

namespace alba {

namespace ProgressCounters {

int getOverAllProgress() {
    if (0 == numberOfStepsEnabled) {
        return 0;
    }
    return (getExtractProgress() + getCombineAndSortProgress() + grepProcessProgress + cropProcessProgress) /
           numberOfStepsEnabled;
}

void resetProgressCounters() {
    numberOfFilesToBeAnalyzedForExtraction = 0;
    numberOfFilesAnalyzedForExtraction = 0;
    totalSizeToBeReadForCombine = 0;
    totalSizeReadForCombine = 0;
    writeProgressForCombine = 0;
    grepProcessProgress = 0;
    cropProcessProgress = 0;
    numberOfStepsEnabled = 0;
}

int getExtractProgress() {
    return getCorrectProgressValue(numberOfFilesAnalyzedForExtraction, numberOfFilesToBeAnalyzedForExtraction);
}

int getCombineAndSortProgress() {
    return (getCorrectProgressValue(totalSizeReadForCombine, totalSizeToBeReadForCombine) + writeProgressForCombine) /
           2;
}

template <typename NumberType>
int getCorrectProgressValue(NumberType const numerator, NumberType const denominator) {
    if (denominator == 0) {
        return 0;
    }
    if (numerator > denominator) {
        return 100;
    }
    return 100 * numerator / denominator;
}

int numberOfFilesToBeAnalyzedForExtraction;
int numberOfFilesAnalyzedForExtraction;
double totalSizeToBeReadForCombine;
double totalSizeReadForCombine;
int writeProgressForCombine;
int grepProcessProgress;
int cropProcessProgress;
int numberOfStepsEnabled;

}  // namespace ProgressCounters

}  // namespace alba
