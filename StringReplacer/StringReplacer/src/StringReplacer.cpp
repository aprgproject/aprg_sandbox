#include "StringReplacer.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <Debug/AlbaDebug.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

StringReplacer::StringReplacer()
{
}

void StringReplacer::replaceCToCPlusPlusStylePrintOnDirectories(string const& inputDirectory, string const& outputDirectory)
{
    AlbaLocalPathHandler::ListOfPaths files;
    AlbaLocalPathHandler::ListOfPaths directories;
    AlbaLocalPathHandler inputPathHandler(inputDirectory);
    AlbaLocalPathHandler outputPathHandler(outputDirectory);
    inputPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for(string const& file: files)
    {
        AlbaLocalPathHandler inputFilePathHandler(file);
        if(isCOrCPlusPlusFile(inputFilePathHandler.getExtension()))
        {
            string outputFilePath(inputFilePathHandler.getFullPath());
            transformReplaceStringIfFound(outputFilePath, inputPathHandler.getFullPath(), outputPathHandler.getFullPath());
            AlbaLocalPathHandler outputFilePathHandler(outputFilePath);
            replaceCToCPlusPlusStylePrintOnFile(inputFilePathHandler.getFullPath(), outputFilePathHandler.getFullPath());
        }
    }
}

void StringReplacer::replaceCToCPlusPlusStylePrintOnFile(string const& inputFilePath, string const& outputFilePath)
{
    AlbaLocalPathHandler outputFilePathHandler(outputFilePath);
    outputFilePathHandler.createDirectoriesForNonExisitingDirectories();
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);
    ALBA_PRINT2(inputFilePath, outputFilePath);
    if(inputFile.is_open())
    {
        AlbaFileReader inputFileReader(inputFile);
        string print;
        bool isOnPrint(false);
        while(inputFileReader.isNotFinished())
        {
            string lineInInputFile(inputFileReader.getLine());
            bool hasPrintInLineInInputFile = hasPrintInLine(lineInInputFile);
            bool hasSemiColonInLineInInputFile = hasEndOfPrintInLine(lineInInputFile);
            ALBA_PRINT4(lineInInputFile, isOnPrint, hasPrintInLineInInputFile, hasSemiColonInLineInInputFile);
            if(isOnPrint)
            {
                if(hasPrintInLineInInputFile && hasSemiColonInLineInInputFile)
                {
                    outputFile << gethCPlusPlusStylePrintFromC(getStringWithoutStartingAndTrailingWhiteSpace(print)) << endl;
                    print=lineInInputFile;
                    print.clear();
                    isOnPrint=false;
                }
                else if(hasPrintInLineInInputFile)
                {
                    outputFile << gethCPlusPlusStylePrintFromC(getStringWithoutStartingAndTrailingWhiteSpace(print)) << endl;
                    print=lineInInputFile;
                }
                else if(hasSemiColonInLineInInputFile)
                {
                    print+=" ";
                    print+=lineInInputFile;
                    outputFile << gethCPlusPlusStylePrintFromC(getStringWithoutStartingAndTrailingWhiteSpace(print)) << endl;
                    print.clear();
                    isOnPrint=false;
                }
                else
                {
                    print+=" ";
                    print+=lineInInputFile;
                }
            }
            else
            {
                if(hasPrintInLineInInputFile && hasSemiColonInLineInInputFile)
                {
                    print+=lineInInputFile;
                    outputFile << gethCPlusPlusStylePrintFromC(getStringWithoutStartingAndTrailingWhiteSpace(print)) << endl;
                    print.clear();
                }
                else if(hasPrintInLineInInputFile)
                {
                    print+=lineInInputFile;
                    isOnPrint=true;
                }
                else
                {
                    outputFile << lineInInputFile <<endl;
                }
            }
        }
    }
}

