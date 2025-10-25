#include <iostream>
#include <vector>

template <typename T>
class T_Table {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    // Конструктор, получающий количество строк и столбцов
    T_Table(size_t numRows, size_t numCols)
        : rows(numRows), cols(numCols) {
          data.resize(rows);
            for (size_t i = 0; i < rows; ++i) {
                data[i].resize(cols);
            }
    }

    // Неконстантная версия оператора [] для доступа к строкам (Запись)
    std::vector<T>& operator[](size_t index) {
        return data[index];
    }

    // Константная версия оператора [] для доступа к строкам (Чтение)
    const std::vector<T>& operator[](size_t index) const {
        return data[index];
    }

    // Функция Size, возвращающая размер таблицы (пару: строки, столбцы)
    std::pair<size_t, size_t> Size() const {
        return { rows, cols };
    }
};


int main() {
    // Создание таблицы 2x3
    T_Table<int> test(2, 3);

    // Запись значения
    test[0][0] = 4;
    test[0][1] = 5;
    test[1][2] = 10;

    // Чтение значений
    std::cout << test[0][0] << std::endl; // выводит 4
    std::cout << test[0][1] << std::endl; // выводит 5
    std::cout << test[1][2] << std::endl; // выводит 10

    // Получение размера таблицы
    auto size = test.Size();
    std::cout << "Rows: " << size.first << ", Cols: " << size.second << std::endl;

    return 0;
}