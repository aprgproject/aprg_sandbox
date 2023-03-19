#include "BaseTermHelpers.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

BaseTermUniquePointer duplicateUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return make_unique<Term>(getTermConstReferenceFromUniquePointer(uniquePointer));
}

Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm){
    return static_cast<Term const&>(baseTerm);
}
Term const& getTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return static_cast<Term const&>(*uniquePointer.get());
}

Term && getTermRValueReferenceFromBaseTerm(BaseTerm && baseTerm)
{
    return static_cast<Term &&>(baseTerm);
}

Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm){
    return static_cast<Term &>(baseTerm);
}
Term & getTermReferenceFromUniquePointer(BaseTermUniquePointer & uniquePointer)
{
    return *static_cast<Term*>(uniquePointer.get());
}

BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term)
{
    return static_cast<BaseTerm const&>(term);}

BaseTerm const& getBaseTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return static_cast<BaseTerm const&>(*uniquePointer.get());
}

BaseTerm & getBaseTermReferenceFromTerm(Term & term)
{
    return static_cast<BaseTerm &>(term);}

BaseTerm & getBaseTermReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return static_cast<BaseTerm &>(*uniquePointer.get());
}

}

}