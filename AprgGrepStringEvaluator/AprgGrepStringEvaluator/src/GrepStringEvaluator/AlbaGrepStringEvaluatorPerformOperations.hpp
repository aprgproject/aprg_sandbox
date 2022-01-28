#pragma once

#include <ExpressionEvaluator/ExpressionEvaluator.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp>
#include <GrepStringEvaluator/AlbaGrepStringOperatorType.hpp>

namespace alba
{

namespace ExpressionEvaluator
{

template <>
AlbaGrepStringEvaluatorTerm performUnaryOperation<AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>
(AlbaGrepStringOperatorType const& operatorObject, AlbaGrepStringEvaluatorTerm const& value);

template <>
AlbaGrepStringEvaluatorTerm performBinaryOperation<AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>
(AlbaGrepStringEvaluatorTerm const& value1, AlbaGrepStringOperatorType const& operatorObject, AlbaGrepStringEvaluatorTerm const& value2);

}

}