#include "WrappedTerm.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/EnumHelpers.hpp>

#include <sstream>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

WrappedTerm::WrappedTerm(
        BaseTerm const& baseTerm)
    : baseTermSharedPointer(copyAndCreateNewTermAndReturnSharedPointer(getTermConstReferenceFromBaseTerm(baseTerm)))
{}

WrappedTerm::WrappedTerm(WrappedTerm const& wrappedTerm)
    : baseTermSharedPointer(createNewTermAndReturnSharedPointer(wrappedTerm.baseTermSharedPointer))
{}

bool WrappedTerm::operator==(WrappedTerm const& second) const
{
    Term const& term1(getTermConstReferenceFromSharedPointer(baseTermSharedPointer));
    Term const& term2(getTermConstReferenceFromSharedPointer(second.baseTermSharedPointer));
    return term1 == term2;
}

bool WrappedTerm::operator!=(WrappedTerm const& second) const
{
    return !(operator==(second));
}

bool WrappedTerm::operator<(WrappedTerm const& second) const
{
    Term const& term1(getTermConstReferenceFromSharedPointer(baseTermSharedPointer));
    Term const& term2(getTermConstReferenceFromSharedPointer(second.baseTermSharedPointer));
    return term1 < term2;
}

void WrappedTerm::clear()
{
    baseTermSharedPointer.reset();
}

ostream & operator<<(ostream & out, WrappedTerm const& wrappedTerm)
{
    out << getTermConstReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer);
    return out;
}

}

}
