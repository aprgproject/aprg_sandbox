#include "../../../src/FileDirectoryDatabase/CMake/CMakeReader.hpp"
#include "../../MtDirectoryConstants.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace codeReview;
using namespace std;

TEST (CMakeFileReadTest, DISABLED_ActualTest)
{
    CMakeDatabase fileDirectoryDatabase;
    CMakeReader reader("C:\\NSNWORK\\HSCH++2\\tcom_flexi3-trunk-hsch\\C_Application\\SC_TCOM\\SS_HSCH\\CMakeLists.txt", fileDirectoryDatabase);
    reader.readFile();
    reader.printVariables();
    fileDirectoryDatabase.printFilesAndDirectories();
/*
    //string string1("TcomLogPrint.c");
    string string1("CellStateChanger");
    //string string1("TCellId");
    bool isFoundResult;
    string string2("");
    CMakeDatabase& cMakeDatabase = fileDirectoryDatabase.find_InnerDirection("WaitFachDeletionLtcomReleaseStateHandler.cpp", isFoundResult, string2);
    cout<<"XXXFindFile: "<<string2<<endl;
    string string3("");
    cMakeDatabase.find_OuterDirection("Environment.hpp", isFoundResult, string3);
    cout<<"XXXFindHeaderFile: "<<string3<<endl;
    */
}

TEST(CMakeReaderTest, CMakeFileRead_ProjectCommandSyntaxTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "PROJECT(IdentifierMustNotHaveSpecialCharacters_!@#$%^&*)" << endl;
    testFile << "   project  ((         IdentifierCanContainLettersAndNumbers_abcdefghijklmnopqrstuvwxyz1234567890      ))           " << endl;
    testFile << "   ProJECT " << endl;
    testFile << "   (   ( (     " << endl;
    testFile << "           IdentifierInASeparateLine    " << endl;
    testFile << "    )   )  )       " << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    VariableMapType& variableMap = reader.getVariableMapReference();
    ASSERT_EQ(variableMap.at("PROJECT_NAME").size(), 3);
    auto it = variableMap.at("PROJECT_NAME").begin();
    EXPECT_EQ(*(it++), "IdentifierCanContainLettersAndNumbers_abcdefghijklmnopqrstuvwxyz1234567890");
    EXPECT_EQ(*(it++), "IdentifierInASeparateLine");
    EXPECT_EQ(*(it++), "IdentifierMustNotHaveSpecialCharacters_");
}

