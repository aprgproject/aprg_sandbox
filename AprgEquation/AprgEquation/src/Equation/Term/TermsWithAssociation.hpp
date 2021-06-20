#pragma once

#include <Equation/Constructs/VariablesToValuesTypes.hpp>
#include <Equation/Term/BaseTermPointers.hpp>
#include <Equation/Term/TermAssociationType.hpp>

#include <functional>
#include <list>
#include <vector>

namespace alba
{

namespace equation
{

class TermsWithAssociation
{
public:
    friend class Expression;
    struct TermWithDetails
    {
        TermWithDetails(BaseTerm const& baseTerm, TermAssociationType const associationParameter);
        TermWithDetails(TermWithDetails const& termWithDetails);
        bool operator==(TermWithDetails const& second) const;
        bool operator!=(TermWithDetails const& second) const;
        bool operator<(TermWithDetails const& second) const;
        bool hasPositiveAssociation() const;
        bool hasNegativeAssociation() const;
        unsigned int getAssociationPriority() const;
        void clear();
        BaseTermSharedPointer baseTermSharedPointer;
        TermAssociationType association;
    };
    using TermsWithDetails=std::vector<TermWithDetails>;

    TermsWithAssociation();
    ~TermsWithAssociation();

    bool operator==(TermsWithAssociation const& second) const;
    bool operator!=(TermsWithAssociation const& second) const;
    bool operator<(TermsWithAssociation const& second) const;
    bool isEmpty() const;

    unsigned int getSize() const;
    BaseTerm const& getFirstTermConstReference() const;
    TermsWithDetails const& getTermsWithDetails() const;

    void clear();
    void sort();
    void substituteVariablesToValues(VariablesToValuesMap const& variableValueMap);
    void putTermWithDetails(TermWithDetails const& termWithDetails);
    void putTermWithPositiveAssociation(BaseTerm const& baseTerm);
    void putTermWithNegativeAssociation(BaseTerm const& baseTerm);
    void reverseTheAssociationOfTheTerms();

private:
    TermsWithDetails m_termsWithDetails;
};

}

}
