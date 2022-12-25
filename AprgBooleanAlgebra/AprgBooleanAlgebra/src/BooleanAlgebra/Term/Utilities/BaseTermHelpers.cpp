#include "BaseTermHelpers.hpp"

using namespace std;

namespace alba
{
namespace booleanAlgebra
{

BaseTermUniquePointer createAUniquePointerFromTerm(Term const& term)
{
    return static_cast<BaseTermUniquePointer>(make_unique<Term>(term));
}

BaseTermSharedPointer createASharedPointerFromTerm(Term const& term)
{
    return static_cast<BaseTermSharedPointer>(make_shared<Term>(term));
}

Term const& getTermConstReferenceFromBaseTerm(BaseTerm const& baseTerm){
    return dynamic_cast<Term const&>(baseTerm);
}

Term const& getTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer)
{
    return dynamic_cast<Term const&>(*uniquePointer.get());
}

Term const& getTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return dynamic_cast<Term const&>(*sharedPointer.get());
}

Term & getTermReferenceFromBaseTerm(BaseTerm & baseTerm){
    return dynamic_cast<Term &>(baseTerm);
}

Term & getTermReferenceFromUniquePointer(BaseTermUniquePointer & uniquePointer){
    return *dynamic_cast<Term*>(uniquePointer.get());
}

Term & getTermReferenceFromSharedPointer(BaseTermSharedPointer & sharedPointer)
{
    return *dynamic_cast<Term*>(sharedPointer.get());
}

BaseTerm const& getBaseTermConstReferenceFromTerm(Term const& term){
    return dynamic_cast<BaseTerm const&>(term);
}

BaseTerm const& getBaseTermConstReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer){
    return dynamic_cast<BaseTerm const&>(*uniquePointer.get());
}

BaseTerm const& getBaseTermConstReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return dynamic_cast<BaseTerm const&>(*sharedPointer.get());
}

BaseTerm & getBaseTermReferenceFromTerm(Term & term){
    return dynamic_cast<BaseTerm &>(term);
}

BaseTerm & getBaseTermReferenceFromUniquePointer(BaseTermUniquePointer const& uniquePointer){
    return dynamic_cast<BaseTerm &>(*uniquePointer.get());
}

BaseTerm & getBaseTermReferenceFromSharedPointer(BaseTermSharedPointer const& sharedPointer)
{
    return dynamic_cast<BaseTerm &>(*sharedPointer.get());
}

}
}