TEST(CMakeReaderTest, CMakeFileRead_SetCommandWithOnlyOneValueForOneVariableSyntaxTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "set(VAR1 VALUE_!@#$%^&*)" << endl;
    testFile << "  SET  (   VAR2 VALUE_1234567890    )    " << endl;
    testFile << "  sEt  (           VAR3 VALUE_abcdefghijklmnopqrstuvwxyz      )        " << endl;
    testFile << "   Set ((       VAR4     VALUE_DIR1\\/\\/\\DIR2\\\\///\\DIR3    ))       " << endl;
    testFile << "   SEt " << endl;
    testFile << "   ( ( (     " << endl;
    testFile << "   VAR5     " << endl;
    testFile << "VALUE_DIR5    " << endl;
    testFile << "VALUE_DIR1////DIR2\\..\\\\///DIR3    " << endl;
    testFile << "VALUE_DIR1////DIR2\\..\\\\///DIR3/\\DIR4\\\\..\\/DIR5    " << endl;
    testFile << "    )    )      )       " << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    VariableMapType& variableMap = reader.getVariableMapReference();
    ASSERT_EQ(variableMap.at("VAR1").size(), 1);
    ASSERT_EQ(variableMap.at("VAR2").size(), 1);
    ASSERT_EQ(variableMap.at("VAR3").size(), 1);
    ASSERT_EQ(variableMap.at("VAR4").size(), 1);
    ASSERT_EQ(variableMap.at("VAR5").size(), 1);
    EXPECT_EQ(*(variableMap.at("VAR1").begin()), "VALUE_!@#$%^&*");
    EXPECT_EQ(*(variableMap.at("VAR2").begin()), "VALUE_1234567890");
    EXPECT_EQ(*(variableMap.at("VAR3").begin()), "VALUE_abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(*(variableMap.at("VAR4").begin()), "VALUE_DIR1\\DIR2\\DIR3");
    EXPECT_EQ(*(variableMap.at("VAR5").begin()), "VALUE_DIR5 VALUE_DIR1\\DIR3 VALUE_DIR1\\DIR3\\DIR5");
}

TEST(CMakeReaderTest, CMakeFileRead_SetCommandWithOnlyOneValueForOneVariableSyntaxTest_NoLineSeparators)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "set(VAR1 VALUE_!@#$%^&*)";
    testFile << "  SET  (   VAR2 VALUE_1234567890    )    ";
    testFile << "  sEt  (           VAR3 VALUE_abcdefghijklmnopqrstuvwxyz      )        ";
    testFile << "   Set ((       VAR4     VALUE_DIR1\\/\\/\\DIR2\\\\///\\DIR3    ))       ";
    testFile << "   SEt ";
    testFile << "   ( ( (     ";
    testFile << "   VAR5     ";
    testFile << "VALUE_DIR5    ";
    testFile << "VALUE_DIR1////DIR2\\..\\\\///DIR3    ";
    testFile << "VALUE_DIR1////DIR2\\..\\\\///DIR3/\\DIR4\\\\..\\/DIR5    ";
    testFile << "    )    )      )       ";
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    VariableMapType& variableMap = reader.getVariableMapReference();
    ASSERT_EQ(variableMap.at("VAR1").size(), 1);
    ASSERT_EQ(variableMap.at("VAR2").size(), 1);
    ASSERT_EQ(variableMap.at("VAR3").size(), 1);
    ASSERT_EQ(variableMap.at("VAR4").size(), 1);
    ASSERT_EQ(variableMap.at("VAR5").size(), 1);
    EXPECT_EQ(*(variableMap.at("VAR1").begin()), "VALUE_!@#$%^&*");
    EXPECT_EQ(*(variableMap.at("VAR2").begin()), "VALUE_1234567890");
    EXPECT_EQ(*(variableMap.at("VAR3").begin()), "VALUE_abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(*(variableMap.at("VAR4").begin()), "VALUE_DIR1\\DIR2\\DIR3");
    EXPECT_EQ(*(variableMap.at("VAR5").begin()), "VALUE_DIR5 VALUE_DIR1\\DIR3 VALUE_DIR1\\DIR3\\DIR5");
}

TEST(CMakeReaderTest, CMakeFileRead_SetCommandWithMultipleValuesForOneVariable)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "SET(VAR1 VALUE_DIRNAME)" << endl;
    testFile << "SET(VAR1 VALUE_1c)" << endl;
    testFile << "SET(VAR1 VALUE_2a)" << endl;
    testFile << "SET(VAR1 VALUE_1b)" << endl;
    testFile << "SET(VAR1 VALUE_4)" << endl;
    testFile << "SET(VAR1 VALUE_1a)" << endl;
    testFile << "SET(VAR1 VALUE_2)" << endl;
    testFile << "SET(VAR1 VALUE_DIR/////)" << endl;
    testFile << "SET(VAR1 VALUE_DIR\\/\\/)" << endl;
    testFile << "SET(VAR1 VALUE_DIR\\)" << endl;
    testFile << "SET(VAR1 VALUE_3)" << endl;
    testFile << "SET(VAR1 VALUE_DIR)" << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    VariableMapType& variableMap = reader.getVariableMapReference();
    ASSERT_EQ(variableMap.at("VAR1").size(), 10);
    auto it = variableMap.at("VAR1").begin();
    EXPECT_EQ(*(it++), "VALUE_1a");
    EXPECT_EQ(*(it++), "VALUE_1b");
    EXPECT_EQ(*(it++), "VALUE_1c");
    EXPECT_EQ(*(it++), "VALUE_2");
    EXPECT_EQ(*(it++), "VALUE_2a");
    EXPECT_EQ(*(it++), "VALUE_3");
    EXPECT_EQ(*(it++), "VALUE_4");
    EXPECT_EQ(*(it++), "VALUE_DIR");
    EXPECT_EQ(*(it++), "VALUE_DIRNAME");
    EXPECT_EQ(*(it++), "VALUE_DIR\\");
}

