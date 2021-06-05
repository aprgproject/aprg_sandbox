#include "Expression.hpp"

#include <Optional/AlbaOptional.hpp>
#include <Term.hpp>
#include <Utilities.hpp>

#include <sstream>

using namespace std;

namespace alba
{
namespace equation
{
Expression::Expression()
{}

Expression::~Expression()
{}

bool Expression::operator==(Expression const& second) const
{
    BaseTermSharedPointers const& pointers1(m_wrappedTerms.getBaseTermPointersConstReference());
    BaseTermSharedPointers const& pointers2(second.m_wrappedTerms.getBaseTermPointersConstReference());
    bool result(false);
    if(pointers1.size() == pointers2.size())
    {
        result=true;
        unsigned int size = pointers1.size();
        for(unsigned int i=0; i<size; i++)
        {
            Term const& termReference1 = *dynamic_cast<Term const*const>(pointers1.at(i).get());
            Term const& termReference2 = *dynamic_cast<Term const*const>(pointers2.at(i).get());
            result = termReference1 == termReference2;
            if(!result)
            {
                break;
            }
        }
    }
    return result;
}

string Expression::getDisplayableString() const
{
    stringstream result;
    for(BaseTermSharedPointer const& sharedPointer : m_wrappedTerms.getBaseTermPointersConstReference())
    {
        Term const& term = *dynamic_cast<Term const*const>(sharedPointer.get());
        result << term.getDisplayableString();
    }
    return result.str();
}

OperatorLevel Expression::getCommonOperatorLevel() const
{
    OperatorLevel result(OperatorLevel::Unknown);
    bool isOperatorFound(false);
    for(BaseTermSharedPointer const& sharedPointer : m_wrappedTerms.getBaseTermPointersConstReference())
    {
        Term const& term = *dynamic_cast<Term const*const>(sharedPointer.get());
        if(term.isOperator())
        {
            Operator const& operatorTerm(term.getOperatorConstReference());
            if(isOperatorFound)
            {
                if(result != operatorTerm.getOperatorLevel())
                {
                    result = OperatorLevel::Unknown;
                    break;
                }
            }
            else
            {
                result = operatorTerm.getOperatorLevel();
                isOperatorFound = true;
            }
        }
    }
    return result;
}

WrappedTerms & Expression::getWrappedTermsReference()
{
    return m_wrappedTerms;}

WrappedTerms const& Expression::getWrappedTermsConstReference() const
{
    return m_wrappedTerms;
}

void Expression::simplify()
{

}

}

}