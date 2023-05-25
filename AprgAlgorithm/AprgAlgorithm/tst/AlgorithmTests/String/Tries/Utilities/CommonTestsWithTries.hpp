#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace CommonTestsWithTries {

template <typename Trie>
void testIsEmptyWhenEmptyWithInt() {
    Trie trie;

    EXPECT_TRUE(trie.isEmpty());
}

template <typename Trie>
void testIsEmptyWhenNotEmptyWithInt() {
    Trie trie;
    trie.put("she", 0);

    EXPECT_FALSE(trie.isEmpty());
}

template <typename Trie>
void testDoesContainWithInt() {
    Trie trie;
    trie.put("she", 0);

    EXPECT_FALSE(trie.doesContain("he"));
    EXPECT_TRUE(trie.doesContain("she"));
}

template <typename Trie>
void testGetSizeWhenEmptyWithInt() {
    Trie trie;

    EXPECT_EQ(0, trie.getSize());
}

template <typename Trie>
void testGetSizeWhenNotEmptyWithInt() {
    Trie trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    EXPECT_EQ(3, trie.getSize());
}

template <typename Trie>
void testGetWithInt() {
    Trie trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    EXPECT_EQ(0, trie.get("she"));
    EXPECT_EQ(1, trie.get("sells"));
    EXPECT_EQ(2, trie.get("sea"));
    EXPECT_EQ(0, trie.get("he"));
}

template <typename Trie>
void testGetLongestPrefixOfWithInt() {
    Trie trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);
    trie.put("shells", 3);
    trie.put("by", 4);
    trie.put("the", 5);
    trie.put("sea", 6);
    trie.put("shore", 7);
    trie.put("s", 8);

    EXPECT_EQ("shells", trie.getLongestPrefixOf("shellscore"));
    EXPECT_EQ("shells", trie.getLongestPrefixOf("shells"));
    EXPECT_EQ("", trie.getLongestPrefixOf("this"));
    EXPECT_EQ("", trie.getLongestPrefixOf("this string does not exist"));
}

template <typename Trie>
void testPutWithInt() {
    Trie trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    ASSERT_EQ(3, trie.getSize());
    EXPECT_EQ(0, trie.get("she"));
    EXPECT_EQ(1, trie.get("sells"));
    EXPECT_EQ(2, trie.get("sea"));
}

template <typename Trie>
void testDeleteBasedOnKeyWithInt() {
    Trie trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    trie.deleteBasedOnKey("she");
    ASSERT_EQ(2, trie.getSize());
    EXPECT_EQ(1, trie.get("sells"));
    EXPECT_EQ(2, trie.get("sea"));

    trie.deleteBasedOnKey("sells");
    ASSERT_EQ(1, trie.getSize());
    EXPECT_EQ(2, trie.get("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_TRUE(trie.isEmpty());
}

template <typename Trie>
void testGetKeysWithInt() {
    using Keys = typename Trie::Keys;
    Trie trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);
    trie.put("shells", 3);
    trie.put("by", 4);
    trie.put("the", 5);
    trie.put("sea", 6);
    trie.put("shore", 7);
    trie.put("s", 8);

    Keys keysToVerify(trie.getKeys());

    Keys expectedKeys{"by", "s", "sea", "sells", "she", "shells", "shore", "the"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename Trie>
void testGetAllKeysWithPrefixWithInt() {
    using Keys = typename Trie::Keys;
    Trie trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);
    trie.put("shells", 3);
    trie.put("by", 4);
    trie.put("the", 5);
    trie.put("sea", 6);
    trie.put("shore", 7);
    trie.put("s", 8);

    Keys keysToVerify(trie.getAllKeysWithPrefix("s"));

    Keys expectedKeys{"s", "sea", "sells", "she", "shells", "shore"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename Trie>
void testGetAllKeysThatMatchWithInt() {
    using Keys = typename Trie::Keys;
    Trie trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);
    trie.put("shells", 3);
    trie.put("by", 4);
    trie.put("the", 5);
    trie.put("sea", 6);
    trie.put("shore", 7);
    trie.put("s", 8);

    Keys keysToVerify(trie.getAllKeysThatMatch("s.."));

    Keys expectedKeys{"sea", "she"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename Trie>
void testExample1WithInt() {
    Trie trie;
    trie.put("CANAL", 2251);
    trie.put("CANDY", 48430);
    trie.put("THE", 625);
    trie.put("THERE", 354468);

    ASSERT_EQ(4, trie.getSize());
    EXPECT_EQ(2251, trie.get("CANAL"));
    EXPECT_EQ(48430, trie.get("CANDY"));
    EXPECT_EQ(625, trie.get("THE"));
    EXPECT_EQ(354468, trie.get("THERE"));

    trie.deleteBasedOnKey("CANAL");
    trie.deleteBasedOnKey("CANDY");
    trie.deleteBasedOnKey("THE");
    trie.deleteBasedOnKey("THERE");

    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0, trie.get("CANAL"));
    EXPECT_EQ(0, trie.get("CANDY"));
    EXPECT_EQ(0, trie.get("THE"));
    EXPECT_EQ(0, trie.get("THERE"));
}

}  // namespace CommonTestsWithTries

}  // namespace algorithm

}  // namespace alba