TEST(CMakeReaderTest, CMakeFileRead_SetCommandRealValuesAreUpdated)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "SET(VAR_DIR VALUE_DIRNAME)" << endl;
    testFile << "SET(VAR1 ${VAR_DIR}\\\\VALUE_1c)" << endl;
    testFile << "SET(VAR1 ${VAR_DIR}/\\/VALUE_1a)" << endl;
    testFile << "SET(VAR1 ${VAR_DIR}////VALUE_1b)" << endl;
    testFile << "SET(VAR2 ${VAR1}\\\\VALUE_2)" << endl;
    testFile << "SET(VAR2 ${VAR1}////VALUE_2a)" << endl;
    testFile << "SET(VAR3 ${VAR2}\\VALUE_31)" << endl;
    testFile << "SET(VAR3 ${VAR2}//VALUE_3a)" << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    VariableMapType& variableMap = reader.getVariableMapReference();
    ASSERT_EQ(variableMap.at("VAR1").size(), 3);
    auto it1 = variableMap.at("VAR1").begin();
    EXPECT_EQ(*(it1++), "VALUE_DIRNAME\\VALUE_1a");
    EXPECT_EQ(*(it1++), "VALUE_DIRNAME\\VALUE_1b");
    EXPECT_EQ(*(it1++), "VALUE_DIRNAME\\VALUE_1c");

    ASSERT_EQ(variableMap.at("VAR2").size(), 6);
    auto it2 = variableMap.at("VAR2").begin();
    EXPECT_EQ(*(it2++), "VALUE_DIRNAME\\VALUE_1a\\VALUE_2");
    EXPECT_EQ(*(it2++), "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a");
    EXPECT_EQ(*(it2++), "VALUE_DIRNAME\\VALUE_1b\\VALUE_2");
    EXPECT_EQ(*(it2++), "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a");
    EXPECT_EQ(*(it2++), "VALUE_DIRNAME\\VALUE_1c\\VALUE_2");
    EXPECT_EQ(*(it2++), "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a");

    ASSERT_EQ(variableMap.at("VAR3").size(), 12);
    auto it3 = variableMap.at("VAR3").begin();
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\VALUE_31");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\VALUE_3a");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\VALUE_31");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\VALUE_3a");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\VALUE_31");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\VALUE_3a");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\VALUE_31");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\VALUE_3a");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\VALUE_31");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\VALUE_3a");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\VALUE_31");
    EXPECT_EQ(*(it3++), "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\VALUE_3a");
}

TEST(CMakeReaderTest, CMakeFileRead_IncludeDirectoriesCommandSyntaxTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "INCLUDE_DIRECTORIES(DirectoriesCanContainSpecialCharacters_!@#$%^&*)" << endl;
    testFile << "   include_directories  (  DirectoriesCanContainLetters_abcdefghijklmnopqrstuvwxyz      )" << endl;
    testFile << "   INCLUDE_directories  ((   DirectoriesCanContainNumbers_1234567890    ))   " << endl;
    testFile << "   include_DIRECTORIES " << endl;
    testFile << "   (   ((    " << endl;
    testFile << "           DirectoryInASeparateLine    " << endl;
    testFile << "    )       )           )       " << endl;
    testFile << "incLUDE_direcTORIES(Directories\\Can\\Contain\\Slashes)" << endl;
    testFile << "INCLude_DIRECtories(Directory\\//\\Slashes////Are\\/\\\\///Converted///To\\/\\Back//Slashes)" << endl;
    testFile << "incLude_direcTories(Directories/Are//Simplified/../..//\\Double/Periods/Are/\\../Removed)" << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    SetOfFiles& setOfFiles = fileDirectoryDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 7);
    string currentDirectory(MT_FILE_READER_TEST_DIRECTORY);
    auto it = setOfFiles.begin();
    EXPECT_EQ(*(it++), currentDirectory + "DirectoriesCanContainLetters_abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(*(it++), currentDirectory + "DirectoriesCanContainNumbers_1234567890");
    EXPECT_EQ(*(it++), currentDirectory + "DirectoriesCanContainSpecialCharacters_!@#$%^&*");
    EXPECT_EQ(*(it++), currentDirectory + "Directories\\Can\\Contain\\Slashes");
    EXPECT_EQ(*(it++), currentDirectory + "Directories\\Double\\Periods\\Removed");
    EXPECT_EQ(*(it++), currentDirectory + "DirectoryInASeparateLine");
    EXPECT_EQ(*(it++), currentDirectory + "Directory\\Slashes\\Are\\Converted\\To\\Back\\Slashes");
}

