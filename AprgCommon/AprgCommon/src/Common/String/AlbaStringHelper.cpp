#include "AlbaStringHelper.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Randomizer/AlbaRandomizer.hpp>

#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <set>
#include <sstream>

using namespace std;

namespace alba
{

namespace stringHelper
{

wstring convertStringToWideString(string const& stringInput)
{
    return wstring(stringInput.begin(), stringInput.end());
}

string convertWideStringToString(wstring const& wstringInput)
{
    return string(wstringInput.begin(), wstringInput.end());
}

unsigned int getLevenshteinDistance(string const& mainString, string const& string2)
{
    unsigned int mainStringLength = static_cast<unsigned int>(mainString.size());
    unsigned int string2Length = static_cast<unsigned int>(string2.size());

    vector<unsigned int> current(string2Length + 1);
    vector<unsigned int> previous(string2Length + 1);

    unsigned int i = 0;
    generate(previous.begin(), previous.end(), [&] {return i++; });

    for (i = 0; i < mainStringLength; ++i)
    {
        current[0] = i + 1;

        for (unsigned int j = 0; j < string2Length; ++j)
        {
            unsigned int cost = mainString[i] == string2[j] ? 0 : 1;
            current[j + 1] = min(min(current[j] + 1, previous[j + 1] + 1), previous[j] + cost);
        }

        current.swap(previous);
    }
    return previous[string2Length];
}

unsigned int generateUniqueId(string const& mainString)
{
    unsigned int uniqueId=1;
    uniqueId = accumulate(mainString.begin(), mainString.end(), uniqueId, [](unsigned int c1, unsigned char c2)
    {
        return (c1*c2)+1;
    });
    return uniqueId;
}

string constructFileLocator(string const& file, int const lineNumber)
{
    stringstream ss;
    ss << file.substr(file.find_last_of('\\')+1) << "[" << lineNumber << "]";
    return ss.str();
}

string getRandomAlphaNumericString(unsigned int const length)
{
    AlbaRandomizer randomizer;
    int alphaNumericCharMapIndexMax = static_cast<int>(ALPHA_NUMERIC_CHAR_MAP.length())-1;
    string result;
    result.reserve(length);
    generate_n(back_inserter(result), length, [&]()
    {
        return ALPHA_NUMERIC_CHAR_MAP[static_cast<unsigned int>(randomizer.getRandomValueInUniformDistribution(0, alphaNumericCharMapIndexMax))];
    });
    return result;
}

bool isWildcardMatch(string const& mainString, string const& wildcard, unsigned int const mainStringIndex, unsigned int const wildcardIndex)
{
    bool result(false);
    bool isMainStringDone = mainStringIndex >= mainString.size();
    bool isWildcardDone = wildcardIndex >= wildcard.size();
    if(isMainStringDone && isWildcardDone)
    {
        result = true;
    }
    else if(isWildcardDone)
    {
        result = false;
    }
    else if(isMainStringDone)
    {
        bool isWildcardDoneOnNextIndex = wildcardIndex+1 >= wildcard.size();
        result = wildcard[wildcardIndex] == '*' && isWildcardDoneOnNextIndex;
    }
    else if(wildcard[wildcardIndex] == mainString[mainStringIndex])
    {
        result = isWildcardMatch(mainString, wildcard, mainStringIndex+1, wildcardIndex+1);
    }
    else if(wildcard[wildcardIndex] == '?')
    {
        result = isWildcardMatch(mainString, wildcard, mainStringIndex+1, wildcardIndex+1) || isWildcardMatch(mainString, wildcard, mainStringIndex, wildcardIndex+1);
    }
    else if(wildcard[wildcardIndex] == '*')
    {
        result = isWildcardMatch(mainString, wildcard, mainStringIndex, wildcardIndex+1) || isWildcardMatch(mainString, wildcard, mainStringIndex+1, wildcardIndex);
    }
    return result;
}

bool isStringFoundInsideTheOtherStringCaseSensitive(string const& mainString, string const& string2)
{
    return isNotNpos(static_cast<int>(mainString.find(string2)));
}

bool isStringFoundInsideTheOtherStringNotCaseSensitive(string const& mainString, string const& string2)
{
    return isStringFoundInsideTheOtherStringCaseSensitive(getStringWithCapitalLetters(mainString), getStringWithCapitalLetters(string2));
}

bool isEqualNotCaseSensitive(string const& mainString, string const& string2)
{
    return getStringWithCapitalLetters(mainString) == getStringWithCapitalLetters(string2);
}

bool isEqualWithLowestCommonLength(string const& string1, string const& string2)
{
    unsigned int length1 = string1.length();
    unsigned int length2 = string2.length();
    unsigned int lowestLength = (length1>length2) ? length2 : length1;
    return string1.substr(0, lowestLength) == string2.substr(0, lowestLength);
}

bool isNumber(string const& mainString)
{
    return any_of(mainString.begin(), mainString.end(), [](char const character){ return isNumber(character);});
}

bool isWhiteSpace(string const& mainString)
{
    return all_of(mainString.begin(), mainString.end(), [](char const character){ return isWhiteSpace(character);});
}

bool isNewline(string const& mainString)
{
    return all_of(mainString.begin(), mainString.end(), [](char const character){ return isNewline(character);});
}

bool isIdentifier(string const& mainString)
{
    bool isIdentifier(false);
    if(!mainString.empty())
    {
        char firstCharacter = mainString[0];
        isIdentifier = isLetter(firstCharacter) || isUnderscore(firstCharacter);
    }
    return isIdentifier;
}

bool isOneWord(string const& mainString)
{
    return (!mainString.empty()) && none_of(mainString.begin(), mainString.end(), [](char const character){ return isWhiteSpace(character);});
}

void fetchArgumentsToStringInMain(strings & argumentsInMain, int const argc, char const * const argv[])
{
    for (int argumentIndex=0; argumentIndex<argc; argumentIndex++)
    {
        argumentsInMain.emplace_back(argv[argumentIndex]);
    }
}

bool transformReplaceStringIfFound(string& mainString, string const& toReplace, string const& replaceWith)
{
    bool found=false;
    unsigned int toReplaceLength = toReplace.length();
    unsigned int replaceWithLength = replaceWith.length();
    unsigned int index = mainString.find(toReplace);
    while(isNotNpos(static_cast<int>(index)))
    {
        found = true;
        mainString.replace(index, toReplaceLength, replaceWith);
        index = mainString.find(toReplace, index + replaceWithLength);
    }
    return found;
}


template <SplitStringType splitStringType> void splitToStrings(strings & listOfStrings, string const& mainString, string const& delimiters)
{
    unsigned int startingIndexOfFind(0);
    unsigned int delimiterIndex = mainString.find_first_of(delimiters);
    unsigned int delimeterLength = 1;
    unsigned int mainStringLength = mainString.length();
    while(isNotNpos(static_cast<int>(delimiterIndex)))
    {
        if(startingIndexOfFind != delimiterIndex)
        {
            listOfStrings.emplace_back(mainString.substr(startingIndexOfFind, delimiterIndex-startingIndexOfFind));
        }
        if(SplitStringType::WithDelimeters == splitStringType)
        {
            listOfStrings.emplace_back(mainString.substr(delimiterIndex, delimeterLength));
        }
        startingIndexOfFind = delimiterIndex + delimeterLength;
        delimiterIndex = mainString.find_first_of(delimiters, startingIndexOfFind);
    }
    if(startingIndexOfFind != mainStringLength)
    {
        listOfStrings.emplace_back(mainString.substr(startingIndexOfFind, mainStringLength-startingIndexOfFind));
    }
}

template void splitToStrings<SplitStringType::WithoutDelimeters> (strings & listOfStrings, string const& mainString, string const& delimiter);
template void splitToStrings<SplitStringType::WithDelimeters> (strings & listOfStrings, string const& mainString, string const& delimiter);

string combineStrings(strings const& listOfStrings, string const& delimiters)
{
    string result = accumulate(listOfStrings.cbegin(), listOfStrings.cend(), string(), [&delimiters](string const& previousResult, string const& currentString)
    {
            return string(previousResult + currentString + delimiters);
});

    if(result.size() > delimiters.size())
    {
        result = result.substr(0, result.size() - delimiters.size());
    }
    return result;
}

void splitLinesToAchieveTargetLength(strings & strings, string const& mainString, unsigned int const targetLength)
{
    set<unsigned int> transitionIndexes;
    unsigned int mainStringLength = mainString.length();
    bool isPreviousCharacterAWhitespace(false);
    transitionIndexes.emplace(0);
    for(unsigned int i = 0; i < mainStringLength; i++)
    {
        char currentCharacter = mainString[i];
        if(isPreviousCharacterAWhitespace && !isWhiteSpace(currentCharacter))
        {
            transitionIndexes.emplace(i-1);
        }
        else if(!isPreviousCharacterAWhitespace && isWhiteSpace(currentCharacter))
        {
            transitionIndexes.emplace(i);
        }
        isPreviousCharacterAWhitespace = isWhiteSpace(currentCharacter);
    }
    transitionIndexes.emplace(mainStringLength);

    unsigned int previousSplittingIndex = 0;
    for(unsigned int splittingIndex = targetLength; splittingIndex < mainStringLength; splittingIndex += targetLength)
    {
        char currentCharacter = mainString[splittingIndex];

        if(!isWhiteSpace(currentCharacter))
        {
            auto pairOfIndex = containerHelper::getLowerAndUpperValuesInSet(transitionIndexes, splittingIndex);
            unsigned int lowerTransitionIndex(pairOfIndex.first+1);
            unsigned int upperTransitionIndex(pairOfIndex.second);
            int lowerDelta = static_cast<int>(splittingIndex-lowerTransitionIndex);
            int upperDelta = static_cast<int>(upperTransitionIndex-splittingIndex);

            bool isUpperValid(upperDelta >= 0);
            bool isLowerValid(lowerDelta >= 0 && lowerTransitionIndex != previousSplittingIndex);
            if(isUpperValid && isLowerValid)
            {
                if(upperDelta < lowerDelta)
                {
                    splittingIndex = upperTransitionIndex;
                }
                else
                {
                    splittingIndex = lowerTransitionIndex;
                }
            }
            else if(isUpperValid)
            {
                splittingIndex = upperTransitionIndex;
            }
            else if(isLowerValid)
            {
                splittingIndex = lowerTransitionIndex;
            }
        }
        strings.emplace_back(mainString.substr(previousSplittingIndex, splittingIndex-previousSplittingIndex));
        previousSplittingIndex = splittingIndex;
    }
    if(previousSplittingIndex!=mainStringLength)
    {
        strings.emplace_back(mainString.substr(previousSplittingIndex));
    }
}

void splitToStringsUsingASeriesOfDelimeters(strings & listOfStrings, string const& mainString, strings const& seriesOfDelimiters)
{
    if(!seriesOfDelimiters.empty())
    {
        unsigned int startingIndexOfFind(0);
        unsigned int mainStringLength = mainString.length();
        unsigned int delimiterIndex(0);
        for(string const& delimeter : seriesOfDelimiters)
        {
            delimiterIndex = mainString.find(delimeter, startingIndexOfFind);
            if(isNpos(static_cast<int>(delimiterIndex)))
            {
                break;
            }
            if(startingIndexOfFind != delimiterIndex)
            {
                listOfStrings.emplace_back(mainString.substr(startingIndexOfFind, delimiterIndex-startingIndexOfFind));
            }
            startingIndexOfFind = delimiterIndex + delimeter.length();
        }
        if(startingIndexOfFind != mainStringLength)
        {
            listOfStrings.emplace_back(mainString.substr(startingIndexOfFind, mainStringLength-startingIndexOfFind));
        }
    }
}

string getStringWithCapitalLetters(string const& mainString)
{
    string result;
    result.resize(mainString.length());
    transform(mainString.begin(), mainString.end(), result.begin(), ::toupper);
    return result;
}

string getStringWithFirstNonWhiteSpaceCharacterToCapital(string const& mainString)
{
    string result;
    result = mainString;
    unsigned int resultLength = result.length();
    for (unsigned int i = 0; i < resultLength; ++i)
    {
        if(!isWhiteSpace(result[i]))
        {
            result[i] = static_cast<char>(::toupper(result[i]));
            break;
        }
    }
    return result;
}

string getStringWithLowerCaseLetters(string const& mainString)
{
    string result;
    result.resize(mainString.length());
    transform(mainString.begin(), mainString.end(), result.begin(), ::tolower);
    return result;
}

string getStringWithUrlDecodedString(string const& mainString)
{
    string result;
    unsigned int index = 0, length = mainString.length();
    while(index < length)
    {
        if(mainString[index] == '%' &&
                (static_cast<int>(index) < static_cast<int>(length)-2) &&
                isHexDigit(mainString[index + 1]) &&
                isHexDigit(mainString[index + 2]))
        {
            result += convertHexStringToNumber<char>(mainString.substr(index + 1, 2));
            index += 3;
        }
        else
        {
            result += mainString[index++];
        }
    }
    return result;
}

string getStringThatContainsWhiteSpaceIndention(string const& mainString)
{
    string result;
    unsigned int firstIndexOfNotOfCharacters(mainString.find_first_not_of(WHITESPACE_STRING));
    if(isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters)))
    {
        result = mainString.substr(0, firstIndexOfNotOfCharacters);
    }
    return result;
}

