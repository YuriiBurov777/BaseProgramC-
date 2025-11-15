#include "Parser.h"
//
////template<typename T>
////T  Parser::get_value(const std::string& key_path)
//
//
std::string Parser::trim(const std::string& str)
{
     size_t start = str.find_first_not_of(" \t");
     if (start == std::string::npos) return "";
     size_t end = str.find_last_not_of(" \t");
     return str.substr(start, end - start + 1);
 }
//
bool Parser::is_comment_line(const std::string& line)
{
    std::string trimmed = trim(line);
    return trimmed.empty() || trimmed[0] == ';';
}
//
bool Parser::is_section_line(const std::string& line)
{
    std::string trimmed = trim(line);
    return !trimmed.empty() && trimmed[0] == '[' && trimmed.back() == ']';
}
//
std::string Parser::extract_section_name(const std::string& line)
{
    std::string trimmed = trim(line);
    std::string section_name = trim(trimmed.substr(1, trimmed.length() - 2));

    // Проверка на пустую секцию
    if (section_name.empty()) {
        throw std::runtime_error("Пустое название раздела");
    }

    return section_name;
}
//
std::pair<std::string, std::string> Parser::parse_variable_line(const std::string& line)
{
    size_t equals_pos = line.find('=');

    // УСЛОВИЕ: Проверка на некорректный формат файла - нет знака равенства
    if (equals_pos == std::string::npos) {
        throw std::runtime_error("Недопустимая строка переменной: в строке не найдено '=': " + line);
    }

    std::string key = trim(line.substr(0, equals_pos));
    std::string value = trim(line.substr(equals_pos + 1));

    // Проверка на пустой ключ
    if (key.empty()) {
        throw std::runtime_error("Пустое имя ключа в строке: " + line);
    }

    // Удаляем комментарий из значения
    size_t comment_pos = value.find(';');
    if (comment_pos != std::string::npos) {
        value = trim(value.substr(0, comment_pos));
    }

    return { key, value };
}
//
void Parser::parse_file()
{
    std::ifstream file(filename);

    // УСЛОВИЕ: Проблема со считыванием файла
    if (!file.is_open()) {
        throw std::runtime_error("Не удается открыть файл: " + filename);
    }

    std::string line;
    std::string current_section;
    int line_number = 0;

    while (std::getline(file, line)) {
        line_number++;

        try {
            // Пропускаем комментарии и пустые строки
            if (is_comment_line(line)) {
                continue;
            }

            // Обрабатываем секцию
            if (is_section_line(line)) {
                current_section = extract_section_name(line);
                continue;
            }

            // Обрабатываем переменные только если есть текущая секция
            if (!current_section.empty()) {
                auto pair = parse_variable_line(line);  // получаем пару
                std::string key = pair.first;           // первый элемент = ключ
                std::string value = pair.second;        // второй элемент = значение
                if (!key.empty()) {
                    data[current_section][key] = value;
                }
            }
        }
        catch (const std::exception& e) {
            // УСЛОВИЕ: Файл некорректный - добавляем информацию о строке
            throw std::runtime_error("Ошибка в строке " + std::to_string(line_number) +
                ": " + e.what());
        }
    }

    // Проверяем, что файл не пустой
    if (data.empty()) {
        throw std::runtime_error("Файл пуст или не содержит допустимых данных: " + filename);
    }
}
//
//
//
//
//
//
//