TEST(CMakeReaderTest, CMakeFileRead_IncludeDirectoriesCommandRealValuesAreUpdated)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "SET(FILENAME FileTest1)" << endl;
    testFile << "SET(EXTENSION .txt)" << endl;
    testFile << "SET(EXTENSION .log)" << endl;
    testFile << "SET(VAR_DIR VALUE_DIRNAME)" << endl;
    testFile << "SET(VAR1 ${VAR_DIR}\\\\VALUE_1c)" << endl;
    testFile << "SET(VAR1 ${VAR_DIR}/\\/VALUE_1a)" << endl;
    testFile << "SET(VAR1 ${VAR_DIR}////VALUE_1b)" << endl;
    testFile << "SET(VAR2 ${VAR1}\\\\VALUE_2)" << endl;
    testFile << "SET(VAR2 ${VAR1}////VALUE_2a)" << endl;
    testFile << "INCLUDE_DIRECTORIES(${VAR2}\\//${FILENAME}${EXTENSION})" << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    SetOfFiles& setOfFiles = fileDirectoryDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 12);
    string currentDirectory(MT_FILE_READER_TEST_DIRECTORY);
    auto it = setOfFiles.begin();
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.txt");
}

TEST(CMakeReaderTest, CMakeFileRead_IncludeDirectoriesCommandAbsolutePathGiven)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "INCLUDE_DIRECTORIES(C:\\/DIR1/DIR2///DIR3\\\\/\\/DIR4/)" << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    SetOfDirectories& setOfDirectories = fileDirectoryDatabase.getSetOfDirectoriesReference();
    ASSERT_EQ(setOfDirectories.size(), 1);
    EXPECT_EQ(*(setOfDirectories.begin()), "C:\\DIR1\\DIR2\\DIR3\\DIR4\\");
}

