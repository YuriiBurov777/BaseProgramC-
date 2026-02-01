#pragma once

// Класс пула потоков

class thread_pool {

public:

    thread_pool(size_t num_threads = (std::thread::hardware_concurrency() - 1)) {
        // Минимум один поток
        if (num_threads == 0) {
            num_threads = 1;
        }

        // Создаем рабочие потоки
        workers_.reserve(num_threads);
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back(&thread_pool::work, this);
        }

        std::cout << "Пул потоков " << num_threads << std::endl;
    }

    // Деструктор - корректное завершение работы пула
    ~thread_pool() {
        stop_flag_ = true;
        tasks_queue_.stop();

        // Дожидаемся завершения всех потоков
        for (auto& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }

        std::cout << "Пул потоков удален" << std::endl;
    }

    // Запрещаем копирование
    thread_pool(const thread_pool&) = delete;
    thread_pool& operator=(const thread_pool&) = delete;

    // Добавление задачи с использованием function (не возвращаем результат)
    template<typename F>
    void submit(F&& func) {
        if (stop_flag_) {
            throw std::runtime_error("Пул потоков остановлен");
        }
        tasks_queue_.push(std::forward<F>(func));
    }

    // Добавление задачи с использованием function (возвращаем результат)
    template<typename T>
    std::future<T> submit(std::function<T()> func) {
        if (stop_flag_) {
            throw std::runtime_error("Пул потоков остановлен");
        }
        auto task = std::make_shared<std::packaged_task<T()>>(std::move(func)); // Автоматически создает promise
        auto result = task->get_future();
        tasks_queue_.push([task]() { (*task)(); });

        return result;
    }

    // Ожидание завершения всех задач
    void wait_all() {
        while (!tasks_queue_.empty() || active_tasks_ > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    // Получение количества активных задач
    int get_active_tasks() const {
        return active_tasks_;
    }

    // Получение количества задач в очереди
    size_t get_queued_tasks() const {
        return tasks_queue_.size();
    }

    // Получение количества рабочих потоков
    size_t get_thread_count() const {
        return workers_.size();
    }

private:
    safe_queue<std::function<void()>> tasks_queue_;
    std::vector<std::thread> workers_;
    std::atomic<bool> stop_flag_{ false };
    std::atomic<int> active_tasks_{ 0 };

    // Метод, который выполняют рабочие потоки
    void work() {
        while (!stop_flag_) {
            std::function<void()> task;

            // Получаем задачу из очереди
            if (tasks_queue_.pop(task)) {
                active_tasks_++;
                try {
                    task(); // Выполняем задачу
                }
                catch (const std::exception& e) {
                    std::cerr << "Исключение в пуле потоков: " << e.what() << std::endl;
                }
                active_tasks_--;
            }
        }
    }


};