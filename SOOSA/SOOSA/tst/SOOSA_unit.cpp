#include <SOOSA.hpp>
#include <SoosaConfiguration.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

TEST(SoosaTest, SampleTest1)
{
    SoosaConfiguration configuration;
    configuration.path = R"(C:\APRG\SOOSA\SOOSA\tst\FilesForTests\TestRotate.bmp)";
    configuration.formDetailsDirectoryPath = R"(C:\APRG\SOOSA\SOOSA\basis\FormDetails\)";
    configuration.area = "area";
    configuration.period = "period";
    configuration.discharge = "12.345";
    SOOSA soosa(configuration);
    soosa.process();
    EXPECT_EQ(5, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(2));    EXPECT_EQ(2, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(12));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(13));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(14));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(15));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(16));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(17));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(18));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(19));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(20));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(21));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(22));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(23));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(24));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(25));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(26));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(27));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(28));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(29));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(30));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(31));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(32));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(33));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(34));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(35));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(36));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(37));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(38));
}