TEST(CMakeReaderTest, CMakeFileRead_IncludeCommandSyntaxTest_WithSetTestForIncludeFiles)
{
    string includeDirectoryFullPath(MT_FILE_READER_TEST_INCLUDE_DIRECTORY);
    ofstream includeFileStream1(includeDirectoryFullPath + "include1.txt");
    ofstream includeFileStream2(includeDirectoryFullPath + "include2.txt");
    ofstream includeFileStream3(includeDirectoryFullPath + "include3.txt");
    ASSERT_TRUE(includeFileStream1.is_open());
    ASSERT_TRUE(includeFileStream2.is_open());
    ASSERT_TRUE(includeFileStream3.is_open());
    includeFileStream1 << "set(VAR1 VALUE_!@#$%^&*)" << endl;
    includeFileStream1 << "  SET  (   VAR2 VALUE_1234567890    )    " << endl;
    includeFileStream2 << "  sEt  (           VAR3 VALUE_abcdefghijklmnopqrstuvwxyz      )        " << endl;
    includeFileStream2 << "   Set ((       VAR4     VALUE_DIR1\\/\\/\\DIR2\\\\///\\DIR3    ))       " << endl;
    includeFileStream3 << "   SEt " << endl;
    includeFileStream3 << "   (     ((   (     " << endl;
    includeFileStream3 << "   VAR5     " << endl;
    includeFileStream3 << "VALUE_DIR5    " << endl;
    includeFileStream3 << "VALUE_DIR1////DIR2\\..\\\\///DIR3    " << endl;
    includeFileStream3 << "VALUE_DIR1////DIR2\\..\\\\///DIR3/\\DIR4\\\\..\\/DIR5    " << endl;
    includeFileStream3 << "    )   )) )       " << endl;
    includeFileStream1.close();
    includeFileStream2.close();
    includeFileStream3.close();

    string includeDirectoryName(MT_FILE_READER_TEST_INCLUDE_DIRECTORY_NAME);
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "INCLUDE(" << includeDirectoryFullPath << "include1.txt" << ")" << endl;
    testFile << "   include         (       " << includeDirectoryName << "\\/\\//include2.txt" << "  )      " << endl;
    testFile << "   INClude " << endl;
    testFile << "   (     " << endl;
    testFile << "\\///\\" << includeDirectoryName << "\\/\\//include3.txt" << endl;
    testFile << "    )       " << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    VariableMapType& variableMap = reader.getVariableMapReference();
    ASSERT_EQ(variableMap.at("VAR1").size(), 1);
    ASSERT_EQ(variableMap.at("VAR2").size(), 1);
    ASSERT_EQ(variableMap.at("VAR3").size(), 1);
    ASSERT_EQ(variableMap.at("VAR4").size(), 1);
    ASSERT_EQ(variableMap.at("VAR5").size(), 1);
    EXPECT_EQ(*(variableMap.at("VAR1").begin()), "VALUE_!@#$%^&*");
    EXPECT_EQ(*(variableMap.at("VAR2").begin()), "VALUE_1234567890");
    EXPECT_EQ(*(variableMap.at("VAR3").begin()), "VALUE_abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(*(variableMap.at("VAR4").begin()), "VALUE_DIR1\\DIR2\\DIR3");
    EXPECT_EQ(*(variableMap.at("VAR5").begin()), "VALUE_DIR5 VALUE_DIR1\\DIR3 VALUE_DIR1\\DIR3\\DIR5");
}

TEST(CMakeReaderTest, CMakeFileRead_IncludeCommandTest_WithIncludeDirectoriesRealValuesAreUpdatedTest)
{
    string includeDirectoryFullPath(MT_FILE_READER_TEST_INCLUDE_DIRECTORY);
    ofstream includeFileStream1(includeDirectoryFullPath + "include1.txt");
    ofstream includeFileStream2(includeDirectoryFullPath + "include2.txt");
    ofstream includeFileStream3(includeDirectoryFullPath + "include3.txt");
    ASSERT_TRUE(includeFileStream1.is_open());
    ASSERT_TRUE(includeFileStream2.is_open());
    ASSERT_TRUE(includeFileStream3.is_open());
    includeFileStream1 << "SET(FILENAME FileTest1)" << endl;
    includeFileStream1 << "SET(EXTENSION .txt)" << endl;
    includeFileStream2 << "SET(EXTENSION .log)" << endl;
    includeFileStream2 << "SET(VAR_DIR VALUE_DIRNAME)" << endl;
    includeFileStream2 << "SET(VAR1 ${VAR_DIR}\\\\VALUE_1c)" << endl;
    includeFileStream2 << "SET(VAR1 ${VAR_DIR}/\\/VALUE_1a)" << endl;
    includeFileStream3 << "SET(VAR1 ${VAR_DIR}////VALUE_1b)" << endl;
    includeFileStream3 << "SET(VAR2 ${VAR1}\\\\VALUE_2)" << endl;
    includeFileStream3 << "SET(VAR2 ${VAR1}////VALUE_2a)" << endl;
    includeFileStream3 << "INCLUDE_DIRECTORIES(${VAR2}\\//${FILENAME}${EXTENSION})" << endl;
    includeFileStream1.close();
    includeFileStream2.close();
    includeFileStream3.close();

    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "INCLUDE(" << includeDirectoryFullPath << "include1.txt" << ")" << endl;
    testFile << "INCLUDE(" << includeDirectoryFullPath << "include2.txt" << ")" << endl;
    testFile << "INCLUDE(" << includeDirectoryFullPath << "include3.txt" << ")" << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    SetOfFiles& setOfFiles = fileDirectoryDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 12);
    string currentDirectory(MT_FILE_READER_TEST_DIRECTORY);
    auto it = setOfFiles.begin();
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it++), currentDirectory + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.txt");
}

