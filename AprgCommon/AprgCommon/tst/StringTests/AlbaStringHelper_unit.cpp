#include <String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;
using namespace alba::stringHelper;

namespace alba
{

TEST(GetNewStringFromStringTest, FindAndReplaceStrings)
{
    string string1("Mark is the no#1 guy in the world. Mark is also the nicest guy.");

    EXPECT_FALSE(transformReplaceStringIfFound(string1, "alba", "ALBA"));
    EXPECT_TRUE(transformReplaceStringIfFound(string1, "Mark", "MARK"));
    EXPECT_EQ("MARK is the no#1 guy in the world. MARK is also the nicest guy.", string1);
    EXPECT_TRUE(transformReplaceStringIfFound(string1, "guy", "programmer"));
    EXPECT_EQ("MARK is the no#1 programmer in the world. MARK is also the nicest programmer.", string1);
}

TEST(GetNewStringFromStringTest, FindAndReplaceStringsWithRedundantStrings)
{
    string string1("Mark is the no#1 guy in the world. Mark is also the nicest guy.");

    EXPECT_TRUE(transformReplaceStringIfFound(string1, "M", "MMMMMMMMMMMM"));
    EXPECT_EQ("MMMMMMMMMMMMark is the no#1 guy in the world. MMMMMMMMMMMMark is also the nicest guy.", string1);
}

TEST(SplitStringTest, SplitBySpaces)
{
    string string1("   Mark is the no#1      guy in the  world.    Mark is also the nicest guy.    ");
    strings expectedStrings {"Mark", "is", "the", "no#1", "guy", "in", "the", "world.", "Mark", "is", "also", "the", "nicest", "guy."};
    strings actualStrings;
    splitToStrings<SplitStringType::WithoutDelimeters>(actualStrings, string1, " ");

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    unsigned int size = min(expectedStrings.size(), actualStrings.size());
    for(unsigned int i=0; i<size; i++)
    {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitBySpacesWithDelimeters)
{
    string string1("   Mark is the no#1      guy in the  world.   ");
    strings expectedStrings {" ", " ", " ", "Mark", " ", "is", " ", "the", " ", "no#1", " ", " ", " ", " ", " ", " ", "guy", " ", "in", " ", "the", " ", " ", "world.", " ", " ", " "};
    strings actualStrings;
    splitToStrings<SplitStringType::WithDelimeters>(actualStrings, string1, " ");

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    unsigned int size = min(expectedStrings.size(), actualStrings.size());
    for(unsigned int i=0; i<size; i++)
    {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitLinesToAchieveTargetLengthWithLargeTargetLength)
{
    string string1("   Mark is the no#1      guy in the  world.   ThisIsALongString");
    strings expectedStrings {"   Mark is", " the no#1 ", "     guy ", "in the  ", "world.   ", "ThisIsALongString"};
    strings actualStrings;
    const int targetLength = 10;

    splitLinesToAchieveTargetLength(actualStrings, string1, targetLength);

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    unsigned int size = min(expectedStrings.size(), actualStrings.size());
    for(unsigned int i=0; i<size; i++)
    {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitLinesToAchieveTargetLength_LastLineIsIncluded)
{
    string string1("TupcIlm starts when its deployed on board 0x1011 (same with legacy Aalman)");
    strings expectedStrings {"TupcIlm starts when its deployed", " on board 0x1011 (same with ", "legacy Aalman)"};
    strings actualStrings;
    const int targetLength = 30;

    splitLinesToAchieveTargetLength(actualStrings, string1, targetLength);

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    unsigned int size = min(expectedStrings.size(), actualStrings.size());
    for(unsigned int i=0; i<size; i++)
    {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitLinesToAchieveTargetLengthCanBeSplitPerCharacter)
{
    string string1("   Mark is the no#1      ");
    strings expectedStrings {" ", " ", " ", "Mark", " ", "is", " ", "the", " ", "no#1", " ", " ", " ", " ", " ", " "};
    strings actualStrings;
    const int targetLength = 1;

    splitLinesToAchieveTargetLength(actualStrings, string1, targetLength);

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    unsigned int size = min(expectedStrings.size(), actualStrings.size());
    for(unsigned int i=0; i<size; i++)
    {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitBySeriesOfDelimeters)
{
    string string1(R"(TLH_DEBUG_PRINT("Creating new licence entry in DB for featureCode: %d.", featureCode);)");
    strings delimeters{R"((")", R"(",)", ");"};
    strings expectedStrings{"TLH_DEBUG_PRINT", R"(Creating new licence entry in DB for featureCode: %d.)", " featureCode"};
    strings actualStrings;
    splitToStringsUsingASeriesOfDelimeters(actualStrings, string1, delimeters);

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    unsigned int size = min(expectedStrings.size(), actualStrings.size());
    for(unsigned int i=0; i<size; i++)
    {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(CombineStringTest, CombinedStringsWithComma)
{
    strings stringsToCombine {"Mark", "is", "the", "no#1", "guy", "in", "the", "world.", "Mark", "is", "also", "the", "nicest", "guy."};
    string expectedString("Mark,is,the,no#1,guy,in,the,world.,Mark,is,also,the,nicest,guy.");
    string actualString(combineStrings(stringsToCombine, ","));

    EXPECT_EQ(expectedString, actualString);
}

TEST(UniqueIdTest, GenerateUniqueId)
{
    string string1("Mark is the no#1 guy in the world. Mark is also the nicest guy.");
    string string2("MARK is the no#1 programmer in the world. MARK is also the nicest programmer.");
    unsigned int uniqueId1 = generateUniqueId(string1);
    unsigned int uniqueId2 = generateUniqueId(string2);
    EXPECT_EQ(552749853u, uniqueId1);
    EXPECT_EQ(1436619827u, uniqueId2);
}

TEST(ConstructFileLocatorTest, ConstructFileLocator)
{
    EXPECT_FALSE(constructFileLocator(__FILE__, __LINE__).empty());
}

TEST(RandomStringTest, RandomString100Characters)
{
    unsigned int length(100);
    EXPECT_EQ(length, getRandomAlphaNumericString(length).length());
}

TEST(UniqueIdTest, CheckLevenshteinDistance)
{
    string string1("This is a statement");
    string string2("This is  statement");
    string string3("This is not a statement");
    string string4("This is b statement");
    EXPECT_EQ(1u, getLevenshteinDistance(string1, string2));
    EXPECT_EQ(4u, getLevenshteinDistance(string1, string3));
    EXPECT_EQ(1u, getLevenshteinDistance(string1, string4));
}
TEST(ConvertCaseFromStringTest, ConvertToCapitalLettersUsingAllLetters)
{
    string testString("AbCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    EXPECT_EQ(capitalLetters, getStringWithCapitalLetters(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToCapitalLettersUsingAllLettersWithSpecialCharacters)
{
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("1234567890!@#$%^&*( )ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    EXPECT_EQ(capitalLetters, getStringWithCapitalLetters(testString));
}


TEST(ConvertCaseFromStringTest, ConvertToFirstNonWhiteSpaceCharacterToCapitalWithFirstLetter)
{
    string testString("abCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(capitalLetters, getStringWithFirstNonWhiteSpaceCharacterToCapital(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToFirstNonWhiteSpaceCharacterToCapitalWithFirstWhiteSpaceCharacter)
{
    string testString("     abCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("     AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(capitalLetters, getStringWithFirstNonWhiteSpaceCharacterToCapital(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToFirstNonWhiteSpaceCharacterToCapitalWithFirstNumber)
{
    string testString("1abCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("1abCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(capitalLetters, getStringWithFirstNonWhiteSpaceCharacterToCapital(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToLowerCaseLettersUsingAllLettersWithSpecialCharacters)
{
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string lowerCaseLetters("1234567890!@#$%^&*( )abcdefghijklmnopqrstuvwxyz");

    EXPECT_EQ(lowerCaseLetters, getStringWithLowerCaseLetters(testString));
}

TEST(ConvertUrlFromStringTest, DecodeUrlString)
{
    string testString("https%3A%2F%2Fmywebsite%2Fdocs%2Fenglish%2Fsite%2Fmybook.do%3Frequest_type");
    string decodedUrl("https://mywebsite/docs/english/site/mybook.do?request_type");

    EXPECT_EQ(decodedUrl, getStringWithUrlDecodedString(testString));
}

TEST(ConvertUrlFromStringTest, DecodeUrlString2)
{
    string testString("Last+Week+Tonight+with+John+Oliver-+The+IRS+%28HBO%29");
    string decodedUrl("Last+Week+Tonight+with+John+Oliver-+The+IRS+(HBO)");

    EXPECT_EQ(decodedUrl, getStringWithUrlDecodedString(testString));
}

TEST(GetPartialStringFromStringTest, GetStringThatContainsWhiteSpaceIndention)
{
    string testString("     \n\n1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z    ");
    string whiteSpaceIndention("     \n\n");

    EXPECT_EQ(whiteSpaceIndention, getStringThatContainsWhiteSpaceIndention(testString));
}

TEST(GetPartialStringFromStringTest, GetWithoutStartingAndTrailingWhiteSpaceUsingWhiteSpaceOnly)
{
    string testString("     \n\n    \t\t\t   ");
    EXPECT_TRUE(getStringWithoutStartingAndTrailingWhiteSpace(testString).empty());
}

TEST(GetPartialStringFromStringTest, GetWithoutStartingAndTrailingWhiteSpaceUsingAllLettersWithSpecialCharacters)
{
    string testString("     \n\n1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z    ");
    string withoutStartingAndTrailingWhiteSpace("1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z");

    EXPECT_EQ(withoutStartingAndTrailingWhiteSpace, getStringWithoutStartingAndTrailingWhiteSpace(testString));
}

TEST(GetPartialStringFromStringTest, GetWithoutRedundantWhiteSpaceUsingAllLettersWithSpecialCharacters)
{
    string testString("     \n\n1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z    ");
    string withoutRedundantWhiteSpace("1 2 3 4 5 6 7 8 9 0!@#$%^&*( )a b c d e f g h i j k l m n o p q r s t u v w x y z");

    EXPECT_EQ(withoutRedundantWhiteSpace, getStringWithoutRedundantWhiteSpace(testString));
}

TEST(GetPartialStringFromStringTest, GetWithoutRedundantWhiteSpaceWithTabsAndNewLine)
{
    string correctOutput("Mark is the no#1 guy in the world");
    EXPECT_EQ(correctOutput, getStringWithoutRedundantWhiteSpace("Mark is the no#1 guy in the world"));
    EXPECT_EQ(correctOutput, getStringWithoutRedundantWhiteSpace("    Mark    is the no#1 guy  in the     world    "));
    EXPECT_EQ(correctOutput, getStringWithoutRedundantWhiteSpace("Mark is\n\tthe\tno#1    \n\n\nguy\tin\r\rthe\nworld"));
}

TEST(GetPartialStringFromStringTest, GetStringWithoutQuotationsUsingAllLettersWithSpecialCharacters)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string withoutQuotations("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(withoutQuotations, getStringWithoutQuotations(testString));
}

TEST(GetPartialStringFromStringTest, GetStringWithoutCharacterAtTheStartUsingAllLetters)
{
    string testString("_AbCDEFghIjKlMnopQRstUvWxYz");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(withoutUnderscore, getStringWithoutCharAtTheStart(testString, '_'));
}

TEST(GetPartialStringFromStringTest, GetStringWithoutCharacterAtTheEndUsingAllLetters)
{
    string testString("AbCDEFghIjKlMnopQRstUvWxYz_");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(withoutUnderscore, getStringWithoutCharAtTheEnd(testString, '_'));
}

TEST(GetPartialStringFromStringTest, GetStringWithoutCharacterAtTheStartAndEndUsingAllLetters)
{
    string testString("_AbCDEFghIjKlMnopQRstUvWxYz_");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(withoutUnderscore, getStringWithoutCharAtTheStartAndEnd(testString, '_'));
}

TEST(GetPartialStringFromStringTest, GetStringBeforeThisStringWithCharactersAfterQuestionMarkIsRemoved)
{
    string testString("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg?v=1354256522");
    string withCharactersAfterQuestionMarkRemoved("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg");
    string questionMarkString("?");

    EXPECT_EQ(withCharactersAfterQuestionMarkRemoved, getStringBeforeThisString(testString, questionMarkString));
}

TEST(GetPartialStringFromStringTest, GetStringAfterThisStringUsingAllLettersWithSpecialCharacters)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string stringInBetweenAtTheStart(R"(567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string stringInBetweenInTheMiddle(R"(^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");

    EXPECT_EQ(stringInBetweenAtTheStart, getStringAfterThisString(testString, R"("1234)"));
    EXPECT_EQ(stringInBetweenInTheMiddle, getStringAfterThisString(testString, "@#$%"));
    EXPECT_TRUE(getStringAfterThisString(testString, "777").empty());
}

TEST(GetPartialStringFromStringTest, GetStringInBetweenTwoStringsUsingAllLettersWithSpecialCharacters)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string firstString("1234567890");
    string secondString("AbCDEFghIjKlMnopQRstUvWxYz");
    string stringInBetween("!@#$%^&*( )");

    EXPECT_EQ(stringInBetween, getStringInBetweenTwoStrings(testString, firstString, secondString));
    EXPECT_TRUE(getStringInBetweenTwoStrings(testString, secondString, firstString).empty());
    EXPECT_TRUE(getStringInBetweenTwoStrings(testString, firstString, firstString).empty());
}

TEST(GetPartialStringFromStringTest, GetStringBeforeThisCharacters)
{
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ("1234567890", getStringBeforeThisCharacters(testString, "$#^%@&!*"));
    EXPECT_EQ("1234567890!@#$%^&*(", getStringBeforeThisCharacters(testString, " "));
    EXPECT_EQ("", getStringBeforeThisCharacters(testString, "a"));
}

TEST(GetPartialStringFromStringTest, CopyBeforeStringAndAfterStringWhenStringIsFound)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string expectedBeforeString(R"("1234567890!@#$%^&*( ))");
    string expectedAfterString(R"(EFghIjKlMnopQRstUvWxYz")");
    string actualBeforeString;
    string actualAfterString;

    copyBeforeStringAndAfterString(testString, "AbCD", actualBeforeString, actualAfterString);
    EXPECT_EQ(expectedBeforeString, actualBeforeString);
    EXPECT_EQ(expectedAfterString, actualAfterString);
}

TEST(GetPartialStringFromStringTest, CopyBeforeStringAndAfterStringWhenStringIsNotFound)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string actualBeforeString;
    string actualAfterString;

    copyBeforeStringAndAfterString(testString, "777", actualBeforeString, actualAfterString);
    EXPECT_TRUE(actualBeforeString.empty());
    EXPECT_TRUE(actualBeforeString.empty());
}

TEST(GetNewStringFromStringTest, GetStringReplacingSpecialCharactersWithUnderscore)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string withoutSpecialCharacters("_1234567890_AbCDEFghIjKlMnopQRstUvWxYz_");

    EXPECT_EQ(withoutSpecialCharacters, getStringAndReplaceNonAlphanumericCharactersToUnderScore(testString));
}

TEST(GetNewStringFromStringTest, GetStringReplacingSpacesWithUnderscore)
{
    string testString(R"( Mark Earvin Alba 1234567890 ")");
    string withoutSpecialCharacters("_Mark_Earvin_Alba_1234567890_");

    EXPECT_EQ(withoutSpecialCharacters, getStringAndReplaceNonAlphanumericCharactersToUnderScore(testString));
}

TEST(GetNewStringFromStringTest, GetStringByRepeatingUntilDesiredLength)
{
    EXPECT_EQ("", getStringByRepeatingUntilDesiredLength("",50));
    EXPECT_EQ("", getStringByRepeatingUntilDesiredLength("MARK",0));
    EXPECT_EQ("MARKMARK", getStringByRepeatingUntilDesiredLength("MARK",8));
    EXPECT_EQ("MARKMARKMA", getStringByRepeatingUntilDesiredLength("MARK",10));
}


TEST(GetStringNumberFromStringTest, GetStringNumberAfterThisString)
{
    EXPECT_EQ(string("1234"), getNumberAfterThisString("INF/TCOM/R, nbccId: 1234, ", "nbccId: "));
    EXPECT_EQ(string("5678"), getNumberAfterThisString("INF/TCOM/R, nbccId: 5678 ", "nbccId: "));
    EXPECT_EQ(string("7890"), getNumberAfterThisString("INF/TCOM/R, nbccId: 7890", "nbccId: "));
}

TEST(GetStringNumberFromStringTest, GetStringHexNumberAfterThisString)
{
    EXPECT_EQ(string("AFBA"), getHexNumberAfterThisString("INF/TCOM/R, nbccId: AFBA, ", "nbccId: "));
    EXPECT_EQ(string("1234"), getHexNumberAfterThisString("INF/TCOM/R, nbccId: 1234 ", "nbccId: "));
    EXPECT_EQ(string("AC3EB434"), getHexNumberAfterThisString("INF/TCOM/R, nbccId: AC3EB434", "nbccId: "));
}

TEST(GetStringWithAlignmentFromStringTest, GetStringUsingJustifyAlignment)
{
    EXPECT_EQ(string("                        M                         "), getStringWithJustifyAlignment("M", 50));
    EXPECT_EQ(string("         M         a         r         k          "), getStringWithJustifyAlignment("Mark", 50));
    EXPECT_EQ(string("Mark        Earvin        Alba        1234567890  "), getStringWithJustifyAlignment("Mark Earvin Alba 1234567890", 50));
    EXPECT_EQ(string("Mark Earvin Alba 1234567890"), getStringWithJustifyAlignment("Mark Earvin Alba 1234567890", 1));
    EXPECT_EQ(string("                                                  "), getStringWithJustifyAlignment("", 50));
}

TEST(GetStringWithAlignmentFromStringTest, GetStringUsingCenterAlignment)
{
    EXPECT_EQ(string("                       Mark                       "), getStringWithCenterAlignment("Mark", 50));
    EXPECT_EQ(string("           Mark Earvin Alba 1234567890            "), getStringWithCenterAlignment("Mark Earvin Alba 1234567890", 50));
    EXPECT_EQ(string("Mark Earvin Alba 1234567890"), getStringWithCenterAlignment("Mark Earvin Alba 1234567890", 1));
    EXPECT_EQ(string("                                                  "), getStringWithCenterAlignment("", 50));
}

TEST(GetStringWithAlignmentFromStringTest, GetStringUsingRightAlignment)
{
    EXPECT_EQ(string("                                              Mark"), getStringWithRightAlignment("Mark", 50));
    EXPECT_EQ(string("                       Mark Earvin Alba 1234567890"), getStringWithRightAlignment("Mark Earvin Alba 1234567890", 50));
    EXPECT_EQ(string("Mark Earvin Alba 1234567890"), getStringWithRightAlignment("Mark Earvin Alba 1234567890", 1));
    EXPECT_EQ(string("                                                  "), getStringWithRightAlignment("", 50));
}

TEST(GetStringWithAlignmentFromStringTest, GetStringUsingLeftAlignment)
{
    EXPECT_EQ(string("Mark                                              "), getStringWithLeftAlignment("Mark", 50));
    EXPECT_EQ(string("Mark Earvin Alba 1234567890                       "), getStringWithLeftAlignment("Mark Earvin Alba 1234567890", 50));
    EXPECT_EQ(string("Mark Earvin Alba 1234567890"), getStringWithLeftAlignment("Mark Earvin Alba 1234567890", 1));
    EXPECT_EQ(string("                                                  "), getStringWithLeftAlignment("", 50));
}


TEST(GetNewStringFromStringTest, GetStringWithoutRedundantSlashesUsingAllLettersWithSpecialCharacters)
{
    string testString(R"(////DIR1\\/\\/\\/DIR2\\\\DIR3///DIR4\\\\//DIR5////\\\\)");
    string withoutRedundantSlashes(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");

    EXPECT_EQ(withoutRedundantSlashes, getCorrectPathWithReplacedSlashCharacters(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetStringWithoutRedundantPeriodInPathUsingAllLettersWithSpecialCharacters)
{
    string testString(R"(\DIR1\DIR2\..\DIR3\DIR4\..\..\DIR5\)");
    string withoutRedundantPeriodInPath(R"(\DIR1\DIR5\)");

    EXPECT_EQ(withoutRedundantPeriodInPath, getCorrectPathWithoutDoublePeriod(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetStringBeforeDoublePeriodInPathUsingAllLettersWithSpecialCharacters)
{
    string testString(R"(\DIR1\DIR2\..\DIR3\DIR4\..\..\DIR5\)");
    string beforeDoublePeriod(R"(DIR5\)");

    EXPECT_EQ(beforeDoublePeriod, getStringBeforeDoublePeriod(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetStringBeforeDoublePeriodInPathUsingNoDoublePeriodInput)
{
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");
    string beforeDoublePeriod(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");

    EXPECT_EQ(beforeDoublePeriod, getStringBeforeDoublePeriod(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetImmediateDirectoryNameUsingLastCharacterIsSlash)
{
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");
    string immediateDirectoryName("DIR5");

    EXPECT_EQ(immediateDirectoryName, getImmediateDirectoryName(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetImmediateDirectoryNameUsingLastCharacterIsNotSlash)
{
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5)");
    string immediateDirectoryName("DIR5");

    EXPECT_EQ(immediateDirectoryName, getImmediateDirectoryName(testString, R"(\)"));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringCaseSensitiveWithLettersOnly)
{
    string longString("Mark is the no#1 guy in the world");

    EXPECT_FALSE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "mark"));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "Mark"));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringCaseSensitiveWithLettersAndNumbersAndSpecialCharacters)
{
    string longString("Mark is the no#1 guy in the world");

    EXPECT_FALSE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "nO#1"));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "no#1"));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringCaseSensitiveWithSameLength)
{
    string longString("Attribute = ");

    EXPECT_FALSE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "aTTRIBUTE = "));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "Attribute = "));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringNotCaseSensitiveWithLettersOnly)
{
    string longString("Mark is the no#1 guy in the world");

    EXPECT_TRUE(isStringFoundInsideTheOtherStringNotCaseSensitive(longString, "mark"));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringNotCaseSensitive(longString, "Mark"));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringNotCaseSensitiveWithLettersAndNumbersAndSpecialCharacters)
{
    string longString("Mark is the no#1 guy in the world");

    EXPECT_TRUE(isStringFoundInsideTheOtherStringNotCaseSensitive(longString, "nO#1"));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringNotCaseSensitive(longString, "no#1"));
}

TEST(BooleanStringTest, StringCompareNotCaseSensitive)
{
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("1234567890!@#$%^&*( )abcdEFghijklMnOPQRstUvWxYz");

    EXPECT_TRUE(isEqualNotCaseSensitive(testString, capitalLetters));
}

TEST(BooleanStringTest, StringCompareWithLowestCommonLength)
{
    string testString1("1234567890!@#$%^&*( )AbCD");
    string testString2("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_TRUE(isEqualWithLowestCommonLength(testString1, testString2));
    EXPECT_TRUE(isEqualWithLowestCommonLength(testString2, testString1));
}

TEST(BooleanStringTest, IsNumberTest)
{
    string testString1("AbCDEFghIjKlMnopQRstUvWxYz");
    string testString2("AbCD1234567890!@#$%^&*( )");
    string testString3("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_FALSE(isNumber(testString1));
    EXPECT_TRUE(isNumber(testString2));
    EXPECT_TRUE(isNumber(testString3));
}

TEST(BooleanStringTest, IsWhiteSpaceTest)
{
    string testString1("   AbCDEFghIjKlMnopQRstUvWxYz  ");
    string testString2("       ");
    string testString3("   \n\n    \t\t\t\t");

    EXPECT_FALSE(isWhiteSpace(testString1));
    EXPECT_TRUE(isWhiteSpace(testString2));
    EXPECT_TRUE(isWhiteSpace(testString3));
}

TEST(BooleanStringTest, IsIdentifierTest)
{
    string testString1("   AbCDEFghIjKlMnopQRstUvWxYz  ");
    string testString2("   \n\n    \t\t\t\t");
    string testString3("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string testString4("abc1234");
    string testString5("_abc1234");

    EXPECT_FALSE(isIdentifier(testString1));
    EXPECT_FALSE(isIdentifier(testString2));
    EXPECT_FALSE(isIdentifier(testString3));
    EXPECT_TRUE(isIdentifier(testString4));
    EXPECT_TRUE(isIdentifier(testString5));
}

TEST(BooleanStringTest, IsOneWordTest)
{
    string testString1("   AbCDEFghIjKlMnopQRstUvWxYz  ");
    string testString2("   \n\n    \t\t\t\t");
    string testString3("AbCDE FghIj KlM nopQR stU vWx Yz");
    string testString4("AbCDEFghIjKlMnopQRstUvWxYz1234567890!@#$%^&*()");
    string testString5("");

    EXPECT_FALSE(isOneWord(testString1));
    EXPECT_FALSE(isOneWord(testString2));
    EXPECT_FALSE(isOneWord(testString3));
    EXPECT_TRUE(isOneWord(testString4));
    EXPECT_FALSE(isOneWord(testString5));
}

TEST(BooleanStringTest, IsWildcardMatchTest)
{
    EXPECT_TRUE(isWildcardMatch("alba", "a*ba"));
    EXPECT_TRUE(isWildcardMatch("albaisthebest", "al?ba*"));
    EXPECT_FALSE(isWildcardMatch("alba", "a*m"));
    EXPECT_FALSE(isWildcardMatch("markalba", "*mark"));
    EXPECT_TRUE(isWildcardMatch("markisthebest", "mark*best"));
    EXPECT_FALSE(isWildcardMatch("alba", "alb*b?a"));
    EXPECT_TRUE(isWildcardMatch("alba", "*l*a"));
    EXPECT_TRUE(isWildcardMatch("alba", "*?l*a"));
}

TEST(ConvertFromStringTest, ConvertStringToBool)
{
    EXPECT_TRUE(convertStringToBool("true"));
    EXPECT_FALSE(convertStringToBool("false"));
    EXPECT_TRUE(convertStringToBool("TruE"));
    EXPECT_FALSE(convertStringToBool("fAlse"));
    EXPECT_FALSE(convertStringToBool("0"));
    EXPECT_FALSE(convertStringToBool("00000"));
    EXPECT_TRUE(convertStringToBool("1"));
    EXPECT_TRUE(convertStringToBool("-892347589"));
    EXPECT_FALSE(convertStringToBool("this is a random string"));
}

TEST(ConvertFromStringTest, ConvertStringToIntegerWithNumbersOnly)
{
    EXPECT_EQ(0, convertStringToNumber<int>("this is a random string"));
    EXPECT_EQ(12345, convertStringToNumber<int>("12345"));
    EXPECT_EQ(-67890, convertStringToNumber<int>("-67890"));
    EXPECT_EQ(67890, convertStringToNumber<int>("--67890"));
    EXPECT_EQ(67890, convertStringToNumber<int>("--67-890"));
    EXPECT_EQ(67890, convertStringToNumber<int>("0--67-890"));
}

TEST(ConvertFromStringTest, ConvertStringToIntegerWithNumbersAndLettersAndSpecialCharacters)
{
    EXPECT_EQ(12345, convertStringToNumber<int>("1a2l3b4a5"));
    EXPECT_EQ(12345, convertStringToNumber<int>("12345.6789"));
    EXPECT_EQ(0, convertStringToNumber<int>("a&-.6$7*8(9)0"));
    EXPECT_EQ(6, convertStringToNumber<int>("$@!-a-a6.78)9(0"));
    EXPECT_EQ(6, convertStringToNumber<int>(")(*&^%$--6(*&.^%7-89(*&^%0"));
}

TEST(ConvertFromStringTest, ConvertStringToDoubleWithNumbersOnly)
{
    EXPECT_DOUBLE_EQ(12345.6789, convertStringToNumber<double>("12345.6789"));
    EXPECT_DOUBLE_EQ(-67890.1111, convertStringToNumber<double>("-67890.1111"));
    EXPECT_DOUBLE_EQ(67890.12345, convertStringToNumber<double>("--67890.12345"));
    EXPECT_DOUBLE_EQ(67890.9999999, convertStringToNumber<double>("--67-890.9999999"));
    EXPECT_DOUBLE_EQ(67890.67890, convertStringToNumber<double>("0--67-890. 67890"));
}

TEST(ConvertFromStringTest, ConvertStringToDoubleWithNumbersAndLettersAndSpecialCharacters)
{
    EXPECT_DOUBLE_EQ(12345.6789, convertStringToNumber<double>("12l3^s45.67l$89"));
    EXPECT_DOUBLE_EQ(-67890.1111, convertStringToNumber<double>("-67s8*a9s0.1s11d1"));
    EXPECT_DOUBLE_EQ(67890.12345, convertStringToNumber<double>("--6d&7sd8s90.12345"));
    EXPECT_DOUBLE_EQ(67890.9999999, convertStringToNumber<double>("--6s7-8$f90.9d9*99$999"));
    EXPECT_DOUBLE_EQ(67890.67890, convertStringToNumber<double>("0--67-j 8#9j0.678& dk90"));
}

TEST(ConvertFromStringTest, HexConvertStringToIntegerWithNumbersOnly)
{
    EXPECT_EQ(0x12345, convertHexStringToNumber<int>("12345"));
    EXPECT_EQ(0xABCDE, convertHexStringToNumber<int>("ABCDE"));
    EXPECT_EQ(0x1A2B3, convertHexStringToNumber<int>("1A2B3"));
    EXPECT_EQ(0xA1B2C, convertHexStringToNumber<int>("A1B2C"));
    EXPECT_EQ(0xA1B2C, convertHexStringToNumber<int>("xxxA#$%1 @#$#@B ^&*&^2%^&%^C*(&"));
}

TEST(ConvertFromStringTest, ConvertStringToDoubleWithAlbaNumber)
{
    AlbaNumber numberToVerify1(convertStringToAlbaNumber("12345"));
    AlbaNumber numberToVerify2(convertStringToAlbaNumber("12345.6789"));

    EXPECT_EQ(AlbaNumber::Type::Integer, numberToVerify1.getType());
    EXPECT_EQ(12345, numberToVerify1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, numberToVerify2.getType());
    EXPECT_DOUBLE_EQ(12345.6789, numberToVerify2.getDouble());
}

TEST(ConvertToStringTest, ConvertNumberToStringWithDefaultParameters)
{
    NumberToStringConverter converter;    EXPECT_EQ("12345", converter.convert(12345));
    EXPECT_EQ("12345.7", converter.convert(12345.6789));
    EXPECT_EQ("-67890.1", converter.convert(-67890.1111));
}
TEST(ConvertToStringTest, ConvertNumberToStringWithUnderPrecision)
{
    NumberToStringConverter converter;
    converter.setPrecision(8);
    EXPECT_EQ("12345", converter.convert(12345));
    EXPECT_EQ("12345.679", converter.convert(12345.6789));
    EXPECT_EQ("-67890.111", converter.convert(-67890.1111));
}

TEST(ConvertToStringTest, ConvertNumberToStringWithOverPrecision)
{
    NumberToStringConverter converter;
    converter.setPrecision(15);
    EXPECT_EQ("12345", converter.convert(12345));
    EXPECT_EQ("12345.6789", converter.convert(12345.6789));
    EXPECT_EQ("-67890.1111", converter.convert(-67890.1111));
}

TEST(ConvertToStringTest, ConvertNumberToStringWithLessFieldWidth)
{
    NumberToStringConverter converter;
    converter.setPrecision(15);
    converter.setFieldWidth(3);
    EXPECT_EQ("12345", converter.convert(12345));
    EXPECT_EQ("12345.6789", converter.convert(12345.6789));
    EXPECT_EQ("-67890.1111", converter.convert(-67890.1111));
}

TEST(ConvertToStringTest, ConvertNumberToStringWithMoreFieldWidth)
{
    NumberToStringConverter converter;
    converter.setPrecision(15);
    converter.setFieldWidth(15);
    EXPECT_EQ("          12345", converter.convert(12345));
    EXPECT_EQ("     12345.6789", converter.convert(12345.6789));
    EXPECT_EQ("    -67890.1111", converter.convert(-67890.1111));
}

TEST(ConvertToStringTest, ConvertNumberToStringWithFillCharacter)
{
    NumberToStringConverter converter;
    converter.setPrecision(15);
    converter.setFieldWidth(15);
    converter.setFillCharacter('0');
    EXPECT_EQ("000000000012345", converter.convert(12345));
    EXPECT_EQ("0000012345.6789", converter.convert(12345.6789));
    EXPECT_EQ("0000-67890.1111", converter.convert(-67890.1111));
}

}

