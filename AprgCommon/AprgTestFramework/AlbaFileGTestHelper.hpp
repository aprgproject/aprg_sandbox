#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <vector>

// To use a test fixture, derive a class from testing::Test.
class AlbaFileGTestHelper : public testing::Test {
public:protected:  // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp();

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    virtual void TearDown();

    std::ifstream& openFileToRead(std::string const& fileName);
    std::ofstream& openFileToWrite(std::string const& fileName);
    void closeAllFileHandlers();
    void writeLineToFile(std::string const& string1);
    void writeLineToFile(std::string const& string1, std::ofstream& fileWriter);
private:
    std::vector<std::ifstream> listOfFileReaders;
    std::vector<std::ofstream> listOfFileWriters;
};