string getStringWithoutStartingAndTrailingCharacters(string const& mainString, string const& characters)
{
    string result(mainString);
    unsigned int firstIndexOfNotOfCharacters(result.find_first_not_of(characters));
    if(isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters)))
    {
        result.erase(0, firstIndexOfNotOfCharacters);
        unsigned int lastIndexOfOfNotOfCharacters(result.find_last_not_of(characters));
        if(isNotNpos(static_cast<int>(lastIndexOfOfNotOfCharacters)))
        {
            result.erase(lastIndexOfOfNotOfCharacters+1);
        }
    }
    else
    {
        result.clear();
    }
    return result;
}

string getStringWithoutStartingAndTrailingWhiteSpace(string const& mainString)
{
    return getStringWithoutStartingAndTrailingCharacters(mainString, WHITESPACE_STRING);
}

string getStringWithoutWhiteSpace(string const& mainString)
{
    string result;
    unsigned int index = 0, length = mainString.length();
    while(index < length)
    {
        if(!isWhiteSpace(mainString[index]))
        {
            result+=mainString[index];
        }
        index++;
    }
    return result;
}

string getStringWithoutRedundantWhiteSpace(string const& mainString)
{
    string result;
    unsigned int index = 0, length = mainString.length();
    while(index < length)
    {
        unsigned int indexNotWhiteSpace = mainString.find_first_not_of(WHITESPACE_STRING, index);
        if(isNpos(static_cast<int>(indexNotWhiteSpace))){break;}
        unsigned int indexWhiteSpace = mainString.find_first_of(WHITESPACE_STRING, indexNotWhiteSpace);
        index = (isNotNpos(static_cast<int>(indexWhiteSpace))) ? indexWhiteSpace : length;
        result += (!result.empty()) ? " " : string();
        result += mainString.substr(indexNotWhiteSpace, index-indexNotWhiteSpace);
    }
    return result;
}

