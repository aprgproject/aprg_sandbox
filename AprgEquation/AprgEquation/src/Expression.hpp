#pragma once

#include <BaseTermData.hpp>
#include <OperatorLevel.hpp>
#include <TermType.hpp>
#include <WrappedTerms.hpp>

#include <string>

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
    std::string getDisplayableString() const;
    OperatorLevel getCommonOperatorLevel() const;

    WrappedTerms & getWrappedTermsReference();
    WrappedTerms const& getWrappedTermsConstReference() const;

    void simplify();
private:
    WrappedTerms m_wrappedTerms;
};
}

}