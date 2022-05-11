#include <Algorithm/PriorityQueue/HeapPriorityQueue.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
template<typename Object>
class MaxItemsSaver
{
public:
    using MinPriorityQueue = HeapPriorityQueue<Object, std::greater>;
    using Objects = std::vector<Object>;

    MaxItemsSaver(unsigned int const numberOfItemsToSave)
        : m_numberOfItemsToSave(numberOfItemsToSave)
    {}

    void save(Object const& object)
    {
        m_minimumPriorityQueue.insert(object);
        while(m_minimumPriorityQueue.getSize() > m_numberOfItemsToSave)
        {
            m_minimumPriorityQueue.deleteAndGetTopObject();
        }
    }

    Objects getMaxItemsAndClear()
    {
        Objects result;
        while(!m_minimumPriorityQueue.isEmpty())
        {
            result.emplace_back(m_minimumPriorityQueue.deleteAndGetTopObject());
        }
        return result;
    }

private:
    unsigned int m_numberOfItemsToSave;
    MinPriorityQueue m_minimumPriorityQueue; // counter intuitive to use min priority queue here but think about it
};

using MaxItemsSaverForTest = MaxItemsSaver<unsigned int>;

}

TEST(MaxItemsSaverTest, GetMaxItemsAndClearWorks)
{
    MaxItemsSaverForTest saver(3);
    saver.save(5U);
    saver.save(100U);
    saver.save(11U);
    saver.save(19U);
    saver.save(66U);
    saver.save(45U);
    saver.save(721U);
    saver.save(98U);
    saver.save(976U);

    MaxItemsSaverForTest::Objects expectedObjects{100U, 721U, 976U};
    EXPECT_EQ(expectedObjects, saver.getMaxItemsAndClear());
}

}

}
