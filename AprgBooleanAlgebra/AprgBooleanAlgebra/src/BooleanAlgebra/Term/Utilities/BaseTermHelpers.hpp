#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermPointers.hpp>
#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

BaseTermUniquePointer createBasePointer(BaseTerm const& baseTerm);
BaseTermUniquePointer createBasePointer(BaseTerm && baseTerm);
BaseTermUniquePointer duplicateUniquePointer(BaseTermUniquePointer const& uniquePointer);
Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm);
Term const& getTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);
Term && getTermRValueReferenceFromBaseTerm(BaseTerm && baseTerm);
Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm);
Term & getTermReferenceFromUniquePointer(BaseTermUniquePointer & uniquePointer);
BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term);
BaseTerm const& getBaseTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);
BaseTerm & getBaseTermReferenceFromTerm(Term & term);
BaseTerm & getBaseTermReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer);

}
}