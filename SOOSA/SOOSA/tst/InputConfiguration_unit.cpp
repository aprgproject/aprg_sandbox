#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <InputConfiguration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace soosa {

TEST(InputConfigurationTest, GetNumberOfColumnsWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_EQ(0U, inputConfiguration.getNumberOfColumns());

    inputConfiguration.addQuestion(1, "Question1AtColumn1");
    inputConfiguration.addQuestion(1, "Question2AtColumn1");
    inputConfiguration.addQuestion(1, "Question3AtColumn1");
    inputConfiguration.addQuestion(2, "Question1AtColumn2");
    inputConfiguration.addQuestion(2, "Question2AtColumn2");
    EXPECT_EQ(2U, inputConfiguration.getNumberOfColumns());
}

TEST(InputConfigurationTest, GetNumberOfQuestionsWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_EQ(0U, inputConfiguration.getNumberOfQuestions());

    inputConfiguration.addQuestion(1, "Question1AtColumn1");
    inputConfiguration.addQuestion(1, "Question2AtColumn1");
    inputConfiguration.addQuestion(1, "Question3AtColumn1");
    inputConfiguration.addQuestion(2, "Question1AtColumn2");
    inputConfiguration.addQuestion(2, "Question2AtColumn2");
    EXPECT_EQ(5U, inputConfiguration.getNumberOfQuestions());
}

TEST(InputConfigurationTest, GetNumberOfQuestionsAtColumnWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_EQ(0U, inputConfiguration.getNumberOfQuestionsAtColumn(1U));

    inputConfiguration.addQuestion(1, "Question1AtColumn1");
    inputConfiguration.addQuestion(1, "Question2AtColumn1");
    inputConfiguration.addQuestion(1, "Question3AtColumn1");
    inputConfiguration.addQuestion(2, "Question1AtColumn2");
    inputConfiguration.addQuestion(2, "Question2AtColumn2");
    EXPECT_EQ(3U, inputConfiguration.getNumberOfQuestionsAtColumn(1U));
    EXPECT_EQ(2U, inputConfiguration.getNumberOfQuestionsAtColumn(2U));
}

TEST(InputConfigurationTest, GetQuestionIndexInColumnWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_EQ(0U, inputConfiguration.getQuestionIndexInColumn(1U, 1U));

    inputConfiguration.addQuestion(1, "Question1AtColumn1");
    inputConfiguration.addQuestion(1, "Question2AtColumn1");
    inputConfiguration.addQuestion(1, "Question3AtColumn1");
    inputConfiguration.addQuestion(2, "Question1AtColumn2");
    inputConfiguration.addQuestion(2, "Question2AtColumn2");
    EXPECT_EQ(0U, inputConfiguration.getQuestionIndexInColumn(1U, 0U));
    EXPECT_EQ(1U, inputConfiguration.getQuestionIndexInColumn(1U, 1U));
    EXPECT_EQ(3U, inputConfiguration.getQuestionIndexInColumn(2U, 0U));
    EXPECT_EQ(4U, inputConfiguration.getQuestionIndexInColumn(2U, 1U));
}

TEST(InputConfigurationTest, GetMinimumSatisfactoryScoreWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_EQ(0U, inputConfiguration.getMinimumSatisfactoryScore());

    inputConfiguration.setMainParameters("AreaToTest", "PeriodToTest", 1.234, 7U);
    EXPECT_EQ(7U, inputConfiguration.getMinimumSatisfactoryScore());
}

TEST(InputConfigurationTest, GetQuestionAtWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_TRUE(inputConfiguration.getQuestionAt(1U).empty());

    inputConfiguration.addQuestion(1, "Question1AtColumn1");
    inputConfiguration.addQuestion(1, "Question2AtColumn1");
    inputConfiguration.addQuestion(1, "Question3AtColumn1");
    inputConfiguration.addQuestion(2, "Question1AtColumn2");
    inputConfiguration.addQuestion(2, "Question2AtColumn2");
    EXPECT_EQ("Question1AtColumn1", inputConfiguration.getQuestionAt(0U));
    EXPECT_EQ("Question2AtColumn1", inputConfiguration.getQuestionAt(1U));
    EXPECT_EQ("Question3AtColumn1", inputConfiguration.getQuestionAt(2U));
    EXPECT_EQ("Question1AtColumn2", inputConfiguration.getQuestionAt(3U));
    EXPECT_EQ("Question2AtColumn2", inputConfiguration.getQuestionAt(4U));
}

