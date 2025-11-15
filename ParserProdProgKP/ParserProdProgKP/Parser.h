#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

class Parser {

public:
    Parser(const std::string& file_path) : filename(file_path) {
        parse_file();
    }

    template<typename T>
    T get_value(const std::string& key_path)
    {
        // Разбираем путь section.key
        size_t dot_pos = key_path.find('.');

        // УСЛОВИЕ: Некорректный формат пути
        if (dot_pos == std::string::npos) {
            throw std::runtime_error("Неверный формат пути к ключу. Ожидаемый раздел.ключ, получено" + key_path);
        }

        std::string section = key_path.substr(0, dot_pos);
        std::string key = key_path.substr(dot_pos + 1);

        // Проверка на пустые секцию или ключ
        if (section.empty() || key.empty()) {
            throw std::runtime_error("Неверный путь к ключу: раздел или ключ пуст в: " + key_path);
        }

        // УСЛОВИЕ: Если в файле нет значения для этой переменной
        auto section_it = data.find(section);
        if (section_it == data.end()) {
            throw std::runtime_error("Раздел не найден:'" + section + "'в пути: " + key_path);
        }

        auto key_it = section_it->second.find(key);
        if (key_it == section_it->second.end()) {
            throw std::runtime_error("Ключ не найден: '" + key + "' в разделе '" + section +
                "' в пути: " + key_path);
        }

        const std::string& value_str = key_it->second;

        // Преобразование значения в нужный тип с обработкой ошибок
        try {
            if constexpr (std::is_same_v<T, int>) {
                return std::stoi(value_str);
            }
            else if constexpr (std::is_same_v<T, double>) {
                return std::stod(value_str);
            }
            else if constexpr (std::is_same_v<T, float>) {
                return std::stof(value_str);
            }
            else if constexpr (std::is_same_v<T, bool>) {
                std::string lower_value = value_str;
                std::transform(lower_value.begin(), lower_value.end(), lower_value.begin(), ::tolower);
                if (lower_value == "true" || lower_value == "1" || lower_value == "yes") {
                    return true;
                }
                else if (lower_value == "false" || lower_value == "0" || lower_value == "no") {
                    return false;
                }
                else {
                    throw std::runtime_error("Недопустимое логическое значение: " + value_str);
                }
            }
            else if constexpr (std::is_same_v<T, std::string>) {
                return value_str;
            }
            else {
                throw std::runtime_error("Неподдерживаемый тип для значения: " + value_str);
            }
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Ошибка преобразования значения '" + value_str +
                "' в пути " + key_path + ": " + e.what());
        }
    }

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
    std::string filename;

    // Вспомогательные функции
    // обрезка пробелов
    std::string trim(const std::string& str);


    //проверка комментария
    bool is_comment_line(const std::string& line);
 

    //проверка секции
    bool is_section_line(const std::string& line);
  

    //извлечение имени секции
    std::string extract_section_name(const std::string& line); 
  

    //разбор строки с переменной
    std::pair<std::string, std::string> parse_variable_line(const std::string& line);
 

    void parse_file();
    

};
