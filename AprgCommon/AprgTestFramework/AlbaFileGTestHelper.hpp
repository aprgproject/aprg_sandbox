#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

// To use a test fixture, derive a class from testing::Test.
class AlbaFileGTestHelper : public testing::Test {
public:
protected:  // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp();

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    virtual void TearDown();

    ifstream& openFileToRead(string const& fileName);
    ofstream& openFileToWrite(string const& fileName);
    void closeAllFileHandlers();
    void writeLineToFile(string const& string1);
    void writeLineToFile(string const& string1, ofstream& fileWriter);
private:
    vector<ifstream> listOfFileReaders;
    vector<ofstream> listOfFileWriters;
};
