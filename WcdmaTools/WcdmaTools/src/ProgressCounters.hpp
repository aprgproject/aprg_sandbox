#pragma once

namespace alba {

namespace ProgressCounters {

int getOverAllProgress();
void resetProgressCounters();
int getExtractProgress();
int getCombineAndSortProgress();
template <typename NumberType>
int getCorrectProgressValue(NumberType const numerator, NumberType const denominator);

extern int numberOfFilesToBeAnalyzedForExtraction;
extern int numberOfFilesAnalyzedForExtraction;
extern double totalSizeToBeReadForCombine;
extern double totalSizeReadForCombine;
extern int writeProgressForCombine;
extern int grepProcessProgress;
extern int cropProcessProgress;
extern int numberOfStepsEnabled;

}  // namespace ProgressCounters

}  // namespace alba
