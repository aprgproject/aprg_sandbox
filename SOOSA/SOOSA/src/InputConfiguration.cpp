#include "InputConfiguration.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

using namespace std;

namespace alba
{

namespace soosa
{

InputConfiguration::InputConfiguration()
    : m_path()
    , m_area()
    , m_period()
    , m_discharge{}
    , m_minimumSatisfactoryScore{}
    , m_formDetails{}
{}

unsigned int InputConfiguration::getMinimumSatisfactoryScore() const
{
    return m_minimumSatisfactoryScore;
}

unsigned int InputConfiguration::getNumberOfColumns() const
{
    return m_formDetails.columnToNumberOfQuestionsMap.size();}

unsigned int InputConfiguration::getNumberOfQuestions() const
{
    return m_formDetails.questions.size();}

unsigned int InputConfiguration::getNumberOfQuestionsAtColumn(unsigned int const column) const
{
    unsigned int numberOfQuestions=0;
    if(m_formDetails.columnToNumberOfQuestionsMap.find(column) != m_formDetails.columnToNumberOfQuestionsMap.end())
    {
        numberOfQuestions = m_formDetails.columnToNumberOfQuestionsMap.at(column);
    }
    return numberOfQuestions;
}

unsigned int InputConfiguration::getQuestionNumberInColumn(unsigned int const columnNumber, unsigned int const questionOffsetInColumn) const
{
    unsigned int questionNumber=0;
    FormDetails::ColumnToNumberOfQuestionsMap::const_iterator columnMapIterator = m_formDetails.columnToNumberOfQuestionsMap.find(columnNumber);
    if(columnMapIterator!=m_formDetails.columnToNumberOfQuestionsMap.end())
    {
        if(columnMapIterator == m_formDetails.columnToNumberOfQuestionsMap.begin())
        {
            questionNumber = questionOffsetInColumn;
        }
        else
        {
            questionNumber = accumulate(m_formDetails.columnToNumberOfQuestionsMap.begin(), columnMapIterator, 0U, [](unsigned int partialResult, FormDetails::ColumnToNumberOfQuestionsPair const& columnQuestionPair)
            {
                return partialResult+=columnQuestionPair.second;
            });
            questionNumber += questionOffsetInColumn;
        }
    }
    return questionNumber;
}

string InputConfiguration::getPath() const
{
    return m_path;
}

string InputConfiguration::getArea() const
{
    return m_area;
}

string InputConfiguration::getPeriod() const
{
    return m_period;
}

double InputConfiguration::getDischarge() const
{
    return m_discharge;
}

string InputConfiguration::getQuestionAt(unsigned int const questionNumber) const
{
    string question;
    if(questionNumber < m_formDetails.questions.size())    {
        question = m_formDetails.questions[questionNumber];
    }
    return question;
}

void InputConfiguration::setPath(string const& path)
{
    m_path = path;
}

void InputConfiguration::setMainParameters(
        string const& area,
        string const& period,
        double const discharge,
        unsigned int const minimumSatisfactoryScore)
{
    m_area = area;
    m_period = period;
    m_discharge = discharge;
    m_minimumSatisfactoryScore = minimumSatisfactoryScore;
}

void InputConfiguration::addQuestion(unsigned int const columnNumber, string const& question)
{
    m_formDetails.columnToNumberOfQuestionsMap[columnNumber]++;
    m_formDetails.questions.emplace_back(question);
}

void InputConfiguration::setFormDetailTitle(string const& title)
{
    m_formDetails.title=title;
}

}

}