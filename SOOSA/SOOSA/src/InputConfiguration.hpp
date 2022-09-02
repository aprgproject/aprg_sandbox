#pragma once

#include <map>
#include <string>
#include <vector>

namespace alba
{

namespace soosa
{

struct FormDetails
{
    using ColumnToNumberOfQuestionsMap=std::map<unsigned int, unsigned int>;    using ColumnToNumberOfQuestionsPair=std::pair<unsigned int, unsigned int>;
    std::string title;
    std::vector<std::string> questions;
    ColumnToNumberOfQuestionsMap columnToNumberOfQuestionsMap;};

class InputConfiguration
{
public:

    InputConfiguration();

    unsigned int getMinimumSatisfactoryScore() const;
    unsigned int getNumberOfColumns() const;
    unsigned int getNumberOfQuestions() const;
    unsigned int getNumberOfQuestionsAtColumn(unsigned int const column) const;    unsigned int getQuestionNumberInColumn(unsigned int const columnNumber, unsigned int const questionOffsetInColumn) const;
    std::string getPath() const;
    std::string getArea() const;
    std::string getPeriod() const;
    double getDischarge() const;
    std::string getQuestionAt(unsigned int const questionNumber) const;
    void setPath(std::string const& path);
    void setMainParameters(std::string const& area, std::string const& period, double const discharge, unsigned int const minimumSatisfactoryScore);
    void addQuestion(unsigned int const columnNumber, std::string const& question);
    void setFormDetailTitle(std::string const& title);
private:    std::string m_path;
    std::string m_area;
    std::string m_period;
    double m_discharge;
    unsigned int m_minimumSatisfactoryScore;
    FormDetails m_formDetails;
};

}

}