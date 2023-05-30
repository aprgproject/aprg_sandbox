#include "InputConfiguration.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

using namespace std;

namespace alba {

namespace soosa {

InputConfiguration::InputConfiguration()
    : m_path(), m_area(), m_period(), m_discharge{}, m_minimumSatisfactoryScore{}, m_formDetails{} {}

int InputConfiguration::getNumberOfColumns() const { return m_formDetails.columnToNumberOfQuestionsMap.size(); }

int InputConfiguration::getNumberOfQuestions() const { return m_formDetails.questions.size(); }

int InputConfiguration::getNumberOfQuestionsAtColumn(int const column) const {
    int numberOfQuestions = 0;
    if (m_formDetails.columnToNumberOfQuestionsMap.find(column) != m_formDetails.columnToNumberOfQuestionsMap.cend()) {
        numberOfQuestions = m_formDetails.columnToNumberOfQuestionsMap.at(column);
    }
    return numberOfQuestions;
}

int InputConfiguration::getQuestionIndexInColumn(int const columnNumber, int const questionOffsetInColumn) const {
    int questionIndex = 0;
    FormDetails::ColumnToNumberOfQuestionsMap::const_iterator columnMapIterator =
        m_formDetails.columnToNumberOfQuestionsMap.find(columnNumber);
    if (columnMapIterator != m_formDetails.columnToNumberOfQuestionsMap.cend()) {
        if (columnMapIterator == m_formDetails.columnToNumberOfQuestionsMap.cbegin()) {
            questionIndex = questionOffsetInColumn;
        } else {
            questionIndex = accumulate(
                m_formDetails.columnToNumberOfQuestionsMap.cbegin(), columnMapIterator, 0,
                [](int partialResult, FormDetails::ColumnToNumberOfQuestionsPair const& columnQuestionPair) {
                    return partialResult += columnQuestionPair.second;
                });
            questionIndex += questionOffsetInColumn;
        }
    }
    return questionIndex;
}

int InputConfiguration::getMinimumSatisfactoryScore() const { return m_minimumSatisfactoryScore; }

string InputConfiguration::getQuestionAt(int const questionIndex) const {
    string question;
    if (questionIndex < static_cast<int>(m_formDetails.questions.size())) {
        question = m_formDetails.questions[questionIndex];
    }
    return question;
}

string InputConfiguration::getFormDetailsTitle() const { return m_formDetails.title; }

string InputConfiguration::getPath() const { return m_path; }

string InputConfiguration::getArea() const { return m_area; }

string InputConfiguration::getPeriod() const { return m_period; }

double InputConfiguration::getDischarge() const { return m_discharge; }

void InputConfiguration::setPath(string const& path) { m_path = path; }

void InputConfiguration::setMainParameters(
    string const& area, string const& period, double const discharge, int const minimumSatisfactoryScore) {
    m_area = area;
    m_period = period;
    m_discharge = discharge;
    m_minimumSatisfactoryScore = minimumSatisfactoryScore;
}

void InputConfiguration::addQuestion(int const columnNumber, string const& question) {
    m_formDetails.columnToNumberOfQuestionsMap[columnNumber]++;
    m_formDetails.questions.emplace_back(question);
}

void InputConfiguration::setFormDetailsTitle(string const& title) { m_formDetails.title = title; }

}  // namespace soosa

}  // namespace alba
