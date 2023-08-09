#include "Polynomial.hpp"

#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

Polynomial::Polynomial()
{}

Polynomial::Polynomial(Monomials const& monomials)
    : m_monomials(monomials)
    , m_isSimplified(false)
{}

Polynomial::Polynomial(initializer_list<Monomial> const& monomials)
    : m_monomials()
    , m_isSimplified(false)
{
    m_monomials.reserve(monomials.size());
    copy(monomials.begin(), monomials.end(), back_inserter(m_monomials));
}

bool Polynomial::operator==(Polynomial const& second) const
{
    Monomials const& monomials1(m_monomials);
    Monomials const& monomials2(second.m_monomials);
    bool result(false);
    if(monomials1.size() == monomials2.size())
    {
        using MonomialsIterator=Monomials::const_iterator;
        using MismatchResultType=pair<MonomialsIterator, MonomialsIterator>;
        MismatchResultType mismatchResult = mismatch(monomials1.cbegin(), monomials1.end(), monomials2.cbegin());
        result = mismatchResult.first == monomials1.cend();
    }
    return result;
}

bool Polynomial::operator!=(Polynomial const& second) const
{
    return !(operator==(second));
}

bool Polynomial::operator<(Polynomial const& second) const
{
    Monomials const& monomials1(m_monomials);
    Monomials const& monomials2(second.m_monomials);
    bool result(false);
    if(monomials1.size() == monomials2.size())
    {
        unsigned int size = monomials1.size();
        for(unsigned int i = 0; i < size; i++)
        {
            Monomial const& monomial1(monomials1.at(i));
            Monomial const& monomial2(monomials2.at(i));
            if(monomial1 != monomial2)
            {
                result = monomial1 < monomial2;
                break;
            }
        }
    }
    else
    {
        result =  monomials1.size() < monomials2.size();
    }
    return result;
}

bool Polynomial::isEmpty() const
{
    return m_monomials.empty();
}

Monomials const& Polynomial::getMonomialsConstReference() const
{
    return m_monomials;
}

string Polynomial::getDisplayableString() const
{
    stringstream result;
    if(m_monomials.empty())
    {
        result << "(EmptyPolynomial)";
    }
    else
    {
        result << "(";
        bool shouldPutPlusSymbol(false);
        for(Monomial const& monomial : m_monomials)
        {
            if(shouldPutPlusSymbol)
            {
                result << " + ";
            }
            shouldPutPlusSymbol=true;
            result << monomial.getDisplayableString();
        }
        result << ")";
    }
    return result.str();
}

Monomials & Polynomial::getMonomialsReference()
{
    clearInternalFlags();
    return m_monomials;
}

void Polynomial::clear()
{
    m_monomials.clear();
    clearInternalFlags();
}

void Polynomial::simplify()
{
    if(!m_isSimplified)
    {
        if(hasNotANumber(*this))
        {
            setNan();
        }
        else
        {
            simplifyContinuouslyIfChanged();
        }
        setAsSimplified();
    }
}

void Polynomial::sortMonomialsWithInversePriority()
{
    stable_sort(m_monomials.begin(), m_monomials.end(), [](Monomial const& monomial1, Monomial const& monomial2)
    {
        return monomial2 < monomial1;
    });
    clearInternalFlags();
}

void Polynomial::addMonomial(Monomial const& monomial)
{
    bool isFoundInPolynomial(false);
    for(Monomial & monomialInternal : m_monomials)
    {
        if(canBeMergedInAMonomialByAdditionOrSubtraction(monomialInternal, monomial))
        {
            isFoundInPolynomial=true;
            monomialInternal.setConstant(monomialInternal.getConstantConstReference() + monomial.getConstantConstReference());
        }
    }
    if(!isFoundInPolynomial)
    {
        m_monomials.emplace_back(monomial);
    }
    clearInternalFlags();
}

void Polynomial::addPolynomial(Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        addMonomial(monomial);
    }
    clearInternalFlags();
}

void Polynomial::multiplyNumber(AlbaNumber const& number)
{
    for(Monomial & monomial : m_monomials)
    {
        monomial.setConstant(monomial.getConstantConstReference()*number);
    }
    clearInternalFlags();
}

void Polynomial::divideNumber(AlbaNumber const& number)
{
    for(Monomial & monomial : m_monomials)
    {
        monomial.setConstant(monomial.getConstantConstReference()/number);
    }
    clearInternalFlags();
}

void Polynomial::multiplyMonomial(Monomial const& monomial)
{
    for(Monomial & monomialInternal : m_monomials)
    {
        monomialInternal.multiplyMonomial(monomial);
    }
    clearInternalFlags();
}

void Polynomial::multiplyPolynomial(Polynomial const& polynomial)
{
    Monomials monomialsCopy(m_monomials);
    m_monomials.clear();
    for(Monomial const& monomial2 : polynomial.getMonomialsConstReference())
    {
        for(Monomial const& monomial1 : monomialsCopy)
        {
            Monomial newMonomial(monomial1);
            newMonomial.multiplyMonomial(monomial2);
            addMonomial(newMonomial);
        }
    }
    clearInternalFlags();
}

void Polynomial::divideMonomial(Monomial const& monomial)
{
    for(Monomial & monomialInternal : m_monomials)
    {
        monomialInternal.divideMonomial(monomial);
    }
    clearInternalFlags();
}

void Polynomial::raiseToUnsignedInteger(unsigned int const exponent)
{
    Polynomial base(*this);
    for(unsigned int exponentCount=1; exponentCount<exponent; exponentCount++)
    {
        multiplyPolynomial(base);
    }
    clearInternalFlags();
}

void Polynomial::setAsSimplified()
{
    m_isSimplified = true;
}

void Polynomial::clearInternalFlags()
{
    m_isSimplified = false;
}

bool Polynomial::isFurtherSimplificationNeeded(
        Polynomial const& beforeSimplify,
        Polynomial const& afterSimplify) const
{
    return beforeSimplify != afterSimplify && !hasNotANumber(afterSimplify);
}

void Polynomial::setNan()
{
    m_monomials.clear();
    addMonomial(Monomial(AlbaNumber(AlbaNumber::Value::NotANumber), {}));
}

void Polynomial::simplifyContinuouslyIfChanged()
{
    Polynomial beforeSimplify;
    Polynomial afterSimplify;
    do
    {
        beforeSimplify=*this;
        simplifyMonomialsAndReAdd();
        sortMonomialsWithInversePriority();
        afterSimplify=*this;
    }
    while(isFurtherSimplificationNeeded(beforeSimplify, afterSimplify));
}

void Polynomial::simplifyMonomialsAndReAdd()
{
    Monomials previousMonomials(m_monomials);
    m_monomials.clear();
    for(Monomial & monomial : previousMonomials)
    {
        monomial.simplify();
        if(!isTheValue(monomial, 0))
        {
            addMonomial(monomial);
        }
    }
}

ostream & operator<<(ostream & out, Polynomial const& polynomial)
{
    out << polynomial.getDisplayableString();
    return out;
}

}

}