string getStringWithoutQuotations(string const& mainString)
{
    unsigned int length = mainString.length();
    if(length>2 && mainString[0] == '\"' && mainString[length-1] == '\"')
    {
        return mainString.substr(1, length-2);
    }
    return mainString;
}

string getStringWithoutCharAtTheStartAndEnd(string const& mainString, char const char1)
{
    return getStringWithoutCharAtTheStart(getStringWithoutCharAtTheEnd(mainString, char1), char1);
}

string getStringWithoutCharAtTheStart(string const& mainString, char const char1)
{
    unsigned int length = mainString.length();
    unsigned int start = (mainString[0] == char1) ? 1 : 0;
    return mainString.substr(start, length-start);
}

string getStringWithoutCharAtTheEnd(string const& mainString, char const char1)
{
    unsigned int length = mainString.length();
    unsigned int end = (length <= 0) ? 0 : (mainString[length-1] == char1) ? length-1 : length;
    return mainString.substr(0, end);
}

string getStringWithoutOpeningClosingOperators(string const& mainString, char const openingOperator, char const closingOperator)
{
    unsigned int length = mainString.length();
    unsigned int start = (mainString[0] == openingOperator) ? 1 : 0;
    unsigned int end = (length <= 0) ? 0 : (mainString[length-1] == closingOperator) ? length-1 : length;
    return mainString.substr(start, end-start);
}

