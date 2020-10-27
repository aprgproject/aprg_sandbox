#include "FindingsToAddHelper.hpp"

namespace codeReview
{

namespace FindingsToAddHelper
{

bool isExpectedNewLineIncluded(FindingsToAdd const findingsToAdd)
{
    return findingsToAdd == FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace;
}

bool isUnexpectedWhiteSpaceIncluded(FindingsToAdd const findingsToAdd)
{
    return findingsToAdd == FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace ||
            findingsToAdd == FindingsToAdd::UnexpectsWhiteSpace ||
            findingsToAdd == FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace;
}

bool isUnexpectedNewLineIncluded(FindingsToAdd const findingsToAdd)
{
    return findingsToAdd == FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace;
}

}//namespace FindingsToAddHelper

}//namespace codeReview
