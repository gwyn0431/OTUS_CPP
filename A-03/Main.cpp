#include <iostream>
#include "ReservingAllocator/ReservingAllocator.h"
#include "ForwardList/ForwardList.h"
#include <map>

const int GTen = 10;

int Factorial(int Number)
{
    if(Number < 0)
    {
        return 0;
    } 
        
    if (Number == 0)
    {
        return 1;
    }
        
    return Number * Factorial(Number - 1);
}

void MapTests()
{
    std::map<int, int> DefaultAllocMap;
    for (int Index = 0; Index < GTen; ++Index) 
    {
        DefaultAllocMap.emplace(Index, Factorial(Index));
    }

    std::map<int, int, std::less<int>, ReservingAllocator<std::pair<const int, int>, GTen>> CustomAllocMap;
    for (int Index = 0; Index < GTen; ++Index) 
    {
        CustomAllocMap.emplace(Index, Factorial(Index));
    }

    for (auto Element : CustomAllocMap)
    {
        std::cout << Element.first << " " << Element.second << std::endl;
    }
}

void ForwardListTests()
{
    ForwardList<int> DefaultAllocList;
    for (int Index = 0; Index < GTen; ++Index) 
    {
        DefaultAllocList.Push(Index);
    }

    ForwardList<int, ReservingAllocator<int, GTen>> CustomAllocList;
    for (int Index = 0; Index < GTen; ++Index) 
    {
        CustomAllocList.Push(Index);
    }

    try
    {
        for (auto Element : CustomAllocList)
        {
            std::cout << Element << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }   
}

int main()
{
    MapTests();
    ForwardListTests();

    return 0;
}