void copyBeforeStringAndAfterString(
        string const& mainString,
        string const& stringToSearch,
        string & beforeString,
        string & afterString,
        unsigned int const indexToStartTheSearch)
{
    beforeString.clear();
    afterString.clear();
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStartTheSearch);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        beforeString = mainString.substr(0, firstIndexOfFirstString);
        afterString = mainString.substr(lastIndexOfFirstString);
    }
}

string getStringBeforeThisString(string const& mainString, string const& stringToSearch, unsigned int const indexToStart)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStart);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        result = mainString.substr(0, firstIndexOfFirstString);
    }
    return result;
}

string getStringAfterThisString(string const& mainString, string const& stringToSearch, unsigned int const indexToStart)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStart);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        result = mainString.substr(lastIndexOfFirstString);
    }
    return result;
}

string getStringInBetweenTwoStrings(string const& mainString, string const& firstString, string const& secondString, unsigned int const indexToStart)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(firstString, indexToStart);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + firstString.length();
        unsigned int firstIndexOfSecondString = mainString.find(secondString, lastIndexOfFirstString);
        if(isNotNpos(static_cast<int>(firstIndexOfSecondString)))
        {
            result = mainString.substr(lastIndexOfFirstString, firstIndexOfSecondString-lastIndexOfFirstString);
        }
    }
    return result;
}

