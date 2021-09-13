#include <DirectoryConstants.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <SackReader/AlbaSackReader.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST(AlbaSackReaderTest, SackTest)
{
    AlbaSackReader sackReader(R"(D:\W\trunk\I_Interface)", "[.cpp] || [.hpp] || [.c] || [.h]");
    sackReader.process();
    sackReader.printAll();
}

TEST(AlbaSackReaderTest, ClassesAreRecognized)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "class myClass" << endl;
    testFile << "{" << endl;
    testFile << "unsigned long int integerParameter;" << endl;
    testFile << "double doubleParameter;" << endl;
    testFile << "};" << endl;
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType myClass = sackReader.getType("myClass");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    ASSERT_EQ(2U, myClassParameters.size());
    EXPECT_EQ("unsigned long int", myClassParameters[0].getTypeName());
    EXPECT_EQ("integerParameter", myClassParameters[0].getParameterName());
    EXPECT_EQ("double", myClassParameters[1].getTypeName());
    EXPECT_EQ("doubleParameter", myClassParameters[1].getParameterName());
}

TEST(AlbaSackReaderTest, ClassesAreRecognizedInForwardDeclaration)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "class myClass;" << endl;
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType myClass = sackReader.getType("myClass");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    ASSERT_EQ(0U, myClassParameters.size());
}

TEST(AlbaSackReaderTest, TypedefAreRecognized)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef type1 type2;" << endl;
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType type1 = sackReader.getType("type1");
    AlbaSackReaderType::Parameters type1Parameters = type1.getParameters();
    AlbaSackReaderType::TypeNames type1OtherTypes = type1.getOtherTypes();
    AlbaSackReaderType type2 = sackReader.getType("type2");
    AlbaSackReaderType::Parameters type2Parameters = type2.getParameters();
    AlbaSackReaderType::TypeNames type2OtherTypes = type2.getOtherTypes();
    ASSERT_EQ(0U, type1Parameters.size());
    ASSERT_EQ(1U, type1OtherTypes.size());
    EXPECT_EQ("type2", *(type1OtherTypes.begin()));
    ASSERT_EQ(0U, type2Parameters.size());
    ASSERT_EQ(1U, type2OtherTypes.size());
    EXPECT_EQ("type1", *(type2OtherTypes.begin()));
}

TEST(AlbaSackReaderTest, TypedefArrayAreRecognized)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef type1 type2 [ 5 ] ;" << endl;
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType type1 = sackReader.getType("type1");
    AlbaSackReaderType::Parameters type1Parameters = type1.getParameters();
    AlbaSackReaderType::TypeNames type1OtherTypes = type1.getOtherTypes();
    AlbaSackReaderType type2 = sackReader.getType("type2[5]");
    AlbaSackReaderType::Parameters type2Parameters = type2.getParameters();
    AlbaSackReaderType::TypeNames type2OtherTypes = type2.getOtherTypes();
    ASSERT_EQ(0U, type1Parameters.size());
    ASSERT_EQ(1U, type1OtherTypes.size());
    EXPECT_EQ("type2[5]", *(type1OtherTypes.begin()));
    ASSERT_EQ(0U, type2Parameters.size());
    ASSERT_EQ(1U, type2OtherTypes.size());
    EXPECT_EQ("type1", *(type2OtherTypes.begin()));
}

TEST(AlbaSackReaderTest, TypedefWithStructAreRecognized)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef struct type1 type2;" << endl;
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType type2 = sackReader.getType("type2");
    AlbaSackReaderType::Parameters type2Parameters = type2.getParameters();
    AlbaSackReaderType::TypeNames type2OtherTypes = type2.getOtherTypes();
    ASSERT_EQ(0U, type2Parameters.size());
    ASSERT_EQ(0U, type2OtherTypes.size());
}

TEST(AlbaSackReaderTest, TypedefWithStructWithParametersAreRecognized)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef struct myStruct1" << endl;
    testFile << "{" << endl;
    testFile << "unsigned long int integerParameter;" << endl;
    testFile << "double doubleParameter;" << endl;
    testFile << "} myStruct2;" << endl;
    testFile.close();


    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType myClass = sackReader.getType("myStruct2");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    AlbaSackReaderType::TypeNames myClassOtherTypes = myClass.getOtherTypes();
    ASSERT_EQ(2U, myClassParameters.size());
    EXPECT_EQ("unsigned long int", myClassParameters[0].getTypeName());
    EXPECT_EQ("integerParameter", myClassParameters[0].getParameterName());
    EXPECT_EQ("double", myClassParameters[1].getTypeName());
    EXPECT_EQ("doubleParameter", myClassParameters[1].getParameterName());
    ASSERT_EQ(0U, myClassOtherTypes.size());
}

TEST(AlbaSackReaderTest, TypedefWithSingleStructWithParametersAreRecognized)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef struct" << endl;
    testFile << "{" << endl;
    testFile << "unsigned long int integerParameter;" << endl;
    testFile << "double doubleParameter;" << endl;
    testFile << "} myStruct1;" << endl;
    testFile.close();


    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType myClass = sackReader.getType("myStruct1");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    AlbaSackReaderType::TypeNames myClassOtherTypes = myClass.getOtherTypes();
    ASSERT_EQ(2U, myClassParameters.size());
    EXPECT_EQ("unsigned long int", myClassParameters[0].getTypeName());
    EXPECT_EQ("integerParameter", myClassParameters[0].getParameterName());
    EXPECT_EQ("double", myClassParameters[1].getTypeName());
    EXPECT_EQ("doubleParameter", myClassParameters[1].getParameterName());
    ASSERT_EQ(0U, myClassOtherTypes.size());
    EXPECT_FALSE(myClass.isUnion());
}

TEST(AlbaSackReaderTest, TypedefWithUnionWithParametersAreRecognized)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef union myUnion1" << endl;
    testFile << "{" << endl;
    testFile << "unsigned long int integerParameter;" << endl;
    testFile << "double doubleParameter;" << endl;
    testFile << "} myUnion2;" << endl;
    testFile.close();


    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType myClass = sackReader.getType("myUnion2");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    AlbaSackReaderType::TypeNames myClassOtherTypes = myClass.getOtherTypes();
    ASSERT_EQ(2U, myClassParameters.size());
    EXPECT_EQ("unsigned long int", myClassParameters[0].getTypeName());
    EXPECT_EQ("integerParameter", myClassParameters[0].getParameterName());
    EXPECT_EQ("double", myClassParameters[1].getTypeName());
    EXPECT_EQ("doubleParameter", myClassParameters[1].getParameterName());
    ASSERT_EQ(0U, myClassOtherTypes.size());
    EXPECT_TRUE(myClass.isUnion());
}

TEST(AlbaSackReaderTest, TypedefWithEnumAreRecognized)
{
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "typedef enum {" << endl;
    testFile << "MyEnum_Value0  = 0," << endl;
    testFile << "MyEnum_Value2  = 2," << endl;
    testFile << "MyEnum_Value5  = 5" << endl;
    testFile << "} MyEnum;" << endl;
    testFile << endl;
    testFile.close();

    AlbaSackReader sackReader(file1ToReadPathHandler.getFullPath());
    sackReader.process();
    AlbaSackReaderType myClass = sackReader.getType("MyEnum");
    AlbaSackReaderType::Parameters myClassParameters = myClass.getParameters();
    ASSERT_EQ(0U, myClassParameters.size());
}

}
