#include <Common/Debug/AlbaFundamentalOperationsCounter.hpp>

#include <gtest/gtest.h>

#include <memory>

using namespace std;

namespace alba
{

namespace
{

class SampleClass
{
public:
    SampleClass()
        : m_dataPointer()
    {}
    SampleClass(int const data)
        : m_dataPointer(make_unique<int>(data))
    {}
    SampleClass(SampleClass const& parameter)
        : m_dataPointer(make_unique<int>(*parameter.m_dataPointer))
    {}
    SampleClass& operator=(SampleClass const& parameter)
    {
        m_dataPointer = make_unique<int>(*parameter.m_dataPointer);
        return *this;
    }
    SampleClass(SampleClass && parameter)
        : m_dataPointer(move(parameter.m_dataPointer))
    {}
    SampleClass& operator=(SampleClass && parameter)
    {
        m_dataPointer = move(parameter.m_dataPointer);
        return *this;
    }
    unique_ptr<int> m_dataPointer;
};

using ClassForTest = AlbaFundamentalOperationsCounter<SampleClass>;
using CountsForTest = AlbaFundamentalOperationsCounts<SampleClass>;

ClassForTest getRValue()
{
    ClassForTest namedReturnedObject(5678);
    return namedReturnedObject;
}

}

TEST(AlbaFundamentalOperationsCounterTest, UserConstructionIsCounted)
{
    CountsForTest::getInstance().resetCounts();

    ClassForTest object(1234);

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForTest::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, DefaultConstructionIsCounted)
{
    CountsForTest::getInstance().resetCounts();

    ClassForTest object;

    EXPECT_EQ("userConstructionCount: 0 defaultConstructionCount: 1 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForTest::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, DestructionIsCounted)
{
    CountsForTest::getInstance().resetCounts();

    {
        ClassForTest object;
    }

    EXPECT_EQ("userConstructionCount: 0 defaultConstructionCount: 1 destructionCount: 1 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForTest::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, CopyConstructionIsCounted)
{
    ClassForTest originalObject(1234);
    CountsForTest::getInstance().resetCounts();

    ClassForTest object(originalObject);

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForTest::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, CopyAssignmentIsCounted)
{
    ClassForTest originalObject(1234);
    ClassForTest object(5678);
    CountsForTest::getInstance().resetCounts();

    object = originalObject;

    EXPECT_EQ("userConstructionCount: 0 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 1 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForTest::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, MoveConstructionIsCounted)
{
    CountsForTest::getInstance().resetCounts();

    ClassForTest object(getRValue());

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForTest::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, MoveAssignmentIsCounted)
{
    ClassForTest originalObject(1234);
    ClassForTest object(5678);
    CountsForTest::getInstance().resetCounts();

    object = getRValue();

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 1 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 1",
              CountsForTest::getInstance().getReport());
}

TEST(AlbaFundamentalOperationsCounterTest, ObjectIsConstructedOnceDueToRvo)
{
    CountsForTest::getInstance().resetCounts();

    ClassForTest object(getRValue());

    EXPECT_EQ("userConstructionCount: 1 defaultConstructionCount: 0 destructionCount: 0 copyConstructionCount: 0 copyAssignmentCount: 0 moveConstructionCount: 0 moveAssignmentCount: 0",
              CountsForTest::getInstance().getReport());
}

}
