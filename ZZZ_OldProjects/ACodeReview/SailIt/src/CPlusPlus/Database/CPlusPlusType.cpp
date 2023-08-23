#include "CPlusPlusType.hpp"

#include <iostream>

using namespace std;

namespace codeReview {

CPlusPlusType::CPlusPlusType()
    : m_isConst(false), m_isReference(false), m_pointerCount(0), m_typeType(CPlusPlusTypeType::NoType), m_typeName() {}

CPlusPlusType::CPlusPlusType(string const& typeName, CPlusPlusTypeType const cPlusPlusTypeType, int pointerCount)
    : m_isConst(false),
      m_isReference(false),
      m_pointerCount(pointerCount),
      m_typeType(cPlusPlusTypeType),
      m_typeName(typeName) {}

ostream& operator<<(ostream& out, CPlusPlusType const& cPlusPlusType) {
    return out << "Type: " << cPlusPlusType.getTypeName() << " isConst: " << cPlusPlusType.isConst()
               << " PointerCount: " << cPlusPlusType.getPointerCount()
               << " isReference: " << cPlusPlusType.isReference();
}

string CPlusPlusType::getTypeName() const { return m_typeName; }

string CPlusPlusType::getString() const {
    string typeString(m_typeName);
    if (m_isConst) {
        typeString += " const";
    }
    if (m_isReference) {
        typeString += "&";
    }
    for (int i = 0; i < m_pointerCount; i++) {
        typeString += "*";
    }
    return typeString;
}

int CPlusPlusType::getTemplateInstantiationIndex() const { return m_templateInstantationIndex; }

int CPlusPlusType::getPointerCount() const { return m_pointerCount; }

bool CPlusPlusType::isConst() const { return m_isConst; }

bool CPlusPlusType::isPrimitive() const { return CPlusPlusTypeType::Primitive == m_typeType; }

bool CPlusPlusType::isClass() const { return CPlusPlusTypeType::Class == m_typeType; }

bool CPlusPlusType::isTemplateType() const { return CPlusPlusTypeType::TemplateType == m_typeType; }

bool CPlusPlusType::isTemplateClassInstantiation() const {
    return CPlusPlusTypeType::TemplateClassInstantiation == m_typeType;
}

bool CPlusPlusType::isNotAPointerOrReference() const { return !isPointer() && !isReference(); }

bool CPlusPlusType::isPointer() const { return 0 < m_pointerCount; }

bool CPlusPlusType::isReference() const { return m_isReference; }

bool CPlusPlusType::isEqualIgnoreReference(CPlusPlusType const& type) const {
    CPlusPlusType const& thisType(*this);
    CPlusPlusType nonReferenceType(type);
    nonReferenceType.clearReferenceFlag();
    CPlusPlusType referenceType(type);
    referenceType.setAsReference();
    return thisType == nonReferenceType || thisType == referenceType;
}

void CPlusPlusType::swapType(CPlusPlusTypeType& type1, CPlusPlusTypeType& type2) const {
    if (CPlusPlusTypeType::ConstantNumber == type2) {
        CPlusPlusTypeType tempType(type1);
        type1 = type2;
        type2 = tempType;
    }
}

bool CPlusPlusType::operator==(CPlusPlusType const& cPlusPlusType) const {
    // How about primitive type, bool int double
    // implementation for primitivetypes should be equal
    if (m_isConst != cPlusPlusType.m_isConst) return false;
    if (m_isReference != cPlusPlusType.m_isReference) return false;
    if (m_pointerCount != cPlusPlusType.m_pointerCount) return false;
    CPlusPlusTypeType type1(m_typeType);
    CPlusPlusTypeType type2(cPlusPlusType.m_typeType);
    swapType(type1, type2);
    if (CPlusPlusTypeType::ConstantNumber == type1 && CPlusPlusTypeType::Primitive == type2) return true;
    if (type1 != type2) return false;
    if (m_typeName != cPlusPlusType.m_typeName) return false;
    return true;
}

void CPlusPlusType::incrementPointerCount() { m_pointerCount++; }

void CPlusPlusType::decrementPointerCount() {
    if (m_pointerCount > 0) {
        m_pointerCount--;
    }
}

void CPlusPlusType::clearReferenceFlag() { m_isReference = false; }

void CPlusPlusType::setAsReference() { m_isReference = true; }

void CPlusPlusType::setAsConst() { m_isConst = true; }

void CPlusPlusType::set(string const& typeName, CPlusPlusTypeType const cPlusPlusTypeType) {
    m_typeName = typeName;
    m_typeType = cPlusPlusTypeType;
}

void CPlusPlusType::setTypeName(string const& typeName) { m_typeName = typeName; }

void CPlusPlusType::setTemplateInstantiationIndex(int index) { m_templateInstantationIndex = index; }

}  // namespace codeReview
