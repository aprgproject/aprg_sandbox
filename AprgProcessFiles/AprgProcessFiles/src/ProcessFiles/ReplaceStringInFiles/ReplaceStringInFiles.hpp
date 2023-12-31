#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <string>

namespace alba {

class ReplaceStringInFiles {
public:
    using StringPair = std::pair<std::string, std::string>;
    using StringPairs = std::vector<StringPair>;

    ReplaceStringInFiles() = default;

    void replaceStringWithStringOnDirectories(
        std::string const& inputDirectory, std::string const& outputDirectory, StringPairs const& replacePairs);
    void replaceStringWithStringOnFile(
        std::string const& inputFilePath, std::string const& outputFilePath, StringPairs const& replacePairs);

    void replaceCToCPlusPlusStylePrintOnDirectories(
        std::string const& inputDirectory, std::string const& outputDirectory);
    void replaceCToCPlusPlusStylePrintOnFile(std::string const& inputFilePath, std::string const& outputFilePath);
    std::string getCPlusPlusStylePrintFromC(std::string const& inputString) const;

private:
    std::string getNewPrintStreamBasedFromOldPrintFunction(std::string const& printFunction) const;
    void removeStartingAndTrailingWhiteSpaceInPrintParameters(stringHelper::strings& printParameters) const;
    std::string constructCPlusPlusPrint(
        std::string const& newPrintStream, std::string const& endPrintStream, std::string const& printString,
        stringHelper::strings const& printParameters) const;
    void appendCharacterToResult(std::string& result, bool& isOnStringLiteral, char const c) const;
    void appendParameterToResult(std::string& result, bool& isOnStringLiteral, std::string const& parameter) const;
    bool isCOrCPlusPlusFile(std::string const& extension);
    bool hasPrintInLine(std::string const& line);
    bool hasEndOfPrintInLine(std::string const& line);
};

}  // namespace alba
