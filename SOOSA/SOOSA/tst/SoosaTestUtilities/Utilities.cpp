#include "Utilities.hpp"

using namespace std;

namespace alba {

namespace soosa {

SoosaConfiguration getSoosaConfiguration() {
    SoosaConfiguration soosaConfiguration;

    // Line model parameters
    soosaConfiguration.bufferNameAndValueString("m_acceptableLineDeviationForLineModelInPixels", "2");
    soosaConfiguration.bufferNameAndValueString("m_removalRatioForSquareErrorsInLineModel", "0.05");
    soosaConfiguration.bufferNameAndValueString("m_minimumLineSamples", "10");

    // Line and bar parameters
    soosaConfiguration.bufferNameAndValueString("m_bitmapWidthToBarWidthMultiplier", "0.05");
    soosaConfiguration.bufferNameAndValueString("m_lineBarWidthSearchInitialBlackPointsValue", "20");
    soosaConfiguration.bufferNameAndValueString("m_lineBarWidthSearchAcceptedRunningBlackRatio", "0.80");
    soosaConfiguration.bufferNameAndValueString("m_acceptableDistanceOverWidthRatioFromWidthMidpoint", "0.40");
    soosaConfiguration.bufferNameAndValueString("m_acceptableMinimumDistanceFromWidthMidpoint", "4.00");
    soosaConfiguration.bufferNameAndValueString("m_acceptableSdOverMeanDeviationForLine", "0.50");
    soosaConfiguration.bufferNameAndValueString("m_acceptableSdOverMeanDeviationForBar", "0.10");
    soosaConfiguration.bufferNameAndValueString("m_removalRatioForLineAndBar", "0.05");
    soosaConfiguration.bufferNameAndValueString("m_initialValueForMaximumDistanceBetweenBarHeights", "10.00");
    soosaConfiguration.bufferNameAndValueString("m_multiplierForMaximumDistanceBetweenBarHeights", "0.10");
    soosaConfiguration.bufferNameAndValueString("m_acceptableSdOverMeanDeviationForBarHeight", "0.10");
    soosaConfiguration.bufferNameAndValueString("m_removalRatioForBarHeight", "0.02");

    // Choices related parameters
    soosaConfiguration.bufferNameAndValueString("m_numberOfChoices", "5");
    soosaConfiguration.bufferNameAndValueString("m_colorIntensityForWhite", "170");
    soosaConfiguration.bufferNameAndValueString("m_barHeightToDiameterMultiplier", "0.75");
    soosaConfiguration.bufferNameAndValueString("m_minimumPercentageOfBlackPixelsForAFilledCircle", "0.40");

    soosaConfiguration.update();
    return soosaConfiguration;
}

InputConfiguration getInputConfigurationForCharityPayWards(string const& inputPath) {
    InputConfiguration inputConfiguration;
    inputConfiguration.setPath(inputPath);
    inputConfiguration.setFormDetailsTitle("Form Title");
    inputConfiguration.setMainParameters("area", "period", 12.345, 3);
    inputConfiguration.addQuestion(1, "01. Patient Admission - promptness of service");
    inputConfiguration.addQuestion(1, "02. Patient Admission - courtesy of admitting clerks");
    inputConfiguration.addQuestion(1, "03. Patient Admission - ward policies are well-explained");    inputConfiguration.addQuestion(1, "04. Hospital Environment - cleanliness of surroundings");
    inputConfiguration.addQuestion(1, "05. Hospital Environment - cleanliness of toilet/bathroom");
    inputConfiguration.addQuestion(1, "06. Hospital Environment - ventilation/air-conditioning");
    inputConfiguration.addQuestion(1, "07. Hospital Environment - lighting");    inputConfiguration.addQuestion(1, "08. Hospital Environment - furniture and fixtures  are in good condition");
    inputConfiguration.addQuestion(1, "09. Hospital Environment - appliances  are working properly");
    inputConfiguration.addQuestion(1, "10. Nursing Care - promptness of service");
    inputConfiguration.addQuestion(1, "11. Nursing Care - quality of patient care");
    inputConfiguration.addQuestion(1, "12. Nursing Care - courtesy in dealing with patients");
    inputConfiguration.addQuestion(
        1,
        "13. Nursing Care - patient is well-informed regarding his medication, diagnostic tests, dietary needs, & "
        "others");
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
    inputConfiguration.addQuestion(2, "24. Medical Social Service - provision of patient's medical needs");
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
    inputConfiguration.addQuestion(
        2, "37. Patient Discharge - patient is well-informed regarding requirements prior to discharge");
    inputConfiguration.addQuestion(
        2,
        "38. Patient Discharge - adequacy of instructions regarding medication and on how to care for the patient at "
        "home");
    inputConfiguration.addQuestion(2, "39. Overall assessment of the hospital");
    return inputConfiguration;
}

InputConfiguration getInputConfigurationForDemObas(string const& inputPath) {
    InputConfiguration inputConfiguration;
    inputConfiguration.setPath(inputPath);
    inputConfiguration.setFormDetailsTitle("Form Title");
    inputConfiguration.setMainParameters("area", "period", 12.345, 3);
    inputConfiguration.addQuestion(1, "01. Patient Admission - promptness of service");
    inputConfiguration.addQuestion(1, "02. Patient Admission - courtesy of admitting clerks");
    inputConfiguration.addQuestion(1, "03. Hospital Environment - cleanliness of surroundings");    inputConfiguration.addQuestion(1, "04. Hospital Environment - cleanliness of toilet/bathroom");
    inputConfiguration.addQuestion(1, "05. Hospital Environment - ventilation/air-conditioning");
    inputConfiguration.addQuestion(1, "06. Hospital Environment - lighting");
    inputConfiguration.addQuestion(1, "07. Nursing Care - promptness of service");    inputConfiguration.addQuestion(1, "08. Nursing Care - quality of patient care");
    inputConfiguration.addQuestion(1, "09. Nursing Care - courtesy in dealing with patients");
    inputConfiguration.addQuestion(
        1, "10. Nursing Care - ability to give important information regarding the needs  of patient");
    inputConfiguration.addQuestion(1, "11. Medical Care - promptness of service");
    inputConfiguration.addQuestion(1, "12. Medical Care - quality of care and treatment");
    inputConfiguration.addQuestion(1, "13. Medical Care - courtesy in dealing with patients");
    inputConfiguration.addQuestion(
        1, "14. Medical Care - ability to give important information regarding the patient's  condition");
    inputConfiguration.addQuestion(2, "15. Pharmacy - availability of medicines and medical supplies");
    inputConfiguration.addQuestion(2, "16. Pharmacy - promptness of  service");
    inputConfiguration.addQuestion(2, "17. Pharmacy - courtesy of staff");
    inputConfiguration.addQuestion(2, "18. Medical Social Service - courtesy in dealing with patients");
    inputConfiguration.addQuestion(2, "19. Medical Social Service - provision of patient's medical needs");
    inputConfiguration.addQuestion(2, "20. Laboratory - promptness of  service");
    inputConfiguration.addQuestion(2, "21. Laboratory - courtesy of staff");
    inputConfiguration.addQuestion(2, "22. Radiology - promptness of  service");
    inputConfiguration.addQuestion(2, "23. Radiology - courtesy of staff");
    inputConfiguration.addQuestion(2, "24. ECG - promptness of  service");
    inputConfiguration.addQuestion(2, "25. ECG - courtesy of staff");
    inputConfiguration.addQuestion(2, "26. Cashier/Cash Services - promptness of  service");
    inputConfiguration.addQuestion(2, "27. Cashier/Cash Services - courtesy of staff");
    inputConfiguration.addQuestion(
        2,
        "28. Security Services - ability to ensure that the area is safe and secured by  observing people and "
        "enforcing hospital rules and  regulations");
    inputConfiguration.addQuestion(2, "29 Security Services - courtesy of security personnel");
    inputConfiguration.addQuestion(2, "30. Overall assessment of the hospital");
    return inputConfiguration;
}

InputConfiguration getInputConfigurationForSpecialUnits(string const& inputPath) {
    InputConfiguration inputConfiguration;
    inputConfiguration.setPath(inputPath);
    inputConfiguration.setFormDetailsTitle("Form Title");
    inputConfiguration.setMainParameters("area", "period", 12.345, 3);
    inputConfiguration.addQuestion(1, "01. Hospital Environment - cleanliness of the area");
    inputConfiguration.addQuestion(1, "02. Hospital Environment - ventilation/air-conditioning");
    inputConfiguration.addQuestion(1, "03. Hospital Environment - lighting");    inputConfiguration.addQuestion(1, "04. Nursing Care - promptness of service");
    inputConfiguration.addQuestion(1, "05. Nursing Care - quality of patient care");
    inputConfiguration.addQuestion(1, "06. Nursing Care - courtesy in dealing with patients/watchers");
    inputConfiguration.addQuestion(1, "07. Medical Care - promptness of service");    inputConfiguration.addQuestion(1, "08. Medical Care - quality of care and treatment");
    inputConfiguration.addQuestion(1, "09. Medical Care - courtesy in dealing with patients");
    inputConfiguration.addQuestion(1, "10. Pharmacy - availability of medicines and medical supplies");
    inputConfiguration.addQuestion(1, "11. Pharmacy - promptness of  service");
    inputConfiguration.addQuestion(1, "12. Pharmacy - courtesy of staff");
    inputConfiguration.addQuestion(1, "13. Overall assessment of the hospital");
    return inputConfiguration;
}

void checkAnswersForCharityPayWardsPattern1(SOOSA const& soosa) {
    EXPECT_EQ(39, soosa.getNumberOfAnswers());
    EXPECT_EQ(5, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(3));
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

void checkAnswersForDemObasPattern1(SOOSA const& soosa) {
    EXPECT_EQ(19, soosa.getNumberOfAnswers());
    EXPECT_EQ(0, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(12));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(13));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(14));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(15));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(16));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(17));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(18));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(19));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(20));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(21));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(22));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(23));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(24));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(25));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(26));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(27));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(28));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(29));
}

