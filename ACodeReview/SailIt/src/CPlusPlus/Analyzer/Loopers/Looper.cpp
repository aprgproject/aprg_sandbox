#include "Looper.hpp"
#include <iostream>
#include <map>

using namespace std;

namespace codeReview
{

Looper::Looper(DequeOfTerms& terms, unsigned int const uniqueFileId)
    : m_currentIndex(0)
    , m_endIndex(terms.size())
    , m_terms(terms)
    , m_uniqueGroupId(uniqueFileId)
{
    doAtConstruction();
}

Looper::Looper(Looper const& copyLooper)
    : m_currentIndex(copyLooper.m_currentIndex)
    , m_endIndex(copyLooper.m_endIndex)
    , m_terms(copyLooper.m_terms)
    , m_uniqueGroupId(copyLooper.m_uniqueGroupId)
{
    doAtConstruction();
}

Looper::Looper(Looper const& startLooper, Looper const& endLooper)
    : m_currentIndex(startLooper.m_currentIndex)
    , m_endIndex(endLooper.m_currentIndex)
    , m_terms(startLooper.m_terms)
    , m_uniqueGroupId(startLooper.m_uniqueGroupId)
{
    doAtConstruction();
}

Looper::~Looper()
{
    doAtDestruction();
}

ostream& operator<<(ostream & out, Looper const& looper)
{
    return (out << "Loopers=" << Looper::s_activeLoopers.size()
            << " Looper(" << looper.m_currentIndex
            << " to " << looper.m_endIndex
            << ")");
}

void Looper::operator++(int)
{
    m_currentIndex++;
}

void Looper::operator--(int)
{
    m_currentIndex--;
}

Looper Looper::operator+(int const offset) const
{
    Looper tempLooper(*this);
    tempLooper.m_currentIndex += offset;
    return tempLooper;
}

Looper Looper::operator-(int const offset) const
{
    Looper tempLooper(*this);
    tempLooper.m_currentIndex -= offset;
    return tempLooper;
}

bool Looper::isFinished() const
{
    return m_currentIndex >= m_endIndex;
}

bool Looper::isNotFinished() const
{
    return m_currentIndex < m_endIndex;
}

bool Looper::isNotFinishedWhenBackward() const
{
    return m_currentIndex >= 0;
}

Term& Looper::getContentReference() const
{
    return m_terms.at(m_currentIndex);
}

int Looper::getCurrentIndex() const
{
    return m_currentIndex;
}

TermsIterator Looper::getCurrentIterator() const
{
    return m_terms.begin()+m_currentIndex;
}

int Looper::getEndIndex() const
{
    return m_endIndex;
}

TermsIterator Looper::getEndIterator() const
{
    return m_terms.begin()+m_endIndex;
}

int Looper::getLength() const
{
    return m_endIndex-m_currentIndex;
}

UniqueId Looper::getUniqueFileId() const
{
    return m_uniqueGroupId;
}

void Looper::setCurrentIndex(Looper const& indexLooper)
{
    m_currentIndex = indexLooper.m_currentIndex;
}

void Looper::hardSetCurrentIndex(LooperIndex const index)
{
    m_currentIndex = index;
}

void Looper::copyLooper(Looper const& copyLooper)
{
    m_currentIndex = copyLooper.m_currentIndex;
    m_endIndex = copyLooper.m_endIndex;
}

void Looper::setContent(Term const& term)
{
    m_terms.at(m_currentIndex) = term;
}

void Looper::setEndIndex(Looper const& indexLooper)
{
    m_endIndex = indexLooper.m_currentIndex;
}

void Looper::fixLoopers(UniqueId const uniqueFileId, ModifyDetails const& modifyDetails)
{
    for (ActiveLoopersMap::iterator it = s_activeLoopers.begin(); it != s_activeLoopers.end(); it++)
    {
        Looper& fixIndexLooper = *(it->second);
        if (fixIndexLooper.getUniqueFileId() == uniqueFileId)
        {
            fixIndexLooper.fixIndexes(modifyDetails);
        }
    }
}

void Looper::doAtConstruction()
{
    m_uniqueId = s_objectCount;
    s_activeLoopers[m_uniqueId] = this;
    s_objectCount++;

}

void Looper::doAtDestruction()
{
    s_activeLoopers.erase(m_uniqueId);
    s_objectCount--;
}

void Looper::fixIndexes(ModifyDetails const& modifyDetails)
{
    m_currentIndex = getFixedIndex(m_currentIndex, modifyDetails);
    m_endIndex = getFixedIndex(m_endIndex, modifyDetails);
}

int Looper::getFixedIndex(int const indexToFix, ModifyDetails const& modifyDetails)
{
    int fixedIndex = indexToFix;
    if(fixedIndex > modifyDetails.m_startIndex)
    {
        fixedIndex += modifyDetails.m_lengthAdded;
        if(fixedIndex < modifyDetails.m_startIndex)
        {
            fixedIndex = modifyDetails.m_startIndex;
        }
    }
    return fixedIndex;
}

UniqueId Looper::s_objectCount=0;
ActiveLoopersMap Looper::s_activeLoopers;

}// namespace codeReview
