#include <AlbaStringHelper.hpp>

#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace alba::stringHelper;

TEST(GetDataFromStringTest, ConvertToCapitalLetters_AllEnglishLetters)
{
    string testString("AbCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    EXPECT_EQ(getStringWithCapitalLetters(testString), capitalLetters);
}

TEST(GetDataFromStringTest, ConvertToCapitalLetters_AllEnglishLettersWithSpecialCharacters)
{
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("1234567890!@#$%^&*( )ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    EXPECT_EQ(getStringWithCapitalLetters(testString), capitalLetters);
}

TEST(GetDataFromStringTest, ConvertToLowerCaseLetters_AllEnglishLettersWithSpecialCharacters)
{
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string lowerCaseLetters("1234567890!@#$%^&*( )abcdefghijklmnopqrstuvwxyz");

    EXPECT_EQ(getStringWithLowerCaseLetters(testString), lowerCaseLetters);
}

TEST(GetDataFromStringTest, DecodeUrlString)
{
    string testString("https%3A%2F%2Fmywebsite%2Fdocs%2Fenglish%2Fsite%2Fmybook.do%3Frequest_type");
    string decodedUrl("https://mywebsite/docs/english/site/mybook.do?request_type");

    EXPECT_EQ(getStringWithUrlDecodedString(testString), decodedUrl);
}

TEST(GetDataFromStringTest, DecodeUrlString2)
{
    string testString("Last+Week+Tonight+with+John+Oliver-+The+IRS+%28HBO%29");
    string decodedUrl("Last+Week+Tonight+with+John+Oliver-+The+IRS+(HBO)");

    EXPECT_EQ(getStringWithUrlDecodedString(testString), decodedUrl);
}

TEST(GetDataFromStringTest, GetWithoutStartingAndTrailingWhiteSpace_WhiteSpaceOnly)
{
    string testString("     \n\n    \t\t\t   ");
    EXPECT_TRUE(getStringWithoutStartingAndTrailingWhiteSpace(testString).empty());
}

TEST(GetDataFromStringTest, GetWithoutStartingAndTrailingWhiteSpace_AllEnglishLettersWithSpecialCharacters)
{
    string testString("     \n\n1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z    ");
    string withoutStartingAndTrailingWhiteSpace("1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z");

    EXPECT_EQ(getStringWithoutStartingAndTrailingWhiteSpace(testString), withoutStartingAndTrailingWhiteSpace);
}

TEST(GetDataFromStringTest, GetWithoutRedundantWhiteSpace_AllEnglishLettersWithSpecialCharacters)
{
    string testString("     \n\n1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z    ");
    string withoutRedundantWhiteSpace("1 2 3 4 5 6 7 8 9 0!@#$%^&*( )a b c d e f g h i j k l m n o p q r s t u v w x y z");

    EXPECT_EQ(getStringWithoutRedundantWhiteSpace(testString), withoutRedundantWhiteSpace);
}

TEST(GetDataFromStringTest, GetStringWithoutQuotations_AllEnglishLettersWithSpecialCharacters)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string withoutQuotations("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(getStringWithoutQuotations(testString), withoutQuotations);
}

TEST(GetDataFromStringTest, GetStringWithoutCharacterAtTheStart_AllEnglishLetters)
{
    string testString("_AbCDEFghIjKlMnopQRstUvWxYz");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(getStringWithoutCharAtTheStart(testString, '_'), withoutUnderscore);
}

TEST(GetDataFromStringTest, GetStringWithoutCharacterAtTheEnd_AllEnglishLetters)
{
    string testString("AbCDEFghIjKlMnopQRstUvWxYz_");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(getStringWithoutCharAtTheEnd(testString, '_'), withoutUnderscore);
}

TEST(GetDataFromStringTest, GetStringWithoutCharacterAtTheStartAndEnd_AllEnglishLetters)
{
    string testString("_AbCDEFghIjKlMnopQRstUvWxYz_");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(getStringWithoutCharAtTheStartAndEnd(testString, '_'), withoutUnderscore);
}

TEST(GetDataFromStringTest, GetStringBeforeThisString_WithCharactersAfterQuestionMarkRemoved)
{
    string testString("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg?v=1354256522");
    string withCharactersAfterQuestionMarkRemoved("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg");
    string questionMarkString("?");

    EXPECT_EQ(getStringBeforeThisString(testString, questionMarkString), withCharactersAfterQuestionMarkRemoved);
}

TEST(GetDataFromStringTest, GetStringAfterThisString_AllEnglishLettersWithSpecialCharacters)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string stringInBetweenAtTheStart(R"(567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string stringInBetweenInTheMiddle(R"(^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");

    EXPECT_EQ(getStringAfterThisString(testString, R"("1234)"), stringInBetweenAtTheStart);
    EXPECT_EQ(getStringAfterThisString(testString, "@#$%"), stringInBetweenInTheMiddle);
    EXPECT_TRUE(getStringAfterThisString(testString, "777").empty());
}

TEST(GetDataFromStringTest, GetStringInBetweenTwoStrings_AllEnglishLettersWithSpecialCharacters)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string firstString("1234567890");
    string secondString("AbCDEFghIjKlMnopQRstUvWxYz");
    string stringInBetween("!@#$%^&*( )");

    EXPECT_EQ(getStringInBetweenTwoStrings(testString, firstString, secondString), stringInBetween);
    EXPECT_TRUE(getStringInBetweenTwoStrings(testString, secondString, firstString).empty());
    EXPECT_TRUE(getStringInBetweenTwoStrings(testString, firstString, firstString).empty());
}

TEST(GetDataFromStringTest, CopyBeforeStringAndAfterString_AllEnglishLettersWithSpecialCharacters)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string expectedBeforeString(R"("1234567890!@#$%^&*( ))");
    string expectedAfterString(R"(EFghIjKlMnopQRstUvWxYz")");
    string actualBeforeString;
    string actualAfterString;

    copyBeforeStringAndAfterString(testString, "AbCD", actualBeforeString, actualAfterString);
    EXPECT_EQ(expectedBeforeString, actualBeforeString);
    EXPECT_EQ(expectedAfterString, actualAfterString);

    copyBeforeStringAndAfterString(testString, "777", actualBeforeString, actualAfterString);
    EXPECT_TRUE(actualBeforeString.empty());
    EXPECT_TRUE(actualBeforeString.empty());
}

TEST(GetDataFromStringTest, GetStringReplacingSpecialCharactersWithUnderscore)
{
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string withoutSpecialCharacters("_1234567890_AbCDEFghIjKlMnopQRstUvWxYz_");

    EXPECT_EQ(getStringAndReplaceNonAlphanumericCharactersToUnderScore(testString), withoutSpecialCharacters);
}

TEST(GetDataFromStringTest, GetStringReplacingSpacesWithUnderscore)
{
    string testString(R"( Mark Earvin Alba 1234567890 ")");
    string withoutSpecialCharacters("_Mark_Earvin_Alba_1234567890_");

    EXPECT_EQ(getStringAndReplaceNonAlphanumericCharactersToUnderScore(testString), withoutSpecialCharacters);
}

TEST (getStringNumberAfterThisStringTest, getStringNumberAfterThisStringTest)
{
    EXPECT_EQ(string("1234"), getNumberAfterThisString("INF/TCOM/R, nbccId: 1234, ", "nbccId: "));
    EXPECT_EQ(string("5678"), getNumberAfterThisString("INF/TCOM/R, nbccId: 5678 ", "nbccId: "));
    EXPECT_EQ(string("7890"), getNumberAfterThisString("INF/TCOM/R, nbccId: 7890", "nbccId: "));
}


TEST(GetDataFromStringTest, GetStringWithoutRedundantSlashes_AllEnglishLettersWithSpecialCharacters)
{
    string testString(R"(////DIR1\\/\\/\\/DIR2\\\\DIR3///DIR4\\\\//DIR5////\\\\)");
    string withoutRedundantSlashes(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");

    EXPECT_EQ(getCorrectPathWithReplacedSlashCharacters(testString, R"(\)"), withoutRedundantSlashes);
}

TEST(GetDataFromStringTest, GetStringWithoutRedundantPeriodInPath_AllEnglishLettersWithSpecialCharacters)
{
    string testString(R"(\DIR1\DIR2\..\DIR3\DIR4\..\..\DIR5\)");
    string withoutRedundantPeriodInPath(R"(\DIR1\DIR5\)");

    EXPECT_EQ(getCorrectPathWithoutDoublePeriod(testString, R"(\)"), withoutRedundantPeriodInPath);
}

TEST(GetDataFromStringTest, GetStringBeforeDoublePeriodInPath_AllEnglishLettersWithSpecialCharacters)
{
    string testString(R"(\DIR1\DIR2\..\DIR3\DIR4\..\..\DIR5\)");
    string beforeDoublePeriod(R"(DIR5\)");

    EXPECT_EQ(getStringBeforeDoublePeriod(testString, R"(\)"), beforeDoublePeriod);
}

TEST(GetDataFromStringTest, GetStringBeforeDoublePeriodInPath_NoDoublePeriodInput)
{
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");
    string beforeDoublePeriod(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");

    EXPECT_EQ(getStringBeforeDoublePeriod(testString, R"(\)"), beforeDoublePeriod);
}

TEST(GetDataFromStringTest, GetImmediateDirectoryName_LastCharacterIsSlash)
{
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");
    string immediateDirectoryName("DIR5");

    EXPECT_EQ(getImmediateDirectoryName(testString, R"(\)"), immediateDirectoryName);
}

TEST(GetDataFromStringTest, GetImmediateDirectoryName_LastCharacterIsNotSlash)
{
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5)");
    string immediateDirectoryName("DIR5");

    EXPECT_EQ(getImmediateDirectoryName(testString, R"(\)"), immediateDirectoryName);
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringCaseSensitive_WithLettersOnly)
{
    string longString("Mark is the no#1 guy in the world");

    EXPECT_FALSE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "mark"));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "Mark"));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringCaseSensitive_WithLettersAndNumbersAndSpecialCharacters)
{
    string longString("Mark is the no#1 guy in the world");

    EXPECT_FALSE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "nO#1"));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "no#1"));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringCaseSensitive_WithSameLength)
{
    string longString("Attribute = ");

    EXPECT_FALSE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "aTTRIBUTE = "));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringCaseSensitive(longString, "Attribute = "));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringNotCaseSensitive_WithLettersOnly)
{
    string longString("Mark is the no#1 guy in the world");

    EXPECT_TRUE(isStringFoundInsideTheOtherStringNotCaseSensitive(longString, "mark"));
    EXPECT_TRUE(isStringFoundInsideTheOtherStringNotCaseSensitive(longString, "Mark"));
}

