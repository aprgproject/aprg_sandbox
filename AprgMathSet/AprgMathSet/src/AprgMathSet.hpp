#pragma once

#include <String/AlbaStringHelper.hpp>

#include <functional>
#include <ostream>
#include <set>
#include <sstream>
#include <vector>

namespace alba
{

template <typename ElementType>
class AprgMathSet
{
public:
    using Rule = std::function<bool(ElementType const&)>;
    using RosterInitializerList = std::initializer_list<ElementType>;
    using RosterList = std::vector<ElementType>;
    using RosterContainer = std::set<ElementType>;
    using VoidElementFunction = std::function<void(ElementType const&)>;
    using GenerateFunction = std::function<void(VoidElementFunction const& generateElementFunction)>;

    AprgMathSet()
        : m_description("Null set")
        , m_ruleToBeInTheSet([](ElementType const&)->bool{return false;})
{}

AprgMathSet(RosterList const& rosterList)
{
    constructSetBasedOnRosterList(rosterList);
}

AprgMathSet(RosterInitializerList const& initializerList)
{
    RosterList rosterList;
    std::copy(initializerList.begin(), initializerList.end(), std::back_inserter(rosterList));
    constructSetBasedOnRosterList(rosterList);
}

AprgMathSet(std::string const& description, Rule const& rule)
    : m_description(description)
{
    m_ruleToBeInTheSet = rule;
}

bool contains(ElementType const& elementToCheck) const
{
    return m_ruleToBeInTheSet(elementToCheck);
}

bool doesNotContain(ElementType const& elementToCheck) const
{
    return !contains(elementToCheck);
}

std::string getDescription() const
{
    return std::string("{")+m_description+"}";
}

std::string getGeneratedRosterString(GenerateFunction const& generateFunction) const
{
    std::stringstream descriptionStream;
    unsigned int index=0;
    generateFunction([&](ElementType const& element)
    {
        if(contains(element))
        {
            enumerateElements(descriptionStream, element, index);
            index++;
        }
    });
    return std::string("{... ")+descriptionStream.str()+" ...}";
}

bool isASubsetOf(AprgMathSet const& mathSet2, GenerateFunction const& generateFunction) const
{
    bool result(true);
    generateFunction([&](ElementType const& element)
    {
        if(contains(element) && mathSet2.doesNotContain(element))
        {
            result = false;
        }
    });
    return result;
}

bool isASupersetOf(AprgMathSet const& mathSet2, GenerateFunction const& generateFunction) const
{
    bool result(true);
    generateFunction([&](ElementType const& element)
    {
        if(mathSet2.contains(element) && doesNotContain(element))
        {
            result = false;
        }
    });
    return result;
}

bool isDisjointWith(AprgMathSet const& mathSet2, GenerateFunction const& generateFunction) const
{
    bool result(true);
    generateFunction([&](ElementType const& element)
    {
        if(contains(element) && mathSet2.contains(element))
        {
            result = false;
        }
    });
    return result;
}

AprgMathSet getComplement() const
{
    Rule ruleToBeInTheNewSet  = [&](ElementType const& elementToCheck) -> bool
    {
        return !m_ruleToBeInTheSet(elementToCheck);
    };
    return AprgMathSet(std::string("complement of ")+getDescription(), ruleToBeInTheNewSet);
}

AprgMathSet getUnionWith(AprgMathSet const& mathSet2) const
{
    Rule ruleToBeInTheNewSet  = [&](ElementType const& elementToCheck) -> bool
    {
        return m_ruleToBeInTheSet(elementToCheck) || mathSet2.m_ruleToBeInTheSet(elementToCheck);
    };
    return AprgMathSet(getDescription() + " union " + mathSet2.getDescription(), ruleToBeInTheNewSet);
}

AprgMathSet getIntersectionWith(AprgMathSet const& mathSet2) const
{
    Rule ruleToBeInTheNewSet  = [&](ElementType const& elementToCheck) -> bool
    {
        return m_ruleToBeInTheSet(elementToCheck) && mathSet2.m_ruleToBeInTheSet(elementToCheck);
    };
    return AprgMathSet(getDescription() + " intersection " + mathSet2.getDescription(), ruleToBeInTheNewSet);
}

private:
void constructSetBasedOnRosterList(RosterList const& rosterList)
{
    m_ruleToBeInTheSet = [rosterList](ElementType const& elementToCheck) mutable -> bool
    {
        bool result(false);
        for(ElementType const& elementInRoster : rosterList)
        {
            if(elementToCheck==elementInRoster)
            {
                result = true;
                break;
            }
        }
        return result;
    };
    std::stringstream descriptionStream;
    unsigned int index=0;
    for(ElementType const& elementInRoster : rosterList)
    {
        enumerateElements(descriptionStream, elementInRoster, index);
        index++;
    }
    m_description = descriptionStream.str();
}

void enumerateElements(std::stringstream & descriptionStream, ElementType const& elementInRoster, unsigned int const index) const
{
    if(index==0)
    {
        descriptionStream << elementInRoster;
    }
    else
    {
        descriptionStream << ", " << elementInRoster;
    }
}

std::string m_description;
Rule m_ruleToBeInTheSet;
};

template <typename ElementType>
AprgMathSet<ElementType> getUnion(
        AprgMathSet<ElementType> const& set1,
        AprgMathSet<ElementType> const& set2)
{
    return set1.getUnionWith(set2);
}

template <typename ElementType>
AprgMathSet<ElementType> getIntersection(
        AprgMathSet<ElementType> const& set1,
        AprgMathSet<ElementType> const& set2)
{
    return set1.getIntersectionWith(set2);
}

template <typename ElementType1, typename ElementType2>
AprgMathSet<std::pair<ElementType1, ElementType2>> getCarterisianProduct(
        AprgMathSet<ElementType1> const& set1,
        AprgMathSet<ElementType2> const& set2,
        typename AprgMathSet<ElementType1>::GenerateFunction const& generateFunction1,
        typename AprgMathSet<ElementType2>::GenerateFunction const& generateFunction2)
{
    std::vector<std::pair<ElementType1, ElementType2>> rosterList;
    generateFunction1([&](ElementType1 const& elementInSet1)
    {
        if(set1.contains(elementInSet1))
        {
            generateFunction2([&](ElementType2 const& elementInSet2)
            {
                if(set2.contains(elementInSet2))
                {
                    rosterList.emplace_back(elementInSet1, elementInSet2);
                }
            });
        }
    });
    return AprgMathSet<std::pair<ElementType1, ElementType2>>(rosterList);
}

template <typename ElementType1, typename ElementType2>
std::ostream & operator<<(std::ostream & out, std::pair<ElementType1, ElementType2> const& pairWithTwoElements)
{
    out << "(" << pairWithTwoElements.first << "," << pairWithTwoElements.second << ")";
    return out;
}


}
