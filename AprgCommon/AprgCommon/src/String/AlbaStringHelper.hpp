#pragma once

#include <Optional/AlbaOptional.hpp>

#include <string>
#include <vector>

namespace alba
{

std::string const WHITESPACE_STRING = " \t\n\r";
std::string const ALPHA_NUMERIC_CHAR_MAP = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

namespace stringHelper
{

typedef std::vector<std::string> strings;

unsigned int getLevenshteinDistance(std::string const& mainString, std::string const& string2);
unsigned int generateUniqueId(std::string const& mainString);
std::string constructFileLocator(std::string file, int lineNumber);
std::string getRandomAlphaNumericString(unsigned int const length);

bool isStringFoundInsideTheOtherStringCaseSensitive(std::string const& mainString, std::string const& string2);
bool isStringFoundInsideTheOtherStringNotCaseSensitive(std::string const& mainString, std::string const& string2);
bool isEqualNotCaseSensitive(std::string const& mainString, std::string const& string2);
bool isEqualWithLowestCommonLength(std::string const& string1, std::string const& string2);
bool isNumber(std::string const& mainString);
bool isWhiteSpace(std::string const& mainString);
bool isIdentifier(std::string const& mainString);
bool isOneWord(std::string const& mainString);

bool transformReplaceStringIfFound(std::string & mainString, std::string const& toReplace, std::string const& replaceWith);
enum class SplitStringType
{
    WithDelimeters,
    WithoutDelimeters
};
template <SplitStringType splitStringType> void splitToStrings(strings & strings, std::string const& mainString,  std::string const& delimiters);
void splitLinesToAchieveTargetLength(stringHelper::strings & strings, std::string const& mainString, unsigned int const targetLength);

std::string getStringWithCapitalLetters(std::string const& mainString);
std::string getStringWithLowerCaseLetters(std::string const& mainString);
std::string getStringWithUrlDecodedString(std::string const& mainString);
std::string getStringThatContainsWhiteSpaceIndention(std::string const& mainString);
std::string getStringWithoutStartingAndTrailingCharacters(std::string const& mainString, std::string const& characters);
std::string getStringWithoutStartingAndTrailingWhiteSpace(std::string const& mainString);
std::string getStringWithoutWhiteSpace(std::string const& mainString);std::string getStringWithoutRedundantWhiteSpace(std::string const& mainString);
std::string getStringWithoutQuotations(std::string const& mainString);
std::string getStringWithoutCharAtTheStartAndEnd(std::string const& mainString, char const char1);
std::string getStringWithoutCharAtTheStart(std::string const& mainString, char const char1);std::string getStringWithoutCharAtTheEnd(std::string const& mainString, char const char1);
std::string getStringWithoutOpeningClosingOperators(std::string const& mainString, char const openingOperator, char const closingOperator);
void copyBeforeStringAndAfterString(std::string const& mainString, std::string const& stringToSearch, std::string & beforeString, std::string & afterString, int const indexToStartTheSearch = 0);
std::string getStringBeforeThisString(std::string const& mainString, std::string const& stringToSearch, int const indexToStart=0);
std::string getStringAfterThisString(std::string const& mainString, std::string const& stringToSearch, int const indexToStart=0);
std::string getStringInBetweenTwoStrings(std::string const& mainString, std::string const& firstString, std::string const& secondString, int const indexToStart=0);
std::string getStringBeforeThisCharacters(std::string const& mainString, std::string const& characters, int const indexToStart=0);
std::string getStringAndReplaceNonAlphanumericCharactersToUnderScore(std::string const& path);
std::string getStringByRepeatingUntilDesiredLength(std::string const& stringToRepeat, unsigned int desiredLength);
std::string getNumberAfterThisString(std::string const& mainString, std::string const& stringToSearch);std::string getHexNumberAfterThisString(std::string const& mainString, std::string const& stringToSearch);

std::string getStringWithJustifyAlignment(std::string const& mainString, unsigned int length);
std::string getStringWithCenterAlignment(std::string const& mainString, unsigned int length);std::string getStringWithRightAlignment(std::string const& mainString, unsigned int length);
std::string getStringWithLeftAlignment(std::string const& mainString, unsigned int length);

std::string getCorrectPathWithoutUrlParameters(std::string const& path);
std::string getUrlParameters(std::string const& path);
std::string getCorrectPathWithReplacedSlashCharacters(std::string const& path, std::string const& slashCharacterString);
std::string getCorrectPathWithoutDoublePeriod(std::string const& mainString, std::string const& slashCharacterString);
std::string getStringBeforeDoublePeriod(std::string const& mainString, std::string const& slashCharacterString);
std::string getImmediateDirectoryName(std::string const& mainString, std::string const& slashCharacterString);
template<char slashCharacterString> std::string getCorrectPathWithReplacedSlashCharacters(std::string const& path);
template<char slashCharacterString> std::string getCorrectPathWithoutDoublePeriod(std::string const& path);
template<char slashCharacterString> std::string getStringBeforeDoublePeriod(std::string const& path);
template<char slashCharacterString> std::string getImmediateDirectoryName(std::string const& path);

bool convertStringToBool(std::string const& stringToConvert);
template <typename NumberType> NumberType convertStringToNumber(std::string const& stringToConvert);
template <typename NumberType> NumberType convertHexStringToNumber(std::string const& stringToConvert);

class NumberToStringConverter
{
public:
    template <typename NumberType> std::string convert(NumberType number);
    void setPrecision(int precision);
    void setFieldWidth(int fieldWidth);
    void setFillCharacter(char fillCharacter);
private:
    alba::AlbaOptional<int> m_precisionOptional;
    alba::AlbaOptional<int> m_fieldWidthOptional;
    alba::AlbaOptional<char> m_fillCharacterOptional;
};

inline bool isWhiteSpace(char const c)
{
    return (' '==c || '\t'==c || '\n'==c || '\r'==c);
}

inline bool isNotNpos(int const index)
{
    return (int)std::string::npos != index;
}

inline bool isNpos(int const index)
{
    return (int)std::string::npos == index;
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

inline bool isPrintable(char const c)
{
    return (' '<=c && '~'>=c);
}

inline bool isSlashCharacter(char const c)
{
    return ('\\'==c || '/'==c);
}

inline bool isNotEmptyLine(std::string const& mainString)
{
    return isNotNpos(mainString.find_first_not_of(WHITESPACE_STRING));
}

inline bool isPeriodOrDoublePeriod(std::string const& mainString)
{
    return ("."==mainString)||(".."==mainString);
}

inline bool isLessThanStringLength(std::string const& mainString, int const index)
{
    return (index < (int)mainString.length());
}

} //namespace stringHelper

}//namespace alba
