#include "iostream"
#include "ProjectVersionManager.h"

int main(int, char**)
{
    UProjectVersionManager::PrintProjectVersion();
    std::cout << "Hello, World!" << std::endl;

    char WindowFreezer;
    std::cin >> WindowFreezer;

    return 0;
}