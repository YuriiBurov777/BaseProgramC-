#pragma once

// Класс потокобезопасной очереди

template<typename T>
class safe_queue {

public:
    safe_queue() = default;

    // Запрещаем копирование
    safe_queue(const safe_queue&) = delete;
    safe_queue& operator=(const safe_queue&) = delete;

    // Помещаем элемент в очередь
    void push(T item) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(item));
        }
        cond_var_.notify_one(); // Уведомление для одного потока в ожидании
    }

    // Извлекаем элемент из очереди 
    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);

        // Ожидаем, пока не появится элемент или не будет установлен флаг остановки. 
        cond_var_.wait(lock, [this]() {
            return !queue_.empty() || stop_flag_;
            });

        // Если очередь пуста и флаг остановки установлен, возвращаем false
        if (queue_.empty() && stop_flag_) {
            return false;
        }

        item = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    // Проверка, пуста ли очередь
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    // Получение размера очереди
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    // Остановка очереди (для корректного завершения)
    void stop() {
        stop_flag_ = true;
        cond_var_.notify_all();
    }

private:
    std::queue<T> queue_;  // Основная очередь
    mutable std::mutex mutex_; // Синхронизация
    std::condition_variable cond_var_; // Условная переменная для ожидания
    std::atomic<bool> stop_flag_{ false }; // Переменная остановки

};


