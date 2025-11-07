#include <gtest/gtest.h>
#include "headers/Multimap.hpp"

// ================================================
// 01. INSERT TESTS
// ================================================

TEST(MultimapTest, InsertMultipleSameKeys)
{
    Multimap<int, std::string> mmap;
    mmap.insert({1, "A"});
    mmap.insert({1, "B"});
    mmap.insert({2, "C"});

    EXPECT_EQ(mmap.count(1), 2);
    EXPECT_EQ(mmap.count(2), 1);
}

TEST(MultimapTest, InsertRange)
{
    std::vector<std::pair<int, std::string>> data = {{1, "A"}, {2, "B"}, {1, "C"}};
    Multimap<int, std::string> mmap;
    mmap.insert(data.begin(), data.end());

    EXPECT_EQ(mmap.count(1), 2);
    EXPECT_EQ(mmap.count(2), 1);
}

// ================================================
// 02. ERASE TESTS
// ================================================

TEST(MultimapTest, EraseByKey)
{
    Multimap<int, std::string> mmap;
    mmap.insert({1, "X"});
    mmap.insert({1, "Y"});
    mmap.insert({2, "Z"});

    size_t erased = mmap.erase(1);
    EXPECT_EQ(erased, 2);
    EXPECT_EQ(mmap.count(1), 0);
    EXPECT_EQ(mmap.count(2), 1);
}

// ================================================
// 03. FIND / EQUAL_RANGE TESTS
// ================================================

TEST(MultimapTest, FindReturnsFirstOccurrence)
{
    Multimap<int, std::string> mmap;
    mmap.insert({1, "A"});
    mmap.insert({1, "B"});
    mmap.insert({2, "C"});

    auto it = mmap.find(1);
    ASSERT_NE(it, mmap.end());
    EXPECT_EQ(it->second, "A");  // առաջին հանդիպածն է
}

TEST(MultimapTest, EqualRangeGivesAllSameKeys)
{
    Multimap<int, std::string> mmap;
    mmap.insert({1, "A"});
    mmap.insert({1, "B"});
    mmap.insert({1, "C"});
    mmap.insert({2, "X"});

    auto range = mmap.equal_range(1);
    int count = 0;
    for (auto it = range.first; it != range.second; ++it)
        count++;

    EXPECT_EQ(count, 3);
}

// ================================================
// 04. COUNT TESTS
// ================================================

TEST(MultimapTest, CountReturnsCorrectNumber)
{
    Multimap<int, char> mmap;
    mmap.insert({1, 'a'});
    mmap.insert({1, 'b'});
    mmap.insert({2, 'c'});

    EXPECT_EQ(mmap.count(1), 2);
    EXPECT_EQ(mmap.count(2), 1);
    EXPECT_EQ(mmap.count(3), 0);
}

// ================================================
// 05. EMPTY / SIZE TESTS
// ================================================

TEST(MultimapTest, EmptyAndSizeWorkCorrectly)
{
    Multimap<int, int> mmap;
    EXPECT_TRUE(mmap.empty());
    EXPECT_EQ(mmap.size(), 0u);

    mmap.insert({5, 10});
    EXPECT_FALSE(mmap.empty());
    EXPECT_EQ(mmap.size(), 1u);

    mmap.insert({5, 11});
    EXPECT_EQ(mmap.size(), 2u);
}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

