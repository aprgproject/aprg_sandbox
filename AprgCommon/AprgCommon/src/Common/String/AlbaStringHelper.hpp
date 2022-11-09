#pragma once

#include <Common/Container/AlbaOptional.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <iomanip>
#include <string>
#include <vector>

namespace alba
{

namespace stringHelper
{
using strings = std::vector<std::string>;
using StringPair = std::pair<std::string, std::string>;
using StringPairs = std::vector<StringPair>;

std::string const WHITESPACE_STRING = " \t\n\r";
std::string const ALPHA_NUMERIC_CHAR_MAP = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

inline bool isWhiteSpace(char const c)
{
    return (' '==c || '\t'==c || '\n'==c || '\r'==c);}

inline bool isNewline(char const c)
{
    return ('\n'==c || '\r'==c);
}

inline bool isNotNpos(int const index)
{
    //ToDo: is npos really unsigned? if its then convert to unsigned, do this to all npos functions
    return static_cast<int>(std::string::npos) != index;
}

inline bool isNpos(int const index)
{
    return static_cast<int>(std::string::npos) == index;
}

inline bool isValidIndex(int const index, int const stringLength)
{
    return  isNotNpos(index) && 0 <= index  && stringLength >= index;
}

inline bool isCapitalLetter(char const c)
{
    return ('A'<=c && 'Z'>=c) ;
}

inline bool isLetter(char const c)
{
    return ('a'<=c && 'z'>=c) || ('A'<=c && 'Z'>=c) ;
}

inline bool isNumber(char const c)
{
    return ('0'<=c && '9'>=c);
}

inline bool isUnderscore(char const c)
{
    return '_'==c;
}

inline bool isHexDigit(char const c)
{
    return isNumber(c) || ('a'<=c && 'f'>=c) || ('A'<=c && 'F'>=c);
}

inline bool isLetterOrNumber(char const c)
{
    return isLetter(c)||isNumber(c);
}

inline bool isLetterOrNumberOrUnderscore(char const c)
{
    return isLetter(c)||isNumber(c)||isUnderscore(c);
}

inline bool isSlashCharacter(char const c)
{
    return ('\\'==c || '/'==c);
}

inline bool isDisplayableCharacter(char const c)
{
    return (' '<=c && '~'>=c);
}

inline bool isNotEmptyLine(std::string const& mainString)
{
    return isNotNpos(static_cast<int>(mainString.find_first_not_of(WHITESPACE_STRING)));
}

inline bool isPeriodOrDoublePeriod(std::string const& mainString)
{
    return ("."==mainString)||(".."==mainString);
}

inline bool isLessThanStringLength(std::string const& mainString, int const index)
{
    return (index < static_cast<int>(mainString.length()));
}

unsigned int generateUniqueId(std::string const& mainString);
unsigned int getLevenshteinDistance(std::string const& string1, std::string const& string2);
unsigned int getHammingDistance(std::string const& string1, std::string const& string2);
unsigned int getNumberOfSubStrings(std::string const& mainString);
unsigned int getNumberOfSubsequences(std::string const& mainString);
int getRotationValue(std::string const& mainString, std::string const& rotation);
int getPeriodValue(std::string const& mainString, std::string const& period);


bool isNumber(std::string const& mainString);
bool isWhiteSpace(std::string const& mainString);
bool isNewline(std::string const& mainString);
bool isIdentifier(std::string const& mainString);
bool isOneWord(std::string const& mainString);
bool isSubstring(std::string const& mainString, std::string const& subString);
bool isSubsequence(std::string const& mainString, std::string const& subsequence);
bool isPrefix(std::string const& mainString, std::string const& prefix);
bool isSuffix(std::string const& mainString, std::string const& suffix);
bool isRotation(std::string const& mainString, std::string const& rotation);
bool isPeriod(std::string const& mainString, std::string const& period);
bool isBorder(std::string const& mainString, std::string const& border);
bool isEqualNotCaseSensitive(std::string const& mainString, std::string const& string2);
bool isEqualWithLowestCommonLength(std::string const& string1, std::string const& string2);
bool isStringFoundInsideTheOtherStringCaseSensitive(std::string const& mainString, std::string const& string2);
bool isStringFoundInsideTheOtherStringNotCaseSensitive(std::string const& mainString, std::string const& string2);
bool isWildcardMatch(std::string const& mainString, std::string const& wildcard, unsigned int const mainStringIndex=0, unsigned int const wildcardIndex=0);



// String processing

std::string getStringWithCapitalLetters(std::string const& mainString);
std::string getStringWithFirstNonWhiteSpaceCharacterToCapital(std::string const& mainString);
std::string getStringWithLowerCaseLetters(std::string const& mainString);
std::string getStringWithUrlDecodedString(std::string const& mainString);
std::string getStringThatContainsWhiteSpaceIndention(std::string const& mainString);
std::string getStringWithoutStartingAndTrailingCharacters(std::string const& mainString, std::string const& characters);
std::string getStringWithoutStartingAndTrailingWhiteSpace(std::string const& mainString);
std::string getStringWithoutWhiteSpace(std::string const& mainString);
std::string getStringWithoutRedundantWhiteSpace(std::string const& mainString);
std::string getStringWithoutQuotations(std::string const& mainString);
std::string getStringWithoutCharAtTheStartAndEnd(std::string const& mainString, char const char1);
std::string getStringWithoutCharAtTheStart(std::string const& mainString, char const char1);
std::string getStringWithoutCharAtTheEnd(std::string const& mainString, char const char1);
std::string getStringWithoutOpeningClosingOperators(std::string const& mainString, char const openingOperator, char const closingOperator);
std::string getLongestCommonPrefix(std::string const& first, std::string const& second);
void copyBeforeStringAndAfterString(std::string const& mainString, std::string const& stringToSearch, std::string & beforeString, std::string & afterString, unsigned int const indexToStartTheSearch = 0);
std::string getStringBeforeThisString(std::string const& mainString, std::string const& stringToSearch, unsigned int const indexToStart=0);
std::string getStringAfterThisString(std::string const& mainString, std::string const& stringToSearch, unsigned int const indexToStart=0);
std::string getStringInBetweenTwoStrings(std::string const& mainString, std::string const& firstString, std::string const& secondString, unsigned int const indexToStart=0);
std::string getStringBeforeThisCharacters(std::string const& mainString, std::string const& characters, unsigned int const indexToStart=0);
std::string getStringAndReplaceNonAlphanumericCharactersToUnderScore(std::string const& path);
std::string getStringByRepeatingUntilDesiredLength(std::string const& stringToRepeat, unsigned int desiredLength);
std::string getNumberAfterThisString(std::string const& mainString, std::string const& stringToSearch);
std::string getHexNumberAfterThisString(std::string const& mainString, std::string const& stringToSearch);
std::string getHexEquivalentOfCharacters(std::string const& stringToCheck);



// Utilities

std::string constructFileLocator(std::string const& file, int const lineNumber);
std::string getRandomAlphaNumericString(unsigned int const length);
strings getArgumentsToStringInMain(int const argc, char const * const argv[]);



// Find and replace

bool transformReplaceStringIfFound(std::string & mainString, std::string const& toReplace, std::string const& replaceWith);



// Split and combine

enum class SplitStringType
{
    WithDelimeters,
    WithoutDelimeters
};
template <SplitStringType splitStringType> void splitToStrings(strings & listOfStrings, std::string const& mainString, std::string const& delimiters);
std::string combineStrings(strings const& strings, std::string const& delimiters);
void splitLinesToAchieveTargetLength(strings & listOfStrings, std::string const& mainString, unsigned int const targetLength);
void splitToStringsUsingASeriesOfDelimeters(strings & listOfStrings, std::string const& mainString, strings const& seriesOfDelimiters);



// Wide string related

std::wstring convertStringToWideString(std::string const& stringInput);
std::string convertWideStringToString(std::wstring const& wstringInput);



// Alignments

std::string getStringWithJustifyAlignment(std::string const& mainString, unsigned int const length);
std::string getStringWithCenterAlignment(std::string const& mainString, unsigned int const length);
std::string getStringWithRightAlignment(std::string const& mainString, unsigned int const length);
std::string getStringWithLeftAlignment(std::string const& mainString, unsigned int const length);



// PathHelpers

std::string getCorrectPathWithoutUrlParameters(std::string const& path);
std::string getUrlParameters(std::string const& path);
std::string getCorrectPathWithReplacedSlashCharacters(std::string const& path, std::string const& slashCharacterString);
std::string getCorrectPathWithoutDoublePeriod(std::string const& mainString, std::string const& slashCharacterString);
std::string getStringBeforeDoublePeriod(std::string const& mainString, std::string const& slashCharacterString);
std::string getImmediateDirectoryName(std::string const& mainString, std::string const& slashCharacterString);
template <char slashCharacterString> std::string getCorrectPathWithReplacedSlashCharacters(std::string const& path);
template <char slashCharacterString> std::string getCorrectPathWithoutDoublePeriod(std::string const& path);
template <char slashCharacterString> std::string getStringBeforeDoublePeriod(std::string const& path);
template <char slashCharacterString> std::string getImmediateDirectoryName(std::string const& path);



// string to type converters

bool convertStringToBool(std::string const& stringToConvert);
template <typename NumberType> NumberType convertStringToNumber(std::string const& stringToConvert);
template <typename NumberType> NumberType convertHexCharacterToNumber(char const character);
template <typename NumberType> NumberType convertHexStringToNumber(std::string const& stringToConvert);
AlbaNumber convertStringToAlbaNumber(std::string const& stringToConvert);

template <typename NumberType>
NumberType convertStringToNumber(std::string const& stringToConvert)
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


template <typename NumberType>
NumberType convertHexCharacterToNumber(char const character)
{
    NumberType value{};
    if(isHexDigit(character))
    {
        if(isNumber(character))
        {
            value = static_cast<NumberType>(character - '0');
        }
        else if(isCapitalLetter(character))
        {
            value = static_cast<NumberType>(character - 'A' + 0xA);
        }
        else
        {
            value = static_cast<NumberType>(character - 'a' + 0xA);
        }
    }
    return value;
}

template <typename NumberType>
NumberType convertHexStringToNumber(std::string const& stringToConvert)
{
    NumberType value = 0;
    for (char const currentCharacter : stringToConvert)
    {
        if(isHexDigit(currentCharacter))
        {
            value *= 0x10;
            value += convertHexCharacterToNumber<NumberType>(currentCharacter);
        }
    }
    return value;
}



// type to string converters

std::string convertBoolToString(bool const value);

class NumberToStringConverter
{
public:
    template <typename NumberType> std::string convert(NumberType const number);
    std::string convert(AlbaNumber const& number);
    void setPrecision(int const precision);
    void setFieldWidth(int const fieldWidth);
    void setFillCharacter(char const fillCharacter);
    void setMaximumLength(unsigned int const maximumLength);
private:
    alba::AlbaOptional<int> m_precisionOptional;
    alba::AlbaOptional<int> m_fieldWidthOptional;
    alba::AlbaOptional<char> m_fillCharacterOptional;
    alba::AlbaOptional<unsigned int> m_maximumLengthOptional;
};

template <typename NumberType>
std::string NumberToStringConverter::convert(NumberType const number)
{
    std::string result;
    std::stringstream temporaryStream;
    if(m_precisionOptional)
    {
        temporaryStream.precision(m_precisionOptional.getReference());
    }
    if(m_fillCharacterOptional)
    {
        temporaryStream << std::setfill(m_fillCharacterOptional.getReference());
    }
    if(m_fieldWidthOptional)
    {
        temporaryStream << std::setw(m_fieldWidthOptional.getReference());
    }
    temporaryStream << number;
    result = temporaryStream.str();
    if(m_maximumLengthOptional)
    {
        result = result.substr(m_maximumLengthOptional.getReference());
    }
    return result;
}

} //namespace stringHelper

}//namespace alba
