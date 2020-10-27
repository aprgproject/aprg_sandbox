#include <AprgFileExtractor.hpp>

#include <iostream>
#include <string>

using namespace alba;
using namespace std;

namespace alba
{

namespace ProgressCounters
{
int numberOfFilesToBeAnalyzedForExtraction;
int numberOfFilesAnalyzedForExtraction;
}

}

int main(int argc, char *argv[])
{
    if(argc!=3)
    {
        cout<<"There are must be only 2 arguments."<<endl;
        return 1;
    }
    string condition(argv[1]);
    string inputPath(argv[2]);
    AprgFileExtractor fileExtractor(condition);
    fileExtractor.extractAllRelevantFiles(inputPath);
}
