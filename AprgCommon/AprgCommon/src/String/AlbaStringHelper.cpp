#include "AlbaStringHelper.hpp"

#include <Container/AlbaContainerHelper.hpp>
#include <Randomizer/AlbaRandomizer.hpp>

#include <algorithm>
#include <cctype>
#include <functional>
#include <iomanip>
#include <set>
#include <sstream>
#include <typeinfo>

using namespace std;

namespace alba
{

unsigned int stringHelper::getLevenshteinDistance(string const& mainString, string const& string2)
{
    int mainStringLength = mainString.size();
    int string2Length = string2.size();

    vector<unsigned int> current(string2Length + 1);
    vector<unsigned int> previous(string2Length + 1);

    int i = 0;
    generate(previous.begin(), previous.end(), [&] {return i++; });

    for (i = 0; i < mainStringLength; ++i)
    {
        current[0] = i + 1;

        for (int j = 0; j < string2Length; ++j)
        {
            auto cost = mainString[i] == string2[j] ? 0 : 1;
            current[j + 1] = min(min(current[j] + 1, previous[j + 1] + 1), previous[j] + cost);
        }

        current.swap(previous);
    }
    return previous[string2Length];
}

unsigned int stringHelper::generateUniqueId(string const& mainString)
{
    unsigned int uniqueId=1;
    uniqueId = accumulate(mainString.begin(), mainString.end(), uniqueId, [](unsigned int c1, unsigned char c2)
    {
        return (c1*c2)+1;
    });
    return uniqueId;
}

string stringHelper::constructFileLocator(string file, int lineNumber)
{
    stringstream ss;
    ss << file.substr(file.find_last_of(R"(\)")+1) << "[" << lineNumber << "]";
    return ss.str();
}

std::string stringHelper::getRandomAlphaNumericString(unsigned int const length)
{
    AlbaRandomizer randomizer;
    int alphaNumericCharMapIndexMax = ALPHA_NUMERIC_CHAR_MAP.length()-1;
    string result;
    result.reserve(length);
    std::generate_n(std::back_inserter(result), length, [&]()
    {
        return ALPHA_NUMERIC_CHAR_MAP[randomizer.getRandomValueInUniformDistribution(0, alphaNumericCharMapIndexMax)];
    });
    return result;
}

bool stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(string const& mainString, string const& string2)
{
    return isNotNpos(mainString.find(string2));
}

bool stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(string const& mainString, string const& string2)
{
    return isStringFoundInsideTheOtherStringCaseSensitive(getStringWithCapitalLetters(mainString), getStringWithCapitalLetters(string2));
}

bool stringHelper::isEqualNotCaseSensitive(string const& mainString, string const& string2)
{
    return getStringWithCapitalLetters(mainString) == getStringWithCapitalLetters(string2);
}

bool stringHelper::isEqualWithLowestCommonLength(string const& string1, string const& string2)
{
    unsigned int length1 = string1.length();
    unsigned int length2 = string2.length();
    unsigned int lowestLength = (length1>length2) ? length2 : length1;
    return string1.substr(0, lowestLength) == string2.substr(0, lowestLength);
}

bool stringHelper::isNumber(string const& mainString)
{
    return std::any_of(mainString.begin(), mainString.end(), [](char const character){ return isNumber(character);});
}

bool stringHelper::isWhiteSpace(string const& mainString)
{
    return std::all_of(mainString.begin(), mainString.end(), [](char const character){ return isWhiteSpace(character);});
}

bool stringHelper::isIdentifier(string const& mainString)
{
    bool isIdentifier(false);
    if(!mainString.empty())
    {
        char firstCharacter = mainString[0];
        isIdentifier = isLetter(firstCharacter) || isUnderscore(firstCharacter);
    }
    return isIdentifier;
}

bool stringHelper::isOneWord(string const& mainString)
{
    return (!mainString.empty()) && std::none_of(mainString.begin(), mainString.end(), [](char const character){ return isWhiteSpace(character);});
}

bool stringHelper::transformReplaceStringIfFound(string& mainString, string const& toReplace, string const& replaceWith)
{
    bool found=false;
    int toReplaceLength = toReplace.length();
    int replaceWithLength = replaceWith.length();
    int index = mainString.find(toReplace);
    while(isNotNpos(index))
    {
        found = true;
        mainString.replace(index, toReplaceLength, replaceWith);
        index = mainString.find(toReplace, index + replaceWithLength);
    }
    return found;
}

template <stringHelper::SplitStringType splitStringType> void stringHelper::splitToStrings(stringHelper::strings & strings, std::string const& mainString, std::string const& delimiters)
{
    int startingIndex(0);
    int delimiterIndex = mainString.find_first_of(delimiters);
    int delimeterLength = 1;
    int mainStringLength = mainString.length();
    while(isNotNpos(delimiterIndex))
    {
        if(startingIndex != delimiterIndex)
        {
            strings.emplace_back(mainString.substr(startingIndex, delimiterIndex-startingIndex));
        }
        if(SplitStringType::WithDelimeters == splitStringType)
        {
            strings.emplace_back(mainString.substr(delimiterIndex, delimeterLength));
        }
        startingIndex = delimiterIndex + delimeterLength;
        delimiterIndex = mainString.find_first_of(delimiters, startingIndex);
    }
    if(startingIndex != mainStringLength)
    {
        strings.emplace_back(mainString.substr(startingIndex, mainStringLength-startingIndex));
    }
}

template void stringHelper::splitToStrings<stringHelper::SplitStringType::WithoutDelimeters> (stringHelper::strings & strings, std::string const& mainString, std::string const& delimiter);
template void stringHelper::splitToStrings<stringHelper::SplitStringType::WithDelimeters> (stringHelper::strings & strings, std::string const& mainString, std::string const& delimiter);

void stringHelper::splitLinesToAchieveTargetLength(stringHelper::strings & strings, std::string const& mainString, unsigned int const targetLength)
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
            auto pairOfIndex = containerHelper::getRangeFromSetBasedFromValue(transitionIndexes, splittingIndex);
            unsigned int lowerTransitionIndex(pairOfIndex.first+1);
            unsigned int upperTransitionIndex(pairOfIndex.second);
            int lowerDelta = splittingIndex-lowerTransitionIndex;
            int upperDelta = upperTransitionIndex-splittingIndex;

