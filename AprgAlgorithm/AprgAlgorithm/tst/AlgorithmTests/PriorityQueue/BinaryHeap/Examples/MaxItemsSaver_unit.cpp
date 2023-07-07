#include <Algorithm/PriorityQueue/BinaryHeap/BinaryHeapPriorityQueue.hpp>

#include <gtest/gtest.h>
#include <vector>

using namespace std;
namespace alba {

namespace algorithm {

namespace {
template <typename Object>
class MaxItemsSaver {
public:
    using MinPriorityQueue = BinaryHeapPriorityQueue<Object, greater>;
    using Objects = vector<Object>;

    MaxItemsSaver(int const numberOfItemsToSave) : m_numberOfItemsToSave(numberOfItemsToSave) {}
    void save(Object const& object) {
        m_minimumPriorityQueue.insert(object);
        while (m_minimumPriorityQueue.getSize() > m_numberOfItemsToSave) {            m_minimumPriorityQueue.deleteAndGetTopObject();
        }
    }

    Objects getMaxItemsAndClear() {
        Objects result;
        while (!m_minimumPriorityQueue.isEmpty()) {
            result.emplace_back(m_minimumPriorityQueue.deleteAndGetTopObject());
        }
        return result;
    }

private:
    int m_numberOfItemsToSave;
    MinPriorityQueue m_minimumPriorityQueue;  // counter intuitive to use min priority queue here but think about it
};

using MaxItemsSaverForTest = MaxItemsSaver<int>;

}  // namespace

TEST(MaxItemsSaverTest, GetMaxItemsAndClearWorks) {
    MaxItemsSaverForTest saver(3);
    saver.save(5);
    saver.save(100);
    saver.save(11);
    saver.save(19);
    saver.save(66);
    saver.save(45);
    saver.save(721);
    saver.save(98);
    saver.save(976);

    MaxItemsSaverForTest::Objects expectedObjects{100, 721, 976};
    EXPECT_EQ(expectedObjects, saver.getMaxItemsAndClear());
}

}  // namespace algorithm

}  // namespace alba
