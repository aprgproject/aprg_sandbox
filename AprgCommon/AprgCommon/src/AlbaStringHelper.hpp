#pragma once

#include <string>

using std::string;

namespace alba{

string const WHITESPACE_STRING = " \t\n\r";

namespace stringHelper{

unsigned int getLevenshteinDistance(string const& string1, string const& string2);
unsigned int generateUniqueId(string const& string1);
string constructFileLocator(string file, int lineNumber);

bool isStringFoundInsideTheOtherStringCaseSensitive(string const& string1, string const& string2);
bool isStringFoundInsideTheOtherStringNotCaseSensitive(string const& string1, string const& string2);
bool isEqualNotCaseSensitive(string const& string1, string const& string2);

bool transformReplaceStringIfFound(string& string1, string const& toReplace, string const& replaceWith);

string getStringWithCapitalLetters(string const& string1);
string getStringWithLowerCaseLetters(string const& string1);
string getStringWithUrlDecodedString(string const& string1);
string getStringWithoutStartingAndTrailingWhiteSpace(string const& string1);
string getStringWithoutRedundantWhiteSpace(string const& string1);
string getStringWithoutQuotations(string const& string1);
string getStringWithoutCharAtTheStartAndEnd(string const& string1, char const char1);
string getStringWithoutCharAtTheStart(string const& string1, char const char1);
string getStringWithoutCharAtTheEnd(string const& string1, char const char1);
string getStringWithoutOpeningClosingOperators(string const& string1, char const openingOperator, char const closingOperator);
void copyBeforeStringAndAfterString(string const& mainString, string const& stringToSearch, string & beforeString, string & afterString, int const indexToStartTheSearch = 0);
string getStringBeforeThisString(string const& mainString, string const& stringToSearch, int const indexToStart=0);
string getStringAfterThisString(string const& mainString, string const& stringToSearch, int const indexToStart=0);
string getStringInBetweenTwoStrings(string const& mainString, string const& firstString, string const& secondString, int const indexToStart=0);
string getStringAndReplaceNonAlphanumericCharactersToUnderScore(string const& path);
string getNumberAfterThisString(string const& mainString, string const& stringToSearch);

string getCorrectPathWithoutUrlParameters(string const& path);
string getUrlParameters(string const& path);
string getCorrectPathWithReplacedSlashCharacters(string const& path, string const& slashCharacterString);
string getCorrectPathWithoutDoublePeriod(string const& string1, string const& slashCharacterString);
string getStringBeforeDoublePeriod(string const& string1, string const& slashCharacterString);
string getImmediateDirectoryName(string const& string1, string const& slashCharacterString);
template<char slashCharacterString> string getCorrectPathWithReplacedSlashCharacters(string const& path);
template<char slashCharacterString> string getCorrectPathWithoutDoublePeriod(string const& path);
template<char slashCharacterString> string getStringBeforeDoublePeriod(string const& path);
template<char slashCharacterString> string getImmediateDirectoryName(string const& path);

bool convertStringToBool(string const& stringToConvert);
template <typename NumberType> NumberType convertStringToNumber(string const& stringToConvert);
template <typename NumberType> NumberType convertHexStringToNumber(string const& stringToConvert);
template <typename NumberType> string convertNumberToString(NumberType number);

inline bool isWhiteSpace(char const c)
{
    return (' '==c || '\t'==c || '\n'==c || '\r'==c);
}

inline bool isNotNpos(int const index)
{
    return (int)string::npos != index;
}

inline bool isNpos(int const index)
{
    return (int)string::npos == index;
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

inline bool isNotEmptyLine(string const& string1)
{
    return isNotNpos(string1.find_first_not_of(WHITESPACE_STRING));
}

inline bool isPeriodOrDoublePeriod(string const& string1)
{
    return ("."==string1)||(".."==string1);
}

inline bool isLessThanStringLength(string const& string1, int const index)
{
    return (index < (int)string1.length());
}

} //namespace stringHelper

}//namespace alba
