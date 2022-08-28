#pragma once

#include <Algorithm/Combinatorics/Subsets/SubsetGenerationUsingRecursion.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <functional>
#include <ostream>
#include <set>
#include <sstream>
#include <vector>

namespace alba
{

namespace math
{

//This needs to first because template needs to available so that compiler can use it.
template <typename ElementType1, typename ElementType2>
std::ostream & operator<<(std::ostream & out, std::pair<ElementType1, ElementType2> const& pairWithTwoElements)
{
    out << "(" << pairWithTwoElements.first << "," << pairWithTwoElements.second << ")";
    return out;
}

template <typename ElementType>
class MathSet
{
public:
    using MathSets = std::vector<MathSet>;
    using Rule = std::function<bool(ElementType const&)>;
    using RosterInitializerList = std::initializer_list<ElementType>;
    using RosterList = std::vector<ElementType>;
    using RosterSet = std::set<ElementType>;
    using RosterLists = std::vector<RosterList>;
    using VoidElementFunction = std::function<void(ElementType const&)>;
    using GenerateFunction = std::function<void(VoidElementFunction const& generateElementFunction)>;

    MathSet()
        : m_description("Null set")
    #define NULL_RULE [](ElementType const&)->bool{return false;} // need to macro because it affects indentions
        , m_ruleToBeInTheSet(NULL_RULE)
    #undef NULL_RULE
    {}

    MathSet(RosterList const& rosterList)
    {
        constructSetBasedOnRosterList(rosterList);
    }

    MathSet(RosterInitializerList const& initializerList)
    {
        RosterList rosterList;
        rosterList.reserve(initializerList.size());
        std::copy(initializerList.begin(), initializerList.end(), std::back_inserter(rosterList));
        constructSetBasedOnRosterList(rosterList);
    }

    MathSet(std::string const& description, Rule const& rule)
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
                enumerateElement(descriptionStream, element, index);
                index++;
            }
        });
        return std::string("{... ")+descriptionStream.str()+" ...}";
    }

    bool isASubsetOf(MathSet const& mathSet2, GenerateFunction const& generateFunction) const
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

    bool isASupersetOf(MathSet const& mathSet2, GenerateFunction const& generateFunction) const
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

    bool isDisjointWith(MathSet const& mathSet2, GenerateFunction const& generateFunction) const
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

    MathSet getComplement() const
    {
        Rule ruleToBeInTheNewSet = [&](ElementType const& elementToCheck) -> bool
        {
            return !m_ruleToBeInTheSet(elementToCheck);
        };
        return MathSet(std::string("complement of ")+getDescription(), ruleToBeInTheNewSet);
    }

    MathSet getUnionWith(MathSet const& mathSet2) const
    {
        Rule ruleToBeInTheNewSet = [&](ElementType const& elementToCheck) -> bool
        {
            return m_ruleToBeInTheSet(elementToCheck) || mathSet2.m_ruleToBeInTheSet(elementToCheck);
        };
        return MathSet(getDescription() + " union " + mathSet2.getDescription(), ruleToBeInTheNewSet);
    }

    MathSet getIntersectionWith(MathSet const& mathSet2) const
    {
        Rule ruleToBeInTheNewSet = [&](ElementType const& elementToCheck) -> bool
        {
            return m_ruleToBeInTheSet(elementToCheck) && mathSet2.m_ruleToBeInTheSet(elementToCheck);
        };
        return MathSet(getDescription() + " intersection " + mathSet2.getDescription(), ruleToBeInTheNewSet);
    }

    MathSet getDifferenceWith(MathSet const& mathSet2) const
    {
        //The difference (A\B) = A intersection B' consists of elements that are in A but not in B. Note that B can contain elements that are not in A.
        Rule ruleToBeInTheNewSet = [&](ElementType const& elementToCheck) -> bool
        {
            return m_ruleToBeInTheSet(elementToCheck) && !mathSet2.m_ruleToBeInTheSet(elementToCheck);
        };
        return MathSet(getDescription() + " difference " + mathSet2.getDescription(), ruleToBeInTheNewSet);
    }

    MathSets getSubsets(GenerateFunction const& generateFunction) const
    {
        RosterList roster;
        generateFunction([&](ElementType const& element)
        {
            if(contains(element))
            {
                roster.emplace_back(element);
            }
        });
        algorithm::SubsetGenerationUsingRecursion<RosterList> subsetGeneration;
        RosterLists subsetsRoster(subsetGeneration.generateOrderedSubsetsUsingDfs(roster));
        MathSets result;
        for(RosterList const& subsetRoster : subsetsRoster)
        {
            result.emplace_back(subsetRoster);
        }
        return result;
    }

private:
    void constructSetBasedOnRosterList(RosterList const& rosterList)
    {
        RosterSet rosterSet(rosterList.cbegin(), rosterList.cend());
        m_ruleToBeInTheSet = [rosterSet](ElementType const& elementToCheck) mutable -> bool
        {
            return rosterSet.find(elementToCheck) != rosterSet.cend();
        };
        m_description = getDescriptionForRosterList(rosterList);
    }

    std::string getDescriptionForRosterList(RosterList const& rosterList) const
    {
        std::stringstream descriptionStream;
        unsigned int index=0;
        for(ElementType const& elementInRoster : rosterList)
        {
            enumerateElement(descriptionStream, elementInRoster, index);
            index++;
        }
        return descriptionStream.str();
    }

    void enumerateElement(std::stringstream & descriptionStream, ElementType const& elementInRoster, unsigned int const index) const
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
MathSet<ElementType> getUnion(
        MathSet<ElementType> const& set1,
        MathSet<ElementType> const& set2)
{
    return set1.getUnionWith(set2);
}

template <typename ElementType>
MathSet<ElementType> getIntersection(
        MathSet<ElementType> const& set1,
        MathSet<ElementType> const& set2)
{
    return set1.getIntersectionWith(set2);
}

template <typename ElementType>
MathSet<ElementType> getDifference(
        MathSet<ElementType> const& set1,
        MathSet<ElementType> const& set2)
{
    return set1.getDifferenceWith(set2);
}

template <typename ElementType1, typename ElementType2>
MathSet<std::pair<ElementType1, ElementType2>> getCartersianProduct(
        MathSet<ElementType1> const& set1,
        MathSet<ElementType2> const& set2,
        typename MathSet<ElementType1>::GenerateFunction const& generateFunction1,
        typename MathSet<ElementType2>::GenerateFunction const& generateFunction2)
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
    return MathSet<std::pair<ElementType1, ElementType2>>(rosterList);
}

template <typename ElementType>
std::ostream & operator<<(std::ostream & out, MathSet<ElementType> const& set)
{
    out << set.getDescription();
    return out;
}

}

}
