#pragma once

#include <ostream>
#include <string>

using std::string;
using std::ostream;

namespace codeReview
{

enum class CPlusPlusTypeType
{
    Class,
    ConstantNumber,
    NoType,
    Primitive,
    TemplateClass,
    TemplateClassInstantiation,
    TemplateType
};

class CPlusPlusType
{
public:
    CPlusPlusType();
    CPlusPlusType(string const& typeName, CPlusPlusTypeType const cPlusPlusTypeType, int pointerCount=0);
    friend ostream& operator<<(ostream & out, CPlusPlusType const& cPlusPlusType);
    string getTypeName() const;
    string getString() const;
    int getPointerCount() const;
    int getTemplateInstantiationIndex() const;
    bool isConst() const;
    bool isPrimitive() const;
    bool isClass() const;
    bool isTemplateType() const;
    bool isTemplateClassInstantiation() const;
    bool isNotAPointerOrReference() const;    
    bool isPointer() const;
    bool isReference() const;
    bool isEqualIgnoreReference(CPlusPlusType const& type) const;
    void swapType(CPlusPlusTypeType& type1, CPlusPlusTypeType& type2) const;

    bool operator==(CPlusPlusType const& cPlusPlusType) const;
    void incrementPointerCount();
    void decrementPointerCount();
    void clearReferenceFlag();
    void setAsReference();
    void setAsConst();
    void set(string const& typeName, CPlusPlusTypeType const cPlusPlusTypeType);
    void setTypeName(string const& typeName);
    void setTemplateInstantiationIndex(int index);

private:
    bool m_isConst;
    bool m_isReference;
    int m_pointerCount;
    CPlusPlusTypeType m_typeType;
    string m_typeName;
    int m_templateInstantationIndex;
};

}


