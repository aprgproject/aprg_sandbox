#pragma once

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

namespace algorithm {

namespace CommonTestsWithSet {

template <typename Set>
void testIsEmptyWhenEmptyWithUnsignedIntAndChar() {
    Set setObject;

    EXPECT_TRUE(setObject.isEmpty());
}

template <typename Set>
void testIsEmptyWhenNotEmptyWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(5);

    EXPECT_FALSE(setObject.isEmpty());
}

template <typename Set>
void testDoesContainWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(5);

    EXPECT_FALSE(setObject.doesContain(4));
    EXPECT_TRUE(setObject.doesContain(5));
}

template <typename Set>
void testGetSizeWhenEmptyWithUnsignedIntAndChar() {
    Set setObject;

    EXPECT_EQ(0, setObject.getSize());
}

template <typename Set>
void testGetSizeWhenNotEmptyWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(7);
    setObject.put(5);
    setObject.put(6);

    EXPECT_EQ(3, setObject.getSize());
}

template <typename Set>
void testGetWithUnsignedIntAndChar() {
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7);
    setObject.put(5);
    setObject.put(6);

    EXPECT_EQ((Keys{5, 6, 7}), setObject.getKeys());
}

template <typename Set>
void testGetRankWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(8);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);

    EXPECT_EQ(0, setObject.getRank(3));
    EXPECT_EQ(0, setObject.getRank(4));
    EXPECT_EQ(1, setObject.getRank(5));
    EXPECT_EQ(2, setObject.getRank(6));
    EXPECT_EQ(2, setObject.getRank(7));
    EXPECT_EQ(3, setObject.getRank(8));
    EXPECT_EQ(4, setObject.getRank(9));
}

template <typename Set>
void testGetMinimumWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(8);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);

    EXPECT_EQ(4, setObject.getMinimum());
}

template <typename Set>
void testGetMaximumWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(8);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);

    EXPECT_EQ(8, setObject.getMaximum());
}

template <typename Set>
void testSelectAtWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(8);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);

    EXPECT_EQ(4, setObject.selectAt(0));
    EXPECT_EQ(5, setObject.selectAt(1));
    EXPECT_EQ(7, setObject.selectAt(2));
    EXPECT_EQ(8, setObject.selectAt(3));
}

template <typename Set>
void testGetFloorWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(8);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);

    EXPECT_EQ(0, setObject.getFloor(3));
    EXPECT_EQ(4, setObject.getFloor(4));
    EXPECT_EQ(5, setObject.getFloor(5));
    EXPECT_EQ(5, setObject.getFloor(6));
    EXPECT_EQ(7, setObject.getFloor(7));
    EXPECT_EQ(8, setObject.getFloor(8));
    EXPECT_EQ(8, setObject.getFloor(9));
}

template <typename Set>
void testGetCeilingWithUnsignedIntAndChar() {
    Set setObject;
    setObject.put(8);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);

    EXPECT_EQ(4, setObject.getCeiling(3));
    EXPECT_EQ(4, setObject.getCeiling(4));
    EXPECT_EQ(5, setObject.getCeiling(5));
    EXPECT_EQ(7, setObject.getCeiling(6));
    EXPECT_EQ(7, setObject.getCeiling(7));
    EXPECT_EQ(8, setObject.getCeiling(8));
    EXPECT_EQ(0, setObject.getCeiling(9));
}

template <typename Set>
void testPutWithUnsignedIntAndChar() {
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7);
    setObject.put(5);
    setObject.put(6);

    EXPECT_EQ((Keys{5, 6, 7}), setObject.getKeys());
}

template <typename Set>
void testDeleteBasedOnKeyWithUnsignedIntAndChar() {
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7);
    setObject.put(5);
    setObject.put(6);

    setObject.deleteBasedOnKey(5);
    EXPECT_EQ((Keys{6, 7}), setObject.getKeys());

    setObject.deleteBasedOnKey(6);
    EXPECT_EQ((Keys{7}), setObject.getKeys());

    setObject.deleteBasedOnKey(7);
    EXPECT_TRUE(setObject.getKeys().empty());
}

template <typename Set>
void testDeleteMinimumWithUnsignedIntAndChar() {
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7);
    setObject.put(5);
    setObject.put(6);

    setObject.deleteMinimum();
    EXPECT_EQ((Keys{6, 7}), setObject.getKeys());
}

template <typename Set>
void testDeleteMaximumWithUnsignedIntAndChar() {
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(7);
    setObject.put(5);
    setObject.put(6);

    setObject.deleteMaximum();
    EXPECT_EQ((Keys{5, 6}), setObject.getKeys());
}

template <typename Set>
void testGetKeysWithUnsignedIntAndChar() {
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(8);
    setObject.put(9);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);
    setObject.put(3);

    Keys keysToVerify(setObject.getKeys());

    Keys expectedKeys{3, 4, 5, 7, 8, 9};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename Set>
void testGetKeysInRangeInclusiveWithUnsignedIntAndChar() {
    using Keys = typename Set::Keys;
    Set setObject;
    setObject.put(8);
    setObject.put(9);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);
    setObject.put(3);

    Keys keysToVerify(setObject.getKeysInRangeInclusive(5, 8));

    Keys expectedKeys{5, 7, 8};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}  // namespace CommonTestsWithSet

}  // namespace algorithm

}  // namespace alba
