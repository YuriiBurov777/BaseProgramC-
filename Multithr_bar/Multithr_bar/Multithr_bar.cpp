#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <random>
#include <iomanip>
#include <windows.h>

std::mutex cout_mutex;

void worker(int thread_num, int work_length, int line_offset) {
    auto start = std::chrono::steady_clock::now();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sleep_time(50, 200);

    for (int i = 0; i <= work_length; i++) {
        {
            std::lock_guard<std::mutex> lock(cout_mutex);

            // Перемещаем курсор к строке своего потока
            // Каждый поток имеет свою фиксированную строку
            std::cout << "\033[" << (line_offset + thread_num) << ";1H";

            // Очищаем строку
            std::cout << "\033[K";

            // Выводим информацию о потоке
            std::cout << std::setw(2) << thread_num
                << " | ID:" << std::setw(12) << std::this_thread::get_id()
                << " | [";

            // Прогресс-бар (40 символов)
            int bar_width = 40;
            int progress = (i * bar_width) / work_length;

            // Рисуем заполненную часть
            for (int j = 0; j < progress; j++) {
                std::cout << "?";
            }

            // Рисуем оставшуюся часть
            for (int j = progress + 1; j < bar_width; j++) {
                std::cout << " ";
            }

            std::cout << "] " << std::setw(3) << (i * 100) / work_length << "%";

            // Возвращаем курсор вниз, чтобы не мешать
            std::cout << "\033[" << (line_offset + 10) << ";1H";
            std::cout.flush();
        }

        // Имитация работы (кроме последней итерации)
        if (i < work_length) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time(gen)));
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        // Переходим к строке потока для вывода времени
        std::cout << "\033[" << (line_offset + thread_num) << ";55H";
        std::cout << "Время: " << std::setw(5) << duration.count() << " мс";
        std::cout << "\033[" << (line_offset + 10) << ";1H";
        std::cout.flush();
    }
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int num_threads = 5;      // Количество потоков
    const int work_length = 100;    // Длина расчёта

    std::vector<std::thread> threads;

    // Очищаем экран и выводим заголовок
    std::cout << "\033[2J\033[1;1H";  // Очистка экрана и курсор в начало
    std::cout << "Многопоточный расчёт с прогресс-барами\n";
    std::cout << "---------------------------------------\n\n";

    // Оставляем пустые строки под прогресс-бары
    for (int i = 0; i < num_threads + 2; i++) {
        std::cout << std::endl;
    }

    // Выводим подпись внизу
    std::cout << "\n-------------------------------------\n";
    std::cout << "Расчёт выполняется...\n";

    // Запоминаем позицию начала прогресс-баров (строка 5)
    int line_offset = 5;

    // Создаём потоки
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(worker, i + 1, work_length, line_offset);
    }

    // Ждём завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    // Перемещаемся вниз для вывода итогового сообщения
    std::cout << "\033[" << (line_offset + num_threads + 5) << ";1H";
    std::cout << "\nВсе потоки завершены!\n";

    return 0;
}