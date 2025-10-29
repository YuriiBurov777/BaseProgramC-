
#include <iostream>
#include <vector>
#include <set>
#include <list>

template<typename T>
const void  Print(T cont) {
    for (auto type : cont) {
        std::cout << type << "  ";
    }
}


int main()
{
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    Print(test_set);
    std::cout << std::endl;

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    Print(test_set);
    std::cout << std::endl;

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    Print(test_set);
    std::cout << std::endl;

    std::set<int> test_set2 = { 1, 2, 3, 4 };
    Print(test_set2);
    std::cout << std::endl;

    std::list<double> test_list2 = { 1.1, 2.2, 3.3, 4.4 };
    Print(test_list2);
    std::cout << std::endl;
    
    return 0;
}

