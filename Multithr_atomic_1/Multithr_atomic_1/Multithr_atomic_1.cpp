
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <Windows.h>

class SimpleCQ {

public:
    SimpleCQ(int max) : maxClients(max), running(true) {
        clientCount.store(0, std::memory_order_relaxed);
    }

    // Метод с использованием memory_order_seq_cst (самое строгое упорядочение)
    void clientThreadSeqCst() {
        while (running.load(std::memory_order_acquire)) {
            int current = clientCount.load(std::memory_order_seq_cst);
            if (current < maxClients) {
                // Пытаемся увеличить счетчик с последовательной согласованностью
                int expected = current;
                while (!clientCount.compare_exchange_weak(
                    expected,
                    expected + 1,
                    std::memory_order_seq_cst)) {
                    if (expected >= maxClients) break;
                }

                if (expected < maxClients) {
                    std::cout << "[SeqCst] Пришел новый клиент. В очереди: "
                        << expected + 1 << std::endl;
                }
                else {
                    std::cout << "[SeqCst] Очередь полна! Клиент ушел." << std::endl;
                }
            }
            else {
                std::cout << "[SeqCst] Очередь полна! Клиент ушел." << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "[SeqCst] Поток завершен" << std::endl;
    }

    // Метод с использованием memory_order_acq_rel (приобретение-отпускание)
    void clientThreadAcqRel() {
        while (running.load(std::memory_order_acquire)) {
            int current = clientCount.load(std::memory_order_acquire);
            if (current < maxClients) {
                // Используем операцию приобретения-отпускания
                int newValue = clientCount.fetch_add(1, std::memory_order_acq_rel);
                if (newValue < maxClients) {
                    std::cout << "[AcqRel] Пришел новый клиент. В очереди: "
                        << newValue + 1 << std::endl;
                }
                else {
                    // Откатываем увеличение, если превысили лимит
                    clientCount.fetch_sub(1, std::memory_order_acq_rel);
                    std::cout << "[AcqRel] Очередь полна! Клиент ушел." << std::endl;
                }
            }
            else {
                std::cout << "[AcqRel] Очередь полна! Клиент ушел." << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "[AcqRel] Поток завершен" << std::endl;
    }

    // Метод с использованием memory_order_relaxed (наиболее слабое упорядочение)
    void clientThreadRelaxed() {
        while (running.load(std::memory_order_relaxed)) {
            int current = clientCount.load(std::memory_order_relaxed);
            if (current < maxClients) {
                // Используем relaxed ordering
                clientCount.fetch_add(1, std::memory_order_relaxed);
                current = clientCount.load(std::memory_order_relaxed);
                std::cout << "[Relaxed] Пришел новый клиент. В очереди: "
                    << current << std::endl;

                // Проверяем лимит после увеличения
                if (current > maxClients) {
                    clientCount.fetch_sub(1, std::memory_order_relaxed);
                    std::cout << "[Relaxed] Превышен лимит! Откат." << std::endl;
                }
            }
            else {
                std::cout << "[Relaxed] Очередь полна! Клиент ушел." << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "[Relaxed] Поток завершен" << std::endl;
    }

    // Метод оператора с различными вариантами упорядочения
    void operatorThread(int mode = 0) {
        while (clientCount.load(std::memory_order_acquire) > 0 ||
            running.load(std::memory_order_acquire)) {

            int current = clientCount.load(std::memory_order_acquire);
            if (current > 0) {
                switch (mode) {
                case 0: // SeqCst
                    clientCount.fetch_sub(1, std::memory_order_seq_cst);
                    current = clientCount.load(std::memory_order_seq_cst);
                    std::cout << "[Оператор-SeqCst] Обслужил клиента. В очереди: "
                        << current << std::endl;
                    break;

                case 1: // AcqRel
                    clientCount.fetch_sub(1, std::memory_order_acq_rel);
                    current = clientCount.load(std::memory_order_acquire);
                    std::cout << "[Оператор-AcqRel] Обслужил клиента. В очереди: "
                        << current << std::endl;
                    break;

                case 2: // Relaxed
                    clientCount.fetch_sub(1, std::memory_order_relaxed);
                    current = clientCount.load(std::memory_order_relaxed);
                    std::cout << "[Оператор-Relaxed] Обслужил клиента. В очереди: "
                        << current << std::endl;
                    break;
                }
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        std::cout << "[Оператор] Поток завершен" << std::endl;
    }

    void stop() {
        running.store(false, std::memory_order_release);
    }

    int getClientCount() const {
        return clientCount.load(std::memory_order_acquire);
    }

    private:
    std::atomic<int> clientCount; // Атомарный счетчик клиентов
    int maxClients;               // Максимальное количество клиентов
    std::atomic<bool> running;    // Атомарная переменная для управления потоками
};



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "\n Тест 1: SeqCst ordering (строгая последовательная согласованность) \n";
    {
        SimpleCQ queue(5);
        std::thread client(&SimpleCQ::clientThreadSeqCst, &queue);
        std::thread oper(&SimpleCQ::operatorThread, &queue, 0);

        std::this_thread::sleep_for(std::chrono::seconds(10));
        queue.stop();

        client.join();
        oper.join();
    }

    std::cout << "\n Тест 2: Acquire-Release ordering \n";
    {
        SimpleCQ queue(5);
        std::thread client(&SimpleCQ::clientThreadAcqRel, &queue);
        std::thread oper(&SimpleCQ::operatorThread, &queue, 1);

        std::this_thread::sleep_for(std::chrono::seconds(10));
        queue.stop();

        client.join();
        oper.join();
    }

    std::cout << "\n Тест 3: Relaxed ordering \n";
    {
        SimpleCQ queue(5);
        std::thread client(&SimpleCQ::clientThreadRelaxed, &queue);
        std::thread oper(&SimpleCQ::operatorThread, &queue, 2);

        std::this_thread::sleep_for(std::chrono::seconds(10));
        queue.stop();

        client.join();
        oper.join();
    }

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
