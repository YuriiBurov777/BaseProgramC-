#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>

// Базовый класс наблюдателя
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

// Наблюдаемый класс
class Observable {
private:
    std::vector<Observer*> observers;

    // Удаляем копирование
    Observable(const Observable&) = delete;
    Observable& operator=(const Observable&) = delete;

public:
    Observable() = default;
    ~Observable() = default;

    // Добавление наблюдателя
    void addObserver(Observer* observer) {
        if (observer && std::find(observers.begin(), observers.end(), observer) == observers.end()) {
            observers.push_back(observer);
        }
    }

    // Удаление наблюдателя
    void removeObserver(Observer* observer) {
        auto it = std::remove(observers.begin(), observers.end(), observer);
        observers.erase(it, observers.end());
    }

    // Методы оповещения
    void warning(const std::string& message) const {
        for (auto observer : observers) {
            if (observer) {
                observer->onWarning(message);
            }
        }
    }

    void error(const std::string& message) const {
        for (auto observer : observers) {
            if (observer) {
                observer->onError(message);
            }
        }
    }

    void fatalError(const std::string& message) const {
        for (auto observer : observers) {
            if (observer) {
                observer->onFatalError(message);
            }
        }
    }
};

// Наблюдатель для предупреждений (вывод в консоль)
class WarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "WARNING: " << message << std::endl;
    }
};

// Наблюдатель для ошибок (вывод в файл)
class ErrorObserver : public Observer {
private:
    std::string filePath;

public:
    explicit ErrorObserver(const std::string& path) : filePath(path) {}

    void onError(const std::string& message) override {
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "ERROR: " << message << std::endl;
            file.close();
        }
    }
};

// Наблюдатель для фатальных ошибок (вывод в консоль и файл)
class FatalErrorObserver : public Observer {
private:
    std::string filePath;

public:
    explicit FatalErrorObserver(const std::string& path) : filePath(path) {}

    void onFatalError(const std::string& message) override {
        // Вывод в консоль
        std::cout << "FATAL ERROR: " << message << std::endl;

        // Вывод в файл
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "FATAL ERROR: " << message << std::endl;
            file.close();
        }
    }
};
//Вывод из файла
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

    // Читаю файл построчно
    while (std::getline(file, line)) {
        std::cout << lineNumber << ": " << line << std::endl;
        lineNumber++;
    }

    std::cout << "------------------------\n";
    file.close();
}

int main() {
    Observable observable;

    // Создаю наблюдателей
    WarningObserver warningObs;
    ErrorObserver errorObs("Errors.log");
    FatalErrorObserver fatalObs("Fatal_errors.log");

    // Добавляю наблюдателей
    observable.addObserver(&warningObs);
    observable.addObserver(&errorObs);
    observable.addObserver(&fatalObs);

    // Генерирую события
    observable.warning("This is a warning message");
    observable.error("This is an error message");
    observable.fatalError("This is a fatal error message");

    // Удаляю наблюдателя
    observable.removeObserver(&warningObs);

    // Снова генерирую события (warning уже не будет обработан)
    observable.warning("This warning won't be shown");
    observable.error("Another error");
    observable.fatalError("Another fatal error");

    //Вывожу из файла
    readFromFile("Errors.log");
    readFromFile("Fatal_errors.log");

    return 0;
}