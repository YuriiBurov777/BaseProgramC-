#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <chrono>
#include <atomic>
#include <windows.h>
#include "safe_queue.h"
#include "thread_pool.h"


// Функции для теста
void test_1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Номер1 "
        << std::this_thread::get_id() << std::endl;
}

void test_2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Номер2 "
        << std::this_thread::get_id() << std::endl;
}

void test_3() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Номер3 "
        << std::this_thread::get_id() << std::endl;
}


// Функция с исключением тест
void risky_function() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    throw std::runtime_error("Это тестовое исключение из risky_function");
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        std::cout << "--- Пул потоков ---" << std::endl;
        std::cout << "Количество доступных потоков: "
            << std::thread::hardware_concurrency() << std::endl;

        // Создаем пул потоков
        thread_pool pool;

        // Тест 1: Добавление простых задач
        std::cout << "\nТест 1: submit не возвращает результат" << std::endl;
        pool.submit(test_1);
        pool.submit(test_2);
        pool.submit(test_3);

        // Ждем завершения первых задач
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Тест 2: Добавление задач с возвращаемым значением
        std::cout << "\nТест 2: submit возвращает результат" << std::endl;
        auto future1 = pool.submit<int>([]() {return 10 + 20;});
        auto future2 = pool.submit<double>([]() {return 10.5 + 20.1;});
              
        // Получаем результаты
        std::cout << "Результат 1: " << future1.get() << std::endl;
        std::cout << "Результат 2: " << future2.get() << std::endl;
      
        // Тест 3: Обработка исключений
        std::cout << "\nТест 3: Исключение" << std::endl;
        try {
            pool.submit(risky_function);
            // Даем время на выполнение
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        catch (const std::exception& e) {
            std::cerr  << e.what() << std::endl;
        }

        // Тест 4: Периодическое добавление задач
        std::cout << "\nТест 4: Периодическая отправка заданий" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << "\nДобавление 2-х задач(итерация " << i + 1 << ")" << std::endl;

            // Добавляем 2 задачи одновременно
            pool.submit([i]() {
                std::cout << "Задача 1-" << i << " из потока "
                    << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                });

            pool.submit([i]() {
                std::cout << "Задача 2-" << i << " из потока "
                    << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                });

            // Ждем перед добавлением следующих задач
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // Выводим статистику
            std::cout << "Активные задачи: " << pool.get_active_tasks()
                << ", Задачи в очереди: " << pool.get_queued_tasks() << std::endl;
        }

        // Ждем завершения всех задач
        std::cout << "\nОжидание завершения всех задач..." << std::endl;
        pool.wait_all();

        std::cout << "\nВсе задания выполнены успешно!" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}