#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace alba {

namespace algorithm {

template <typename KeyTemplateType, typename NodeTemplateType, typename BaseDataStructure>
class BaseUnorderedLinkedList : public BaseDataStructure {
public:
    using Key = KeyTemplateType;
    using Node = NodeTemplateType;
    using NodeUniquePointer = std::unique_ptr<Node>;
    using Keys = std::vector<Key>;
    using TraverseFunctionWithNoChange = std::function<void(Node const&, bool&)>;
    using TraverseFunctionWithChange = std::function<void(Node&, bool&)>;

    BaseUnorderedLinkedList() : m_size(0), m_first(nullptr) {}

    ~BaseUnorderedLinkedList() override = default;  // no need for virtual destructor because base destructor is virtual
                                                    // (similar to other virtual functions)

    bool isEmpty() const override { return m_size == 0; }

    bool doesContain(Key const& key) const override {
        bool result(false);
        traverseWithNoChange([&](Node const& node, bool& shouldBreak) {
            if (key == node.key) {
                result = true;
                shouldBreak = true;
            }
        });
        return result;
    }

    int getSize() const override { return m_size; }

    int getRank(Key const& key) const override {
        int result(0);
        traverseWithNoChange([&](Node const& node, bool&) {
            if (key > node.key) {
                result++;
            }
        });
        return result;
    }

    Key getMinimum() const override {
        Key result{};
        bool isFirst(true);
        traverseWithNoChange([&](Node const& node, bool&) {
            if (isFirst) {
                result = node.key;
                isFirst = false;
            } else {
                result = std::min(result, node.key);
            }
        });
        return result;
    }

    Key getMaximum() const override {
        Key result{};
        bool isFirst(true);
        traverseWithNoChange([&](Node const& node, bool&) {
            if (isFirst) {
                result = node.key;
                isFirst = false;
            } else {
                result = std::max(result, node.key);
            }
        });
        return result;
    }

    Key selectAt(int const rank) const override {
        Key result{};
        traverseWithNoChange([&](Node const& node, bool& shouldBreak) {
            int const rankAtTraversal(getRank(node.key));
            if (rank == rankAtTraversal) {
                result = node.key;
                shouldBreak = true;
            }
        });
        return result;
    }

    Key getFloor(Key const& key) const override {
        Key floor{};
        bool isFirst(true);
        traverseWithNoChange([&](Node const& node, bool& shouldBreak) {
            if (key == node.key) {
                floor = node.key;
                shouldBreak = true;
            } else if (isFirst && key > node.key) {
                floor = node.key;
                isFirst = false;
            } else if (!isFirst && key > node.key && key - node.key < key - floor)  // less than key and nearer than key
            {
                floor = node.key;
            }
        });
        return floor;
    }

    Key getCeiling(Key const& key) const override {
        Key ceiling{};
        bool isFirst(true);
        traverseWithNoChange([&](Node const& node, bool& shouldBreak) {
            if (key == node.key) {
                ceiling = node.key;
                shouldBreak = true;
            } else if (isFirst && key < node.key) {
                ceiling = node.key;
                isFirst = false;
            } else if (!isFirst && key < node.key && node.key - key < ceiling - key)  // greater than key and nearer
                                                                                      // than key
            {
                ceiling = node.key;
            }
        });
        return ceiling;
    }

    void deleteBasedOnKey(Key const& key) override {
        Node* previousNodePointer(nullptr);
        for (Node* currentNodePointer = m_first.get(); currentNodePointer != nullptr;
             currentNodePointer = currentNodePointer->next.get()) {
            if (currentNodePointer != nullptr) {
                if (key == currentNodePointer->key) {
                    if (previousNodePointer == nullptr) {
                        m_first = std::move(currentNodePointer->next);
                    } else {
                        previousNodePointer->next = std::move(currentNodePointer->next);
                    }
                    m_size--;
                    break;
                }
            }
            previousNodePointer = currentNodePointer;
        }
    }

    void deleteMinimum() override { deleteBasedOnKey(getMinimum()); }

    void deleteMaximum() override { deleteBasedOnKey(getMaximum()); }

    Keys getKeys() const override {
        Keys result;
        traverseWithNoChange([&](Node const& node, bool&) { result.emplace_back(node.key); });
        std::sort(result.begin(), result.end());
        return result;
    }

    Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override {
        Keys result;
        traverseWithNoChange([&](Node const& node, bool&) {
            if (node.key >= low && node.key <= high) {
                result.emplace_back(node.key);
            }
        });
        std::sort(result.begin(), result.end());
        return result;
    }

protected:
    void traverseWithNoChange(TraverseFunctionWithNoChange const& traverseFunction) const {
        for (Node const* currentNodePointer = m_first.get(); currentNodePointer != nullptr;
             currentNodePointer = currentNodePointer->next.get()) {
            bool shouldBreak(false);
            traverseFunction(*currentNodePointer, shouldBreak);
            if (shouldBreak) {
                break;
            }
        }
    }

    void traverseWithChange(TraverseFunctionWithChange const& traverseFunction) {
        for (Node* currentNodePointer = m_first.get(); currentNodePointer != nullptr;
             currentNodePointer = currentNodePointer->next.get()) {
            bool shouldBreak(false);
            traverseFunction(*currentNodePointer, shouldBreak);
            if (shouldBreak) {
                break;
            }
        }
    }

    int m_size;
    NodeUniquePointer m_first;
};

}  // namespace algorithm

}  // namespace alba
