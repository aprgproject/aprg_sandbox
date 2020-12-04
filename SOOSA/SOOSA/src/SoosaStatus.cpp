#include "SoosaStatus.hpp"

#include <Macros/AlbaMacros.hpp>

using namespace std;

namespace alba
{

string getString(SoosaStatus const status)
{
    switch(status)
    {
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::BitmapError);
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::LineNotFoundBecauseNotEnoughSamples);
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::NumberOfQuestionsDoesNotMatchNumberOfAnswers);
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::NumberOfQuestionCoordinatesDoesNotMatchBetweenColumns);
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::ProblemLocatingChoiceInQuestion);
    ALBA_MACROS_CASE_ENUM_STRING(SoosaStatus::NoError);
    }
    return string();
}

}
