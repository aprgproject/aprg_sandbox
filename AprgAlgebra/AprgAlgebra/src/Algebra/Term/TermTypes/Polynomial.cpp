#include "Polynomial.hpp"

#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <algorithm>
#include <sstream>

using namespace std;

namespace alba
{

namespace algebra
{

Polynomial::Polynomial()
{}

Polynomial::Polynomial(Monomials const& monomials)
    : m_monomials(monomials)
{}

Polynomial::Polynomial(initializer_list<Monomial> const& monomials)
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

bool Polynomial::isOne() const
{
    return isOneMonomial() && getFirstMonomial().isOne();
}

bool Polynomial::isZero() const
{
    return m_monomials.empty();
}

bool Polynomial::isOneMonomial() const
{
    return m_monomials.size() == 1;
}

bool Polynomial::isVariableExponentInMonomialFound(Monomial const& monomial) const
{
    bool result(false);
    for(Monomial const& monomialInternal : m_monomials)
    {
        if(monomial.getVariablesToExponentsMapConstReference()
                == monomialInternal.getVariablesToExponentsMapConstReference())
        {
            result = true;
            break;
        }
    }
    return result;
}

bool Polynomial::hasNegativeExponents() const
{
    bool result(false);
    for(Monomial const& monomial : m_monomials)
    {
        if(monomial.hasNegativeExponents())
        {
            result = true;
            break;
        }
    }
    return result;
}

AlbaNumber Polynomial::getCoefficientOfVariableExponent(Monomial const& monomial) const
{
    AlbaNumber coefficient;
    for(Monomial const& monomialInternal : m_monomials)
    {
        if(monomial.getVariablesToExponentsMapConstReference()
                == monomialInternal.getVariablesToExponentsMapConstReference())
        {
            coefficient = monomialInternal.getConstantConstReference();
            break;
        }
    }
    return coefficient;
}

Monomial Polynomial::getFirstMonomial() const
{
    Monomial result;
    if(!m_monomials.empty())
    {
        result = m_monomials.front();
    }
    return result;
}

Monomials const& Polynomial::getMonomialsConstReference() const
{
    return m_monomials;
}

AlbaNumber Polynomial::getMaxDegree() const
{
    bool isFirst(true);
    AlbaNumber maxDegree;
    for(Monomial const& monomial : m_monomials)
    {
        if(isFirst)
        {
            maxDegree = monomial.getDegree();
            isFirst=false;
        }
        else
        {
            maxDegree = max(maxDegree, monomial.getDegree());
        }
    }
    return maxDegree;
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

void Polynomial::clear()
{
    m_monomials.clear();
}

void Polynomial::simplify()
{
    Polynomial beforeSimplify(*this);
    simplifyMonomialsAndReAdd();
    sortMonomialsWithInversePriority();
    Polynomial afterSimplify(*this);
    simplifyFurtherIfNeeded(beforeSimplify, afterSimplify);
}

void Polynomial::sortMonomialsWithInversePriority()
{
    stable_sort(m_monomials.begin(), m_monomials.end(), [](Monomial const& monomial1, Monomial const& monomial2)
    {
        return monomial2 < monomial1;
    });
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
}

void Polynomial::addPolynomial(Polynomial const& polynomial)
{
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        addMonomial(monomial);
    }
}

void Polynomial::multiplyNumber(AlbaNumber const& number)
{
    for(Monomial & monomial : m_monomials)
    {
        monomial.setConstant(monomial.getConstantConstReference()*number);
    }
}

void Polynomial::divideNumber(AlbaNumber const& number)
{
    for(Monomial & monomial : m_monomials)
    {
        monomial.setConstant(monomial.getConstantConstReference()/number);
    }
}

void Polynomial::multiplyMonomial(Monomial const& monomial)
{
    for(Monomial & monomialInternal : m_monomials)
    {
        monomialInternal.multiplyMonomial(monomial);
    }
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
}

void Polynomial::divideMonomial(Monomial const& monomial)
{
    for(Monomial & monomialInternal : m_monomials)
    {
        monomialInternal.divideMonomial(monomial);
    }
}

void Polynomial::simplifyFurtherIfNeeded(Polynomial const& beforeSimplify, Polynomial const& afterSimplify)
{
    if(beforeSimplify != afterSimplify)
    {
        simplify();
    }
}

void Polynomial::simplifyMonomialsAndReAdd()
{
    Monomials previousMonomials(m_monomials);
    m_monomials.clear();
    for(Monomial & monomial : previousMonomials)
    {
        monomial.simplify();
        if(!monomial.isZero())
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
