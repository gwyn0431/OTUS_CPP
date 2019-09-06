#include "gtest/gtest.h"
#include "CustomAllocator.h"
#include "ForwardList/ForwardList.h"

TEST(CustomAllocatorTests, TestAllocByItself) 
{
    CustomAllocator<int, 1> IntAllocator;
    int* IntPtr = IntAllocator.allocate(1);
    IntAllocator.construct(IntPtr, 15);

    EXPECT_EQ(*IntPtr, 15);

    IntAllocator.destroy(IntPtr);
    IntAllocator.deallocate(IntPtr, 1);

    // second verification exists to check if allocator can validly allocate again, after deallocation
    IntPtr = IntAllocator.allocate(1);
    IntAllocator.construct(IntPtr, 10);

    EXPECT_EQ(*IntPtr, 10);
}

TEST(CustomAllocatorTests, TestAllocExpanding) 
{
    CustomAllocator<int, 1> IntAllocator;
    
    int* FirstIntPtr = IntAllocator.allocate(1);
    IntAllocator.construct(FirstIntPtr, 1);
    int* SecondIntPtr = IntAllocator.allocate(1);
    IntAllocator.construct(SecondIntPtr, 2);

    EXPECT_EQ(*FirstIntPtr, 1);
    EXPECT_EQ(*SecondIntPtr, 2);

    IntAllocator.destroy(FirstIntPtr);
    IntAllocator.deallocate(FirstIntPtr, 1);
    IntAllocator.destroy(SecondIntPtr);
    IntAllocator.deallocate(SecondIntPtr, 1);

    // second verification exists to check if expanded allocator can validly allocate again, after deallocation
    FirstIntPtr = IntAllocator.allocate(1);
    IntAllocator.construct(FirstIntPtr, 10);
    SecondIntPtr = IntAllocator.allocate(1);
    IntAllocator.construct(SecondIntPtr, 20);

    EXPECT_EQ(*FirstIntPtr, 10);
    EXPECT_EQ(*SecondIntPtr, 20);
}

// TEST(CustomAllocatorTests, TestAllocWithMap) 
// {
//     std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>, 5>> Map;

//     for (int Value = 0; Value < 5; ++Value)
//     {
//         Map.emplace(Value, Value);
//     }

//     int Value = 0;
//     for (auto Pair : Map)
//     {
//         EXPECT_EQ(Pair.second, Value++);
//     }
// }

// TEST(CustomAllocatorTests, TestAllocExpandingWithMap) 
// {
//     std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>, 1>> Map;

//     for (int Value = 0; Value < 5; ++Value)
//     {
//         Map.emplace(Value, Value);
//     }

//     int Value = 0;
//     for (auto Pair : Map)
//     {
//         EXPECT_EQ(Pair.second, Value++);
//     }
// }

TEST(CustomAllocatorTests, TestAllocWithMap) 
{
    std::map<int, int, std::less<int>, CustomAllocator<int, 1>> Map;
    Map.emplace(1, 1);

    EXPECT_EQ(Map.at(1), 1);
}

TEST(CustomAllocatorTests, TestAllocWithForwardList) 
{
    ForwardList<int, CustomAllocator<int, 1>> List;
    List.Push(1);

    EXPECT_EQ(*List.begin(), 1);
}

TEST(CustomAllocatorTests, TestAllocExpandingOld) 
{
    ForwardList<int, CustomAllocator<int, 1>> List;
    for (int Value = 0; Value < 5; ++Value)
    {
        List.Push(Value);
    }

    int Value = 0;
    for (ForwardIterator<int> Iter = List.begin(); Iter != List.end(); ++Iter)
    {
        EXPECT_EQ(*Iter, Value++);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}