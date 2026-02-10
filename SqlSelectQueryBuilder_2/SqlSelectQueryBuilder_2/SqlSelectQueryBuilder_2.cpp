#include <iostream>
#include <vector>
#include <map>

class SqlSelectQueryBuilder {

public:
    
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table_name) {
        table = table_name;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        where_conditions.push_back(column + "=" + value);
        return *this;
    }

    // Новый метод: добавление нескольких условий WHERE
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& pair : kv) {
            where_conditions.push_back(pair.first + "=" + pair.second);
        }
        return *this;
    }

    // Новый метод: добавление нескольких колонок
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        // Добавляем все колонки из вектора
        for (const auto& column : columns) {
            this->columns.push_back(column);
        }
        return *this;
    }

    std::string BuildQuery() const {
        std::string result = "SELECT ";

        // Столбцы
        if (columns.empty()) {
            result += "*";
        }
        else {
            for (size_t i = 0; i < columns.size(); i++) {
                result += columns[i];
                if (i + 1 < columns.size()) result += ", ";
            }
        }

        // Таблица
        result += " FROM " + table;

        // Условия WHERE
        if (!where_conditions.empty()) {
            result += " WHERE ";
            for (size_t i = 0; i < where_conditions.size(); i++) {
                result += where_conditions[i];
                if (i + 1 < where_conditions.size()) result += " AND ";
            }
        }

        result += ";";
        return result;
    }
  private:

    std::vector<std::string> columns;
    std::string table;
    std::vector<std::string> where_conditions;
};

int main() {
    // Использование AddWhere с map
    std::cout << "--- AddWhere with map ---\n";
    {
        SqlSelectQueryBuilder builder1;
        builder1.AddFrom("students");

        // Создаем map с несколькими условиями
        std::map<std::string, std::string> conditions;
        conditions["id"] = "42";
        conditions["name"] = "John";
        conditions["age"] = "20";

        builder1.AddWhere(conditions);

        std::cout << builder1.BuildQuery() << "\n";

    }

    // Использование AddColumns с vector
    std::cout << "\n--- AddColumns with vector ---\n";
    {
        SqlSelectQueryBuilder builder2;
        builder2.AddFrom("users");

        // Создаем vector с несколькими колонками
        std::vector<std::string> column_list = { "id", "name", "email", "created_at" };
        builder2.AddColumns(column_list);

        builder2.AddWhere("active", "1");

        std::cout << builder2.BuildQuery() << "\n";
        
    }
  
    // Пустые данные (проверка noexcept)
    std::cout << "\n--- Empty data (noexcept test) ---\n";
    {
        SqlSelectQueryBuilder builder4;
        builder4.AddFrom("test");

        // Пустой map
        std::map<std::string, std::string> empty_map;
        builder4.AddWhere(empty_map);  // Ничего не должно сломаться

        // Пустой vector
        std::vector<std::string> empty_vector;
        builder4.AddColumns(empty_vector);  // Ничего не должно сломаться

        std::cout << builder4.BuildQuery() << "\n";
    }

    // Цепочка вызовов
    std::cout << "\n--- Method chaining ---\n";
    {
        SqlSelectQueryBuilder builder5;

        // Цепочка вызовов
        builder5.AddColumn("id")
            .AddColumns({ "name", "email" })
            .AddFrom("orders")
            .AddWhere("status", "pending")
            .AddWhere({ {"amount", ">100"}, {"date", "2023-01-01"} });

        std::cout << builder5.BuildQuery() << "\n";
    }

    return 0;
}