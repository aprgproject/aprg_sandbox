#include "AlbaStringHelper.hpp"

#include <algorithm>
#include <cctype>
#include <functional>
#include <sstream>
#include <typeinfo>

using namespace std;

namespace alba{

unsigned int stringHelper::getLevenshteinDistance(string const& string1, string const& string2)
{
    int string1Length = string1.size();
    int string2Length = string2.size();

    vector<unsigned int> current(string2Length + 1);
    vector<unsigned int> previous(string2Length + 1);

    int i = 0;
    generate(previous.begin(), previous.end(), [&] {return i++; });

    for (i = 0; i < string1Length; ++i)
    {
        current[0] = i + 1;

        for (int j = 0; j < string2Length; ++j)
        {
            auto cost = string1[i] == string2[j] ? 0 : 1;
            current[j + 1] = min(min(current[j] + 1, previous[j + 1] + 1), previous[j] + cost);
        }

        current.swap(previous);
    }
    return previous[string2Length];
}

unsigned int stringHelper::generateUniqueId(string const& string1)
{
    unsigned int uniqueId=1;
    uniqueId = accumulate(string1.begin(), string1.end(), uniqueId, [](unsigned int c1, unsigned char c2)
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

bool stringHelper::isStringFoundInsideTheOtherStringCaseSensitive(string const& string1, string const& string2)
{
    return isNotNpos(string1.find(string2));
}

bool stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(string const& string1, string const& string2)
{
    return isStringFoundInsideTheOtherStringCaseSensitive(getStringWithCapitalLetters(string1), getStringWithCapitalLetters(string2));
}

bool stringHelper::isEqualNotCaseSensitive(string const& string1, string const& string2)
{
    return getStringWithCapitalLetters(string1) == getStringWithCapitalLetters(string2);
}

bool stringHelper::isNumber(string const& string1)
{
    return std::any_of(string1.begin(), string1.end(), [](char const character){ return isNumber(character);});
}

bool stringHelper::isWhiteSpace(string const& string1)
{
    return std::all_of(string1.begin(), string1.end(), [](char const character){ return isWhiteSpace(character);});
}

bool stringHelper::transformReplaceStringIfFound(string& string1, string const& toReplace, string const& replaceWith)
{
    bool found=false;
    int toReplaceLength = toReplace.length();
    int replaceWithLength = replaceWith.length();
    int index = string1.find(toReplace);
    while(isNotNpos(index))
    {
        found = true;
        string1.replace(index, toReplaceLength, replaceWith);
        index = string1.find(toReplace, index + replaceWithLength);
    }
    return found;
}

string stringHelper::getStringWithCapitalLetters(string const& string1)
{
    string result;
    result.resize(string1.length());
    transform(string1.begin(), string1.end(), result.begin(), ::toupper);
    return result;
}

string stringHelper::getStringWithLowerCaseLetters(string const& string1)
{
    string result;
    result.resize(string1.length());
    transform(string1.begin(), string1.end(), result.begin(), ::tolower);
    return result;
}

string stringHelper::getStringWithUrlDecodedString(string const& string1)
{
    string result;
    int index = 0, length = string1.length();
    while(index < length)
    {
        if(string1[index] == '%' && (index < length-2) && isHexDigit(string1[index + 1]) && isHexDigit(string1[index + 2]))
        {
            result += convertHexStringToNumber<char>(string1.substr(index + 1, 2));
            index += 3;
        }
        else
        {
            result += string1[index++];
        }
    }
    return result;
}

string stringHelper::getStringWithoutStartingAndTrailingCharacters(string const& string1, string const& characters)
{
    string result(string1);
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

string stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(string const& string1)
{
    return getStringWithoutStartingAndTrailingCharacters(string1, WHITESPACE_STRING);
}

string stringHelper::getStringWithoutRedundantWhiteSpace(string const& string1)
{
    string result;
    int index = 0, length = string1.length();
    while(index < length)
    {
        int indexNotWhiteSpace = string1.find_first_not_of(WHITESPACE_STRING, index);
        if(isNpos(indexNotWhiteSpace)){break;}
        int indexWhiteSpace = string1.find_first_of(WHITESPACE_STRING, indexNotWhiteSpace);
        index = (isNotNpos(indexWhiteSpace)) ? indexWhiteSpace : length;
        result += (!result.empty()) ? " " : "";
        result += string1.substr(indexNotWhiteSpace, index-indexNotWhiteSpace);
    }
    return result;
}

string stringHelper::getStringWithoutQuotations(string const& string1)
{
    int length = string1.length();
    if(length>2 && string1[0] == '\"' && string1[length-1] == '\"')
    {
        return string1.substr(1, length-2);
    }
    return string1;
}

string stringHelper::getStringWithoutCharAtTheStartAndEnd(string const& string1, char const char1)
{
    return getStringWithoutCharAtTheStart(getStringWithoutCharAtTheEnd(string1, char1), char1);
}

string stringHelper::getStringWithoutCharAtTheStart(string const& string1, char const char1)
{
    int length = string1.length();
    int start = (string1[0] == char1) ? 1 : 0;
    return string1.substr(start, length-start);
}

string stringHelper::getStringWithoutCharAtTheEnd(string const& string1, char const char1)
{
    int length = string1.length();
    int end = (string1[length-1] == char1) ? length-1 : length;
    return string1.substr(0, end);
}

string stringHelper::getStringWithoutOpeningClosingOperators(string const& string1, char const openingOperator, char const closingOperator)
{
    int length = string1.length();
    int start = (string1[0] == openingOperator) ? 1 : 0;
    int end = (string1[length-1] == closingOperator) ? length-1 : length;
    return string1.substr(start, end-start);
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

string stringHelper::getStringBeforeThisCharacters(string const& string1, string const& characters, int const indexToStart)
{
    string result;
    int firstIndexOfNotOfCharacters(string1.find_first_of(characters, indexToStart));
    if(isNotNpos(firstIndexOfNotOfCharacters))
    {
        result = string1.substr(indexToStart, firstIndexOfNotOfCharacters-indexToStart);
    }
    return result;
}

string stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(string const& path)
{
    bool isPreviousCharacterNonAlphanumeric = false;
    string correctPath = std::accumulate(path.cbegin(), path.cend(), string(""), [&isPreviousCharacterNonAlphanumeric](string partialResult, char const currentCharacter)
    {
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
                                         (string partialResult, char const currentCharacter)
    {
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

string stringHelper::getCorrectPathWithoutDoublePeriod(string const& string1, string const& slashCharacterString)
{
    string correctPath(string1);
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

string stringHelper::getStringBeforeDoublePeriod(string const& string1, string const& slashCharacterString)
{
    int indexOfLastDoublePeriod = string1.rfind(string("..")+slashCharacterString);
    if(isNotNpos(indexOfLastDoublePeriod))
    {
        return string1.substr(indexOfLastDoublePeriod+3);
    }
    return string1;
}

string stringHelper::getImmediateDirectoryName(string const& string1, string const& slashCharacterString)
{
    int indexLastCharacterToSearch = string1.length();
    string result;
    while(result.empty())
    {
        int indexOfLastSlashString = string1.find_last_of(slashCharacterString, indexLastCharacterToSearch);
        if(isNpos(indexOfLastSlashString))
        {
            break;
        }
        result = string1.substr(indexOfLastSlashString+1, indexLastCharacterToSearch-indexOfLastSlashString);
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
            if(isInteger || isPeriodNotYetEncountered)
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

template <typename NumberType>
string stringHelper::convertNumberToString(NumberType number)
{
    stringstream ss;
    ss.precision(10);
    ss << number;
    return ss.str();
}

template string stringHelper::convertNumberToString<int>(int number);
template string stringHelper::convertNumberToString<unsigned int>(unsigned int number);
template string stringHelper::convertNumberToString<float>(float number);
template string stringHelper::convertNumberToString<double>(double number);

}//namespace alba