TEST(CMakeReaderTest, CMakeFileRead_AddSubDirectoryCommandSyntaxTest_WithIncludeDirectoriesRealValuesAreUpdatedTest)
{
    string subDirectoryFullPath(MT_FILE_READER_TEST_SUBDIRECTORY);
    string subDirectoryName(MT_FILE_READER_TEST_SUBDIRECTORY_NAME);

    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "SET(FILENAME FileTest1)" << endl;
    testFile << "SET(EXTENSION .txt)" << endl;
    testFile << "SET(EXTENSION .log)" << endl;
    testFile << "ADD_SUBDIRECTORY(" << subDirectoryFullPath << "DIR1" << ")" << endl;
    testFile << "   add_subdirectory         ((       " << subDirectoryName << "\\/\\//DIR2" << "  ))      " << endl;
    testFile << "   aDD_subDireCToRY " << endl;
    testFile << "   (   (       (     " << endl;
    testFile << "\\///\\" << subDirectoryName << "\\/\\//DIR3" << endl;
    testFile << "    )      )    )       " << endl;
    testFile.close();

    ofstream sourceFileStream1(subDirectoryFullPath + "\\DIR1\\CMakeLists.txt");
    ofstream sourceFileStream2(subDirectoryFullPath + "\\DIR2\\CMakeLists.txt");
    ofstream sourceFileStream3(subDirectoryFullPath + "\\DIR3\\CMakeLists.txt");
    ASSERT_TRUE(sourceFileStream1.is_open());
    ASSERT_TRUE(sourceFileStream2.is_open());
    ASSERT_TRUE(sourceFileStream3.is_open());
    sourceFileStream1 << "SET(VAR_DIR VALUE_DIRNAME)" << endl;
    sourceFileStream1 << "SET(VAR1 ${VAR_DIR}\\\\VALUE_1c)" << endl;
    sourceFileStream1 << "SET(VAR1 ${VAR_DIR}/\\/VALUE_1a)" << endl;
    sourceFileStream1 << "SET(VAR1 ${VAR_DIR}////VALUE_1b)" << endl;
    sourceFileStream1 << "SET(VAR2 ${VAR1}\\\\VALUE_2)" << endl;
    sourceFileStream1 << "SET(VAR2 ${VAR1}////VALUE_2a)" << endl;
    sourceFileStream1 << "INCLUDE_DIRECTORIES(${VAR2}\\//${FILENAME}${EXTENSION})" << endl;
    sourceFileStream1.close();
    sourceFileStream2 << "SET(VAR_DIR VALUE_DIRNAME)" << endl;
    sourceFileStream2 << "SET(VAR1 ${VAR_DIR}\\\\VALUE_1c)" << endl;
    sourceFileStream2 << "SET(VAR1 ${VAR_DIR}/\\/VALUE_1a)" << endl;
    sourceFileStream2 << "SET(VAR1 ${VAR_DIR}////VALUE_1b)" << endl;
    sourceFileStream2 << "SET(VAR2 ${VAR1}\\\\VALUE_2)" << endl;
    sourceFileStream2 << "SET(VAR2 ${VAR1}////VALUE_2a)" << endl;
    sourceFileStream2 << "INCLUDE_DIRECTORIES(${VAR2}\\//${FILENAME}${EXTENSION})" << endl;
    sourceFileStream2.close();
    sourceFileStream3 << "SET(VAR_DIR VALUE_DIRNAME)" << endl;
    sourceFileStream3 << "SET(VAR1 ${VAR_DIR}\\\\VALUE_1c)" << endl;
    sourceFileStream3 << "SET(VAR1 ${VAR_DIR}/\\/VALUE_1a)" << endl;
    sourceFileStream3 << "SET(VAR1 ${VAR_DIR}////VALUE_1b)" << endl;
    sourceFileStream3 << "SET(VAR2 ${VAR1}\\\\VALUE_2)" << endl;
    sourceFileStream3 << "SET(VAR2 ${VAR1}////VALUE_2a)" << endl;
    sourceFileStream3 << "INCLUDE_DIRECTORIES(${VAR2}\\//${FILENAME}${EXTENSION})" << endl;
    sourceFileStream3.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    reader.readFile();
    SubCMakeDatabases& listOfSubFileDirectoryDatabases
            = fileDirectoryDatabase.getSubCMakeDatabasesReference();
    ASSERT_EQ(listOfSubFileDirectoryDatabases.size(), 3);
    CMakeDatabase& cMakeFileDirectoryDatabase1= *(listOfSubFileDirectoryDatabases.begin());
    CMakeDatabase& cMakeFileDirectoryDatabase2= *(listOfSubFileDirectoryDatabases.begin()+1);
    CMakeDatabase& cMakeFileDirectoryDatabase3= *(listOfSubFileDirectoryDatabases.begin()+2);
    SetOfFiles& setOfFiles1
            = cMakeFileDirectoryDatabase1.getSetOfFilesReference();
    SetOfFiles& setOfFiles2
            = cMakeFileDirectoryDatabase2.getSetOfFilesReference();
    SetOfFiles& setOfFiles3
            = cMakeFileDirectoryDatabase3.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles1.size(), 12);
    ASSERT_EQ(setOfFiles2.size(), 12);
    ASSERT_EQ(setOfFiles3.size(), 12);
    string currentDirectory1(subDirectoryFullPath+"DIR1\\");
    string currentDirectory2(subDirectoryFullPath+"DIR2\\");
    string currentDirectory3(subDirectoryFullPath+"DIR3\\");
    auto it1 = setOfFiles1.begin();
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it1++), currentDirectory1 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.txt");
    auto it2 = setOfFiles2.begin();
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it2++), currentDirectory2 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.txt");
    auto it3 = setOfFiles3.begin();
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1a\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1b\\VALUE_2a\\FileTest1.txt");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.log");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2\\FileTest1.txt");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.log");
    EXPECT_EQ(*(it3++), currentDirectory3 + "VALUE_DIRNAME\\VALUE_1c\\VALUE_2a\\FileTest1.txt");
}

