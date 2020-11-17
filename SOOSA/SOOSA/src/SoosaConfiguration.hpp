#pragma once

#include <map>
#include <string>
#include <vector>

namespace alba
{

using SoosaQuestionRange=std::pair<unsigned int, unsigned int>;

struct SoosaFormDetails
{
    std::string title;
    unsigned int numberOfColumns;
    unsigned int numberQuestionsOfColumn1;
    unsigned int numberQuestionsOfColumn2;
    std::vector<std::string> questions;
    std::map<unsigned int, SoosaQuestionRange> columnToQuestionRangeMap;
};

struct SoosaConfiguration
{
    unsigned int numberOfRespondents;
    std::string path;
    std::string formDetailsDirectoryPath;
    std::string area;
    std::string period;
    std::string discharge;
    SoosaFormDetails formDetails;
    unsigned int getColumns() const;
    unsigned int getNumberOfQuestions() const;
    unsigned int getNumberOfQuestionsAtColumn(unsigned int const column) const;
    unsigned int getQuestionNumber(unsigned int const columnNumber, unsigned int const questionOffset) const;
};
}
