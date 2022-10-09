#pragma once

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithTries
{

template <typename Trie>
void testIsEmptyWhenEmptyWithUnsignedInt()
{
    Trie trie;

    EXPECT_TRUE(trie.isEmpty());
}

template <typename Trie>
void testIsEmptyWhenNotEmptyWithUnsignedInt()
{
    Trie trie;
    trie.put("she", 0U);

    EXPECT_FALSE(trie.isEmpty());
}

template <typename Trie>
void testDoesContainWithUnsignedInt()
{
    Trie trie;
    trie.put("she", 0U);

    EXPECT_FALSE(trie.doesContain("he"));
    EXPECT_TRUE(trie.doesContain("she"));
}

template <typename Trie>
void testGetSizeWhenEmptyWithUnsignedInt()
{
    Trie trie;

    EXPECT_EQ(0U, trie.getSize());
}

template <typename Trie>
void testGetSizeWhenNotEmptyWithUnsignedInt()
{
    Trie trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    EXPECT_EQ(3U, trie.getSize());
}

template <typename Trie>
void testGetWithUnsignedInt()
{
    Trie trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    EXPECT_EQ(0U, trie.get("she"));
    EXPECT_EQ(1U, trie.get("sells"));
    EXPECT_EQ(2U, trie.get("sea"));
    EXPECT_EQ(0U, trie.get("he"));
}

template <typename Trie>
void testGetLongestPrefixOfWithUnsignedInt()
{
    Trie trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);
    trie.put("shells", 3U);
    trie.put("by", 4U);
    trie.put("the", 5U);
    trie.put("sea", 6U);
    trie.put("shore", 7U);
    trie.put("s", 8U);

    EXPECT_EQ("shells", trie.getLongestPrefixOf("shellscore"));
    EXPECT_EQ("shells", trie.getLongestPrefixOf("shells"));
    EXPECT_EQ("", trie.getLongestPrefixOf("this"));
    EXPECT_EQ("", trie.getLongestPrefixOf("this string does not exist"));
}

template <typename Trie>
void testPutWithUnsignedInt()
{
    Trie trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    ASSERT_EQ(3U, trie.getSize());
    EXPECT_EQ(0U, trie.get("she"));
    EXPECT_EQ(1U, trie.get("sells"));
    EXPECT_EQ(2U, trie.get("sea"));
}

template <typename Trie>
void testDeleteBasedOnKeyWithUnsignedInt()
{
    Trie trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    trie.deleteBasedOnKey("she");
    ASSERT_EQ(2U, trie.getSize());
    EXPECT_EQ(1U, trie.get("sells"));
    EXPECT_EQ(2U, trie.get("sea"));

    trie.deleteBasedOnKey("sells");
    ASSERT_EQ(1U, trie.getSize());
    EXPECT_EQ(2U, trie.get("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_TRUE(trie.isEmpty());
}

template <typename Trie>
void testGetKeysWithUnsignedInt()
{
    using Keys = typename Trie::Keys;
    Trie trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);
    trie.put("shells", 3U);
    trie.put("by", 4U);
    trie.put("the", 5U);
    trie.put("sea", 6U);
    trie.put("shore", 7U);
    trie.put("s", 8U);

    Keys keysToVerify(trie.getKeys());

    Keys expectedKeys{"by", "s", "sea", "sells", "she", "shells", "shore", "the"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename Trie>
void testGetAllKeysWithPrefixWithUnsignedInt()
{
    using Keys = typename Trie::Keys;
    Trie trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);
    trie.put("shells", 3U);
    trie.put("by", 4U);
    trie.put("the", 5U);
    trie.put("sea", 6U);
    trie.put("shore", 7U);
    trie.put("s", 8U);

    Keys keysToVerify(trie.getAllKeysWithPrefix("s"));

    Keys expectedKeys{"s", "sea", "sells", "she", "shells", "shore"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename Trie>
void testGetAllKeysThatMatchWithUnsignedInt()
{
    using Keys = typename Trie::Keys;
    Trie trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);
    trie.put("shells", 3U);
    trie.put("by", 4U);
    trie.put("the", 5U);
    trie.put("sea", 6U);
    trie.put("shore", 7U);
    trie.put("s", 8U);

    Keys keysToVerify(trie.getAllKeysThatMatch("s.."));

    Keys expectedKeys{"sea", "she"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename Trie>
void testExample1WithUnsignedInt()
{
    Trie trie;
    trie.put("CANAL", 2251U);
    trie.put("CANDY", 48430U);
    trie.put("THE", 625U);
    trie.put("THERE", 354468U);

    ASSERT_EQ(4U, trie.getSize());
    EXPECT_EQ(2251U, trie.get("CANAL"));
    EXPECT_EQ(48430U, trie.get("CANDY"));
    EXPECT_EQ(625U, trie.get("THE"));
    EXPECT_EQ(354468U, trie.get("THERE"));

    trie.deleteBasedOnKey("CANAL");
    trie.deleteBasedOnKey("CANDY");
    trie.deleteBasedOnKey("THE");
    trie.deleteBasedOnKey("THERE");

    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0U, trie.get("CANAL"));
    EXPECT_EQ(0U, trie.get("CANDY"));
    EXPECT_EQ(0U, trie.get("THE"));
    EXPECT_EQ(0U, trie.get("THERE"));
}

}

}

}