string getStringBeforeThisCharacters(string const& mainString, string const& characters, unsigned int const indexToStart)
{
    string result;
    unsigned int firstIndexOfNotOfCharacters(mainString.find_first_of(characters, indexToStart));
    if(isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters)))
    {
        result = mainString.substr(indexToStart, firstIndexOfNotOfCharacters-indexToStart);
    }
    return result;
}

string getStringByRepeatingUntilDesiredLength(string const& stringToRepeat, unsigned int desiredLength)
{
    string result;
    if(!stringToRepeat.empty())
    {
        unsigned int stringToRepeatLength = stringToRepeat.length();
        for(unsigned int index=0; index<=desiredLength; index += stringToRepeatLength)
        {
            result += stringToRepeat;
        }
        result = result.substr(0, desiredLength);
    }
    return result;
}

string getStringAndReplaceNonAlphanumericCharactersToUnderScore(string const& path)
{
    bool isPreviousCharacterNonAlphanumeric = false;
    string correctPath = accumulate(
                path.cbegin(), path.cend(), string(), [&isPreviousCharacterNonAlphanumeric]
                (string const& currentString, char const currentCharacter)
    {
            string partialResult(currentString);
            if(!isLetterOrNumber(currentCharacter))
    {
            if(!isPreviousCharacterNonAlphanumeric)
    {
            partialResult += "_";
}
}
            else
    {
            partialResult += currentCharacter;
}
            isPreviousCharacterNonAlphanumeric = !isLetterOrNumber(currentCharacter);
            return partialResult;
});
    return correctPath;
}