            if(upperDelta >= 0 && lowerDelta >= 0 && lowerTransitionIndex > previousSplittingIndex)
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
            else if(upperDelta >= 0)
            {
                splittingIndex = upperTransitionIndex;
            }
            else if(lowerDelta >= 0 && lowerTransitionIndex > previousSplittingIndex)
            {
                splittingIndex = lowerTransitionIndex;
            }
        }
        strings.emplace_back(mainString.substr(previousSplittingIndex, splittingIndex-previousSplittingIndex));
        previousSplittingIndex = splittingIndex;
    }
}

string stringHelper::getStringWithCapitalLetters(string const& mainString)
{
    string result;
    result.resize(mainString.length());
    transform(mainString.begin(), mainString.end(), result.begin(), ::toupper);
    return result;
}

string stringHelper::getStringWithLowerCaseLetters(string const& mainString)
{
    string result;
    result.resize(mainString.length());
    transform(mainString.begin(), mainString.end(), result.begin(), ::tolower);
    return result;
}

string stringHelper::getStringWithUrlDecodedString(string const& mainString)
{
    string result;
    int index = 0, length = mainString.length();
    while(index < length)
    {
        if(mainString[index] == '%' && (index < length-2) && isHexDigit(mainString[index + 1]) && isHexDigit(mainString[index + 2]))
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

string stringHelper::getStringWithoutStartingAndTrailingCharacters(string const& mainString, string const& characters)
{
    string result(mainString);
    int firstIndexOfNotOfCharacters(result.find_first_not_of(characters));
    if(isNotNpos(firstIndexOfNotOfCharacters))
    {
        result.erase(0, firstIndexOfNotOfCharacters);
        int lastIndexOfOfNotOfCharacters(result.find_last_not_of(characters));
        if(isNotNpos(lastIndexOfOfNotOfCharacters))
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

string stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(string const& mainString)
{
    return getStringWithoutStartingAndTrailingCharacters(mainString, WHITESPACE_STRING);
}

string stringHelper::getStringWithoutWhiteSpace(string const& mainString)
{
    string result;
    int index = 0, length = mainString.length();
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

string stringHelper::getStringWithoutRedundantWhiteSpace(string const& mainString)
{
    string result;
    int index = 0, length = mainString.length();
    while(index < length)
    {
        int indexNotWhiteSpace = mainString.find_first_not_of(WHITESPACE_STRING, index);
        if(isNpos(indexNotWhiteSpace)){break;}
        int indexWhiteSpace = mainString.find_first_of(WHITESPACE_STRING, indexNotWhiteSpace);
        index = (isNotNpos(indexWhiteSpace)) ? indexWhiteSpace : length;
        result += (!result.empty()) ? " " : "";
        result += mainString.substr(indexNotWhiteSpace, index-indexNotWhiteSpace);
    }
    return result;
}

string stringHelper::getStringWithoutQuotations(string const& mainString)
{
    int length = mainString.length();
    if(length>2 && mainString[0] == '\"' && mainString[length-1] == '\"')
    {
        return mainString.substr(1, length-2);
    }
    return mainString;
}

string stringHelper::getStringWithoutCharAtTheStartAndEnd(string const& mainString, char const char1)
{
    return getStringWithoutCharAtTheStart(getStringWithoutCharAtTheEnd(mainString, char1), char1);
}

string stringHelper::getStringWithoutCharAtTheStart(string const& mainString, char const char1)
{
    int length = mainString.length();
    int start = (mainString[0] == char1) ? 1 : 0;
    return mainString.substr(start, length-start);
}

string stringHelper::getStringWithoutCharAtTheEnd(string const& mainString, char const char1)
{
    int length = mainString.length();
    int end = (mainString[length-1] == char1) ? length-1 : length;
    return mainString.substr(0, end);
}

string stringHelper::getStringWithoutOpeningClosingOperators(string const& mainString, char const openingOperator, char const closingOperator)
{
    int length = mainString.length();
    int start = (mainString[0] == openingOperator) ? 1 : 0;
    int end = (mainString[length-1] == closingOperator) ? length-1 : length;
    return mainString.substr(start, end-start);
}

void stringHelper::copyBeforeStringAndAfterString(
        string const& mainString,
        string const& stringToSearch,
        string & beforeString,
        string & afterString,
        int const indexToStartTheSearch)
{
    beforeString.clear();
    afterString.clear();
    int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStartTheSearch);
    if(isNotNpos(firstIndexOfFirstString))
    {
        int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        beforeString = mainString.substr(0, firstIndexOfFirstString);
        afterString = mainString.substr(lastIndexOfFirstString);
    }
}

string stringHelper::getStringBeforeThisString(string const& mainString, string const& stringToSearch, int const indexToStart)
{
    string result;
    int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStart);
    if(isNotNpos(firstIndexOfFirstString))
    {
        result = mainString.substr(0, firstIndexOfFirstString);
    }
    return result;
}

string stringHelper::getStringAfterThisString(string const& mainString, string const& stringToSearch, int const indexToStart)
{
    string result;
    int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStart);
    if(isNotNpos(firstIndexOfFirstString))
    {
        int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        result = mainString.substr(lastIndexOfFirstString);
    }
    return result;
}

string stringHelper::getStringInBetweenTwoStrings(string const& mainString, string const& firstString, string const& secondString, int const indexToStart)
{
    string result;
    int firstIndexOfFirstString = mainString.find(firstString, indexToStart);
    if(isNotNpos(firstIndexOfFirstString))
    {
        int lastIndexOfFirstString = firstIndexOfFirstString + firstString.length();
        int firstIndexOfSecondString = mainString.find(secondString, lastIndexOfFirstString);
        if(isNotNpos(firstIndexOfSecondString))
        {
            result = mainString.substr(lastIndexOfFirstString, firstIndexOfSecondString-lastIndexOfFirstString);
        }
    }
    return result;
}

string stringHelper::getStringBeforeThisCharacters(string const& mainString, string const& characters, int const indexToStart)
{
    string result;
    int firstIndexOfNotOfCharacters(mainString.find_first_of(characters, indexToStart));
    if(isNotNpos(firstIndexOfNotOfCharacters))
    {
        result = mainString.substr(indexToStart, firstIndexOfNotOfCharacters-indexToStart);
    }
    return result;
}

string stringHelper::getStringByRepeatingUntilDesiredLength(std::string const& stringToRepeat, unsigned int desiredLength)
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

string stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(string const& path)
{
    bool isPreviousCharacterNonAlphanumeric = false;
    string correctPath = std::accumulate(path.cbegin(), path.cend(), string(""), [&isPreviousCharacterNonAlphanumeric](string const& currentString, char const currentCharacter)
    {
        string partialResult(currentString);
        if(!isLetterOrNumber(currentCharacter))
        {
            if(!isPreviousCharacterNonAlphanumeric){partialResult += "_";}
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

string stringHelper::getNumberAfterThisString(string const& mainString, string const& stringToSearch)
{
    string result;
    int firstIndexOfFirstString = mainString.find(stringToSearch);
    if(stringHelper::isNotNpos(firstIndexOfFirstString))
    {
        int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        int lastIndexOfNumber;
        for(lastIndexOfNumber = lastIndexOfFirstString; stringHelper::isNumber(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

string stringHelper::getHexNumberAfterThisString(string const& mainString, string const& stringToSearch)
{
    string result;
    int firstIndexOfFirstString = mainString.find(stringToSearch);
    if(stringHelper::isNotNpos(firstIndexOfFirstString))
    {
        int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        int lastIndexOfNumber;
        for(lastIndexOfNumber = lastIndexOfFirstString; stringHelper::isHexDigit(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

string stringHelper::getStringWithJustifyAlignment(string const& mainString, unsigned int length)
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

string stringHelper::getStringWithCenterAlignment(string const& mainString, unsigned int length)
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

string stringHelper::getStringWithRightAlignment(string const& mainString, unsigned int length)
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

string stringHelper::getStringWithLeftAlignment(string const& mainString, unsigned int length)
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

string stringHelper::getCorrectPathWithoutUrlParameters(string const& path)
{
    string correctPathWithoutUrlParameters(path);
    int indexOfQuestionMark = path.find_first_of("?");
    if(stringHelper::isNotNpos(indexOfQuestionMark))
    {
            correctPathWithoutUrlParameters = path.substr(0, indexOfQuestionMark);
    }
    return correctPathWithoutUrlParameters;
}

string stringHelper::getUrlParameters(string const& path)
{
    string urlParameters;
    int indexOfQuestionMark = path.find_first_of("?");
    if(stringHelper::isNotNpos(indexOfQuestionMark))
    {
            urlParameters = path.substr(indexOfQuestionMark);
    }
    return urlParameters;
}

string stringHelper::getCorrectPathWithReplacedSlashCharacters(string const& path, string const& slashCharacterString)
{
    bool isSlashDetected = false;
    string correctPath = std::accumulate(path.cbegin(), path.cend(), string(""),
                                         [&isSlashDetected, slashCharacterString]
                                         (string const& currentString, char const currentCharacter)
    {
        string partialResult(currentString);
        if(isSlashCharacter(currentCharacter))
        {
            if(!isSlashDetected){partialResult += slashCharacterString;}
        }
        else
        {
            partialResult += currentCharacter;
        }
        isSlashDetected = isSlashCharacter(currentCharacter);
        return partialResult;
    });
    return correctPath;
}

string stringHelper::getCorrectPathWithoutDoublePeriod(string const& mainString, string const& slashCharacterString)
{
    string correctPath(mainString);
    bool isDirectoryChanged = true;
    while(isDirectoryChanged)
    {
        isDirectoryChanged = false;
        int indexOfDoublePeriod = correctPath.find(slashCharacterString+".."+slashCharacterString);
        if(isNotNpos(indexOfDoublePeriod))
        {
            int indexOfNearestSlash = correctPath.find_last_of(slashCharacterString, indexOfDoublePeriod-1);
            if(isNotNpos(indexOfNearestSlash))
            {
                isDirectoryChanged = true;
                correctPath.erase(indexOfNearestSlash, indexOfDoublePeriod+3-indexOfNearestSlash);
            }
        }
    }
    return correctPath;
}

string stringHelper::getStringBeforeDoublePeriod(string const& mainString, string const& slashCharacterString)
{
    int indexOfLastDoublePeriod = mainString.rfind(string("..")+slashCharacterString);
    if(isNotNpos(indexOfLastDoublePeriod))
    {
        return mainString.substr(indexOfLastDoublePeriod+3);
    }
    return mainString;
}

string stringHelper::getImmediateDirectoryName(string const& mainString, string const& slashCharacterString)
{
    int indexLastCharacterToSearch = mainString.length();
    string result;
    while(result.empty())
    {
        int indexOfLastSlashString = mainString.find_last_of(slashCharacterString, indexLastCharacterToSearch);
        if(isNpos(indexOfLastSlashString))
        {
            break;
        }
        result = mainString.substr(indexOfLastSlashString+1, indexLastCharacterToSearch-indexOfLastSlashString);
        indexLastCharacterToSearch = indexOfLastSlashString-1;
    }
    return result;
}

template<char slashCharacter>
string stringHelper::getCorrectPathWithReplacedSlashCharacters(string const& path)
{
    return getCorrectPathWithReplacedSlashCharacters(path, string("")+slashCharacter);
}
template string stringHelper::getCorrectPathWithReplacedSlashCharacters<'\\'>(string const& path);
template string stringHelper::getCorrectPathWithReplacedSlashCharacters<'/'>(string const& path);

template<char slashCharacter>
string stringHelper::getCorrectPathWithoutDoublePeriod(string const& path)
{
    return getCorrectPathWithoutDoublePeriod(path, string("")+slashCharacter);
}
template string stringHelper::getCorrectPathWithoutDoublePeriod<'\\'>(string const& path);
template string stringHelper::getCorrectPathWithoutDoublePeriod<'/'>(string const& path);

template<char slashCharacter>
string stringHelper::getStringBeforeDoublePeriod(string const& path)
{
    return getStringBeforeDoublePeriod(path, string("")+slashCharacter);
}
template string stringHelper::getStringBeforeDoublePeriod<'\\'>(string const& path);
template string stringHelper::getStringBeforeDoublePeriod<'/'>(string const& path);

template<char slashCharacter>
string stringHelper::getImmediateDirectoryName(string const& path)
{
    return getImmediateDirectoryName(path, string("")+slashCharacter);
}
template string stringHelper::getImmediateDirectoryName<'\\'>(string const& path);
template string stringHelper::getImmediateDirectoryName<'/'>(string const& path);

bool stringHelper::convertStringToBool(string const& stringToConvert)
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
NumberType stringHelper::convertStringToNumber(string const& stringToConvert)
{
    bool isInteger = (typeid(NumberType) == typeid(int));
    bool isNumberNotYetEncountered(true);
    bool isPeriodNotYetEncountered(true);
    int negative(1);
    int decimalPlacesInPowersOfTen(10);
    NumberType value(0);
    for (char const currentCharacter : stringToConvert)
    {
        if(isNumber(currentCharacter))
        {
            if(isInteger || isPeriodNotYetEncountered) // consider "if constexpr"
            {
                value = (value * 10) + currentCharacter - '0';
                isNumberNotYetEncountered=false;
            }
            else
            {
                value = value + (((NumberType)currentCharacter - '0') / decimalPlacesInPowersOfTen);
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
    return value*negative;
}

template int stringHelper::convertStringToNumber<int>(string const& stringToConvert);
template unsigned int stringHelper::convertStringToNumber<unsigned int>(string const& stringToConvert);
template float stringHelper::convertStringToNumber<float>(string const& stringToConvert);
template double stringHelper::convertStringToNumber<double>(string const& stringToConvert);

template <typename NumberType>
NumberType stringHelper::convertHexStringToNumber(string const& stringToConvert)
{
    NumberType value = 0;
    for (char const currentCharacter : stringToConvert)
    {
        if(isHexDigit(currentCharacter))
        {
            value *= 16;
            if(isNumber(currentCharacter))
            {
                value += currentCharacter - '0';
            }
            else if(isCapitalLetter(currentCharacter))
            {
                value += currentCharacter - 'A' + 10;
            }
            else
            {
                value += currentCharacter - 'a' + 10;
            }
        }
    }
    return value;
}

template char stringHelper::convertHexStringToNumber<char>(string const& stringToConvert);
template int stringHelper::convertHexStringToNumber<int>(string const& stringToConvert);
template unsigned int stringHelper::convertHexStringToNumber<unsigned int>(string const& stringToConvert);
template unsigned char stringHelper::convertHexStringToNumber<unsigned char>(string const& stringToConvert);

template <typename NumberType>
string stringHelper::NumberToStringConverter::convert(NumberType number)
{
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
    return temporaryStream.str();
}

void stringHelper::NumberToStringConverter::setPrecision(int precision)
{
    m_precisionOptional.setValue(precision);
}

void stringHelper::NumberToStringConverter::setFieldWidth(int fieldWidth)
{
    m_fieldWidthOptional.setValue(fieldWidth);
}

void stringHelper::NumberToStringConverter::setFillCharacter(char fillCharacter)
{
    m_fillCharacterOptional.setValue(fillCharacter);
}

template string stringHelper::NumberToStringConverter::convert<int>(int number);
template string stringHelper::NumberToStringConverter::convert<unsigned int>(unsigned int number);
template string stringHelper::NumberToStringConverter::convert<float>(float number);
template string stringHelper::NumberToStringConverter::convert<double>(double number);

}//namespace alba
