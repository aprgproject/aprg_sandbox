#pragma once

#include "FindingsToAdd.hpp"

namespace codeReview
{

namespace FindingsToAddHelper
{
    bool isUnexpectedWhiteSpaceIncluded(FindingsToAdd const findingsToAdd);
    bool isExpectedNewLineIncluded(FindingsToAdd const findingsToAdd);
    bool isUnexpectedNewLineIncluded(FindingsToAdd const findingsToAdd);
}

}