TEST(CMakeReaderTest, CMakeFileRead_AddLibraryCommandSyntaxTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "SET(SUB_DIRECTORY_NAME "<<MT_FILE_READER_TEST_SUBDIRECTORY_NAME<<")"<<endl;
    testFile << "SET(DIRECTORIES \\${SUB_DIRECTORY_NAME}\\DIR1\\)" << endl;
    testFile << "SET(DIRECTORIES ${SUB_DIRECTORY_NAME}\\DIR2\\)" << endl;
    testFile << "SET(DIRECTORIES ${SUB_DIRECTORY_NAME}\\DIR3)" << endl;
    testFile << "SET(FILES \\${SUB_DIRECTORY_NAME}\\DIR1\\File1.log)" << endl;
    testFile << "SET(FILES ${SUB_DIRECTORY_NAME}\\DIR2\\File2.txt)" << endl;
    testFile << "SET(FILES ${SUB_DIRECTORY_NAME}\\DIR3\\File3.bin)" << endl;
    testFile << "ADD_LIBRARY(firstArgument " << MT_FILE_READER_TEST_SUBDIRECTORY << "File4.out)" << endl;
    testFile << "   add_library         ((       firstArgument        ${DIRECTORIES}  ))      " << endl;
    testFile << "   aDD_lIBraRy " << endl;
    testFile << "   (    (    (     " << endl;
    testFile << "   firstArgument     " << endl;
    testFile << "\\///\\${FILES}   " << endl;
    testFile << "    )    )     )       " << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    string currentDirectory(MT_FILE_READER_TEST_SUBDIRECTORY);
    reader.readFile();

    SetOfDirectories& setOfDirectories = fileDirectoryDatabase.getSetOfDirectoriesReference();
    ASSERT_EQ(setOfDirectories.size(), 3);
    auto itDirectory = setOfDirectories.begin();
    EXPECT_EQ(*(itDirectory++), currentDirectory + "DIR1\\");
    EXPECT_EQ(*(itDirectory++), currentDirectory + "DIR2\\");
    EXPECT_EQ(*(itDirectory++), currentDirectory + "DIR3\\"); //appends backslash at the end because of windowspathhelper :)

    SetOfFiles& setOfFiles = fileDirectoryDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 4);
    auto itFile = setOfFiles.begin();
    EXPECT_EQ(*(itFile++), currentDirectory + "DIR1\\File1.log");
    EXPECT_EQ(*(itFile++), currentDirectory + "DIR2\\File2.txt");
    EXPECT_EQ(*(itFile++), currentDirectory + "DIR3\\File3.bin");
    EXPECT_EQ(*(itFile++), currentDirectory + "File4.out");
}