TEST(BooleanStringTest, isStringFoundInsideTheOtherStringNotCaseSensitive_WithLettersAndNumbersAndSpecialCharacters)
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

TEST(GetDataFromStringTest, ConvertStringToBool)
{
    EXPECT_EQ(convertStringToBool("true"), true);
    EXPECT_EQ(convertStringToBool("false"), false);
    EXPECT_EQ(convertStringToBool("TruE"), true);
    EXPECT_EQ(convertStringToBool("fAlse"), false);
    EXPECT_EQ(convertStringToBool("0"), false);
    EXPECT_EQ(convertStringToBool("00000"), false);
    EXPECT_EQ(convertStringToBool("1"), true);
    EXPECT_EQ(convertStringToBool("-892347589"), true);
    EXPECT_EQ(convertStringToBool("this is a random string"), false);
    EXPECT_EQ(convertStringToNumber<int>("this is a random string"), 0);
}

TEST(GetDataFromStringTest, ConvertStringToInteger_WithNumbersOnly)
{
    EXPECT_EQ(convertStringToNumber<int>("12345"), 12345);
    EXPECT_EQ(convertStringToNumber<int>("-67890"), -67890);
    EXPECT_EQ(convertStringToNumber<int>("--67890"), 67890);
    EXPECT_EQ(convertStringToNumber<int>("--67-890"), 67890);
    EXPECT_EQ(convertStringToNumber<int>("0--67-890"), 67890);
}

