#include "AlbaGrepStringEvaluatorPerformOperations.hpp"

using namespace std;

namespace alba
{

namespace ExpressionEvaluator
{

AlbaGrepStringEvaluatorTerm performUnaryOperation(AlbaGrepStringOperatorType const operatorString, AlbaGrepStringEvaluatorTerm const& value)
{
    using OperatorType = AlbaGrepStringOperatorType;
    bool outputValue(false);
    switch (operatorString)
    {
    case OperatorType::NotOperator:
        outputValue = !value.getResult();
        break;
    default:
        break;
    }
    return AlbaGrepStringEvaluatorTerm(outputValue);
}

AlbaGrepStringEvaluatorTerm performBinaryOperation(AlbaGrepStringEvaluatorTerm const& value1, AlbaGrepStringOperatorType const operatorString, AlbaGrepStringEvaluatorTerm const& value2)
{
    using OperatorType = AlbaGrepStringOperatorType;
    bool outputValue(false);
    bool inputValue1(value1.getResult());
    bool inputValue2(value2.getResult());
    switch (operatorString)
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
    return outputValue;
}

}

}
