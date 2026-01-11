// Multithreading_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <Windows.h>

class SimpleCQ {

public:
    SimpleCQ(int max) : clientCount(0), maxClients(max), running(true) {}

    void clientThread() {
        while (running) {
            {
                std::lock_guard<std::mutex> lock(mtx);  // lock_guard автоматически блокирует мьютекс при создании и разблокирует при выходе из области видимости (безопасно)
                if (clientCount < maxClients) {
                    clientCount++;
                    std::cout << "Пришел новый клиент. В очереди: " << clientCount << std::endl;
                }
                else {
                    std::cout << "Очередь полна! Клиент ушел." << std::endl;
                }
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));  // Ждем 1 секунду между появлением клиентов
        }
        std::cout << "Поток завершен" << std::endl;
    }

    void operatorThread() {
        while (clientCount > 0) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (clientCount > 0) {
                    clientCount--;
                    std::cout << "Оператор.Обслужил клиента. В очереди: " << clientCount << std::endl;
                }
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        std::cout << "Оператор.Поток завершен" << std::endl;
    }

    void stop() {
        running = false;// Устанавливаем флаг в false. Оба потока увидят это в условии while(running) и завершатся
    }

private:
    std::mutex mtx;  // Мьютекс для защиты разделяемых данных
    int clientCount; // Счетчик клиентов в очереди 
    int maxClients;  // Максимальное количество клиентов
    bool running;    // Переменная для управления работой потоков
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SimpleCQ queue(5);

    std::thread client(&SimpleCQ::clientThread, &queue); //Запускаем поток клиентов
    std::thread oper(&SimpleCQ::operatorThread, &queue); //Запускаем поток оператора

    // Время работы 60 секунд
    std::this_thread::sleep_for(std::chrono::seconds(60));

    //Останавливаем работу
    queue.stop();

    // Ждем завершения обоих потоков
    // join() блокирует текущий поток до завершения указанного потока
    client.join();
    oper.join();

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