string getNumberAfterThisString(string const& mainString, string const& stringToSearch)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        unsigned int lastIndexOfNumber;
        for(lastIndexOfNumber = lastIndexOfFirstString; isNumber(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

string getHexNumberAfterThisString(string const& mainString, string const& stringToSearch)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        unsigned int lastIndexOfNumber(lastIndexOfFirstString);
        for(; isHexDigit(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

string getStringWithJustifyAlignment(string const& mainString, unsigned int const length)
{
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainString));
    string noWhiteSpace(getStringWithoutWhiteSpace(mainString));
    if(mainString.empty())
    {
        string gap(length, ' ');
        result = gap;
    }
    else if(noRedundantWhiteSpace.length()>=length)
    {
        result = noRedundantWhiteSpace;
    }
    else if(isOneWord(mainString))
    {
        unsigned int noRedundantWhiteSpaceLength = noRedundantWhiteSpace.length();
        unsigned int gapLength = (length-noWhiteSpace.length())/(noRedundantWhiteSpaceLength+1);
        string gap(gapLength, ' ');
        result += gap;
        for(unsigned int i=0; i<noRedundantWhiteSpaceLength; i++)
        {
            result += noRedundantWhiteSpace[i];
            result += gap;
        }
        result += string(length-result.length(), ' ');
    }
    else
    {
        strings actualStrings;
        splitToStrings<SplitStringType::WithoutDelimeters>(actualStrings, noRedundantWhiteSpace, " ");
        unsigned int numberOfStrings = actualStrings.size();
        unsigned int gapLength = (length-noWhiteSpace.length())/(numberOfStrings-1);
        string gap(gapLength, ' ');
        for(unsigned int i=0; i<numberOfStrings; i++)
        {
            result += actualStrings[i];
            if(i<numberOfStrings-1)
            {
                result += gap;
            }
        }
        result += string(length-result.length(), ' ');
    }
    return result;
}

string getStringWithCenterAlignment(string const& mainString, unsigned int const length)
{
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainString));
    if(mainString.empty())
    {
        string gap(length, ' ');
        result = gap;
    }
    else if(noRedundantWhiteSpace.length()>=length)
    {
        result = noRedundantWhiteSpace;
    }
    else
    {
        unsigned int gapLength = (length-noRedundantWhiteSpace.length())/2;
        result += string(gapLength, ' ');
        result += noRedundantWhiteSpace;
        result += string(length-result.length(), ' ');
    }
    return result;
}

string getStringWithRightAlignment(string const& mainString, unsigned int const length)
{
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainString));
    if(mainString.empty())
    {
        string gap(length, ' ');
        result = gap;
    }
    else if(noRedundantWhiteSpace.length()>=length)
    {
        result = noRedundantWhiteSpace;
    }
    else
    {
        unsigned int gapLength = (length-noRedundantWhiteSpace.length());
        result += string(gapLength, ' ');
        result += noRedundantWhiteSpace;
    }
    return result;
}

string getStringWithLeftAlignment(string const& mainString, unsigned int const length)
{
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainString));
    if(mainString.empty())
    {
        string gap(length, ' ');
        result = gap;
    }
    else if(noRedundantWhiteSpace.length()>=length)
    {
        result = noRedundantWhiteSpace;
    }
    else
    {
        unsigned int gapLength = (length-noRedundantWhiteSpace.length());
        result += noRedundantWhiteSpace;
        result += string(gapLength, ' ');
    }
    return result;
}

string getCorrectPathWithoutUrlParameters(string const& path)
{
    string correctPathWithoutUrlParameters(path);
    unsigned int indexOfQuestionMark = path.find_first_of('?');
    if(isNotNpos(static_cast<int>(indexOfQuestionMark)))
    {
        correctPathWithoutUrlParameters = path.substr(0, indexOfQuestionMark);
    }
    return correctPathWithoutUrlParameters;
}

string getUrlParameters(string const& path)
{
    string urlParameters;
    unsigned int indexOfQuestionMark = path.find_first_of('?');
    if(isNotNpos(static_cast<int>(indexOfQuestionMark)))
    {
        urlParameters = path.substr(indexOfQuestionMark);
    }
    return urlParameters;
}

string getCorrectPathWithReplacedSlashCharacters(string const& path, string const& slashCharacterString)
{
    bool wasSlashDetected = false;
    string correctPath = accumulate(path.cbegin(), path.cend(), string(),
                                    [&wasSlashDetected, slashCharacterString]
                                    (string const& currentString, char const currentCharacter)
    {
        string partialResult(currentString);
        if(isSlashCharacter(currentCharacter))
        {
            if(!wasSlashDetected){partialResult += slashCharacterString;}
        }
        else
        {
            partialResult += currentCharacter;
        }
        wasSlashDetected = isSlashCharacter(currentCharacter);
        return partialResult;
    });
    return correctPath;
}

