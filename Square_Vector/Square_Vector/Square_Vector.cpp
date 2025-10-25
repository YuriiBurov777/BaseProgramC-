#include <iostream>
#include <vector>
#include <Windows.h>

// Для простых чисел
   template<typename T>
T square(T& value) {
    return value * value;
}

// Функция изменяет исходный вектор (возводит все элементы в квадрат)
  template<typename T>
void square_in_place(std::vector<T>& vec) {
    for (auto& element : vec) {
        element = square( element);  // изменяем оригинальные элементы
    }
}
// Создание числа

auto creat_value() {
    auto a{ 0 };
    do{

     std::cout << "Введите число." << std::endl;
     std::cin >> a;
   
     if (std::cin.fail()) {
         std::cout << "Ошибка! Введите число." << std::endl;
         std::cin.clear();
         std::cin.ignore(10000, '\n');
     }

     else {
         break;
     }
    } while (true);
    return a;
  }

// Создание вектора
  template <typename T>
std::vector<T> creat_Vector() {
    T a;
    unsigned int count{ 0 };
    std::vector <T> vec;

    do
    {
      std::cout << "Заполните массив. Введите число." << std::endl;
      std::cin >> a;

      if (std::cin.fail()) {
          std::cout << "Ошибка! Введите число." << std::endl;
          std::cin.clear();
          std::cin.ignore(10000, '\n');
      }

      else {
          vec.push_back(a);
          ++count;
      }
        
    } while (count<4);

    return vec;
  }

// Печать
void print() {
    auto a = creat_value();
    auto b = creat_Vector<int>();
    std::cout << "[IN]: " << a << std::endl;
    std::cout << "[OUT]: " << square(a) << std::endl;
    std::cout << "[IN]: "; for (int num : b) { std::cout << num << " ";}
    std::cout << std::endl;
    square_in_place(b);
    std::cout << "[OUT]: ";  for (int num : b) { std::cout << num <<" ";}
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    print();
    
 return 0;
}