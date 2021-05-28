#include "Expression.hpp"

#include <Term.hpp>

namespace alba
{
namespace equation
{

Expression::Expression()
{}

Expression::~Expression()
{}

WrappedTerms & Expression::getWrappedTermsReference()
{
    return m_wrappedTerms;
}

WrappedTerms const& Expression::getWrappedTermsConstReference() const
{
    return m_wrappedTerms;
}

}

}