TEST(CMakeReaderTest, CMakeFileRead_AddExecutableCommandSyntaxTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "SET(SUB_DIRECTORY_NAME "<<MT_FILE_READER_TEST_SUBDIRECTORY_NAME<<")"<<endl;
    testFile << "SET(DIRECTORIES \\${SUB_DIRECTORY_NAME}\\DIR1\\)" << endl;
    testFile << "SET(DIRECTORIES ${SUB_DIRECTORY_NAME}\\DIR2\\)" << endl;
    testFile << "SET(DIRECTORIES ${SUB_DIRECTORY_NAME}\\DIR3)" << endl;
    testFile << "SET(FILES \\${SUB_DIRECTORY_NAME}\\DIR1\\File1.log)" << endl;
    testFile << "SET(FILES ${SUB_DIRECTORY_NAME}\\DIR2\\File2.txt)" << endl;
    testFile << "SET(FILES ${SUB_DIRECTORY_NAME}\\DIR3\\File3.bin)" << endl;
    testFile << "ADD_EXECUTABLE(firstArgument " << MT_FILE_READER_TEST_SUBDIRECTORY << "File4.out)" << endl;
    testFile << "   add_executable         ((       firstArgument        ${DIRECTORIES}  ))      " << endl;
    testFile << "   aDd_exeCUTable " << endl;
    testFile << "   (    (    (     " << endl;
    testFile << "   firstArgument     " << endl;
    testFile << "\\///\\${FILES}   " << endl;
    testFile << "    )    )     )       " << endl;
    testFile.close();

    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeReader reader(MT_FILE_READER_TEST_FILE, fileDirectoryDatabase);
    string currentDirectory(MT_FILE_READER_TEST_SUBDIRECTORY);
    reader.readFile();

    SetOfDirectories& setOfDirectories = fileDirectoryDatabase.getSetOfDirectoriesReference();
    ASSERT_EQ(setOfDirectories.size(), 3);
    auto itDirectory = setOfDirectories.begin();
    EXPECT_EQ(*(itDirectory++), currentDirectory + "DIR1\\");
    EXPECT_EQ(*(itDirectory++), currentDirectory + "DIR2\\");
    EXPECT_EQ(*(itDirectory++), currentDirectory + "DIR3\\"); //appends backslash at the end because of windowspathhelper :)

    SetOfFiles& setOfFiles = fileDirectoryDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 4);
    auto itFile = setOfFiles.begin();
    EXPECT_EQ(*(itFile++), currentDirectory + "DIR1\\File1.log");
    EXPECT_EQ(*(itFile++), currentDirectory + "DIR2\\File2.txt");
    EXPECT_EQ(*(itFile++), currentDirectory + "DIR3\\File3.bin");
    EXPECT_EQ(*(itFile++), currentDirectory + "File4.out");
}


