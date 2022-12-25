#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>
#include <BooleanAlgebra/Term/TermTypes/OperatorLevel.hpp>
#include <BooleanAlgebra/Term/TermTypes/WrappedTerm.hpp>

#include <string>
#include <vector>

namespace alba
{

namespace booleanAlgebra
{

class Expression : public BaseTermData
{
public:

    Expression();
    Expression(BaseTerm const& baseTerm);
    Expression(OperatorLevel const operatorLevel, WrappedTerms const& wrappedTerms);

    // rule of zero

    bool operator==(Expression const& second) const;
    bool operator!=(Expression const& second) const;
    bool operator<(Expression const& second) const;
    Expression operator~() const;

    bool isEmpty() const;    bool isSimplified() const;
    bool containsOnlyOneTerm() const;

    OperatorLevel getCommonOperatorLevel() const;
    BaseTerm const& getFirstTermConstReference() const;
    WrappedTerms const& getWrappedTerms() const;
    std::string getDisplayableString() const;
    std::string getDebugString() const;

    WrappedTerms & getWrappedTermsReference();

    void clear();
    void clearAndPutTermInWrappedTerms(BaseTerm const& baseTerm);

    void putTerm(BaseTerm const& baseTerm);
    void putTerm(BaseTerm const& baseTerm, OperatorLevel const operatorLevel);
    void putTermWithAndOperationIfNeeded(BaseTerm const& baseTerm);
    void putTermWithOrOperationIfNeeded(BaseTerm const& baseTerm);
    void putWrappedTerm(WrappedTerm const& termToSave);
    void putWrappedTerms(WrappedTerms const& termsToSave);

    void set(OperatorLevel const operatorLevel, WrappedTerms const& wrappedTerms);
    void setTerm(BaseTerm const& baseTerm);
    void setCommonOperatorLevel(OperatorLevel const operatorLevel);
    void setCommonOperatorLevelIfStillUnknown(OperatorLevel const operatorLevel);

    void simplify();
    void sort();
    void negate();

    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:

    //put functions
    void putTermWithAndOperation(BaseTerm const& baseTerm);
    void putTermWithOrOperation(BaseTerm const& baseTerm);
    void putTermForExpressionAndNonExpressions(
            BaseTerm const& baseTerm);

    friend std::ostream & operator<<(std::ostream & out, Expression const& expression);

    OperatorLevel m_commonOperatorLevel;
    WrappedTerms m_wrappedTerms;
    bool m_isSimplified;
};

using Expressions=std::vector<Expression>;

}

}
