#include <fstream>
#include <memory>
#include <string>
#include <iostream>

// Разделяем интерфейсы по форматам
class IHTMLPrintable {
public:
    virtual ~IHTMLPrintable() = default;
    virtual std::string printAsHTML() const = 0;
};

class ITextPrintable {
public:
    virtual ~ITextPrintable() = default;
    virtual std::string printAsText() const = 0;
};

class IJSONPrintable {
public:
    virtual ~IJSONPrintable() = default;
    virtual std::string printAsJSON() const = 0;
};

// Базовый класс данных
class Data {
public:
    explicit Data(std::string data) : data_(std::move(data)) {}
    virtual ~Data() = default;

    const std::string& getData() const { return data_; }

private:
    std::string data_;
};

// Специализированные классы для каждого формата
class HTMLData : public Data, public IHTMLPrintable {
public:
    explicit HTMLData(std::string data) : Data(std::move(data)) {}

    std::string printAsHTML() const override {
        return "<html>" + getData() + "<html/>";
    }
};

class TextData : public Data, public ITextPrintable {
public:
    explicit TextData(std::string data) : Data(std::move(data)) {}

    std::string printAsText() const override {
        return getData();
    }
};

class JSONData : public Data, public IJSONPrintable {
public:
    explicit JSONData(std::string data) : Data(std::move(data)) {}

    std::string printAsJSON() const override {
        return "{ \"data\": \"" + getData() + "\"}";
    }
};

// Функции сохранения не знают о формате данных
void saveToAsHTML(std::ofstream& file, const IHTMLPrintable& printable) {
    file << printable.printAsHTML();
}

void saveToAsText(std::ofstream& file, const ITextPrintable& printable) {
    file << printable.printAsText();
}

void saveToAsJSON(std::ofstream& file, const IJSONPrintable& printable) {
    file << printable.printAsJSON();
}
   

int main() {
    HTMLData htmlData("Hello");
    TextData textData("Hello");
    JSONData jsonData("Hello");

    std::ofstream file("output.txt");

    saveToAsHTML(file, htmlData);
    saveToAsText(file, textData);
    saveToAsJSON(file, jsonData);

    return 0;
}