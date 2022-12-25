#include "BaseTermHelpers.hpp"

namespace alba
{

namespace booleanAlgebra
{

BaseTermSharedPointer createNewTermAndReturnSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return BaseTermSharedPointer(
                    dynamic_cast<BaseTerm*>(
                        new Term(*dynamic_cast<Term*>(sharedPointer.get()))));
}

BaseTermSharedPointer copyAndCreateNewTermAndReturnSharedPointer(Term const& term)
{
    return BaseTermSharedPointer(
                    dynamic_cast<BaseTerm*>(
                        new Term(term)));
}

Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm)
{
    return dynamic_cast<Term const&>(baseTerm);
}

Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return dynamic_cast<Term const&>(*sharedPointer.get());
}

Term const& getTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return dynamic_cast<Term const&>(*uniquePointer.get());
}

Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm)
{
    return dynamic_cast<Term &>(baseTerm);
}

Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer)
{
    return *dynamic_cast<Term*>(sharedPointer.get());
}

Term & getTermReferenceFromUniquePointer(BaseTermUniquePointer & uniquePointer)
{
    return *dynamic_cast<Term*>(uniquePointer.get());
}

BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term)
{
    return dynamic_cast<BaseTerm const&>(term);
}

BaseTerm const& getBaseTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return dynamic_cast<BaseTerm const&>(*sharedPointer.get());
}

BaseTerm const& getBaseTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return dynamic_cast<BaseTerm const&>(*uniquePointer.get());
}

BaseTerm & getBaseTermReferenceFromTerm(Term & term)
{
    return dynamic_cast<BaseTerm &>(term);
}

BaseTerm & getBaseTermReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return dynamic_cast<BaseTerm &>(*sharedPointer.get());
}

BaseTerm & getBaseTermReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return dynamic_cast<BaseTerm &>(*uniquePointer.get());
}

}

}
