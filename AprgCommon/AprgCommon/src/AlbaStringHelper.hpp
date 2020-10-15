#pragma once

#include <string>

namespace alba{

std::string const WHITESPACE_STRING = " \t\n\r";

namespace stringHelper{

unsigned int getLevenshteinDistance(std::string const& string1, std::string const& string2);
unsigned int generateUniqueId(std::string const& string1);
std::string constructFileLocator(std::string file, int lineNumber);

bool isStringFoundInsideTheOtherStringCaseSensitive(std::string const& string1, std::string const& string2);
bool isStringFoundInsideTheOtherStringNotCaseSensitive(std::string const& string1, std::string const& string2);
bool isEqualNotCaseSensitive(std::string const& string1, std::string const& string2);
bool isNumber(std::string const& string1);
bool isWhiteSpace(std::string const& string1);

bool transformReplaceStringIfFound(std::string & string1, std::string const& toReplace, std::string const& replaceWith);

std::string getStringWithCapitalLetters(std::string const& string1);
std::string getStringWithLowerCaseLetters(std::string const& string1);
std::string getStringWithUrlDecodedString(std::string const& string1);
std::string getStringWithoutStartingAndTrailingCharacters(std::string const& string1, std::string const& characters);
std::string getStringWithoutStartingAndTrailingWhiteSpace(std::string const& string1);
std::string getStringWithoutRedundantWhiteSpace(std::string const& string1);
std::string getStringWithoutQuotations(std::string const& string1);
std::string getStringWithoutCharAtTheStartAndEnd(std::string const& string1, char const char1);
std::string getStringWithoutCharAtTheStart(std::string const& string1, char const char1);
std::string getStringWithoutCharAtTheEnd(std::string const& string1, char const char1);
std::string getStringWithoutOpeningClosingOperators(std::string const& string1, char const openingOperator, char const closingOperator);
void copyBeforeStringAndAfterString(std::string const& mainString, std::string const& stringToSearch, std::string & beforeString, std::string & afterString, int const indexToStartTheSearch = 0);
std::string getStringBeforeThisString(std::string const& mainString, std::string const& stringToSearch, int const indexToStart=0);
std::string getStringAfterThisString(std::string const& mainString, std::string const& stringToSearch, int const indexToStart=0);
std::string getStringInBetweenTwoStrings(std::string const& mainString, std::string const& firstString, std::string const& secondString, int const indexToStart=0);
std::string getStringBeforeThisCharacters(std::string const& mainString, std::string const& characters, int const indexToStart=0);
std::string getStringAndReplaceNonAlphanumericCharactersToUnderScore(std::string const& path);
std::string getNumberAfterThisString(std::string const& mainString, std::string const& stringToSearch);

std::string getCorrectPathWithoutUrlParameters(std::string const& path);
std::string getUrlParameters(std::string const& path);
std::string getCorrectPathWithReplacedSlashCharacters(std::string const& path, std::string const& slashCharacterString);
std::string getCorrectPathWithoutDoublePeriod(std::string const& string1, std::string const& slashCharacterString);
std::string getStringBeforeDoublePeriod(std::string const& string1, std::string const& slashCharacterString);
std::string getImmediateDirectoryName(std::string const& string1, std::string const& slashCharacterString);
template<char slashCharacterString> std::string getCorrectPathWithReplacedSlashCharacters(std::string const& path);
template<char slashCharacterString> std::string getCorrectPathWithoutDoublePeriod(std::string const& path);
template<char slashCharacterString> std::string getStringBeforeDoublePeriod(std::string const& path);
template<char slashCharacterString> std::string getImmediateDirectoryName(std::string const& path);

bool convertStringToBool(std::string const& stringToConvert);
template <typename NumberType> NumberType convertStringToNumber(std::string const& stringToConvert);
template <typename NumberType> NumberType convertHexStringToNumber(std::string const& stringToConvert);
template <typename NumberType> std::string convertNumberToString(NumberType number);

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
    return isLetter(c)||isNumber(c)||(c=='_');
}

inline bool isSlashCharacter(char const c)
{
    return ('\\'==c || '/'==c);
}

inline bool isNotEmptyLine(std::string const& string1)
{
    return isNotNpos(string1.find_first_not_of(WHITESPACE_STRING));
}

inline bool isPeriodOrDoublePeriod(std::string const& string1)
{
    return ("."==string1)||(".."==string1);
}

inline bool isLessThanStringLength(std::string const& string1, int const index)
{
    return (index < (int)string1.length());
}

} //namespace stringHelper

}//namespace alba
