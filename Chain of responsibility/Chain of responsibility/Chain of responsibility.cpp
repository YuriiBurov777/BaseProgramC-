#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <memory>

// Типы сообщений
enum class Type {
    WARNING,
    ERROR,
    FATAL,
    UNKNOWN
};

// Класс сообщения
class LogMessage {
public:
    LogMessage(Type msgType, const std::string& msg)
        : type_(msgType), message_(msg) {
    }

    Type type() const {
        return type_;
    }

    const std::string& message() const {
        return message_;
    }

private:
    Type type_;
    std::string message_;
};

// Базовый класс обработчика
class LogHandler {
public:
    virtual ~LogHandler() = default;

    void setNext(std::shared_ptr<LogHandler> next) {
        nextHandler_ = next;
    }

    void handle(const LogMessage& message) {
        if (canHandle(message)) {
            process(message);
        }
        else if (nextHandler_) {
            nextHandler_->handle(message);
        }
        else {
            // Если нет обработчика для данного типа
            throw std::runtime_error("No handler available for message type");
        }
    }

protected:
    virtual bool canHandle(const LogMessage& message) = 0;
    virtual void process(const LogMessage& message) = 0;

private:
    std::shared_ptr<LogHandler> nextHandler_;
};

// Обработчик фатальных ошибок
class FatalErrorHandler : public LogHandler {
protected:
    bool canHandle(const LogMessage& message) override {
        return message.type() == Type::FATAL;
    }

    void process(const LogMessage& message) override {
        throw std::runtime_error("Fatal error: " + message.message());
    }
};

// Обработчик обычных ошибок
class ErrorHandler : public LogHandler {
public:
    ErrorHandler(const std::string& filePath) : filePath_(filePath) {}

protected:
    bool canHandle(const LogMessage& message) override {
        return message.type() == Type::ERROR;
    }

    void process(const LogMessage& message) override {
        std::ofstream file(filePath_, std::ios::app);
        if (file.is_open()) {
            file << "Error: " << message.message() << std::endl;
            file.close();
        }
        else {
            throw std::runtime_error("Cannot open error log file");
        }
    }

private:
    std::string filePath_;
};

// Обработчик предупреждений
class WarningHandler : public LogHandler {
protected:
    bool canHandle(const LogMessage& message) override {
        return message.type() == Type::WARNING;
    }

    void process(const LogMessage& message) override {
        std::cout << "Warning: " << message.message() << std::endl;
    }
};

// Обработчик неизвестных сообщений
class UnknownHandler : public LogHandler {
protected:
    bool canHandle(const LogMessage& message) override {
        return message.type() == Type::UNKNOWN;
    }

    void process(const LogMessage& message) override {
        throw std::runtime_error("Unhandled message: " + message.message());
    }
};

void readFromFile(const std::string& filePath) {
    std::ifstream file(filePath);  // Открываем файл для чтения

    if (!file.is_open()) {  // Проверяем, открылся ли файл
        std::cout << "Не удалось открыть файл: " << filePath << std::endl;
        return;
    }

    std::string line;
    // Читаем файл построчно, пока не закончится
    while (std::getline(file, line)) {
        std::cout << "File : " << line << std::endl;  // Выводим каждую строку
    }

    file.close();  // Закрываем файл
}

int main() {
    try {
        // Создаю обработчики
        auto fatalHandler = std::make_shared<FatalErrorHandler>();
        auto errorHandler = std::make_shared<ErrorHandler>("Errors.log");
        auto warningHandler = std::make_shared<WarningHandler>();
        auto unknownHandler = std::make_shared<UnknownHandler>();

        // Строю цепочку 
        fatalHandler->setNext(errorHandler);
        errorHandler->setNext(warningHandler);
        warningHandler->setNext(unknownHandler);

        // Тесты
        LogMessage warning(Type::WARNING, "Low disk space");
        LogMessage error(Type::ERROR, "Failed to open file");
        LogMessage fatal(Type::FATAL, "Out of memory");
        LogMessage unknown(Type::UNKNOWN, "Unknown event occurred");

        // Обрабатываю сообщения
        try {
            fatalHandler->handle(warning);    // Вывод в консоль
            fatalHandler->handle(error);      // Запись в файл
            fatalHandler->handle(fatal);      // Исключение
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }

        // Проверка обработки неизвестного сообщения
        try {
            fatalHandler->handle(unknown);    // Исключение
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    readFromFile("Errors.log");

    return 0;
}