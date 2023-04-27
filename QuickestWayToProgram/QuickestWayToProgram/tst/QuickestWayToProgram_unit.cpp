#include <Common/Debug/AlbaDebug.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <FileExtractor/AprgFileExtractor.hpp>
#include <NsapHelper.hpp>
#include <QuickestWayToProgram.hpp>

#include <gtest/gtest.h>

#include <windows.h>

#include <algorithm>
#include <bitset>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

using namespace std;

namespace alba {

namespace ProgressCounters {
int numberOfFilesToBeAnalyzedForExtraction;
int numberOfFilesAnalyzedForExtraction;
}  // namespace ProgressCounters

TEST(SampleTest, CountFromMsbValue) {
    vector<pair<int, int>> container{{3, 3}, {5, 5}};
    auto itRight = upper_bound(
        container.cbegin(), container.cend(), 1,
        [](int const value, pair<int, int> const& intPair) { return value < intPair.first; });
    auto itLeft = prev(itRight, 1);
    if (itLeft != container.cend()) {
        ALBA_PRINT1(*itLeft);
    } else {
        ALBA_PRINT1("itLeft is end");
    }
    if (itRight != container.cend()) {
        ALBA_PRINT1(*itRight);
    } else {
        ALBA_PRINT1("itRight is end");
    }
}

/*TEST(SampleTest, CountFromMsbValue) {
    cout << "{";
    for (unsigned int value = 0; value < 256; value++) {
        unsigned int countFromMsb = 0;
        unsigned int valueForMsbBitCount(value);
        for (unsigned int bitIndex = 0; bitIndex < 8; bitIndex++) {
            if (valueForMsbBitCount & 1) {
                break;
            }
            countFromMsb++;
            valueForMsbBitCount >>= 1;
        }
        cout << countFromMsb << "U, ";
        if (value % 32 == 31) {
            cout << "\n";
        }
    }
    cout << "}";
}

TEST(SampleTest, NumeratorAndDenominator) {
    long long int numerator = static_cast<long long int>(-946400) * -5547;
    long long int denominator = static_cast<long long int>(-2146689) * -3566000;
    ALBA_PRINT_PRECISION(30);
    ALBA_PRINT3(numerator, denominator, static_cast<double>(numerator) / denominator);
}

TEST(SampleTest, KBitAndNegativeK) {
    int k = 10;
    int n = 20;
    while (k <= n) {
        ALBA_PRINT2(k, k & -k);
        k += k & -k;
    }

    for (unsigned int k = 0; k <= 256; k++) {
        unsigned int p = k & -k;
        ALBA_PRINT3(k, k - p + 1, k);
    }
}

TEST(SampleTest, RenameFiles) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(N:\MUSIC\111_DoAutomationHere)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        cout << file << "\n";
        filePathHandler.renameFile(
            stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(filePathHandler.getFilenameOnly()) +
            "." + filePathHandler.getExtension());
    }
}

TEST(SampleTest, FindSourceFilesToAdjust_FileList) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(C:\Branches\CP\trunk\SBTS\tcom\C_Application\SC_TCOM)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    ifstream listFileStream(R"(C:\Branches\CP\trunk\diffs\filelist.txt)");

    if (listFileStream.is_open()) {
        AlbaFileReader listFileReader(listFileStream);
        while (listFileReader.isNotFinished()) {
            string filePath(listFileReader.getLineAndIgnoreWhiteSpaces());
            AlbaLocalPathHandler filePathHandler(filePath);
            string extensionInCapitals(stringHelper::getStringWithCapitalLetters(filePathHandler.getExtension()));
            if ((extensionInCapitals == "C" || extensionInCapitals == "CPP" || extensionInCapitals == "H" ||
                 extensionInCapitals == "HPP") &&
                !(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                    filePathHandler.getFullPath(), "CP_LINUX")

                      )) {
                ifstream logStream(filePath);
                if (logStream.is_open()) {
                    AlbaFileReader logFileReader(logStream);
                    while (logFileReader.isNotFinished()) {
                        string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
                        string stringToAnalyze(lineInFile);
                        if (stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                                stringToAnalyze, "createSicad")) {
                            ALBA_PRINT1(filePath);
                            ALBA_PRINT1(stringToAnalyze);
                        }
                    }
                }
            }
        }
    }
}

TEST(SampleTest, ClangFormatFiles) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(F:\Branches\APRG_GIT\aprg_copy\aprg)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        if (filePathHandler.getExtension() == "cpp" || filePathHandler.getExtension() == "hpp" ||
            filePathHandler.getExtension() == "c" || filePathHandler.getExtension() == "h") {
            stringstream ss;
            ss << "clang-format -i -style=file " << file << "\n";
            cout << ss.str() << endl;
            system(ss.str().c_str());
        }
    }
}

TEST(SampleTest, FindSourceFilesToAdjust_FileList) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(C:\Branches\CP\trunk\SBTS\tcom\C_Application\SC_TCOM)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    ifstream listFileStream(R"(C:\Branches\CP\trunk\diffs\filelist.txt)");

    if (listFileStream.is_open()) {
        AlbaFileReader listFileReader(listFileStream);
        while (listFileReader.isNotFinished()) {
            string filePath(listFileReader.getLineAndIgnoreWhiteSpaces());
            AlbaLocalPathHandler filePathHandler(filePath);
            string extensionInCapitals(stringHelper::getStringWithCapitalLetters(filePathHandler.getExtension()));
            if ((extensionInCapitals == "C" || extensionInCapitals == "CPP") &&
                !(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                      filePathHandler.getFullPath(), "CP_MEAS") ||
                  stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                      filePathHandler.getFullPath(), "CP_LINUX") ||
                  stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                      filePathHandler.getFullPath(), "CP_TOAM")

                      )) {
                AlbaLocalPathHandler headerFileWithH(
                    filePathHandler.getDirectory() + filePathHandler.getFilenameOnly() + ".h");
                AlbaLocalPathHandler headerFileWithHpp(
                    filePathHandler.getDirectory() + filePathHandler.getFilenameOnly() + ".hpp");
                string headerIncludeWithH =
                    string(R"(#include ")") + filePathHandler.getFilenameOnly() + string(R"(.h")");
                string headerIncludeWithHpp =
                    string(R"(#include ")") + filePathHandler.getFilenameOnly() + string(R"(.hpp")");
                bool isHeaderFileWithH = headerFileWithH.isFoundInLocalSystem();
                bool isHeaderFileWithHpp = headerFileWithHpp.isFoundInLocalSystem();

                if (isHeaderFileWithH || isHeaderFileWithHpp)
                    // &&
stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(filePathHandler.getFullPath(),
R"(CP_DMGR\src\messages\MessageHandler)"))
                {
    ifstream logStream(filePath);
    if (logStream.is_open()) {
        bool isHeaderIncludeWithQuotationsFound(false);
        AlbaFileReader logFileReader(logStream);
        while (logFileReader.isNotFinished()) {
            string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            string stringToAnalyze(lineInFile);
            if (isHeaderFileWithH &&
                stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(stringToAnalyze, headerIncludeWithH)) {
                isHeaderIncludeWithQuotationsFound = true;
                break;
            }
            if (isHeaderFileWithHpp && stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                                           stringToAnalyze, headerIncludeWithHpp)) {
                isHeaderIncludeWithQuotationsFound = true;
                break;
            }
            // ALBA_PRINT3(stringToAnalyze, isHeaderFileWithH, headerIncludeWithH);
            // ALBA_PRINT3(stringToAnalyze, isHeaderFileWithHpp, headerIncludeWithHpp);
        }
        if (isHeaderIncludeWithQuotationsFound == false) {
            ALBA_PRINT1(filePathHandler.getFullPath());
        }
    }
}
            }
        }
    }
}

TEST(SampleTest, FindHeaderFilesToAdjust_FileList) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(C:\Branches\CP\trunk\SBTS\tcom\C_Application\SC_TCOM)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    ifstream listFileStream(R"(C:\Branches\CP\trunk\diffs\filelist.txt)");

    if (listFileStream.is_open()) {
        AlbaFileReader listFileReader(listFileStream);
        while (listFileReader.isNotFinished()) {
            string filePath(listFileReader.getLineAndIgnoreWhiteSpaces());
            AlbaLocalPathHandler filePathHandler(filePath);
            string extensionInCapitals(stringHelper::getStringWithCapitalLetters(filePathHandler.getExtension()));
            if ((extensionInCapitals == "H" || extensionInCapitals == "HPP") &&
                !(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                      filePathHandler.getFullPath(), "CP_MEAS") ||
                  stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                      filePathHandler.getFullPath(), "CP_LINUX") ||
                  stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                      filePathHandler.getFullPath(), "CP_TOAM")

                      )) {
                ifstream logStream(filePath);
                if (logStream.is_open()) {
                    bool isPragmaOnceFound(false);
                    AlbaFileReader logFileReader(logStream);
                    while (logFileReader.isNotFinished()) {
                        string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
                        string stringToAnalyze(lineInFile);
                        if (stringToAnalyze == "#pragma once") {
                            // ALBA_PRINT1(filePathHandler.getFullPath());
                            // ALBA_PRINT1(stringToAnalyze);
                            isPragmaOnceFound = true;
                            break;
                        }
                    }
                    if (isPragmaOnceFound == false) {
                        ALBA_PRINT1(filePathHandler.getFullPath());
                    }
                }
            }
        }
    }
}

TEST(SampleTest, FindSourceFilesToAdjust_FromDirectory) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(C:\Branches\CP\trunk\SBTS\tcom\C_Application\SC_TCOM)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        string extensionInCapitals(stringHelper::getStringWithCapitalLetters(filePathHandler.getExtension()));
        if ((extensionInCapitals == "H" || extensionInCapitals == "HPP") &&
            !(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                  filePathHandler.getFullPath(), "CP_MEAS") ||
              stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                  filePathHandler.getFullPath(), "CP_LINUX") ||
              stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(filePathHandler.getFullPath(), "CP_TOAM")

                  )) {
            ifstream logStream(file);
            if (logStream.is_open()) {
                AlbaFileReader logFileReader(logStream);
                while (logFileReader.isNotFinished()) {
                    string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
                    string stringToAnalyze(lineInFile);
                    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(stringToAnalyze, "using namespace
fw") || stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(stringToAnalyze, "using fw::")
                            )
                    {
                        ALBA_PRINT1(filePathHandler.getFullPath());
                        ALBA_PRINT1(lineInFile);
                        cout << "\n";
                        break;
                    }
                }
            }
        }
    }
}

TEST(SampleTest, FindSourceFilesToAdjust_FromDirectory) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(C:\Branches\CP\trunk\SBTS\tcom\C_Application\SC_TCOM)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        string extensionInCapitals(stringHelper::getStringWithCapitalLetters(filePathHandler.getExtension()));
        if ((extensionInCapitals == "C" || extensionInCapitals == "CPP") &&
            !(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                  filePathHandler.getFullPath(), "CP_MEAS") ||
              stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                  filePathHandler.getFullPath(), "CP_LINUX") ||
              stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(filePathHandler.getFullPath(), "CP_TOAM")

                  )) {
            ifstream logStream(file);
            if (logStream.is_open()) {
                AlbaFileReader logFileReader(logStream);
                while (logFileReader.isNotFinished()) {
                    string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
                    string stringToAnalyze(lineInFile);
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "using namespace fw", "");
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "using fw", "");
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "fw::flush", "");
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "fw::MessageBackend", "");
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "fw::MessageFactory", "");
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "fw::MessageLogger", "");
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "fw::StlFileReader", "");
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "fw::ObjectManager", "");
                    stringHelper::transformReplaceStringIfFound(stringToAnalyze, "using CommonLogger = fw::", "");
                    if (stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(stringToAnalyze, "fw::")) {
                        ALBA_PRINT1(filePathHandler.getFullPath());
                        ALBA_PRINT1(lineInFile);
                        cout << "\n";
                        break;
                    }
                }
            }
        }
    }
}

TEST(SampleTest, FindNearEmptyFiles) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(C:\Branches\CP\trunk\SBTS\tcom\C_Application\SC_TCOM)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        string extensionInCapitals(stringHelper::getStringWithCapitalLetters(filePathHandler.getExtension()));
        if (extensionInCapitals == "TXT" || extensionInCapitals == "CMAKE" || extensionInCapitals == "C" ||
            extensionInCapitals == "CPP" || extensionInCapitals == "H" || extensionInCapitals == "HPP") {
            if (!stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                    filePathHandler.getFile(), "CMakeLists.txt") &&
                !stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(
                    filePathHandler.getFile(), "_cppc_sup") &&
                filePathHandler.getFileSizeEstimate() < 50) {
                ALBA_PRINT1(filePathHandler.getFullPath());
            }
        }
    }
}

TEST(SampleTest, FindLongAndShortLogStrings) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(C:\Users\malba\Desktop\Delete\FrameworkLogLengthAnalysis\DMGR_MT_LOGS)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& file : files) {
        ifstream logStream(file);
        if (logStream.is_open()) {
            AlbaFileReader logFileReader(logStream);
            while (logFileReader.isNotFinished()) {
                string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
                unsigned int length(lineInFile.length());
                if (length >= 200) {
                    cout << "Line might be long. Length:[" << length << "] [" << lineInFile << "]\n";
                }
                if (length <= 40 && length > 0) {
                    cout << "Line might be short. Length: " << length << " [" << lineInFile << "]\n";
                }
            }
        }
    }
}

TEST(SampleTest, TuesdayChecklistVideos) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(R"(N:\Downloads\TuesdayChecklist)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& file : files) {
        cout << file << "\n";
    }
}

TEST(SampleTest, ExtractFilesAndCopyLogsForSctTests) {
    AprgFileExtractor fileExtractor("[.]");
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler inputDirectoryPathHandler(R"(C:\ZZZ_SCT_Logs\trunk_fsmr3@120334)");
    AlbaLocalPathHandler outputDirectoryPathHandler(R"(C:\ZZZ_SCT_Logs\trunk_fsmr3@120334_fixed)");
    inputDirectoryPathHandler.findFilesAndDirectoriesOneDepth("*.*", files, directories);

    // extract all relevant files at zip files on depth one
    for (string const& file : files) {
        AlbaLocalPathHandler filePath(file);
        if (filePath.getExtension() == "zip") {
            ALBA_PRINT1(filePath.getFullPath());
            fileExtractor.extractAllRelevantFiles(filePath.getFullPath());
        }
    }

    // copy to correct directory
    files.clear();
    directories.clear();
    inputDirectoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for (string const& file : files) {
        string newFilePath(file);
        stringHelper::transformReplaceStringIfFound(newFilePath, inputDirectoryPathHandler.getFullPath(), "");
        newFilePath =
            stringHelper::getStringAfterThisString(stringHelper::getStringAfterThisString(newFilePath, R"(\)"), R"(\)");
        if (!newFilePath.empty()) {
            AlbaLocalPathHandler newFilePathHandler(outputDirectoryPathHandler.getFullPath() + newFilePath);
            newFilePathHandler.createDirectoriesForNonExisitingDirectories();
            AlbaLocalPathHandler(file).copyToNewFile(newFilePathHandler.getFullPath());
        }
    }
}

TEST(SampleTest, BoolPrintTest) {
    bool printThis(true);
    printf("%d", printThis);
}

TEST(SampleTest, CBeginTest) {
    int foo[] = {10, 20, 30, 40, 50};
    std::vector<int> bar;

    // iterate foo: inserting into bar
    for (auto it = std::cbegin(foo); it != std::cend(foo); ++it) bar.push_back(*it);

    // iterate bar: print contents:
    std::cout << "bar contains:";
    for (auto it = std::cbegin(bar); it != std::cend(bar); ++it) std::cout << ' ' << *it;
    std::cout << '\n';
}

TEST(SampleTest, LrmDirectoriesToFind) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(
        R"(C:\Branches\CP\SystemFrameworkImprovement3\tcom-SystemFrameworkImprovement3-lrm\C_Application\SC_TCOM\CP_LRM\tst)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& directory : directories) {
        cout << directory << "\n";
    }
}

TEST(SampleTest, FormatPrints) {
    AlbaLocalPathHandler pathHandler(R"(C:\ZZZ_Logs\PR400441\LF_DSS_OFF\WholeLogsToAnalyze_NoTimeStamp.log)");
    ofstream formattedLogStream(R"(C:\ZZZ_Logs\PR400441\LF_DSS_OFF\WholeLogsToAnalyze_Sorted.log)");
    ifstream logStream(pathHandler.getFullPath());

    set<string> uniqueAndSortedStrings;
    if (logStream.is_open()) {
        AlbaFileReader logFileReader(logStream);

        while (logFileReader.isNotFinished()) {
            string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            uniqueAndSortedStrings.emplace(lineInFile);
        }
    }
    for (string const& stringInStrings : uniqueAndSortedStrings) {
        formattedLogStream << stringInStrings << "\n";
    }
}

void saveMaxLengthString(string& finalPrint, unsigned int& maxLength, string const& samplePrint) {
    if (samplePrint.length() > maxLength) {
        finalPrint = samplePrint;
        maxLength = samplePrint.length();
    }
}

TEST(SampleTest, FormatPrints) {
    AlbaLocalPathHandler pathHandler(R"(C:\ZZZ_Logs\PR400441\SF_DSS_ON\WholeLogsToAnalyze.log)");
    ofstream formattedLogStream(R"(C:\ZZZ_Logs\PR400441\SF_DSS_ON\WholeLogsToAnalyze_NoTimeStamp.log)");
    ifstream logStream(pathHandler.getFullPath());

    if (logStream.is_open()) {
        AlbaFileReader logFileReader(logStream);

        while (logFileReader.isNotFinished()) {
            string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            string debugPrint = stringHelper::getStringAfterThisString(lineInFile, "DBG/");
            string infoPrint = stringHelper::getStringAfterThisString(lineInFile, "INF/");
            string warningPrint = stringHelper::getStringAfterThisString(lineInFile, "WRN/");
            string errorPrint = stringHelper::getStringAfterThisString(lineInFile, "ERR/");
            string vipPrint = stringHelper::getStringAfterThisString(lineInFile, "VIP/");
            unsigned int maxLength = 0;
            string finalPrint;
            saveMaxLengthString(finalPrint, maxLength, debugPrint);
            saveMaxLengthString(finalPrint, maxLength, infoPrint);
            saveMaxLengthString(finalPrint, maxLength, warningPrint);
            saveMaxLengthString(finalPrint, maxLength, errorPrint);
            saveMaxLengthString(finalPrint, maxLength, vipPrint);
            if (!stringHelper::isWhiteSpace(finalPrint)) {
                formattedLogStream << finalPrint << "\n";
            }
        }
    }
}

struct ThreeLogs {
    string originalLog;
    string log1Log;
    string log2Log;
};

string getNearestLine(vector<string> const& lines, string const& lineInOriginal) {
    string nearestLine;
    int lowestDiff = 0xFFFFFFF;
    for (string const& line : lines) {
        int diffInOriginalAndLine = static_cast<int>(stringHelper::getLevenshteinDistance(lineInOriginal, line));
        if (lowestDiff > diffInOriginalAndLine) {
            nearestLine = line;
            lowestDiff = diffInOriginalAndLine;
        }
    }
    return nearestLine;
}

TEST(SampleTest, LogComparePrints) {
    AlbaLocalPathHandler originalPathHandler(R"(C:\ZZZ_Logs\PR400441\LF_DSS_ON\24518_formatted.log)");
    ifstream originalLogStream(originalPathHandler.getFullPath());
    AlbaLocalPathHandler log1PathHandler(R"(C:\ZZZ_Logs\PR400441\LF_DSS_OFF\24518_formatted.log)");
    ifstream log1LogStream(log1PathHandler.getFullPath());
    AlbaLocalPathHandler log2LcgPathHandler(R"(C:\ZZZ_Logs\PR400441\SF_DSS_ON\24518_formatted.log)");
    ifstream log2LcgLogStream(log2LcgPathHandler.getFullPath());
    ofstream resultsLogStream(R"(C:\ZZZ_Logs\PR381361\Compare\Results.log)");

    vector<string> linesInOriginal;
    vector<string> linesInLog1;
    vector<string> linesInLog2;
    map<int, ThreeLogs> scoreToLogsMap;

    if (originalLogStream.is_open() && log1LogStream.is_open() && log2LcgLogStream.is_open()) {
        AlbaFileReader originalLogFileReader(originalLogStream);
        AlbaFileReader log1LogFileReader(log1LogStream);
        AlbaFileReader log2LcgLogFileReader(log2LcgLogStream);

        while (originalLogFileReader.isNotFinished()) {
            string lineInOriginal(originalLogFileReader.getLineAndIgnoreWhiteSpaces());
            linesInOriginal.emplace_back(lineInOriginal);
        }
        while (log1LogFileReader.isNotFinished()) {
            string lineInLog1(log1LogFileReader.getLineAndIgnoreWhiteSpaces());
            linesInLog1.emplace_back(lineInLog1);
        }
        while (log2LcgLogFileReader.isNotFinished()) {
            string lineInLog2(log2LcgLogFileReader.getLineAndIgnoreWhiteSpaces());
            linesInLog2.emplace_back(lineInLog2);
        }
    }

    unsigned int lineCount = 0;
    unsigned int totalLines = linesInOriginal.size();
    for (string const& lineInOriginal : linesInOriginal) {
        cout << "Percentage: " << (lineCount * 100 / totalLines) << " lineCount: " << lineCount
             << " totalLines: " << totalLines << "\n";
        cout << "Original:  [" << lineInOriginal << "]\n";

        string nearestLineInLog2 = getNearestLine(linesInLog2, lineInOriginal);
        cout << "Log2:      [" << nearestLineInLog2 << "]\n";
        if (!nearestLineInLog2.empty()) {
            int diffInOriginalAndNearestLog2 =
                static_cast<int>(stringHelper::getLevenshteinDistance(lineInOriginal, nearestLineInLog2));
            if (diffInOriginalAndNearestLog2 <= 30) {
                cout << "diffInOriginalAndLog2:    [" << diffInOriginalAndNearestLog2 << "]\n";
                string nearestLineInLog1 = getNearestLine(linesInLog1, lineInOriginal);
                cout << "Log1:      [" << nearestLineInLog1 << "]\n";
                if (!nearestLineInLog1.empty()) {
                    int diffInOriginalAndNearestLog1 =
                        static_cast<int>(stringHelper::getLevenshteinDistance(lineInOriginal, nearestLineInLog1));
                    int finalScore = diffInOriginalAndNearestLog2 + diffInOriginalAndNearestLog1;
                    cout << "Score:     [" << finalScore << "]\n";
                    scoreToLogsMap.emplace(finalScore, ThreeLogs{lineInOriginal, nearestLineInLog1, nearestLineInLog2});
                }
            }
        }
        lineCount++;
    }

    using ThreeLogMapType = map<int, ThreeLogs>;
    using ThreeLogPairType = pair<int, ThreeLogs>;
    for (ThreeLogMapType::reverse_iterator iterator = scoreToLogsMap.rbegin(); iterator != scoreToLogsMap.rend();
         iterator++) {
        ThreeLogPairType const& scoreToLogPair = *iterator;
        cout << "Score:     [" << scoreToLogPair.first << "]\n";
        cout << "Original:  [" << scoreToLogPair.second.originalLog << "]\n";
        cout << "Log1:      [" << scoreToLogPair.second.log1Log << "]\n";
        cout << "Log2:      [" << scoreToLogPair.second.log2Log << "]\n";
        resultsLogStream << "Score:     [" << scoreToLogPair.first << "]\n";
        resultsLogStream << "Original:  [" << scoreToLogPair.second.originalLog << "]\n";
        resultsLogStream << "Log1: [" << scoreToLogPair.second.log1Log << "]\n";
        resultsLogStream << "Log2:    [" << scoreToLogPair.second.log2Log << "]\n";
    }
}

void saveMaxLengthString(string& finalPrint, unsigned int& maxLength, string const& samplePrint) {
    if (samplePrint.length() > maxLength) {
        finalPrint = samplePrint;
        maxLength = samplePrint.length();
    }
}

TEST(SampleTest, FormatPrints) {
    AlbaLocalPathHandler pathHandler(R"(C:\ZZZ_Logs\PR400441\LF_DSS_OFF\24518.log)");
    ofstream formattedLogStream(R"(C:\ZZZ_Logs\PR400441\LF_DSS_OFF\24518_formatted.log)");
    ifstream logStream(pathHandler.getFullPath());

    if (logStream.is_open()) {
        AlbaFileReader logFileReader(logStream);

        while (logFileReader.isNotFinished()) {
            string lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            string debugPrint = stringHelper::getStringAfterThisString(lineInFile, "DBG/");
            string infoPrint = stringHelper::getStringAfterThisString(lineInFile, "INF/");
            string warningPrint = stringHelper::getStringAfterThisString(lineInFile, "WRN/");
            string errorPrint = stringHelper::getStringAfterThisString(lineInFile, "ERR/");
            string vipPrint = stringHelper::getStringAfterThisString(lineInFile, "VIP/");
            unsigned int maxLength = 0;
            string finalPrint;
            saveMaxLengthString(finalPrint, maxLength, debugPrint);
            saveMaxLengthString(finalPrint, maxLength, infoPrint);
            saveMaxLengthString(finalPrint, maxLength, warningPrint);
            saveMaxLengthString(finalPrint, maxLength, errorPrint);
            saveMaxLengthString(finalPrint, maxLength, vipPrint);
            formattedLogStream << finalPrint << "\n";
        }
    }
}

TEST(SampleTest, LrmDirectoriesToFind) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(
        R"(D:\SFI3NotCorrupted\tcom-SystemFrameworkImprovement3-grm\C_Application\SC_TCOM\CP_GRM\tst)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& directory : directories) {
        cout << directory << "\n";
    }
}

TEST(SampleTest, NSAPCloudPrinting) {
    u8 mark[4];
    TTransportLayerAddress nsap{0x35, 0x00, 0x01, 0x0A, 0x48, 0xED, 0x8D, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    CommonClassLib::CNsapHelper::convertNsapToIPv4(nsap, mark);

    for (int i = 0; i < 4; i++) {
        cout << "mark[" << i << "]: " << std::dec << (int)mark[i] << "\n";
    }
}

TEST(SampleTest, Shit) {
    u32 m_bitContainerForAllocations = 1;
    u32 hellomellow = m_bitContainerForAllocations & 0x2;
    cout << "shouldCellBeAllocatedBasedOnDssKepler start:\n";
    cout << "shouldCellBeAllocatedBasedOnDssKepler hellomellow: " << hellomellow << "\n";
    if (m_bitContainerForAllocations & 0x2 != 0) {
        cout << "shouldCellBeAllocatedBasedOnDssKepler true:\n";
    } else {
        cout << "shouldCellBeAllocatedBasedOnDssKepler false:\n";
    }

    u32 resultInU32 = m_bitContainerForAllocations & 0x2;
    bool result = resultInU32;
    if (result) {
        cout << "shouldCellBeAllocatedBasedOnDssKepler corrected true:\n";
    } else {
        cout << "shouldCellBeAllocatedBasedOnDssKepler corrected false:\n";
    }
}

TEST(SampleTest, CounterOfCounts) {
    AlbaLocalPathHandler pathHandler(
        R"(H:\Logs\111_MessagePoolExhaustion\09_09_2018\TC_2_LRM_RL_SETUP_REQ_MSG_queue.log)");
    ifstream queueLogStream(pathHandler.getFullPath());

    map<int, string> highestJumpsQueueLengths;
    map<int, string> highestJumpsMsgQueueingTimes;
    map<int, string> highestJumpsMsgPoolUsages;

    int previousQueueLength(0);
    int previousMsgQueueingTime(0);
    int previousMsgPoolUsage(0);

    if (queueLogStream.is_open()) {
        AlbaFileReader queueLogFileReader(queueLogStream);

        while (queueLogFileReader.isNotFinished()) {
            string lineInFile(queueLogFileReader.getLineAndIgnoreWhiteSpaces());
            int queueLength(stringHelper::convertStringToNumber<int>(
                stringHelper::getNumberAfterThisString(lineInFile, R"(queueLength: )")));
            int msgQueueingTime(stringHelper::convertStringToNumber<int>(
                stringHelper::getNumberAfterThisString(lineInFile, R"(msgQueueingTime: )")));
            int msgPoolUsage(stringHelper::convertStringToNumber<int>(
                stringHelper::getHexNumberAfterThisString(lineInFile, R"(msgPoolUsage: )")));

            highestJumpsQueueLengths.emplace(queueLength - previousQueueLength, lineInFile);
            highestJumpsMsgQueueingTimes.emplace(msgQueueingTime - previousMsgQueueingTime, lineInFile);
            highestJumpsMsgPoolUsages.emplace(msgPoolUsage - previousMsgPoolUsage, lineInFile);

            previousQueueLength = queueLength;
            previousMsgQueueingTime = msgQueueingTime;
            previousMsgPoolUsage = msgPoolUsage;

            if (highestJumpsQueueLengths.size() > 20) {
                highestJumpsQueueLengths.erase(highestJumpsQueueLengths.begin());
            }

            if (highestJumpsMsgQueueingTimes.size() > 20) {
                highestJumpsMsgQueueingTimes.erase(highestJumpsMsgQueueingTimes.begin());
            }

            if (highestJumpsMsgPoolUsages.size() > 20) {
                highestJumpsMsgPoolUsages.erase(highestJumpsMsgPoolUsages.begin());
            }
        }
    }
    cout << "highestQueueLengths\n";
    for (pair<int, string> const& printPair : highestJumpsQueueLengths) {
        cout << "queueLengthJump: " << printPair.first << " Print: [" << printPair.second << "]\n";
    }
    cout << "highestMsgQueueingTimes\n";
    for (pair<int, string> const& printPair : highestJumpsMsgQueueingTimes) {
        cout << "msgQueueingTimeJump: " << printPair.first << " Print: [" << printPair.second << "]\n";
    }
    cout << "highestMsgPoolUsages\n";
    for (pair<int, string> const& printPair : highestJumpsMsgPoolUsages) {
        cout << "msgPoolUsageJump: " << printPair.first << " Print: [" << printPair.second << "]\n";
    }
}

TEST(SampleTest, MessageIdCounter) {
    AlbaLocalPathHandler pathHandler(
        R"(H:\Logs\111_MessagePoolExhaustion\09_09_2018\TC_2_LRM_RL_SETUP_REQ_MSG_queue.log)");
    ifstream queueLogStream(pathHandler.getFullPath());

    map<unsigned int, unsigned int> lastMsgRcvdToCount;
    map<unsigned int, unsigned int> lastMsgSentToCount;
    map<unsigned int, unsigned int> lastInternalMsgToCount;
    map<unsigned int, string> highestMsgQueueingTime;
    map<unsigned int, string> highestQueueLength;

    if (queueLogStream.is_open()) {
        AlbaFileReader queueLogFileReader(queueLogStream);

        while (queueLogFileReader.isNotFinished()) {
            string lineInFile(queueLogFileReader.getLineAndIgnoreWhiteSpaces());
            unsigned int lastMsgRcvd(stringHelper::convertHexStringToNumber<unsigned int>(
                stringHelper::getHexNumberAfterThisString(lineInFile, R"(lastMsgRcvd: 0x)")));
            unsigned int lastMsgSent(stringHelper::convertHexStringToNumber<unsigned int>(
                stringHelper::getHexNumberAfterThisString(lineInFile, R"(lastMsgSent: 0x)")));
            unsigned int lastInternalMsg(stringHelper::convertHexStringToNumber<unsigned int>(
                stringHelper::getHexNumberAfterThisString(lineInFile, R"(lastInternalMsg: 0x)")));
            if (lastMsgRcvdToCount.find(lastMsgRcvd) != lastMsgRcvdToCount.cend()) {
                lastMsgRcvdToCount[lastMsgRcvd]++;
            } else {
                lastMsgRcvdToCount[lastMsgRcvd] = 1;
            }
            if (lastMsgSentToCount.find(lastMsgSent) != lastMsgSentToCount.cend()) {
                lastMsgSentToCount[lastMsgSent]++;
            } else {
                lastMsgSentToCount[lastMsgSent] = 1;
            }
            if (lastInternalMsgToCount.find(lastInternalMsg) != lastInternalMsgToCount.cend()) {
                lastInternalMsgToCount[lastInternalMsg]++;
            } else {
                lastInternalMsgToCount[lastInternalMsg] = 1;
            }
        }
    }
    cout << "lastMsgRcvdToCount\n";
    for (pair<unsigned int, unsigned int> const& printPair : lastMsgRcvdToCount) {
        cout << "MessageId: " << hex << printPair.first << " Count: " << dec << printPair.second << "\n";
    }
    cout << "lastMsgSentToCount\n";
    for (pair<unsigned int, unsigned int> const& printPair : lastMsgSentToCount) {
        cout << "MessageId: " << hex << printPair.first << " Count: " << dec << printPair.second << "\n";
    }
    cout << "lastInternalMsgToCount\n";
    for (pair<unsigned int, unsigned int> const& printPair : lastInternalMsgToCount) {
        cout << "MessageId: " << hex << printPair.first << " Count: " << dec << printPair.second << "\n";
    }
}

TEST(SampleTest, ConstTest) {
#define GLO_NULL 1
    void* pointer = (void*)GLO_NULL;
    if (pointer == (void*)GLO_NULL) {
        cout << "GLO NULL works! \n";
    }
    if (pointer == nullptr) {
        cout << "nullptr works! \n";
    }
}

class UglyDataType {
public:
    unsigned int* uglyPointer;  // this is allocated at some point
};
void function1(UglyDataType input) {
    input.uglyPointer = nullptr;  // this will compile
}
void function2(UglyDataType const input)  // Since its mandatory to put const for all parameters we will notice the
    compiler error.{
    input.uglyPointer = nullptr;  // this will not compile
}

TEST(SampleTest, ConstTest) {
    UglyDataType input;
    function2(input);
}

class SampleClass {
public:
    SampleClass(unsigned int const sampleParameter) : m_sampleParameter(sampleParameter) {}
    unsigned int getSampleParameter() const { return m_sampleParameter; }

private:
    unsigned int m_sampleParameter;
};

using SampleClasses = std::vector<SampleClass>;

template <typename T, typename ContainerT, class OperationT>
T sumSample(ContainerT const& container, OperationT const& operation) {
    return std::accumulate(
        container.begin(), container.end(), T(),
        [&operation](T sum, typename ContainerT::value_type const& content) { return sum + (content.*operation)(); });
    //                           boost::bind(std::plus<T>(), 1, boost::bind(operation, 2)));
    // return std::accumulate(container.begin(), container.end(), T(),
    // std::bind(std::plus<T>(), 1, std::bind(static_cast<typename T()>(OperationT::operation),
2)));
}

TEST(SampleTest, BindingToClassMethod) {
    SampleClasses sampleContainer;
    sampleContainer.emplace_back(1);
    sampleContainer.emplace_back(2);
    sampleContainer.emplace_back(3);

    EXPECT_EQ(6, sumSample<unsigned int>(sampleContainer, &SampleClass::getSampleParameter));
}

TEST(SampleTest, CompareProfileToLogsInStreamRoutingPoC) {
    AlbaLocalPathHandler pathHandler(R"(D:\userdata\malba\Desktop\StreamPoC\GSM\WG1_5_GSM_v2.json)");
    ifstream profileStream(pathHandler.getFullPath());

    map<unsigned int, string> ratTypeToAddressMap;
    if (profileStream.is_open()) {
        AlbaFileReader profileFileReader(profileStream);
        string startString(R"(					")");
        string endString(R"(					},)");
        string axcresblockStartString(R"(				"axcresblock": {)");
        string axcresblockendString(R"(				},)");
        unsigned int axcresblockState = 0;
        unsigned int streamState = 0;
        unsigned int currentRp3NodeAddress = 0;
        string currentRatType;

        while (profileFileReader.isNotFinished()) {
            string lineInFile(profileFileReader.getLine());
            if (lineInFile.substr(0, axcresblockStartString.length()) == axcresblockStartString) {
                axcresblockState = 1;
            } else if (lineInFile.substr(0, axcresblockendString.length()) == axcresblockendString) {
                axcresblockState = 2;
            }

            if (axcresblockState == 1) {
                if (lineInFile.substr(0, startString.length()) == startString) {
                    streamState = 1;
                } else if (lineInFile.substr(0, endString.length()) == endString) {
                    streamState = 2;
                }
            }
            if (streamState == 1) {
                if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"("type": ")")) {
                    currentRatType = stringHelper::getStringInBetweenTwoStrings(lineInFile, R"("type": ")", R"(")");
                }
                if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"("rp3NodeAddress": )")) {
                    currentRp3NodeAddress = stringHelper::convertStringToNumber<unsigned int>(
                        stringHelper::getStringInBetweenTwoStrings(lineInFile, R"("rp3NodeAddress": )", R"(,)"));
                }
            } else if (streamState == 2) {
                // cout<<currentRp3NodeAddress<<"   "<<currentRatType<<"\n";
                ratTypeToAddressMap[currentRp3NodeAddress] = currentRatType;
                currentRatType = "unknown";
                currentRp3NodeAddress = 0;
            }
        }
    }
}

TEST(SampleTest, CompareProfileToLogsInStreamRoutingPoC) {
    AlbaLocalPathHandler pathHandler(R"(D:\userdata\malba\Desktop\StreamPoC\GSM\WG1_5_GSM_v2.json)");
    ifstream profileStream(pathHandler.getFullPath());

    map<unsigned int, string> ratTypeToAddressMap;
    if (profileStream.is_open()) {
        AlbaFileReader profileFileReader(profileStream);
        string startString(R"(					")");
        string endString(R"(					},)");
        string axcresblockStartString(R"(				"axcresblock": {)");
        string axcresblockendString(R"(				},)");
        unsigned int axcresblockState = 0;
        unsigned int streamState = 0;
        unsigned int currentRp3NodeAddress = 0;
        string currentRatType;

        while (profileFileReader.isNotFinished()) {
            string lineInFile(profileFileReader.getLine());
            if (lineInFile.substr(0, axcresblockStartString.length()) == axcresblockStartString) {
                axcresblockState = 1;
            } else if (lineInFile.substr(0, axcresblockendString.length()) == axcresblockendString) {
                axcresblockState = 2;
            }

            if (axcresblockState == 1) {
                if (lineInFile.substr(0, startString.length()) == startString) {
                    streamState = 1;
                } else if (lineInFile.substr(0, endString.length()) == endString) {
                    streamState = 2;
                }
            }
            if (streamState == 1) {
                if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"("type": ")")) {
                    currentRatType = stringHelper::getStringInBetweenTwoStrings(lineInFile, R"("type": ")", R"(")");
                }
                if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"("rp3NodeAddress": )")) {
                    currentRp3NodeAddress = stringHelper::convertStringToNumber<unsigned int>(
                        stringHelper::getStringInBetweenTwoStrings(lineInFile, R"("rp3NodeAddress": )", R"(,)"));
                }
            } else if (streamState == 2) {
                // cout<<currentRp3NodeAddress<<"   "<<currentRatType<<"\n";
                ratTypeToAddressMap[currentRp3NodeAddress] = currentRatType;
                currentRatType = "unknown";
                currentRp3NodeAddress = 0;
            }
        }
    }
    AlbaLocalPathHandler murrkuLogsPathHandler(R"(D:\userdata\malba\Desktop\StreamPoC\GSM\analyzeMurkkuLogs.txt)");
    ifstream murrkuLogsStream(murrkuLogsPathHandler.getFullPath());

    if (murrkuLogsStream.is_open()) {
        AlbaFileReader murrkuLogsFileReader(murrkuLogsStream);
        while (murrkuLogsFileReader.isNotFinished()) {
            string lineInFile(murrkuLogsFileReader.getLineAndIgnoreWhiteSpaces());
            if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, R"(bbBusAddr: )")) {
                unsigned int rp3NodeAddress(stringHelper::convertStringToNumber<unsigned int>(
                    stringHelper::getStringInBetweenTwoStrings(lineInFile, R"(bbBusAddr: )", R"( )")));
                // cout<<rp3NodeAddress<<"\n";
                cout << lineInFile << "   [" << ratTypeToAddressMap[rp3NodeAddress] << "]\n";
            }
        }
    }
}

TEST(SampleTest, SaveGetDifferenceFromGreaterMultipleToCsv) {
    AlbaLocalPathHandler pathHandler(R"(C:\APRG\GetDifferenceFromGreaterMultipleGraph.txt)");
    ofstream csvFile(pathHandler.getFullPath());

    csvFile << "size = [\n";
    for (unsigned int multiple = 0; multiple < 20; multiple++) {
        for (unsigned int number = 0; number < 20; number++) {
            unsigned int size(
                mathHelper::getDifferenceFromGreaterMultiple(multiple, number) +
                mathHelper::getNumberOfMultiplesInclusive(multiple, number));
            csvFile << size << " ";
        }
        csvFile << ";\n";
    }
    csvFile << "]\n";
}

TEST(SampleTest, MessageIds_test) {
    AlbaLocalPathHandler pathHandler(
        R"(D:\Branches\trunk\I_Interface\Private\SC_TCOM\Messages\MessageId_TcomTcom.sig)");
    AlbaLocalPathHandler pathHandler2(
        R"(D:\Branches\trunk\wbts_integration\I_Interface\Application_Env\Wn_Env\Bs_Env\Messages\MessageId_TcomDsp.h)");
    AlbaLocalPathHandler pathHandler3(R"(D:\ZZZ_Logs\PR212221\LRMJairus\MessageHistoryBeforeCorruption.txt)");

    ifstream tcomTcomFile(pathHandler.getFullPath());
    ifstream tcomDspile(pathHandler2.getFullPath());
    ifstream messageMapFile(pathHandler3.getFullPath());

    map<unsigned int, string> messageIds;
    if (tcomTcomFile.is_open()) {
        AlbaFileReader tcomTcomFileReader(tcomTcomFile);
        while (tcomTcomFileReader.isNotFinished()) {
            string lineInFile(tcomTcomFileReader.getLineAndIgnoreWhiteSpaces());
            if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "#define")) {
                string messageIdString(stringHelper::getStringInBetweenTwoStrings(lineInFile, "(", ")"));
                bool isTcomBasePrintVisible =
                    stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "TC_TCOM_BASE");
                unsigned int messageId = stringHelper::convertHexStringToNumber<unsigned int>(
                    stringHelper::getHexNumberAfterThisString(messageIdString, "0x"));
                string messageName = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
                    stringHelper::getStringInBetweenTwoStrings(lineInFile, "#define", "("));
                if (messageId > 0) {
                    if (isTcomBasePrintVisible) {
                        messageId = 0x6800 + messageId;
                    }
                    // cout<<"isTcomBasePrintVisible"<<isTcomBasePrintVisible<<" messageId: "<<hex<<messageId<<"
                messageName:
                    "<<dec<<messageName<<"\n "; messageIds.emplace(messageId, messageName);
                }
            }
        }
    }

    if (tcomDspile.is_open()) {
        AlbaFileReader tcomDspFileReader(tcomDspile);
        while (tcomDspFileReader.isNotFinished()) {
            string lineInFile(tcomDspFileReader.getLineAndIgnoreWhiteSpaces());
            if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "#define")) {
                string messageIdString(stringHelper::getStringInBetweenTwoStrings(lineInFile, "(", ")"));
                bool isTcomBasePrintVisible =
                    stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "TC_DSP_BASE");
                unsigned int messageId = stringHelper::convertHexStringToNumber<unsigned int>(
                    stringHelper::getHexNumberAfterThisString(messageIdString, "0x"));
                string messageName = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
                    stringHelper::getStringInBetweenTwoStrings(lineInFile, "#define", "("));
                if (messageId > 0) {
                    if (isTcomBasePrintVisible) {
                        messageId = 0x5000 + messageId;
                    }
                    // cout<<"isTcomBasePrintVisible"<<isTcomBasePrintVisible<<" messageId: "<<hex<<messageId<<"
                messageName:
                    "<<dec<<messageName<<"\n "; messageIds.emplace(messageId, messageName);
                }
            }
        }
    }

    if (messageMapFile.is_open()) {
        AlbaFileReader messageMapFileReader(messageMapFile);
        while (messageMapFileReader.isNotFinished()) {
            string lineInFile(messageMapFileReader.getLineAndIgnoreWhiteSpaces());
            unsigned int messageId = stringHelper::convertHexStringToNumber<unsigned int>(
                stringHelper::getHexNumberAfterThisString(lineInFile, "msgid:0x"));
            unsigned int offset = stringHelper::convertHexStringToNumber<unsigned int>(
                stringHelper::getHexNumberAfterThisString(lineInFile, "off:0x"));
            unsigned int messageSize = stringHelper::convertStringToNumber<unsigned int>(
                stringHelper::getHexNumberAfterThisString(lineInFile, "msgsize:"));
            unsigned int messagePoolCorruptionAddress = 0x3fdb00;
            int distance = (int)offset + (int)messageSize - (int)messagePoolCorruptionAddress;
            if (messageIds.find(messageId) != messageIds.end()) {
                cout << "distance of the end of the message to corruption: " << setw(5) << distance
                     << ", messageId:
                        "<<hex<<messageId<<",
                    messageName : "<<messageIds[messageId] << ",
                                  offset + messageSize : 0x "<<offset+messageSize<<dec<<"\n ";
            } else {
                // cout<<lineInFile<<"\n";
            }
        }
    }
}

bool isLeapYear(unsigned int const year) {
    bool result(true);
    if (year % 4 != 0)
        result = false;
    else if (year % 100 != 0)
        result = true;
    else if (year % 400 != 0)
        result = false;
    return result;
}

unsigned int getMaximumDaysInAMonth(unsigned int const monthIndex, unsigned int const year) {
    unsigned int maximumDaysOfTheMonth = 31;
    if (monthIndex == 3 || monthIndex == 5 || monthIndex == 8 || monthIndex == 10) {
        maximumDaysOfTheMonth = 30;
    } else if (monthIndex == 1) {
        if (isLeapYear(year)) {
            maximumDaysOfTheMonth = 29;
        } else {
            maximumDaysOfTheMonth = 28;
        }
    }
    ALBA_DEBUG_PRINT2(monthIndex, maximumDaysOfTheMonth);
    return maximumDaysOfTheMonth;
}

int getNumberOfLeapYears(unsigned int const year) {
    int beforeThisYear = year - 1;
    //
cout<<"beforeThisYear"<<(beforeThisYear/4)<<","<<(beforeThisYear/100)<<","<<(beforeThisYear/400)<<","<<(beforeThisYear/4)+(beforeThisYear/100)<<","<<(beforeThisYear/4)+(beforeThisYear/100)+(beforeThisYear/400)<<(beforeThisYear/4)+(beforeThisYear/100)+(beforeThisYear/400)+1<<"\n";
    return (beforeThisYear / 4) - (beforeThisYear / 100) + (beforeThisYear / 400) + 1;
}

TEST(SampleTest, DateTimeAlgorithm) {
    AlbaLocalPathHandler pathHandler(R"(C:\APRG\DateMonthStudy2.csv)");
    ofstream fileOutput(pathHandler.getFullPath());

    fileOutput << "month,days\n";

    unsigned int numberOfDays = 0;
    for (unsigned int month = 0; month < 12; month++) {
        fileOutput << month << "," << (bool)(numberOfDays & 2) << "\n";
        numberOfDays += getMaximumDaysInAMonth(month, 1);
    }
}

u32 calculateShiftDelayedSfn(u32 const currentSfn, u32 const calculatedSfn) {
    const u32 RADIO_FRAME_CYCLE = 4096;
    const u32 MAX_FRAME_NUMBER = 4095;
    const u32 MAX_NUM_OF_TTI = 8;
    const u32 SFN_LOW_LIMIT = 12;
    const u32 SFN_HIGH_LIMIT = 220;

    const u32 limit = (currentSfn + SFN_LOW_LIMIT) % RADIO_FRAME_CYCLE;
    u32 tempSfn = calculatedSfn;
    cout << "tempSfn" << tempSfn << "\n";
    cout << "limit" << limit << "\n";
    while (tempSfn > limit) {
        if (tempSfn < MAX_NUM_OF_TTI) {
            break;
        }
        tempSfn = (tempSfn + MAX_NUM_OF_TTI) % RADIO_FRAME_CYCLE;
    }
    cout << "tempSfn" << tempSfn << "\n";
    cout << "limit" << limit << "\n";
    while (tempSfn < limit) {
        if (limit > (MAX_FRAME_NUMBER - MAX_NUM_OF_TTI) && tempSfn < MAX_NUM_OF_TTI) {
            cout << "condition" << MAX_FRAME_NUMBER - MAX_NUM_OF_TTI << "\n";
            cout << "tempSfnInside2" << tempSfn << "\n";
            break;
        }
        cout << "tempSfnInside" << tempSfn << "\n";
        tempSfn = (tempSfn + MAX_NUM_OF_TTI) % (RADIO_FRAME_CYCLE);
    }
    cout << "tempSfn" << tempSfn << "\n";
    cout << "limit" << limit << "\n";
    return tempSfn;
}

u32 calculateShiftDelayedSfnNew(u32 const currentSfn, u32 const calculatedSfn) {
    const u32 RADIO_FRAME_CYCLE = 4096;
    const u32 MAX_FRAME_NUMBER = 4095;
    const u32 MAX_NUM_OF_TTI = 8;
    const u32 SFN_LOW_LIMIT = 12;
    const u32 SFN_HIGH_LIMIT = 220;

    const u32 limit = (currentSfn + SFN_LOW_LIMIT) % RADIO_FRAME_CYCLE;
    u32 ttiAlignmentValueForCalculatedSfn = calculatedSfn % MAX_NUM_OF_TTI;
    u32 ttiAlignmentValueForLimit = limit % MAX_NUM_OF_TTI;
    u32 shiftedSfn = 0;
    if (ttiAlignmentValueForCalculatedSfn == ttiAlignmentValueForLimit) {
        shiftedSfn = limit;
    } else if (ttiAlignmentValueForCalculatedSfn > ttiAlignmentValueForLimit) {
        shiftedSfn = limit + ttiAlignmentValueForCalculatedSfn - ttiAlignmentValueForLimit;
    } else if (ttiAlignmentValueForCalculatedSfn < ttiAlignmentValueForLimit) {
        shiftedSfn = limit + ttiAlignmentValueForCalculatedSfn - ttiAlignmentValueForLimit + MAX_NUM_OF_TTI;
    }
    shiftedSfn = shiftedSfn % RADIO_FRAME_CYCLE;
    return shiftedSfn;
}

TEST(SampleTest, RlhBug) { calculateShiftDelayedSfn(4076, 0); }

TEST(SampleTest, DISABLED_ComparisonOfResultsOfTwoAlgorithms) {
    AlbaLocalPathHandler pathOfNewAlgorithm(R"(D:\userdata\malba\Desktop\Prontos\PR235148\NewResults.csv)");
    AlbaLocalPathHandler pathOfOldAlgorithm(R"(D:\userdata\malba\Desktop\Prontos\PR235148\OldResults.csv)");

    ifstream newAlgoResultFile(pathOfNewAlgorithm.getFullPath());
    ifstream oldAlgoResultFile(pathOfOldAlgorithm.getFullPath());
    AlbaFileReader newAlgoReader(newAlgoResultFile);
    AlbaFileReader oldAlgoReader(oldAlgoResultFile);

    while (newAlgoReader.isNotFinished() || oldAlgoReader.isNotFinished()) {
        string lineInFileInNewAlgo(newAlgoReader.getLineAndIgnoreWhiteSpaces());
        string lineInFileInOldAlgo(oldAlgoReader.getLineAndIgnoreWhiteSpaces());
        if (lineInFileInNewAlgo != lineInFileInOldAlgo) {
            cout << "lineInFileInNewAlgo:[" << lineInFileInNewAlgo << "]\n";
            cout << "lineInFileInOldAlgo:[" << lineInFileInOldAlgo << "]\n";
            // break;
        }
    }
}

TEST(SampleTest, DISABLED_RlhNewLogic) {
    AlbaLocalPathHandler pathHandler(R"(D:\userdata\malba\Desktop\Prontos\PR235148\NewResults.csv)");
    ofstream fileOutput(pathHandler.getFullPath());

    fileOutput << "CurrentSfn,CalculatedSfn,ShiftedSfn\n";
    for (u32 currentSfn = 0; currentSfn <= 4096; currentSfn++) {
        for (u32 calculatedSfn = 0; calculatedSfn <= 4096; calculatedSfn++) {
            fileOutput << currentSfn << "," << calculatedSfn << ","
                       << calculateShiftDelayedSfnNew(currentSfn, calculatedSfn) << "\n";
        }
    }
}

TEST(SampleTest, DISABLED_RlhOldLogic) {
    AlbaLocalPathHandler pathHandler(R"(D:\userdata\malba\Desktop\Prontos\PR235148\OldResults.csv)");
    ofstream fileOutput(pathHandler.getFullPath());

    fileOutput << "CurrentSfn,CalculatedSfn,ShiftedSfn\n";
    for (u32 currentSfn = 0; currentSfn <= 4096; currentSfn++) {
        for (u32 calculatedSfn = 0; calculatedSfn <= 4096; calculatedSfn++) {
            fileOutput << currentSfn << "," << calculatedSfn << ","
                       << calculateShiftDelayedSfn(currentSfn, calculatedSfn) << "\n";
        }
    }
}

TEST(SampleTest, FilesToFind) {
    ListOfPaths files;
    ListOfPaths directories;
    AlbaLocalPathHandler pathHandler(
        R"(D:\ZZZ_Logs\PR224369_NEWEST\WBTS17vsWBTS18\WBTS18Second\trace_TUPCexe_Conman_EU_1448_1494233464)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for (string const& file : files) {
        AlbaLocalPathHandler filePathHandler(file);
        cout<<R"(./decodeTrace )"<<filePathHandler.getFilenameOnly()<<R"(.log SS_TUPC addr2line)\n";
        cout<<R"(./flameGraph )"<<filePathHandler.getFilenameOnly()<<R"(.log_decode >
)"<<filePathHandler.getFilenameOnly()<<R"(.log_flame)\n"; cout<<R"(cat
)"<<filePathHandler.getFilenameOnly()<<R"(.log_flame ~/flamegraphs/FlameGraph-master/stackcollapse-perf.pl |
~/flamegraphs/FlameGraph-master/flamegraph.pl >
generatedflamegraphs2/)"<<filePathHandler.getFilenameOnly()<<R"(.svg)\n";
    }
}


TEST(SampleTest, MessageId_TcomTcom_test)
{
    AlbaLocalPathHandler
pathHandler(R"(D:\Branches\trunk\I_Interface\Private\SC_TCOM\Messages\MessageId_TcomTcom.sig)");
        AlbaLocalPathHandler pathHandler2(R"(D:\userdata\malba\Desktop\SCTRoutes\MessageId_TcomTcom_xml_format.txt)");
        AlbaLocalPathHandler pathHandler3(R"(D:\userdata\malba\Desktop\SCTRoutes\Unedited\routeList_VM.xml)");
        AlbaLocalPathHandler pathHandler4(R"(D:\userdata\malba\Desktop\SCTRoutes\MessageId_comparison.csv)");

        ifstream tcomTcomFile(pathHandler.getFullPath());
        ifstream routeListFile(pathHandler3.getFullPath());
        ofstream xmlFormattedFile(pathHandler2.getFullPath());
        ofstream messageIdComparisonFile(pathHandler4.getFullPath());

        xmlFormattedFile << "<messages>\n";

        map<unsigned int, string> tcomTcomMessageIds;
        set<unsigned int> routeListMessageIds;
        if (tcomTcomFile.is_open()) {
            AlbaFileReader tcomTcomFileReader(tcomTcomFile);
            while (tcomTcomFileReader.isNotFinished()) {
                string lineInFile(tcomTcomFileReader.getLineAndIgnoreWhiteSpaces());
                if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "#define")) {
                    string messageIdString(stringHelper::getStringInBetweenTwoStrings(lineInFile, "(", ")"));
                    bool isTcomBasePrintVisible =
                        stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "TC_TCOM_BASE");
                    unsigned int messageId = stringHelper::convertHexStringToNumber<unsigned int>(
                        stringHelper::getHexNumberAfterThisString(messageIdString, "0x"));
                    string messageName = stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(
                        stringHelper::getStringInBetweenTwoStrings(lineInFile, "#define", "("));
                    if (messageId > 0) {
                        if (isTcomBasePrintVisible) {
                            messageId = 0x6800 + messageId;
                        }
                        cout << "isTcomBasePrintVisible" << isTcomBasePrintVisible << " messageId: " << messageId
                             << " messageName:
                                "<<messageName<<"\n
                            "; tcomTcomMessageIds.emplace(messageId, messageName); xmlFormattedFile<<"\t<message>\n ";
                            xmlFormattedFile
                             << "\t\t<type>" << messageId << "</type>\n";
                        xmlFormattedFile << "\t</message>\n";
                    }
                }
            }
        }
        xmlFormattedFile << "</messages>\n";

        messageIdComparisonFile << "messageId,isExistInRouteList,isExistInTcomTcom,messageName\n";

        bool isMessageSpace;
        if (routeListFile.is_open()) {
            AlbaFileReader routeListFileReader(routeListFile);
            while (routeListFileReader.isNotFinished()) {
                string lineInFile(routeListFileReader.getLineAndIgnoreWhiteSpaces());

                if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "<message>")) {
                    isMessageSpace = true;
                }

                if (isMessageSpace &&
                    stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "<type>")) {
                    unsigned int messageId = stringHelper::convertStringToNumber<unsigned int>(
                        stringHelper::getStringInBetweenTwoStrings(lineInFile, "<type>", "</type>"));
                    if (messageId > 0) {
                        routeListMessageIds.emplace(messageId);
                    }
                    // cout<<"messageId:"<<messageId<<"\n";
                }

                if (stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(lineInFile, "</message>")) {
                    isMessageSpace = false;
                }
            }
        }
        for (unsigned int i = 0; i < 0xFFFF; i++) {
            bool isExistInRouteList = routeListMessageIds.count(i) > 0;
            map<unsigned int, string>::iterator tcomTcomMessageIdIterator = tcomTcomMessageIds.find(i);
            bool isExistInTcomTcom = tcomTcomMessageIdIterator != tcomTcomMessageIds.end();
            if (!isExistInRouteList != !isExistInTcomTcom) {
                messageIdComparisonFile << i << "," << isExistInRouteList << "," << isExistInTcomTcom;
                if (isExistInTcomTcom) {
                    messageIdComparisonFile << ",MessageName:[" << tcomTcomMessageIdIterator->second << "]";
                }
                messageIdComparisonFile << "\n";
            }
        }
    }

    TEST(SampleTest, DISABLED_SampleTest1) { QuickestWayToProgram entity; }

    TEST(SampleTest, DISABLED_SampleTest2) {
        AlbaLocalPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\RAN2861MegaplexerHang\WiresharkMegaPlexerDump.txt)");
        AlbaLocalPathHandler pathHandler2(
            R"(D:\W\ZZZ_Useless_Logs\RAN2861MegaplexerHang\WiresharkMegaPlexerDumpFixed.txt)");

        ifstream wiresharkDumpFile(pathHandler.getFullPath());
        ofstream wiresharkDumpFileFixed(pathHandler2.getFullPath(), ofstream::binary);
        if (wiresharkDumpFile.is_open()) {
            AlbaFileReader wiresharkDumpFileReader(wiresharkDumpFile);
            while (wiresharkDumpFileReader.isNotFinished()) {
                string lineInFile(wiresharkDumpFileReader.getLineAndIgnoreWhiteSpaces());
                string hexDump = lineInFile;
                if (hexDump.length() > 10) {
                    hexDump = lineInFile.substr(10);
                    if (hexDump.length() > 48) {
                        hexDump = hexDump.substr(0, 48);
                    }
                }
                hexDump = stringHelper::getStringWithoutWhiteSpace(hexDump);

                string byteString;
                int state = 0;
                int count = 0;
                for (char const currentCharacter : hexDump) {
                    if (state == 0) {
                        byteString += currentCharacter;
                        state = 1;
                    } else {
                        byteString += currentCharacter;
                        unsigned char byteValue = stringHelper::convertHexStringToNumber<unsigned char>(byteString);
                        // cout<<(unsigned int)byteValue<<"\n";
                        wiresharkDumpFileFixed << byteValue;
                        byteString.clear();
                        state = 0;
                    }
                }
            }
        }
    }

    TEST(SampleTest, DISABLED_WrcTest) {
        int power = 0xFFFFF205;
        cout.precision(10);
        cout << "integer:" << power << "\n";
        cout << "double:" << (double)power << "\n";
    }

    void checkTrace();

    void checkTrace() {
        AlbaLocalPathHandler pathHandler(R"(D:\W\ZZZ_Useless_Logs\RAN2861_slow\PS
NRT\1100_MegaPlexer\Ip_10.68.159.157_41786_544_160706_110531.codec.wtbin)");
        ifstream megaplexerStream(pathHandler.getFullPath(), ifstream::binary);
        if (megaplexerStream.is_open()) {
            char fourBytes[4];
            megaplexerStream.read(fourBytes, 4);
            // cout<<"fourbytes"<<(int)fourBytes[0]<<(int)fourBytes[1]<<(int)fourBytes[2]<<(int)fourBytes[3]<<"\n";
            if (!(fourBytes[0] == 0x0A && fourBytes[1] == 0x0B && fourBytes[2] == 0x0C && fourBytes[3] == 0x0D)) {
                cout << "What the hell is this?" << megaplexerStream.tellg() << "\n";
            }
            megaplexerStream.read(fourBytes, 4);
            int size = ((unsigned int)fourBytes[0] << 24) | ((unsigned int)fourBytes[1] << 16) |
                       ((unsigned int)fourBytes[2] << 8) | ((unsigned int)fourBytes[3]);
            megaplexerStream.seekg(size - 4, ios_base::cur);
            cout << "size" << size << "\n";
        }
    }

    TEST(SampleTest, DISABLED_ConfirmatoryTest) { checkTrace(); }

    TEST(SampleTest, DISABLED_VectorAccumulate) {
        std::vector<int> test({5, 6, 7, 8});
        std::vector<int> transfer =
            std::accumulate(test.begin(), test.end(), std::vector<int>{}, [](std::vector<int> const& ref, int a) {
                std::vector<int> r(ref);
                r.emplace_back(a);
                return r;
            });
    }

    TEST(SampleTest, DISABLED_GenerateSupplementarySacksHpp) {
        AlbaLocalPathHandler currentDirectory(AlbaLocalPathHandler::createPathHandlerForDetectedPath());
        AlbaLocalPathHandler supplementaryDirectory(currentDirectory.getDirectory() + R"(\SupplementarySacks\)");
        AlbaLocalPathHandler supplementaryHeaderFilePath(
            currentDirectory.getDirectory() + R"(\SupplementarySacks.hpp)");
        ListOfPaths files;
        ListOfPaths directories;
        supplementaryDirectory.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

        ofstream supplementaryHeaderFile(supplementaryHeaderFilePath.getFullPath());
        for (string const& file : files) {
            AlbaLocalPathHandler filePath(file);
            supplementaryHeaderFile << "#include <" << filePath.getFile() << ">\n";
        }
    }

    TEST(SampleTest, DISABLED_GenerateFeatureSpecificComponentFiles) {
        AlbaLocalPathHandler currentDirectory(AlbaLocalPathHandler::createPathHandlerForDetectedPath());
        AlbaLocalPathHandler featureSpecificDirectory(currentDirectory.getDirectory());

        ifstream componentNameFile(featureSpecificDirectory.getFullPath() + "ComponentName.hpp");
        ofstream addComponentFile(featureSpecificDirectory.getFullPath() + "AddComponent.hpp");
        ofstream componentsIncludesFile(featureSpecificDirectory.getFullPath() + "ComponentsIncludes.hpp");
        ofstream convertToStringComponentNameFile(
            featureSpecificDirectory.getFullPath() + "ConvertToStringComponentName.hpp");

        AlbaFileReader componentNameFileReader(componentNameFile);
        while (componentNameFileReader.isNotFinished()) {
            string componentName(componentNameFileReader.getLineAndIgnoreWhiteSpaces());
            stringHelper::transformReplaceStringIfFound(componentName, ",", "");
            if (!componentName.empty()) {
                addComponentFile << R"(ADD_COMPONENT(ComponentName::)" << componentName << ", " << componentName
                                 << ")\n";
                componentsIncludesFile << R"(#include <RAN3374/Components/)" << componentName << ".hpp\n";
                convertToStringComponentNameFile << R"(GET_ENUM_STRING(ComponentName::)" << componentName << ")\n";
            }
        }
    }

    TEST(SampleTest, DISABLED_CloudPrinting) {
        char payloadPtr[40];
        int payloadSize = 40;
        std::stringstream line;
        line.str("HEX DUMP: ");
        for (int i = 0; i < payloadSize; i++) {
            char* charPayloadPtr = (char*)payloadPtr;
            unsigned int byte = charPayloadPtr[i] & 0xFF;
            line << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte << " ";
            if (i % 32 == 31) {
                cout << line.str() << "\n";
                line.str("HEX DUMP: ");
            }
        }
        if (!line.str().empty()) {
            cout << line.str() << "\n";
            line.str("");
        }
    }

    TEST(SampleTest, DISABLED_NSAPCloudPrinting) {
        u8 mark[4] = {0xA, 0x45, 0x1A, 0x1A};
        TTransportLayerAddress nsap;
        CommonClassLib::CNsapHelper::convertIPv4toNsap(mark, nsap);

        for (int i = 0; i < 20; i++) {
            cout << "nsap[" << i << "]: " << std::hex << (int)nsap[i] << "\n";
        }
    }

    TEST(SampleTest, DISABLED_u32toi32) {
        typedef unsigned int u32;
        typedef u32 TCounter;
        typedef i32 TPowerLevel;

        TPowerLevel powerLevel1, powerLevel2;
        TCounter test;

        powerLevel1 = -50;
        test = powerLevel1;
        powerLevel2 = test;

        cout << "PowerLevel1" << powerLevel1 << "  PowerLevel2" << powerLevel2 << "  test" << test << "\n";
    }

    TEST(SampleTest, DISABLED_RhapsodyShit) {
        class OMThread {
        public:
            int m_param2;
            virtual int getSize() { return sizeof(*this); }
            virtual int execute() { cout << "OMThread: execute\n"; }
        };
        class CMessageReceiver : public OMThread {
        public:
            int m_param1;
            int m_param3;
            // virtual int getSize(){return sizeof(*this);}
            virtual int execute() { cout << "CMessageReceiver: execute\n"; }
        };

        const char* name = "TCOM_TOAM_EWRP_TASK";
        printf("hello %s\n", name);

        cout << "CMessageReceiver: " << sizeof(CMessageReceiver) << "\n";
        cout << "OMThread: " << sizeof(OMThread) << "\n";
        OMThread* polyPointer = new CMessageReceiver();
        cout << "OMThread: " << sizeof(*polyPointer) << "\n";
        cout << "OMThread getSize(): " << polyPointer->getSize() << "\n";

        int size = polyPointer->getSize();
        cout << "size: " << size << "\n";
        void* polyPointerVoid = polyPointer;
        void* ccsPointer = malloc(size);
        memcpy(ccsPointer, polyPointer, size);
        printf("polyPointer: %p\n", polyPointer);
        printf("ccsPointer: %p\n", ccsPointer);

        OMThread* staticCastPointer = static_cast<OMThread*>(polyPointerVoid);
        staticCastPointer->execute();
    }

    TEST(SampleTest, FindThoseIpAddresses) {
        AlbaLocalPathHandler fileToReadHandler(R"(D:\ZZZ_Logs\NSASampleSnapshots\SampleSnapshots\sorted.log)");
        ifstream fileToReadStream(fileToReadHandler.getFullPath());
        AlbaFileReader fileToRead(fileToReadStream);
        ofstream ipAddressesFile(fileToReadHandler.getDirectory() + "IpAddresses.txt");
        ofstream ipAddressesFile25(fileToReadHandler.getDirectory() + "IpAddresses25.txt");
        while (fileToRead.isNotFinished()) {
            string lineFromFile(fileToRead.getLineAndIgnoreWhiteSpaces());
            int lineFromFileLength = lineFromFile.length();
            int ipState(0);
            bool isIpAddress(false);
            for (int i = 0; i < lineFromFileLength; ++i) {
                // cout <<"printed:["<<lineFromFile[i]<<","<<ipState<<"]\n";
                if (ipState == 0) {
                    if (stringHelper::isNumber(lineFromFile[i])) {
                        ipState = 1;
                    }
                } else if (ipState == 1) {  // 100
                    if (stringHelper::isNumber(lineFromFile[i])) {
                        ipState = 1;
                    } else if (lineFromFile[i] == '.') {
                        ipState = 2;
                    } else {
                        ipState = 0;
                    }
                } else if (ipState == 2) {  // 100.
                    if (stringHelper::isNumber(lineFromFile[i])) {
                        ipState = 3;
                    } else {
                        ipState = 0;
                    }
                } else if (ipState == 3) {  // 100.100
                    if (stringHelper::isNumber(lineFromFile[i])) {
                        ipState = 3;
                    } else if (lineFromFile[i] == '.') {
                        ipState = 4;
                    } else {
                        ipState = 0;
                    }
                } else if (ipState == 4) {  // 100.100.
                    if (stringHelper::isNumber(lineFromFile[i])) {
                        ipState = 5;
                    } else {
                        ipState = 0;
                    }
                } else if (ipState == 5) {  // 100.100.100
                    if (stringHelper::isNumber(lineFromFile[i])) {
                        ipState = 5;
                    } else if (lineFromFile[i] == '.') {
                        ipState = 6;
                    } else {
                        ipState = 0;
                    }
                } else if (ipState == 6) {  // 100.100.100.
                    if (stringHelper::isNumber(lineFromFile[i])) {
                        ipState = 7;
                        isIpAddress = true;
                        break;
                    } else {
                        ipState = 0;
                    }
                }
            }
            if (isIpAddress) {
                ipAddressesFile << lineFromFile << "\n";
                ipAddressesFile25 << lineFromFile.substr(0, 25) << "\n";
            }
        }
    }
    */

}  // namespace alba
