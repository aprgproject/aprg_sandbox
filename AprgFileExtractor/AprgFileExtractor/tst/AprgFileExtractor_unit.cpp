#include <AprgFileExtractor.hpp>

#include <gtest/gtest.h>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

#define PATH_OF_SAMPLE_ZIP_1 R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest.zip)"
#define PATH_OF_SAMPLE_ZIP_2 R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest2.zip)"

using namespace alba;


TEST(AprgFileExtractorTest, ActualTest)
{
    AprgFileExtractor fileExtractor(R"([LRM] || [alarm] || [UDP] || [CPU] || [syslog] || [ccns] || [tcom] || [startup] || [runtime] || [system] || [radparam] || ([bts]&&([.log]||[.zip]||[.tar])) || [snapshot] || ([tech]&&[report]) || [BTSLogFiles])");
    fileExtractor.extractAllRelevantFiles(R"(D:\W\ZZZ_Useless_Logs\PR103380\New folder\)");
}

TEST(AprgFileExtractorTest, ListOfFilesFromZipFileAreCorrectlyRetrieved)
{
    AprgFileExtractor fileExtractor;
    set<string> files;
    fileExtractor.copyRelativeFilePathsFromCompressedFile(PATH_OF_SAMPLE_ZIP_1, files);

    ASSERT_EQ(11, files.size());
    auto fileIterator = files.begin();
    EXPECT_EQ(R"(DirectoryTest\DIR1\File1.log)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR2\File2.txt)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR3\File3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR4\File4.mp3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR5\File5.avi)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\DIR6\SUBDIR1\File6.jpg)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File1.log)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File2.txt)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File4.mp3)", *fileIterator++);
    EXPECT_EQ(R"(DirectoryTest\File5.avi)", *fileIterator++);
}

TEST(AprgFileExtractorTest, OneFileIsExtractedSuccessfully)
{
    AprgFileExtractor fileExtractor;
    AlbaWindowsPathHandler filePathHandler;
    filePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)");
    filePathHandler.deleteFile();
    filePathHandler.reInputPath();
    ASSERT_FALSE(filePathHandler.isFoundInLocalSystem());

    string outputFilePath = fileExtractor.extractOneFile(PATH_OF_SAMPLE_ZIP_1, R"(DirectoryTest\DIR1\File1.log)");

    EXPECT_EQ(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)", outputFilePath);
    filePathHandler.reInputPath();
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
}

TEST(AprgFileExtractorTest, AllFilesAreExtractedSuccessfully)
{
    AprgFileExtractor fileExtractor;
    AlbaWindowsPathHandler directoryPathHandler;
    directoryPathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\)");
    set<string> files;
    set<string> directories;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for(string const& file: files)
    {
        AlbaWindowsPathHandler filePathHandler;
        filePathHandler.inputPath(file);
        filePathHandler.deleteFile();
        filePathHandler.reInputPath();
        ASSERT_FALSE(filePathHandler.isFoundInLocalSystem());
    }

    string outputDirectoryPath = fileExtractor.extractAll(PATH_OF_SAMPLE_ZIP_1);

    EXPECT_EQ(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\)", outputDirectoryPath);
    AlbaWindowsPathHandler outputFilePathHandler;
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DIR1\File1.log)");
    //EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)");
    //EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DIR3\File3)");
    //EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)");
    //EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)");
    //EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\File6.jpg)");
    //EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\File3)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
    outputFilePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\File5.avi)");
    EXPECT_TRUE(outputFilePathHandler.isFoundInLocalSystem());
}

TEST(AprgFileExtractorTest, FilesAreExtractedSuccessfullyWhenSatisyingTheCondition)
{
    AprgFileExtractor fileExtractor("[.log]");
    AlbaWindowsPathHandler filePathHandler;
    filePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)");
    filePathHandler.deleteFile();
    filePathHandler.reInputPath();
    ASSERT_FALSE(filePathHandler.isFoundInLocalSystem());
    filePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DirectoryTest\File1.log)");
    filePathHandler.deleteFile();
    filePathHandler.reInputPath();
    ASSERT_FALSE(filePathHandler.isFoundInLocalSystem());

    fileExtractor.extractAllRelevantFiles(PATH_OF_SAMPLE_ZIP_1);

    filePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DirectoryTest\DIR1\File1.log)");
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
    filePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest\DirectoryTest\File1.log)");
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
}

TEST(AprgFileExtractorTest, FilesAreExtractedRecursivelyWhenSatisyingTheCondition)
{
    AprgFileExtractor fileExtractor("[DirectoryTest]");
    AlbaWindowsPathHandler filePathHandler;
    filePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest2\DirectoryTest2\DirectoryTest2\DirectoryTest2.txt)");
    filePathHandler.deleteFile();
    filePathHandler.reInputPath();
    ASSERT_FALSE(filePathHandler.isFoundInLocalSystem());

    fileExtractor.extractAllRelevantFiles(PATH_OF_SAMPLE_ZIP_2);

    filePathHandler.inputPath(R"(C:\APRG\AprgFileExtractor\AprgFileExtractor\tst\FilesForTests\DirectoryTest2\DirectoryTest2\DirectoryTest2\DirectoryTest2.txt)");
    EXPECT_TRUE(filePathHandler.isFoundInLocalSystem());
}