TEST(GetDataFromStringTest, ConvertStringToInteger_WithNumbersAndLettersAndSpecialCharacters)
{
    EXPECT_DOUBLE_EQ(convertStringToNumber<int>("1a2l3b4a5"), 12345);
    EXPECT_DOUBLE_EQ(convertStringToNumber<int>("12345.6789"), 123456789);
    EXPECT_DOUBLE_EQ(convertStringToNumber<int>("a&-.6$7*8(9)0"), -67890);
    EXPECT_DOUBLE_EQ(convertStringToNumber<int>("$@!-a-a6.78)9(0"), 67890);
    EXPECT_DOUBLE_EQ(convertStringToNumber<int>(")(*&^%$--6(*&.^%7-89(*&^%0"), 67890);
}

TEST(GetDataFromStringTest, ConvertStringToDouble_WithNumbersOnly)
{
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("12345.6789"), 12345.6789);
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("-67890.1111"), -67890.1111);
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("--67890.12345"), 67890.12345);
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("--67-890.9999999"), 67890.9999999);
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("0--67-890.67890"), 67890.67890);
}

TEST(GetDataFromStringTest, ConvertStringToDouble_WithNumbersAndLettersAndSpecialCharacters)
{
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("12l3^s45.67l$89"), 12345.6789);
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("-67s8*a9s0.1s11d1"), -67890.1111);
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("--6d&7sd8s90.12345"), 67890.12345);
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("--6s7-8$f90.9d9*99$999"), 67890.9999999);
    EXPECT_DOUBLE_EQ(convertStringToNumber<double>("0--67-j8#9j0.678&dk90"), 67890.67890);
}

