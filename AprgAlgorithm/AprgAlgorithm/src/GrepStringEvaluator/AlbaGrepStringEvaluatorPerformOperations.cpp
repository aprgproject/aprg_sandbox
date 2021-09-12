#include "AlbaGrepStringEvaluatorPerformOperations.hpp"

using namespace std;

namespace alba
{

namespace ExpressionEvaluator
{

template <>
AlbaGrepStringEvaluatorTerm performUnaryOperation<AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>
(AlbaGrepStringOperatorType const& operatorObject, AlbaGrepStringEvaluatorTerm const& value)
{
    using OperatorType = AlbaGrepStringOperatorType;
    bool outputValue(false);
    switch (operatorObject)
    {
    case OperatorType::NotOperator:
        outputValue = !value.getResult();
        break;
    default:
        break;
    }
    return AlbaGrepStringEvaluatorTerm(outputValue);
}

template <>
AlbaGrepStringEvaluatorTerm performBinaryOperation<AlbaGrepStringEvaluatorTerm, AlbaGrepStringOperatorType>
(AlbaGrepStringEvaluatorTerm const& value1, AlbaGrepStringOperatorType const& operatorObject, AlbaGrepStringEvaluatorTerm const& value2)
{
    using OperatorType = AlbaGrepStringOperatorType;
    bool outputValue(false);
    bool inputValue1(value1.getResult());
    bool inputValue2(value2.getResult());
    switch (operatorObject)
    {
    case OperatorType::AndOperator:
        outputValue = inputValue1 && inputValue2;
        break;
    case OperatorType::OrOperator:
        outputValue = inputValue1 || inputValue2;
        break;
    case OperatorType::XorOperator:
        outputValue = (inputValue1 && (!inputValue2)) || ((!inputValue1) && inputValue2);
        break;
    case OperatorType::XnorOperator:
        outputValue = ((!inputValue1) && (!inputValue2)) || (inputValue1 && inputValue2);
        break;
    default:
        break;
    }
    return AlbaGrepStringEvaluatorTerm(outputValue);
}

}

}
