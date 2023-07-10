#include <Algorithm/String/Tries/TernarySearchTrieSubstringsSet.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using TrieForTest = TernarySearchTrieSubstringsSet;
}

TEST(TernarySearchTrieSubstringsSetTest, IsEmptyWorksWhenEmpty) {
    TrieForTest trie;

    EXPECT_TRUE(trie.isEmpty());
}

TEST(TernarySearchTrieSubstringsSetTest, IsEmptyWorksWhenNotEmpty) {
    TrieForTest trie;
    trie.put("she");

    EXPECT_FALSE(trie.isEmpty());
}

TEST(TernarySearchTrieSubstringsSetTest, DoesContainWorks) {
    TrieForTest trie;
    trie.put("she");

    EXPECT_FALSE(trie.doesContain("he"));
    EXPECT_TRUE(trie.doesContain("she"));
}

TEST(TernarySearchTrieSubstringsSetTest, GetSizeWorksWhenEmpty) {
    TrieForTest trie;

    EXPECT_EQ(0, trie.getSize());
}

TEST(TernarySearchTrieSubstringsSetTest, GetSizeWorksWhenNotEmpty) {
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");

    EXPECT_EQ(8, trie.getSize());
}

TEST(TernarySearchTrieSubstringsSetTest, GetLongestPrefixWorks) {
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");
    trie.put("shells");
    trie.put("by");
    trie.put("the");
    trie.put("sea");
    trie.put("shore");
    trie.put("s");

    EXPECT_EQ("shells", trie.getLongestPrefixOf("shellscore"));
    EXPECT_EQ("shells", trie.getLongestPrefixOf("shells"));
    EXPECT_EQ("th", trie.getLongestPrefixOf("this"));
    EXPECT_EQ("th", trie.getLongestPrefixOf("this string does not exist"));
}

TEST(TernarySearchTrieSubstringsSetTest, PutWorks) {
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");

    ASSERT_EQ(8, trie.getSize());
    EXPECT_TRUE(trie.doesContain("she"));
    EXPECT_TRUE(trie.doesContain("sells"));
    EXPECT_TRUE(trie.doesContain("sea"));
}

TEST(TernarySearchTrieSubstringsSetTest, DeleteBasedOnKeyWorks) {
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");

    trie.deleteBasedOnKey("she");
    ASSERT_EQ(6, trie.getSize());
    EXPECT_TRUE(trie.doesContain("sells"));
    EXPECT_TRUE(trie.doesContain("sea"));

    trie.deleteBasedOnKey("sells");
    ASSERT_EQ(3, trie.getSize());
    EXPECT_TRUE(trie.doesContain("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_TRUE(trie.isEmpty());
}

TEST(TernarySearchTrieSubstringsSetTest, GetKeysWorks) {
    using Strings = typename TrieForTest::Strings;
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");
    trie.put("shells");
    trie.put("by");
    trie.put("the");
    trie.put("sea");
    trie.put("shore");
    trie.put("s");

    Strings keysToVerify(trie.getKeys());

    Strings expectedKeys{"b",    "by",    "s",      "se",  "sea",  "sel",   "sell", "sells", "sh", "she",
                      "shel", "shell", "shells", "sho", "shor", "shore", "t",    "th",    "the"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(TernarySearchTrieSubstringsSetTest, GetAllKeysWithPrefixWorks) {
    using Strings = typename TrieForTest::Strings;
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");
    trie.put("shells");
    trie.put("by");
    trie.put("the");
    trie.put("sea");
    trie.put("shore");
    trie.put("s");

    Strings keysToVerify(trie.getAllKeysWithPrefix("s"));

    Strings expectedKeys{"s",   "se",   "sea",   "sel",    "sell", "sells", "sh",
                      "she", "shel", "shell", "shells", "sho",  "shor",  "shore"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(TernarySearchTrieSubstringsSetTest, GetAllKeysThatMatchWorks) {
    using Strings = typename TrieForTest::Strings;
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");
    trie.put("shells");
    trie.put("by");
    trie.put("the");
    trie.put("sea");
    trie.put("shore");
    trie.put("s");

    Strings keysToVerify(trie.getAllKeysThatMatch("s.."));

    Strings expectedKeys{"sea", "sel", "she"};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(TernarySearchTrieSubstringsSetTest, Example1Works) {
    TrieForTest trie;
    trie.put("CANAL");
    trie.put("CANDY");
    trie.put("THE");
    trie.put("THERE");

    ASSERT_EQ(12, trie.getSize());
    EXPECT_TRUE(trie.doesContain("CANAL"));
    EXPECT_TRUE(trie.doesContain("CANDY"));
    EXPECT_TRUE(trie.doesContain("THE"));
    EXPECT_TRUE(trie.doesContain("THERE"));

    trie.deleteBasedOnKey("CANAL");
    trie.deleteBasedOnKey("CANDY");
    trie.deleteBasedOnKey("THE");
    trie.deleteBasedOnKey("THERE");

    EXPECT_TRUE(trie.isEmpty());
    EXPECT_FALSE(trie.doesContain("CANAL"));
    EXPECT_FALSE(trie.doesContain("CANDY"));
    EXPECT_FALSE(trie.doesContain("THE"));
    EXPECT_FALSE(trie.doesContain("THERE"));
}

TEST(TernarySearchTrieSubstringsSetTest, GetNumberOfNodesWorksWhenEmpty) {
    TrieForTest trie;

    EXPECT_EQ(0, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieSubstringsSetTest, GetNumberOfNodesWorksWhenNotEmpty) {
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");

    EXPECT_EQ(8, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieSubstringsSetTest, PutWorksWithNumberOfNodes) {
    TrieForTest trie;

    trie.put("she");
    trie.put("sells");
    trie.put("sea");

    EXPECT_EQ(8, trie.getSize());
    EXPECT_EQ(8, trie.getNumberOfNodes());
    EXPECT_TRUE(trie.doesContain("she"));
    EXPECT_TRUE(trie.doesContain("sells"));
    EXPECT_TRUE(trie.doesContain("sea"));
}

TEST(TernarySearchTrieSubstringsSetTest, PutWhenEmptyStringHasNoEffect) {
    TrieForTest trie;

    trie.put("");

    EXPECT_EQ(0, trie.getSize());
    EXPECT_EQ(0, trie.getNumberOfNodes());
    EXPECT_FALSE(trie.doesContain(""));
}

TEST(TernarySearchTrieSubstringsSetTest, DeleteBasedOnKeyWorksWithNumberOfNodes) {
    TrieForTest trie;
    trie.put("she");
    trie.put("sells");
    trie.put("sea");

    trie.deleteBasedOnKey("she");
    EXPECT_EQ(6, trie.getSize());
    EXPECT_EQ(6, trie.getNumberOfNodes());
    EXPECT_TRUE(trie.doesContain("sells"));
    EXPECT_TRUE(trie.doesContain("sea"));

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ(3, trie.getSize());
    EXPECT_EQ(3, trie.getNumberOfNodes());
    EXPECT_TRUE(trie.doesContain("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieSubstringsSetTest, DeleteBasedOnKeyWhenEmptyStringHasNoEffect) {
    TrieForTest trie;
    trie.put("");

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0, trie.getNumberOfNodes());

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0, trie.getNumberOfNodes());
}

}  // namespace algorithm

}  // namespace alba
