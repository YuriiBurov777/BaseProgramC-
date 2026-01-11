// Multithreading_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>

// Функция, которую выполняет каждый поток
void sum(const std::vector<int>& a, const std::vector<int>& b,
    std::vector<int>& result, int start, int end) {
    for (int i = start; i < end; i++) {
        result[i] = a[i] + b[i];
    }
}
// Анализ результата
void analyze(double times[][5]) {
    std::cout << "\n Анализ \n";

    for (int s = 0; s < 4; s++) {
        int best = 0;
        for (int t = 1; t < 5; t++) {
            if (times[s][t] < times[s][best]) {
                best = t;
            }
        }

        int threads[] = { 1, 2, 4, 8, 16 };
        std::cout << "Размер " << s + 1 << ": лучше "
            << threads[best] << " потоков\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Показываем сколько ядер у процессора
    std::cout << "Ядер у процессора: " << std::thread::hardware_concurrency() << std::endl;

    // Разные размеры массивов
    int sizes[] = { 1000, 10000, 100000, 1000000 };
    // Разное число потоков
    int threads[] = { 1, 2, 4, 8, 16 };

    // Таблица для результатов
    double times[4][5] = { 0 };

    // Тестируем каждый размер
    for (int s = 0; s < 4; s++) {
        int n = sizes[s];

        // Создаем массивы
        std::vector<int> a(n), b(n), result(n);

        // Заполняем числами
        for (int i = 0; i < n; i++) {
            a[i] = i;
            b[i] = i * 2;
        }

        // Тест с разным числом потоков
        for (int t = 0; t < 5; t++) {
            int num_threads = threads[t];

            // Делим на потоки
            int part = n / num_threads;
            std::thread* th = new std::thread[num_threads];

            // Засекаем время
            auto start = std::chrono::high_resolution_clock::now();

            // Запускаем потоки
            for (int i = 0; i < num_threads; i++) {
                int start_idx = i * part;
                int end_idx = (i == num_threads - 1) ? n : start_idx + part;
                th[i] = std::thread(sum, std::ref(a), std::ref(b),
                    std::ref(result), start_idx, end_idx);
            }

            // Ждем все потоки
            for (int i = 0; i < num_threads; i++) {
                th[i].join();
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;

            times[s][t] = diff.count();

            delete[] th;
        }
    }

    // Выводим таблицу
    std::cout << "\nТаблица времени (секунды):\n";
    std::cout << "Размер\\Потоки\t\t1\t\t2\t\t4\t\t8\t\t16\n";
    std::cout << "                                        \n";

    for (int s = 0; s < 4; s++) {
        std::cout << sizes[s] << "\t\t";
        for (int t = 0; t < 5; t++) {
            std::cout << times[s][t] << "\t";
        }
        std::cout << std::endl;
    }
    analyze(times);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
