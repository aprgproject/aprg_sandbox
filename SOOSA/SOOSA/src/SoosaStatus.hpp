#pragma once

#include <string>

namespace alba
{

enum class SoosaStatus
{
    BitmapError,
    LineNotFoundBecauseNotEnoughSamples,
    NumberOfQuestionsDoesNotMatchNumberOfAnswers,
    NumberOfQuestionCoordinatesDoesNotMatchBetweenColumns,
    ProblemLocatingChoiceInQuestion,
    NoError
};

std::string getString(SoosaStatus const status);

}
