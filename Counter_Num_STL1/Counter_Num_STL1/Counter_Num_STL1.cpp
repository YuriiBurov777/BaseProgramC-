#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <Windows.h>

void CountChar(const std::string& Word, std::map<char, int>& CountChar) {
    for (char checkChar : Word) {
        CountChar[checkChar]++;       //Проверяет в мар наличие символа. Если символа нет создаем. Если есть добавляем +1
    }

}

void sortVec (std::vector<std::pair<char, int>>& vec) {
    sort(vec.begin(), vec.end(),
        [](const std::pair<char, int>& obj1, const std::pair<char, int>& obj2) {
            return obj1.second > obj2.second;
        });
}
void Print(const std::vector<std::pair<char, int>> vec) {
    std::cout << "Результат:" << std::endl;
    for (const auto& pair : vec) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string Text;

    // Ввод текста пользователем
    std::cout << "Введите текст: ";
    std::getline(std::cin, Text);

    // Создаем map для подсчета частоты символов
    std::map<char, int> charMap;

    // Подсчитываем частоту каждого символа
    CountChar(Text, charMap);

    // Преобразуем map в vector пар для сортировки
    std::vector<std::pair<char, int>> charVector(charMap.begin(), charMap.end());

    // Сортируем по убыванию частоты
    sortVec(charVector);

    // Выводим результат
    Print(charVector);

    return 0;
}