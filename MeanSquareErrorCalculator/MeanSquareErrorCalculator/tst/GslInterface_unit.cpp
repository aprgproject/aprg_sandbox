#include <gtest/gtest.h>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <MeanSquareErrorCalculator.hpp>

#define PATH_OF_SAMPLE_FILE APRG_DIR APRG_DIR R"(PeerReviewCollator\PeerReviewCollator\tst\FilesForTests\Yee, Iangelo.csv)"
#define PATH_OF_SAMPLE_DIRECTORY APRG_DIR APRG_DIR R"(PeerReviewCollator\PeerReviewCollator\tst\FilesForTests\DirectoryTest)"
#define PATH_OF_OUTPUT_DIRECTORY APRG_DIR APRG_DIR R"(PeerReviewCollator\PeerReviewCollator\tst\FilesForTests\OutputDirectory)"

using namespace alba;
using namespace std;

TEST(PeerReviewCollatorTest, GetStringForEachCell_QuestionsLine)
{
    PeerReviewCollator collator;
    vector<string> stringsInEachCell;

    collator.copyStringsInEachCell(",Q1,In what areas does your colleague exceed the expectations from your pov? Give some examples/specifics if possible.,", stringsInEachCell);

    ASSERT_EQ(4, stringsInEachCell.size());
    EXPECT_TRUE(stringsInEachCell[0].empty());
    EXPECT_EQ("Q1", stringsInEachCell[1]);
    EXPECT_EQ("In what areas does your colleague exceed the expectations from your pov? Give some examples/specifics if possible.", stringsInEachCell[2]);
    EXPECT_TRUE(stringsInEachCell[3].empty());
}

TEST(PeerReviewCollatorTest, GetStringForEachCell_AnswerLine)
{
    PeerReviewCollator collator;
    vector<string> stringsInEachCell;

    collator.copyStringsInEachCell(R"(," about Alba, Mark Earvin",UniqueString1,)", stringsInEachCell);

    ASSERT_EQ(4, stringsInEachCell.size());
    EXPECT_TRUE(stringsInEachCell[0].empty());
    EXPECT_EQ(" about Alba, Mark Earvin", stringsInEachCell[1]);
    EXPECT_EQ("UniqueString1", stringsInEachCell[2]);
    EXPECT_TRUE(stringsInEachCell[3].empty());
}

TEST(PeerReviewCollatorTest, ProcessLine_OneQuestion)
{
    PeerReviewCollator collator;
    PeerReviewCollator::Questions& questions = collator.getQuestionsReference();

    collator.processLineForPerson("Yee, Iangelo", ",Q1,In what areas does your colleague exceed the expectations from your pov? Give some examples/specifics if possible.,");

    ASSERT_EQ(1, questions.size());
    ASSERT_TRUE(questions.find(1) != questions.end());
    EXPECT_EQ("In what areas does your colleague exceed the expectations from your pov? Give some examples/specifics if possible.", questions[1]);
}

TEST(PeerReviewCollatorTest, ProcessLine_QuestionThenAnswer)
{
    PeerReviewCollator collator;
    PeerReviewCollator::Questions& questions = collator.getQuestionsReference();
    PeerReviewCollator::Answers& answers = collator.getAnswersReference();

    collator.processLineForPerson("Yee, Iangelo", ",Q1,In what areas does your colleague exceed the expectations from your pov? Give some examples/specifics if possible.,");
    collator.processLineForPerson("Yee, Iangelo", R"(," about Mabasa, Jobelle",String1,)");

    ASSERT_EQ(1, questions.size());
    ASSERT_TRUE(questions.find(1) != questions.end());
    EXPECT_EQ("In what areas does your colleague exceed the expectations from your pov? Give some examples/specifics if possible.", questions[1]);
    ASSERT_EQ(1, answers.size());
    Answer& answer = answers.back();
    EXPECT_EQ("Yee, Iangelo", answer.m_person);
    EXPECT_EQ(1, answer.m_questionNumber);
    EXPECT_EQ("String1", answer.m_answer);
    EXPECT_EQ("Mabasa, Jobelle", answer.m_answerForPerson);
}

TEST(PeerReviewCollatorTest, ProcessFile_QuestionsAndAnswersAreCorrectlyRead)
{
    PeerReviewCollator collator;
    collator.processFile(PATH_OF_SAMPLE_FILE);
    PeerReviewCollator::Questions& questions = collator.getQuestionsReference();
    PeerReviewCollator::Answers& answers = collator.getAnswersReference();

    ASSERT_EQ(5, questions.size());
    ASSERT_TRUE(questions.find(1) != questions.end());
    ASSERT_TRUE(questions.find(2) != questions.end());
    ASSERT_TRUE(questions.find(3) != questions.end());
    ASSERT_TRUE(questions.find(4) != questions.end());
    ASSERT_TRUE(questions.find(5) != questions.end());
    EXPECT_EQ("In what areas does your colleague exceed the expectations from your pov? Give some examples/specifics if possible.", questions[1]);
    EXPECT_EQ("In what areas have you helped your colleague improve his/her own performance and to what extent? Give some examples/specifics if possible.", questions[2]);
    EXPECT_EQ("In what areas have your colleague helped you improve your own performance and to what extent? Give some examples/specifics if possible.", questions[3]);
    EXPECT_EQ("In your colleagues\x92 current role, what improvement would you like to see (i.e. areas of concern)? Give some examples/specifics if possible.", questions[4]);
    EXPECT_EQ("Any other comments/feedback?", questions[5]);

    ASSERT_EQ(140, answers.size());
}

TEST(PeerReviewCollatorTest, ProcessDirectory_ActualTest)
{
    PeerReviewCollator collator;
    PeerReviewCollator::Questions& questions = collator.getQuestionsReference();
    PeerReviewCollator::Answers& answers = collator.getAnswersReference();

    collator.processDirectory(PATH_OF_SAMPLE_DIRECTORY);

    ASSERT_EQ(5, questions.size());
    ASSERT_EQ(280, answers.size());
    collator.generateOutput(PATH_OF_OUTPUT_DIRECTORY);
}
