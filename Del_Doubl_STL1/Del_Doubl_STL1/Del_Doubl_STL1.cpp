
#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>

//Создаем вектор и заполняем
std::vector<int> CreateVec() {
    int a{ 0 };
    int size{ 0 };
    std::vector<int> vec;
    do
    {
        std::cout << "Введите положительное число количества элементов" << std::endl;
        std::cin >> size;
        if (size > 0) { 
            std::cout << "Введите число" << std::endl;
            std::cout << "IN" << std::endl;
            break; }
        else {
            std::cout << "Неверно введено число" << std::endl;
            Sleep(2000);
            system("CLS");
        }
    } while (true);

    do
    {
        std::cin >> a;
        vec.push_back(a);
       // std::cout << a << std::endl;
    } while (vec.size() < size);
    return vec;
}
// Создаем SET для отсеивания повторов
void CopyVecToSet(const std::vector<int> vec, std::unordered_set <int>& set) {
    
    for (int num : vec) {
        set.insert(num);
    }
    vec.~vector();
}
//Копируем из SET в вектор без повторов
std::vector<int> CopySetToVec( const std::unordered_set <int> set) {
   
    std::vector<int> vec;
    for (int num : set) {
        vec.push_back(num);
    }
    return vec;
}
//Сортируем вектор
void SortVec(std::vector<int>& vec) {
    
    sort (vec.begin(), vec.end(),
         [](const int a, const int b) {
             return a > b;
         });
}
//Печать результата
void Print(std::vector<int>& vec) {
    std::cout << "\t" << std::endl;
    std::cout << "Out:" << std::endl;
    for (auto num : vec)
    {
        std::cout << num << std::endl;
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Создаем вектор для хранения чисел
    auto vec = CreateVec();

    // Создаем SET для отсеивания повторов
    std::unordered_set <int> set_;
    CopyVecToSet(vec, set_);
    
    //Копируем из SET в вектор без повторов
    vec = CopySetToVec(set_);

    //Сортируем вектор
    SortVec(vec);

    //Печать результата
    Print(vec);
}

