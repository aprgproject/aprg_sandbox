#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <forward_list>
#include <iterator>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Value>
class InsertionSorterForForwardList : public BaseSorter<std::forward_list<Value>> {
public:
    using Values = std::forward_list<Value>;

    InsertionSorterForForwardList() = default;

    void sort(Values& valuesToSort) const override {
        if (!valuesToSort.empty()) {
            Values sortedList{valuesToSort.front()};

            for (auto insertIt = std::next(valuesToSort.begin(), 1); insertIt != valuesToSort.end(); insertIt++) {
                insertToSortedList(sortedList, *insertIt);
            }
            valuesToSort = sortedList;
        }
    }

private:
    void insertToSortedList(Values& sortedList, Value const& value) const {
        bool isInserted(false);
        auto previousIt = sortedList.before_begin();
        for (auto it = sortedList.begin(); it != sortedList.end(); it++, previousIt++) {
            if (value < *it) {
                sortedList.emplace_after(previousIt, value);
                isInserted = true;
                break;
            }
        }
        if (!isInserted) {
            sortedList.emplace_after(previousIt, value);
        }
    }
};

}  // namespace algorithm

}  // namespace alba

//
