#pragma once

#include <Algorithm/SetAndSymbolTable/Common/Array/BaseOrderedArray.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>

namespace alba {

namespace algorithm {

template <typename Key>
class OrderedArraySet : public BaseOrderedArray<Key, BaseSet<Key>> {
public:
    using BaseClass = BaseOrderedArray<Key, BaseSet<Key>>;
    using Keys = typename BaseClass::Keys;

    OrderedArraySet() : BaseClass(), b_size(BaseClass::m_size), b_keys(BaseClass::m_keys) {}

    void put(Key const& key) override {
        int rank(this->getRank(key));
        bool isKeyFound = rank < b_size && b_keys.at(rank) == key;
        if (!isKeyFound) {
            b_keys.emplace_back();
            for (int i = b_size; i > rank; i--) {
                b_keys[i] = b_keys.at(i - 1);
            }
            b_keys[rank] = key;
            b_size++;
        }
    }

    void deleteBasedOnKey(Key const& key) override {
        int rank(this->getRank(key));
        if (rank < b_size && b_keys.at(rank) == key) {
            if (b_size >= 2) {
                for (int i = rank; i < b_size - 1; i++) {
                    b_keys[i] = b_keys.at(i + 1);
                }
            }
            b_keys.pop_back();
            b_size--;
        }
    }

    void deleteMinimum() override {
        for (int i = 0; i < b_size - 1; i++) {
            b_keys[i] = b_keys.at(i + 1);
        }
        b_keys.pop_back();
        b_size--;
    }

    void deleteMaximum() override {
        b_keys.pop_back();
        b_size--;
    }

private:
    int& b_size;
    Keys& b_keys;
};

}  // namespace algorithm

}  // namespace alba
