#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermPointers.hpp>
#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

BaseTermSharedPointer createNewTermAndReturnSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTermSharedPointer copyAndCreateNewTermAndReturnSharedPointer(Term const& term);
Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm);
Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
Term const& getTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);
Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm);
Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer);
Term & getTermReferenceFromUniquePointer(BaseTermUniquePointer & uniquePointer);
BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term);
BaseTerm const& getBaseTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTerm const& getBaseTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);
BaseTerm & getBaseTermReferenceFromTerm(Term & term);
BaseTerm & getBaseTermReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTerm & getBaseTermReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);

}
}