string getCorrectPathWithoutDoublePeriod(string const& mainString, string const& slashCharacterString)
{
    string correctPath(mainString);
    bool isDirectoryChanged = true;
    while(isDirectoryChanged)
    {
        isDirectoryChanged = false;
        string stringToFind(slashCharacterString);
        stringToFind += string("..");
        stringToFind += slashCharacterString;
        unsigned int indexOfDoublePeriod = correctPath.find(stringToFind);
        if(isNotNpos(static_cast<int>(indexOfDoublePeriod)))
        {
            unsigned int indexOfNearestSlash = correctPath.find_last_of(slashCharacterString, indexOfDoublePeriod-1);
            if(isNotNpos(static_cast<int>(indexOfNearestSlash)))
            {
                isDirectoryChanged = true;
                correctPath.erase(indexOfNearestSlash, indexOfDoublePeriod+3-indexOfNearestSlash);
            }
        }
    }
    return correctPath;
}

string getStringBeforeDoublePeriod(string const& mainString, string const& slashCharacterString)
{
    unsigned int indexOfLastDoublePeriod = mainString.rfind(string("..")+slashCharacterString);
    if(isNotNpos(static_cast<int>(indexOfLastDoublePeriod)))
    {
        return mainString.substr(indexOfLastDoublePeriod+3);
    }
    return mainString;
}

string getImmediateDirectoryName(string const& mainString, string const& slashCharacterString)
{
    unsigned int indexLastCharacterToSearch = mainString.length();
    string result;
    while(result.empty())
    {
        unsigned int indexOfLastSlashString = mainString.find_last_of(slashCharacterString, indexLastCharacterToSearch);
        if(isNpos(static_cast<int>(indexOfLastSlashString)))
        {
            break;
        }
        result = mainString.substr(indexOfLastSlashString+1, indexLastCharacterToSearch-indexOfLastSlashString);
        indexLastCharacterToSearch = indexOfLastSlashString-1;
    }
    return result;
}

template <char slashCharacter>
string getCorrectPathWithReplacedSlashCharacters(string const& path)
{
    return getCorrectPathWithReplacedSlashCharacters(path, string()+slashCharacter);
}
template string getCorrectPathWithReplacedSlashCharacters<'\\'>(string const& path);
template string getCorrectPathWithReplacedSlashCharacters<'/'>(string const& path);

template <char slashCharacter>
string getCorrectPathWithoutDoublePeriod(string const& path)
{
    return getCorrectPathWithoutDoublePeriod(path, string()+slashCharacter);
}
template string getCorrectPathWithoutDoublePeriod<'\\'>(string const& path);
template string getCorrectPathWithoutDoublePeriod<'/'>(string const& path);

template <char slashCharacter>
string getStringBeforeDoublePeriod(string const& path)
{
    return getStringBeforeDoublePeriod(path, string()+slashCharacter);
}
template string getStringBeforeDoublePeriod<'\\'>(string const& path);
template string getStringBeforeDoublePeriod<'/'>(string const& path);

template <char slashCharacter>
string getImmediateDirectoryName(string const& path)
{
    return getImmediateDirectoryName(path, string()+slashCharacter);
}
template string getImmediateDirectoryName<'\\'>(string const& path);
template string getImmediateDirectoryName<'/'>(string const& path);

bool convertStringToBool(string const& stringToConvert)
{
    string allCapital(getStringWithCapitalLetters(stringToConvert));
    bool result(false);
    if("TRUE" == allCapital)
    {
        result = true;
    }
    else if("FALSE" == allCapital)
    {
        result = false;
    }
    else
    {
        result = (0 != convertStringToNumber<int>(stringToConvert));
    }
    return result;
}

