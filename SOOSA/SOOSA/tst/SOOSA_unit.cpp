#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <SOOSA.hpp>
#include <InputConfiguration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace soosa
{

namespace
{

InputConfiguration getInputConfigurationForCharityPayWards(string const& inputPath)
{
    InputConfiguration inputConfiguration;
    inputConfiguration.setPath(inputPath);
    inputConfiguration.setFormDetailsTitle("Form Title");
    inputConfiguration.setMainParameters("area", "period", 12.345, 3U);
    inputConfiguration.addQuestion(1, "01. Patient Admission - promptness of service");
    inputConfiguration.addQuestion(1, "02. Patient Admission - courtesy of admitting clerks");
    inputConfiguration.addQuestion(1, "03. Patient Admission - ward policies are well-explained");
    inputConfiguration.addQuestion(1, "04. Hospital Environment - cleanliness of surroundings");
    inputConfiguration.addQuestion(1, "05. Hospital Environment - cleanliness of toilet/bathroom");
    inputConfiguration.addQuestion(1, "06. Hospital Environment - ventilation/air-conditioning");
    inputConfiguration.addQuestion(1, "07. Hospital Environment - lighting");
    inputConfiguration.addQuestion(1, "08. Hospital Environment - furniture and fixtures  are in good condition");
    inputConfiguration.addQuestion(1, "09. Hospital Environment - appliances  are working properly");
    inputConfiguration.addQuestion(1, "10. Nursing Care - promptness of service");
    inputConfiguration.addQuestion(1, "11. Nursing Care - quality of patient care");
    inputConfiguration.addQuestion(1, "12. Nursing Care - courtesy in dealing with patients");
    inputConfiguration.addQuestion(1, "13. Nursing Care - patient is well-informed regarding his medication, diagnostic tests, dietary needs, & others");
    inputConfiguration.addQuestion(1, "14. Medical Care - promptness of service");
    inputConfiguration.addQuestion(1, "15. Medical Care - quality of care and treatment");
    inputConfiguration.addQuestion(1, "16. Medical Care - courtesy in dealing with patients");
    inputConfiguration.addQuestion(1, "17. Medical Care - patient is well-informed regarding his condition/illness");
    inputConfiguration.addQuestion(1, "18. Pharmacy - availability of medicines and medical supplies");
    inputConfiguration.addQuestion(1, "19. Pharmacy - promptness of  service");
    inputConfiguration.addQuestion(1, "20. Pharmacy - courtesy of staff");
    inputConfiguration.addQuestion(2, "21. Dietary Food Service - quality/cleanliness of food");
    inputConfiguration.addQuestion(2, "22. Dietary Food Service - timeliness of meal service");
    inputConfiguration.addQuestion(2, "23. Medical Social Service - courtesy in dealing with patients");
    inputConfiguration.addQuestion(2, "24. Medical Social Service - provision of patient’s medical needs");
    inputConfiguration.addQuestion(2, "25. Laboratory - promptness of  service");
    inputConfiguration.addQuestion(2, "26. Laboratory - courtesy of staff");
    inputConfiguration.addQuestion(2, "27. Radiology - promptness of  service");
    inputConfiguration.addQuestion(2, "28. Radiology - courtesy of staff");
    inputConfiguration.addQuestion(2, "29. ECG - promptness of  service");
    inputConfiguration.addQuestion(2, "30. ECG - courtesy of staff");
    inputConfiguration.addQuestion(2, "31. Billing - promptness of  service");
    inputConfiguration.addQuestion(2, "32. Billing - courtesy of staff");
    inputConfiguration.addQuestion(2, "33. Cashier/Cash Services - promptness of  service");
    inputConfiguration.addQuestion(2, "34. Cashier/Cash Services - courtesy of staff");
    inputConfiguration.addQuestion(2, "35. Security Services - visibility of security personnel");
    inputConfiguration.addQuestion(2, "36. Security Services - courtesy of security personnel");
    inputConfiguration.addQuestion(2, "37. Patient Discharge - patient is well-informed regarding requirements prior to discharge");
    inputConfiguration.addQuestion(2, "38. Patient Discharge - adequacy of instructions regarding medication and on how to care for the patient at home");
    inputConfiguration.addQuestion(2, "39. Overall assessment of the hospital");
    return inputConfiguration;
}

void checkAnswersForCharityPayWards(SOOSA const& soosa)
{
    ASSERT_EQ(39U, soosa.getNumberOfAnswers());
    EXPECT_EQ(5U, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(1U, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(5U, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(1U, soosa.getAnswerToQuestion(12));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(13));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(14));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(15));
    EXPECT_EQ(5U, soosa.getAnswerToQuestion(16));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(17));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(18));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(19));
    EXPECT_EQ(1U, soosa.getAnswerToQuestion(20));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(21));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(22));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(23));
    EXPECT_EQ(5U, soosa.getAnswerToQuestion(24));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(25));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(26));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(27));
    EXPECT_EQ(1U, soosa.getAnswerToQuestion(28));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(29));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(30));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(31));
    EXPECT_EQ(5U, soosa.getAnswerToQuestion(32));
    EXPECT_EQ(4U, soosa.getAnswerToQuestion(33));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(34));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(35));
    EXPECT_EQ(1U, soosa.getAnswerToQuestion(36));
    EXPECT_EQ(2U, soosa.getAnswerToQuestion(37));
    EXPECT_EQ(3U, soosa.getAnswerToQuestion(38));
}

}

TEST(SoosaTest, SampleTest1)
{
    AlbaLocalPathHandler fileToTest(APRG_DIR R"(\SOOSA\FilesForTests\TestSoosa.bmp)");
    InputConfiguration inputConfiguration(getInputConfigurationForCharityPayWards(fileToTest.getFullPath()));
    SOOSA soosa(inputConfiguration);

    soosa.process();

    checkAnswersForCharityPayWards(soosa);
}

}

}
