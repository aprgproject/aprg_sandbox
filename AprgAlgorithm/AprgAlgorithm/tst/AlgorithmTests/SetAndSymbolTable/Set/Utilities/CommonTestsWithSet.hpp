#pragma once

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithSet
{

template <typename Set>
void testIsEmptyWhenEmptyWithUnsignedIntAndChar()
{
    Set setObject;

    EXPECT_TRUE(setObject.isEmpty());
}

template <typename Set>
void testIsEmptyWhenNotEmptyWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(5U);

    EXPECT_FALSE(setObject.isEmpty());
}

template <typename Set>
void testDoesContainWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(5U);

    EXPECT_FALSE(setObject.doesContain(4U));
    EXPECT_TRUE(setObject.doesContain(5U));
}

template <typename Set>
void testGetSizeWhenEmptyWithUnsignedIntAndChar()
{
    Set setObject;

    EXPECT_EQ(0U, setObject.getSize());
}

template <typename Set>
void testGetSizeWhenNotEmptyWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(7U);
    setObject.put(5U);
    setObject.put(6U);

    EXPECT_EQ(3U, setObject.getSize());
}

template <typename Set>
void testGetWithUnsignedIntAndChar()
{
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7U);
    setObject.put(5U);
    setObject.put(6U);

    EXPECT_EQ((Keys{5U, 6U, 7U}), setObject.getKeys());
}

template <typename Set>
void testGetRankWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(8U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);

    EXPECT_EQ(0U, setObject.getRank(3U));
    EXPECT_EQ(0U, setObject.getRank(4U));
    EXPECT_EQ(1U, setObject.getRank(5U));
    EXPECT_EQ(2U, setObject.getRank(6U));
    EXPECT_EQ(2U, setObject.getRank(7U));
    EXPECT_EQ(3U, setObject.getRank(8U));
    EXPECT_EQ(4U, setObject.getRank(9U));
}

template <typename Set>
void testGetMinimumWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(8U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);

    EXPECT_EQ(4U, setObject.getMinimum());
}

template <typename Set>
void testGetMaximumWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(8U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);

    EXPECT_EQ(8U, setObject.getMaximum());
}

template <typename Set>
void testSelectAtWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(8U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);

    EXPECT_EQ(4U, setObject.selectAt(0U));
    EXPECT_EQ(5U, setObject.selectAt(1U));
    EXPECT_EQ(7U, setObject.selectAt(2U));
    EXPECT_EQ(8U, setObject.selectAt(3U));
}

template <typename Set>
void testGetFloorWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(8U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);

    EXPECT_EQ(0U, setObject.getFloor(3U));
    EXPECT_EQ(4U, setObject.getFloor(4U));
    EXPECT_EQ(5U, setObject.getFloor(5U));
    EXPECT_EQ(5U, setObject.getFloor(6U));
    EXPECT_EQ(7U, setObject.getFloor(7U));
    EXPECT_EQ(8U, setObject.getFloor(8U));
    EXPECT_EQ(8U, setObject.getFloor(9U));
}

template <typename Set>
void testGetCeilingWithUnsignedIntAndChar()
{
    Set setObject;
    setObject.put(8U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);

    EXPECT_EQ(4U, setObject.getCeiling(3U));
    EXPECT_EQ(4U, setObject.getCeiling(4U));
    EXPECT_EQ(5U, setObject.getCeiling(5U));
    EXPECT_EQ(7U, setObject.getCeiling(6U));
    EXPECT_EQ(7U, setObject.getCeiling(7U));
    EXPECT_EQ(8U, setObject.getCeiling(8U));
    EXPECT_EQ(0U, setObject.getCeiling(9U));
}

template <typename Set>
void testPutWithUnsignedIntAndChar()
{
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7U);
    setObject.put(5U);
    setObject.put(6U);

    EXPECT_EQ((Keys{5U, 6U, 7U}), setObject.getKeys());
}

template <typename Set>
void testDeleteBasedOnKeyWithUnsignedIntAndChar()
{
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7U);
    setObject.put(5U);
    setObject.put(6U);

    setObject.deleteBasedOnKey(5U);
    EXPECT_EQ((Keys{6U, 7U}), setObject.getKeys());

    setObject.deleteBasedOnKey(6U);
    EXPECT_EQ((Keys{7U}), setObject.getKeys());

    setObject.deleteBasedOnKey(7U);
    EXPECT_TRUE(setObject.getKeys().empty());
}

template <typename Set>
void testDeleteMinimumWithUnsignedIntAndChar()
{
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7U);
    setObject.put(5U);
    setObject.put(6U);

    setObject.deleteMinimum();
    EXPECT_EQ((Keys{6U, 7U}), setObject.getKeys());
}

template <typename Set>
void testDeleteMaximumWithUnsignedIntAndChar()
{
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7U);
    setObject.put(5U);
    setObject.put(6U);

    setObject.deleteMaximum();
    EXPECT_EQ((Keys{5U, 6U}), setObject.getKeys());
}

template <typename Set>
void testGetKeysWithUnsignedIntAndChar()
{
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(8U);
    setObject.put(9U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);
    setObject.put(3U);

    Keys keysToVerify(setObject.getKeys());

    Keys expectedKeys{3U, 4U, 5U, 7U, 8U, 9U};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename Set>
void testGetKeysInRangeInclusiveWithUnsignedIntAndChar()
{
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(8U);
    setObject.put(9U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);
    setObject.put(3U);

    Keys keysToVerify(setObject.getKeysInRangeInclusive(5U, 8U));

    Keys expectedKeys{5U, 7U, 8U};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}

}

}