TEST(GetDataFromStringTest, HexConvertStringToInteger_WithNumbersOnly)
{
    EXPECT_EQ(convertHexStringToNumber<int>("12345"), 0x12345);
    EXPECT_EQ(convertHexStringToNumber<int>("ABCDE"), 0xABCDE);
    EXPECT_EQ(convertHexStringToNumber<int>("1A2B3"), 0x1A2B3);
    EXPECT_EQ(convertHexStringToNumber<int>("A1B2C"), 0xA1B2C);
    EXPECT_EQ(convertHexStringToNumber<int>("xxxA#$%1@#$#@B^&*&^2%^&%^C*(&"), 0xA1B2C);
}

TEST(GetDataFromStringTest, ConvertNumberToString)
{
    EXPECT_EQ(convertNumberToString(12345), "12345");
    EXPECT_EQ(convertNumberToString(12345.6789), "12345.6789");
    EXPECT_EQ(convertNumberToString(-67890.1111), "-67890.1111");
}

TEST(GetDataFromStringTest, RemoveWhitespacesFromString)
{
    string correctOutput("Mark is the no#1 guy in the world");
    EXPECT_EQ(getStringWithoutRedundantWhiteSpace("Mark is the no#1 guy in the world"), correctOutput);
    EXPECT_EQ(getStringWithoutRedundantWhiteSpace("    Mark    is the no#1 guy  in the     world    "), correctOutput);
    EXPECT_EQ(getStringWithoutRedundantWhiteSpace("Mark is\n\tthe\tno#1    \n\n\nguy\tin\r\rthe\nworld"), correctOutput);
}

TEST(TransformStringTest, FindAndReplaceStrings)
{
    string string1("Mark is the no#1 guy in the world. Mark is also the nicest guy.");
    EXPECT_EQ(transformReplaceStringIfFound(string1, "alba", "ALBA"), false);
    EXPECT_EQ(transformReplaceStringIfFound(string1, "Mark", "MARK"), true);
    EXPECT_EQ(string1, "MARK is the no#1 guy in the world. MARK is also the nicest guy.");
    EXPECT_EQ(transformReplaceStringIfFound(string1, "guy", "programmer"), true);
    EXPECT_EQ(string1, "MARK is the no#1 programmer in the world. MARK is also the nicest programmer.");
}

TEST(SplitStringTest, SplitBySpaces)
{
    string string1("   Mark is the no#1      guy in the  world.    Mark is also the nicest guy.    ");
    vector<string> expectedStrings {"Mark", "is", "the", "no#1", "guy", "in", "the", "world.", "Mark", "is", "also", "the", "nicest", "guy."};
    vector<string> actualStrings;
    splitString(actualStrings, string1, " ");

    EXPECT_EQ(actualStrings.size(), expectedStrings.size());
    int size = expectedStrings.size();
    for(int i=0; i<size; i++)
    {
        EXPECT_EQ(actualStrings[i], expectedStrings[i]);
    }
}

TEST(UniqueIdTest, GenerateUniqueId)
{
    string string1("Mark is the no#1 guy in the world. Mark is also the nicest guy.");
    string string2("MARK is the no#1 programmer in the world. MARK is also the nicest programmer.");
    unsigned int uniqueId1 = generateUniqueId(string1);
    unsigned int uniqueId2 = generateUniqueId(string2);
    EXPECT_EQ(uniqueId1, 552749853);    EXPECT_EQ(uniqueId2, 1436619827);
}

TEST(UniqueIdTest, CheckLevenshteinDistance){
    string string1("This is a statement");
    string string2("This is  statement");
    string string3("This is not a statement");
    string string4("This is b statement");
    EXPECT_EQ(getLevenshteinDistance(string1, string2), 1);
    EXPECT_EQ(getLevenshteinDistance(string1, string3), 4);
    EXPECT_EQ(getLevenshteinDistance(string1, string4), 1);
}