template <typename NumberType>
NumberType convertStringToNumber(string const& stringToConvert)
{
    bool isNumberNotYetEncountered(true);
    bool isPeriodNotYetEncountered(true);
    int negative(1);
    int decimalPlacesInPowersOfTen(10);
    NumberType value(0);
    for (char const currentCharacter : stringToConvert)
    {
        if(isNumber(currentCharacter))
        {
            if(isPeriodNotYetEncountered)
            {
                value = (value * 10) + static_cast<NumberType>(currentCharacter - '0');
                isNumberNotYetEncountered=false;
            }
            else
            {
                value = value + ((static_cast<NumberType>(currentCharacter - '0')) / static_cast<NumberType>(decimalPlacesInPowersOfTen));
                decimalPlacesInPowersOfTen*=10;
            }
        }
        else if(currentCharacter == '-' && isNumberNotYetEncountered)
        {
            negative *= -1;
        }
        else if(currentCharacter == '.')
        {
            isPeriodNotYetEncountered = false;
        }
    }
    return value*static_cast<NumberType>(negative);
}

template int convertStringToNumber<int>(string const& stringToConvert);
template unsigned int convertStringToNumber<unsigned int>(string const& stringToConvert);
template float convertStringToNumber<float>(string const& stringToConvert);
template double convertStringToNumber<double>(string const& stringToConvert);

template <typename NumberType>
NumberType convertHexStringToNumber(string const& stringToConvert)
{
    NumberType value = 0;
    for (char const currentCharacter : stringToConvert)
    {
        if(isHexDigit(currentCharacter))
        {
            value *= 16;
            if(isNumber(currentCharacter))
            {
                value += static_cast<NumberType>(currentCharacter - '0');
            }
            else if(isCapitalLetter(currentCharacter))
            {
                value += static_cast<NumberType>(currentCharacter - 'A' + 10);
            }
            else
            {
                value += static_cast<NumberType>(currentCharacter - 'a' + 10);
            }
        }
    }
    return value;
}

template char convertHexStringToNumber<char>(string const& stringToConvert);
template int convertHexStringToNumber<int>(string const& stringToConvert);
template unsigned int convertHexStringToNumber<unsigned int>(string const& stringToConvert);
template unsigned char convertHexStringToNumber<unsigned char>(string const& stringToConvert);

AlbaNumber convertStringToAlbaNumber(string const& stringToConvert)
{
    AlbaNumber result;
    if(isStringFoundInsideTheOtherStringCaseSensitive(stringToConvert, "."))
    {
        result = AlbaNumber(convertStringToNumber<double>(stringToConvert));
    }
    else
    {
        result = AlbaNumber(convertStringToNumber<int>(stringToConvert));
    }
    return result;
}

template <typename NumberType>
string NumberToStringConverter::convert(NumberType const number)
{
    string result;
    stringstream temporaryStream;
    if(m_precisionOptional)
    {
        temporaryStream.precision(m_precisionOptional.getReference());
    }
    if(m_fillCharacterOptional)
    {
        temporaryStream << setfill(m_fillCharacterOptional.getReference());
    }
    if(m_fieldWidthOptional)
    {
        temporaryStream << setw(m_fieldWidthOptional.getReference());
    }
    temporaryStream << number;
    result = temporaryStream.str();
    if(m_maximumLengthOptional)
    {
        result = result.substr(m_maximumLengthOptional.getReference());
    }
    return result;
}

string NumberToStringConverter::convert(AlbaNumber const& number)
{
    return convert(number.getDouble());
}

void NumberToStringConverter::setPrecision(int const precision)
{
    m_precisionOptional.setValue(precision);
}

void NumberToStringConverter::setFieldWidth(int const fieldWidth)
{
    m_fieldWidthOptional.setValue(fieldWidth);
}

void NumberToStringConverter::setFillCharacter(char const fillCharacter)
{
    m_fillCharacterOptional.setValue(fillCharacter);
}

void NumberToStringConverter::setMaximumLength(unsigned int const maximumLength)
{
    m_maximumLengthOptional.setValue(maximumLength);
}

template string NumberToStringConverter::convert<bool>(bool boolValue);
template string NumberToStringConverter::convert<int>(int number);
template string NumberToStringConverter::convert<unsigned int>(unsigned int number);
template string NumberToStringConverter::convert<float>(float number);
template string NumberToStringConverter::convert<double>(double number);

}//namespace stringHelper

}//namespace alba
