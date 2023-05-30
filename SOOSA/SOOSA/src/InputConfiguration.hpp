#pragma once

#include <map>
#include <string>
#include <vector>

namespace alba {

namespace soosa {

struct FormDetails {
    using ColumnToNumberOfQuestionsMap = std::map<int, int>;
    using ColumnToNumberOfQuestionsPair = std::pair<int, int>;
    std::string title;
    std::vector<std::string> questions;
    ColumnToNumberOfQuestionsMap columnToNumberOfQuestionsMap;
};

class InputConfiguration {
public:
    InputConfiguration();

    int getNumberOfColumns() const;
    int getNumberOfQuestions() const;
    int getNumberOfQuestionsAtColumn(int const column) const;
    int getQuestionIndexInColumn(
        int const columnNumber, int const questionOffsetInColumn) const;
    int getMinimumSatisfactoryScore() const;

    std::string getQuestionAt(int const questionIndex) const;
    std::string getFormDetailsTitle() const;
    std::string getPath() const;
    std::string getArea() const;
    std::string getPeriod() const;
    double getDischarge() const;
    void setPath(std::string const& path);
    void setMainParameters(
        std::string const& area, std::string const& period, double const discharge,
        int const minimumSatisfactoryScore);
    void addQuestion(int const columnNumber, std::string const& question);
    void setFormDetailsTitle(std::string const& title);

private:
    std::string m_path;
    std::string m_area;
    std::string m_period;
    double m_discharge;
    int m_minimumSatisfactoryScore;
    FormDetails m_formDetails;
};

}  // namespace soosa

}  // namespace alba
