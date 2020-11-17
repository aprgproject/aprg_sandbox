#include "SoosaConfiguration.hpp"

#include <iostream> //remove this
#include <cassert>

using namespace std;
namespace alba
{
unsigned int SoosaConfiguration::getColumns() const
{
    return formDetails.columnToQuestionRangeMap.size();
}

unsigned int SoosaConfiguration::getNumberOfQuestions() const
{
    return formDetails.questions.size();
}

unsigned int SoosaConfiguration::getNumberOfQuestionsAtColumn(unsigned int const column) const
{
    assert(formDetails.columnToQuestionRangeMap.find(column)!=formDetails.columnToQuestionRangeMap.end());
    SoosaQuestionRange const& questionRange(formDetails.columnToQuestionRangeMap.at(column));
    return questionRange.second - questionRange.first;
}
unsigned int SoosaConfiguration::getQuestionNumber(unsigned int const columnNumber, unsigned int const questionOffset) const
{
    assert(formDetails.columnToQuestionRangeMap.find(columnNumber)!=formDetails.columnToQuestionRangeMap.end());
    SoosaQuestionRange const& questionRange(formDetails.columnToQuestionRangeMap.at(columnNumber));
    return questionOffset + questionRange.first;
}

}