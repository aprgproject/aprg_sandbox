#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp>
#include <GrepStringEvaluator/AlbaGrepStringOperatorType.hpp>

namespace alba
{

namespace ExpressionEvaluator
{

AlbaGrepStringEvaluatorTerm performUnaryOperation(AlbaGrepStringOperatorType const operatorString, AlbaGrepStringEvaluatorTerm const& value);
AlbaGrepStringEvaluatorTerm performBinaryOperation(AlbaGrepStringEvaluatorTerm const& value1, AlbaGrepStringOperatorType const operatorString, AlbaGrepStringEvaluatorTerm const& value2);

}

}
