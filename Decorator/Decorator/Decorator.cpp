#include <string>
#include <iostream>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }

    virtual ~Text() = default; // Виртуальный деструктор для корректного удаления через указатель на базовый класс
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}

    ~DecoratedText() override {
        delete text_;
    }

protected:
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}

    void render(const std::string& data) const override {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}

    void render(const std::string& data) const override {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};
// Класс для добавления параграфа
class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}

    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};
// Класс для переворота строки
class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}

    void render(const std::string& data) const override {
        std::string reversed = data;
        std::reverse(reversed.begin(), reversed.end());
        text_->render(reversed);
    }
};
// Класс для ссылки
class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}

    // Новая сигнатура - два параметра
    void render(const std::string& url, const std::string& text) const {
        std::cout << "<a href=" << url << ">";
        text_->render(text);
        std::cout << "</a>";
    }
};

int main() {

    auto text_block = new ItalicText(new BoldText(new Text()));
    text_block->render("Hello world");
    std::cout << std::endl;
    delete text_block;
    // Пример с параграфом
    auto text_block1 = new Paragraph(new Text());
    text_block1->render("Hello world");
    std::cout << std::endl;
    delete text_block1;
    // Пример с перевернутым текстом
    auto text_block2 = new Reversed(new Text());
    text_block2->render("Hello world");
    std::cout << std::endl;
    delete text_block2;
    // Пример со ссылкой
    auto text_block3 = new Link(new Text());
    text_block3->render("netology.ru", "Hello world");
    std::cout << std::endl;
    delete text_block3;

    return 0;
}