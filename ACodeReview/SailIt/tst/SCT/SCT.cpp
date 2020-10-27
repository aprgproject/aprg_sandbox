#include "../../src/SailIt.hpp"
#include "gtest/gtest.h"

#include <fstream>

using namespace codeReview;
using namespace std;

//TEST(Sct, DISABLED_ActualTest)
TEST(Sct, ActualTest)
{
    SailIt sailIt;
    sailIt.getFileDirectoryDatabaseReference().addFileOrDirectory("C:\\APRG\\ACodeReview\\include");
    //sailIt.addAndAnalyzeThisFileToCPlusPlusDatabase ("C:\\APRG\\ACodeReview\\include\\c++\\iostream");
    sailIt.addAndAnalyzeThisFileToCPlusPlusDatabase("C:\\APRG\\ACodeReview\\include\\stdio.h");
    //sailIt.addAndAnalyzeThisFileToCPlusPlusDatabase("C:\\APRG\\ACodeReview\\include\\_mingw.h");
    //sailIt.addAndAnalyzeThisFileToCPlusPlusDatabase("C:\\APRG\\ACodeReview\\include\\_mingw_off_t.h");
    ofstream outputFile("C:\\APRG\\ACodeReview\\outputFile.txt");
    sailIt.printAll(outputFile);
    ofstream unprocessedTermFile("C:\\APRG\\ACodeReview\\unprocessedTerm.txt");
    sailIt.printFindings(unprocessedTermFile, "Unprocessed term");
}
