#include "AlbaFileGTestHelper.hpp"

#include <algorithm>

void AlbaFileGTestHelper::SetUp()
{}

void AlbaFileGTestHelper::TearDown()
{
    closeAllFileHandlers();
}

ifstream& AlbaFileGTestHelper::openFileToRead(string const& fileName)
{
    listOfFileReaders.resize(listOfFileReaders.size()+1);
    ifstream fileReader;
    //ifstream& fileReader = listOfFileReaders.back();
    return fileReader;
}
ofstream& AlbaFileGTestHelper::openFileToWrite(string const& fileName)
{
    //listOfFileWriters.push_back(ofstream(fileName));
    ofstream fileWriter;
    //ofstream& fileWriter = listOfFileWriters.back();
    return fileWriter;
}
void AlbaFileGTestHelper::closeAllFileHandlers()
{
    listOfFileReaders.clear();
    listOfFileWriters.clear();
}
void AlbaFileGTestHelper::writeLineToFile(string const& string1)
{
    ofstream& fileWriter = listOfFileWriters.front();
    fileWriter<<string1<<"\n";
}
void AlbaFileGTestHelper::writeLineToFile(string const& string1, ofstream& fileWriter)
{
    fileWriter<<string1<<"\n";
}


