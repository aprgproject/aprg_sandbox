#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <forward_list>

namespace alba
{

namespace algorithm
{

template <typename Value>
class MergeSorterForForwardList : public BaseSorter<std::forward_list<Value>>
{
public:
    using Values = std::forward_list<Value>;
    using Iterator = typename Values::iterator;
    using ConstIterator = typename Values::const_iterator;

    MergeSorterForForwardList() = default;

    void sort(Values & valuesToSort) const override
    {
        valuesToSort = getSortedValues(valuesToSort);
    }

private:

    Values getSortedValues(
            Values const& unsortedValues) const
    {
        ConstIterator middle = getMiddleIterator(unsortedValues);
        if(middle == unsortedValues.cend())
        {
            return unsortedValues;
        }
        else
        {
            // Split to two parts
            Values firstPart, secondPart; // this is costly, in a more controllable forward link list we can split it more easily
            Iterator itNewFirstPart=firstPart.before_begin(), itNewSecondPart=secondPart.before_begin();
            for(ConstIterator it=unsortedValues.cbegin(); it!=middle; it++)
            {
                itNewFirstPart = firstPart.emplace_after(itNewFirstPart, *it);
            }
            for(ConstIterator it=middle; it!=unsortedValues.cend(); it++)
            {
                itNewSecondPart = secondPart.emplace_after(itNewSecondPart, *it);
            }

            return mergeTwoRanges(getSortedValues(firstPart), getSortedValues(secondPart)); // this is top down merge sort
        }
    }

    ConstIterator getMiddleIterator(Values const& values) const
    {
        ConstIterator turtoise(values.cbegin());
        ConstIterator hare(values.cbegin());
        while(hare!=values.cend())
        {
            turtoise++;
            hare++;
            if(hare!=values.cend())
            {
                hare++;
            }
        }
        return turtoise;
    }

    Values mergeTwoRanges(
            Values const& firstPart,
            Values const& secondPart) const
    {
        // this is similar with std::forward_list::merge

        Values result;
        Iterator itNewValue=result.before_begin();
        ConstIterator it1=firstPart.cbegin(), it2=secondPart.cbegin();
        for(; it1!=firstPart.cend() && it2!=secondPart.cend(); )
        {
            if(*it1 <= *it2)
            {
                itNewValue = result.emplace_after(itNewValue, *it1);
                it1++;
            }
            else
            {
                itNewValue = result.emplace_after(itNewValue, *it2);
                it2++;
            }
        }
        for(; it1!=firstPart.cend(); it1++)
        {
            itNewValue = result.emplace_after(itNewValue, *it1);
        }
        for(; it2!=secondPart.cend(); it2++)
        {
            itNewValue = result.emplace_after(itNewValue, *it2);
        }
        return result;
    }

};

}

}

