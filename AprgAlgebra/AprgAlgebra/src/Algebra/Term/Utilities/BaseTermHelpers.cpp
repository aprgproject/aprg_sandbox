#include "BaseTermHelpers.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

BaseTermUniquePointer createAUniquePointerFromTerm(Term const& term)
{
    return BaseTermUniquePointer(static_cast<BaseTermUniquePointer>(make_unique<Term>(term)));
}

BaseTermSharedPointer createASharedPointerFromTerm(Term const& term)
{
    return BaseTermSharedPointer(static_cast<BaseTermSharedPointer>(make_shared<Term>(term)));
}

Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm)
{
    return static_cast<Term const&>(baseTerm);
}

Term const& getTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return static_cast<Term const&>(*uniquePointer.get());
}

Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return static_cast<Term const&>(*sharedPointer.get());
}

Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm)
{
    return static_cast<Term &>(baseTerm);
}

Term & getTermReferenceFromUniquePointer(BaseTermUniquePointer & uniquePointer)
{
    return *static_cast<Term*>(uniquePointer.get());
}

Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer)
{
    return *static_cast<Term*>(sharedPointer.get());
}

BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term)
{
    return static_cast<BaseTerm const&>(term);
}

BaseTerm const& getBaseTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return static_cast<BaseTerm const&>(*uniquePointer.get());
}

BaseTerm const& getBaseTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return static_cast<BaseTerm const&>(*sharedPointer.get());
}

BaseTerm & getBaseTermReferenceFromTerm(Term & term)
{
    return static_cast<BaseTerm &>(term);
}

BaseTerm & getBaseTermReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return static_cast<BaseTerm &>(*uniquePointer.get());
}

BaseTerm & getBaseTermReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return static_cast<BaseTerm &>(*sharedPointer.get());
}

}

}