string StringReplacer::gethCPlusPlusStylePrintFromC(string const& inputString) const
{
    string result;
    strings splittedStrings;
    strings delimeters{R"((")", R"(",)", ");"};
    splitToStringsUsingASeriesOfDelimeters(splittedStrings, inputString, delimeters);

    for(string const& splittedString : splittedStrings)
    {
        ALBA_PRINT1(splittedString);
    }
    if(splittedStrings.size()==2)
    {
        strings delimetersForTwo{R"((")", "\");"};
        splittedStrings.clear();
        splitToStringsUsingASeriesOfDelimeters(splittedStrings, inputString, delimetersForTwo);
        string printFunction(splittedStrings[0]);
        string newPrintStream(getNewPrintStreamBasedFromOldPrintFunction(printFunction));
        result+=newPrintStream;
        result+=R"( << ")";
        result+=getStringWithoutStartingAndTrailingWhiteSpace(splittedStrings[1]);
        result+=R"(" << flush();)";
    }
    else if(splittedStrings.size()>=3)
    {
        string printFunction(getStringWithoutStartingAndTrailingWhiteSpace(splittedStrings[0]));
        string printString(splittedStrings[1]);
        strings printParameters;
        splitToStrings<SplitStringType::WithoutDelimeters>(printParameters, splittedStrings[2], ",");
        for(string const& printParameter : printParameters)
        {
            ALBA_PRINT1(printParameter);
        }
        string newPrintStream(getNewPrintStreamBasedFromOldPrintFunction(printFunction));
        removeStartingAndTrailingWhiteSpaceInPrintParameters(printParameters);
        result=constructCPlusPlusPrint(newPrintStream, "flush()", printString, printParameters);
    }
    return result;
}

void StringReplacer::removeStartingAndTrailingWhiteSpaceInPrintParameters(strings & printParameters) const
{
    for(string & printParameter : printParameters)
    {
        printParameter = getStringWithoutStartingAndTrailingWhiteSpace(printParameter);
    }
}

string StringReplacer::getNewPrintStreamBasedFromOldPrintFunction(string const& printFunction) const
{
    string newPrintStream;
    if("TLH_DEBUG_PRINT" == printFunction)
    {
        newPrintStream="debug()";
    }
    else if("TLH_INFO_PRINT" == printFunction)
    {
        newPrintStream="info()";
    }
    else if("TLH_WARNING_PRINT" == printFunction)
    {
        newPrintStream="warning()";
    }
    else if("TLH_ERROR_PRINT" == printFunction)
    {
        newPrintStream="error()";
    }
    return newPrintStream;
}

string StringReplacer::constructCPlusPlusPrint(string const& newPrintStream, string const& endPrintStream, string const& printString, strings const& printParameters) const
{
    string result(newPrintStream);
    bool isPercentEncountered(false);
    bool isOnStringLiteral(false);
    unsigned int printParameterIndex=0;
    for(char  c: printString)
    {
        bool isParameterAppended(false);
        if(isPercentEncountered)
        {
            if(isLetter(c))
            {
                if(printParameterIndex<printParameters.size())
                {
                    appendParameterToResult(result, isOnStringLiteral, printParameters[printParameterIndex++]);
                    isParameterAppended = true;
                }
            }
            else if(!isNumber(c))
            {
                appendCharacterToResult(result, isOnStringLiteral, '%');
            }
        }
        isPercentEncountered = ('%' == c)||(isNumber(c) && isPercentEncountered);
        if(!isPercentEncountered && !isParameterAppended)
        {
            appendCharacterToResult(result, isOnStringLiteral, c);
        }
    }
    appendParameterToResult(result, isOnStringLiteral, endPrintStream);
    result+=";";
    return result;
}

void StringReplacer::appendCharacterToResult(string & result, bool & isOnStringLiteral, char const c) const
{
    if(isOnStringLiteral)
    {
        result+=c;
    }
    else
    {
        result+=R"( << ")";
        result+=c;
    }
    isOnStringLiteral=true;
}

void StringReplacer::appendParameterToResult(string & result, bool & isOnStringLiteral, string const& parameter) const
{
    if(isOnStringLiteral)
    {
        result+=R"(" << )";
        result+=parameter;
    }
    else
    {
        result+=R"( << )";
        result+=parameter;
    }
    isOnStringLiteral=false;
}

bool StringReplacer::isCOrCPlusPlusFile(string const& extension)
{
    return "cpp" == extension || "hpp" == extension || "c" == extension || "h" == extension;
}

bool StringReplacer::hasPrintInLine(string const& line)
{
    return isStringFoundInsideTheOtherStringCaseSensitive(line, "TLH_DEBUG_PRINT") ||
            isStringFoundInsideTheOtherStringCaseSensitive(line, "TLH_INFO_PRINT") ||
            isStringFoundInsideTheOtherStringCaseSensitive(line, "TLH_WARNING_PRINT") ||
            isStringFoundInsideTheOtherStringCaseSensitive(line, "TLH_ERROR_PRINT");
}

bool StringReplacer::hasEndOfPrintInLine(string const& line)
{
    return isStringFoundInsideTheOtherStringCaseSensitive(line, ");");
}

}
