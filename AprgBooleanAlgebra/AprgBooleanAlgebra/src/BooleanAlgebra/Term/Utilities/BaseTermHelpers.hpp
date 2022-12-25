#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermPointers.hpp>
#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

BaseTermUniquePointer createAUniquePointerFromTerm(Term const& term);
BaseTermSharedPointer createASharedPointerFromTerm(Term const& term);
Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm);
Term const& getTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);
Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm);
Term & getTermReferenceFromUniquePointer(BaseTermUniquePointer & uniquePointer);
Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer);
BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term);
BaseTerm const& getBaseTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);
BaseTerm const& getBaseTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);
BaseTerm & getBaseTermReferenceFromTerm(Term & term);
BaseTerm & getBaseTermReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);
BaseTerm & getBaseTermReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer);

}
}