void checkAnswersForDemObasPattern2(SOOSA const& soosa) {
    EXPECT_EQ(23, soosa.getNumberOfAnswers());
    EXPECT_EQ(0, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(12));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(13));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(14));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(15));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(16));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(17));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(18));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(19));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(20));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(21));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(22));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(23));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(24));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(25));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(26));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(27));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(28));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(29));
}

void checkAnswersForDemObasPattern3(SOOSA const& soosa) {
    EXPECT_EQ(30, soosa.getNumberOfAnswers());
    EXPECT_EQ(1, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(12));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(13));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(14));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(15));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(16));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(17));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(18));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(19));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(20));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(21));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(22));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(23));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(24));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(25));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(26));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(27));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(28));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(29));
}

void checkAnswersForDemObasPattern4(SOOSA const& soosa) {
    EXPECT_EQ(26, soosa.getNumberOfAnswers());
    EXPECT_EQ(5, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(12));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(13));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(14));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(15));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(16));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(17));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(18));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(19));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(20));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(21));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(22));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(23));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(24));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(25));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(26));
    EXPECT_EQ(1, soosa.getAnswerToQuestion(27));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(28));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(29));
}

void checkAnswersForDemObasPattern5(SOOSA const& soosa) {
    EXPECT_EQ(19, soosa.getNumberOfAnswers());
    EXPECT_EQ(0, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(12));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(13));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(14));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(15));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(16));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(17));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(18));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(19));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(20));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(21));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(22));
    EXPECT_EQ(2, soosa.getAnswerToQuestion(23));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(24));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(25));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(26));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(27));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(28));
    EXPECT_EQ(0, soosa.getAnswerToQuestion(29));
}

void checkAnswersForSpecialUnitsPattern1(SOOSA const& soosa) {
    EXPECT_EQ(13, soosa.getNumberOfAnswers());
    EXPECT_EQ(5, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(12));
}

void checkAnswersForSpecialUnitsPattern2(SOOSA const& soosa) {
    EXPECT_EQ(13, soosa.getNumberOfAnswers());
    EXPECT_EQ(5, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(4, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(3, soosa.getAnswerToQuestion(12));
}

void checkAnswersForSpecialUnitsPattern3(SOOSA const& soosa) {
    EXPECT_EQ(13, soosa.getNumberOfAnswers());
    EXPECT_EQ(5, soosa.getAnswerToQuestion(0));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(1));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(2));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(3));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(4));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(5));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(6));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(7));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(8));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(9));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(10));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(11));
    EXPECT_EQ(5, soosa.getAnswerToQuestion(12));
}

void checkAnswersForEmptyForm(SOOSA const& soosa) { EXPECT_EQ(0, soosa.getNumberOfAnswers()); }

}  // namespace soosa
}  // namespace alba