#include <iostream>
#include <fstream>
#include <string>
#include <memory>

// Базовый класс
class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

// Наследник для вывода в консоль
class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << "Console: " << message << std::endl;
    }
};

// Наследник для вывода в файл
class FileLogCommand : public LogCommand {
private:
    std::string filePath;

public:
    // Конструктор - указываем путь к файлу
    FileLogCommand(const std::string& path) : filePath(path) {}

    void print(const std::string& message) override {
        std::ofstream file(filePath, std::ios::app); // Открываем файл - добавление
        if (file.is_open()) {
            file << message << std::endl;
            file.close();
            std::cout << "Message written to file: " << filePath << std::endl;
        }
        else {
            std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        }
    }
};

// Функция для выполнения команд логирования
void print(LogCommand& command) {
    std::string message = "Log entry at " + std::to_string(time(nullptr));
    command.print(message);
}

void readFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Couldn't open the file: " << filePath << std::endl;
        return;
    }

    std::cout << "\nFile Contents " << filePath << ":\n";
    std::cout << "------------------------\n";

    std::string line;
    int lineNumber = 1;

    // Читаем файл построчно
    while (std::getline(file, line)) {
        std::cout << lineNumber << ": " << line << std::endl;
        lineNumber++;
    }

    std::cout << "------------------------\n";
    file.close();
}

int main() {

    // Создаем команды
    ConsoleLogCommand consoleLogger;
    FileLogCommand fileLogger("Log.txt");

    // Выполняем команды через функцию print
    print(consoleLogger);  // Выведет в консоль
    print(fileLogger);     // Запишет в файл

    readFromFile("Log.txt");

    return 0;
}