TEST(InputConfigurationTest, GetFormDetailsTitleWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_TRUE(inputConfiguration.getFormDetailsTitle().empty());

    inputConfiguration.setFormDetailsTitle("FormDetailsTitleToTest");
    EXPECT_EQ("FormDetailsTitleToTest", inputConfiguration.getFormDetailsTitle());
}

TEST(InputConfigurationTest, GetPathWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_TRUE(inputConfiguration.getPath().empty());

    inputConfiguration.setPath("PathToTest");
    EXPECT_EQ("PathToTest", inputConfiguration.getPath());
}

TEST(InputConfigurationTest, GetAreaWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_TRUE(inputConfiguration.getArea().empty());

    inputConfiguration.setMainParameters("AreaToTest", "PeriodToTest", 1.234, 7U);
    EXPECT_EQ("AreaToTest", inputConfiguration.getArea());
}

TEST(InputConfigurationTest, GetPeriodWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_TRUE(inputConfiguration.getPeriod().empty());

    inputConfiguration.setMainParameters("AreaToTest", "PeriodToTest", 1.234, 7U);
    EXPECT_EQ("PeriodToTest", inputConfiguration.getPeriod());
}

TEST(InputConfigurationTest, GetDischargeWorks) {
    InputConfiguration inputConfiguration;

    EXPECT_EQ(0U, inputConfiguration.getDischarge());

    inputConfiguration.setMainParameters("AreaToTest", "PeriodToTest", 1.234, 7U);
    EXPECT_DOUBLE_EQ(1.234, inputConfiguration.getDischarge());
}

TEST(InputConfigurationTest, SetPathWorks) {
    InputConfiguration inputConfiguration;

    inputConfiguration.setPath("PathToTest");

    EXPECT_EQ("PathToTest", inputConfiguration.getPath());
}

TEST(InputConfigurationTest, SetMainParametersWorks) {
    InputConfiguration inputConfiguration;

    inputConfiguration.setMainParameters("AreaToTest", "PeriodToTest", 1.234, 7U);

    EXPECT_EQ("AreaToTest", inputConfiguration.getArea());
    EXPECT_EQ("PeriodToTest", inputConfiguration.getPeriod());
    EXPECT_DOUBLE_EQ(1.234, inputConfiguration.getDischarge());
    EXPECT_EQ(7U, inputConfiguration.getMinimumSatisfactoryScore());
}

TEST(InputConfigurationTest, AddQuestionWorks) {
    InputConfiguration inputConfiguration;

    inputConfiguration.addQuestion(1, "Question1AtColumn1");
    inputConfiguration.addQuestion(2, "Question1AtColumn2");
    inputConfiguration.addQuestion(3, "Question1AtColumn3");
    inputConfiguration.addQuestion(3, "Question2AtColumn3");

    ASSERT_EQ(3U, inputConfiguration.getNumberOfColumns());
    EXPECT_EQ(1U, inputConfiguration.getNumberOfQuestionsAtColumn(1U));
    ASSERT_EQ(4U, inputConfiguration.getNumberOfQuestions());
    EXPECT_EQ("Question1AtColumn1", inputConfiguration.getQuestionAt(0U));
}

TEST(InputConfigurationTest, SetFormDetailsTitleWorks) {
    InputConfiguration inputConfiguration;

    inputConfiguration.setFormDetailsTitle("FormDetailsTitleToTest");

    EXPECT_EQ("FormDetailsTitleToTest", inputConfiguration.getFormDetailsTitle());
}

}  // namespace soosa

}  // namespace alba
