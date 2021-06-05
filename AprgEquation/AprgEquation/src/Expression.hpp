#pragma once

#include <BaseTermData.hpp>
#include <TermType.hpp>
#include <WrappedTerms.hpp>

namespace alba
{

namespace equation
{

class Expression : public BaseTermData
{
public:
    Expression();
    ~Expression();

    bool operator==(Expression const& second) const;

    WrappedTerms & getWrappedTermsReference();
    WrappedTerms const& getWrappedTermsConstReference() const;

private:
    WrappedTerms m_wrappedTerms;
};

}

}
