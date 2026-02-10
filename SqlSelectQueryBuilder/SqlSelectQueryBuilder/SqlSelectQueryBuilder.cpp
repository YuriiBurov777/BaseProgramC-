#include <iostream>
#include <vector>
#include <map>

class SqlSelectQueryBuilder {

public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns_.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        where_conditions_[column] = value;
        return *this;
    }

    std::string BuildQuery() const {
        std::string query = "SELECT ";

        // Обработка колонок
        if (columns_.empty()) {
            query += "*";
        }
        else {
            for (size_t i = 0; i < columns_.size(); ++i) {
                query += columns_[i];
                if (i < columns_.size() - 1) {
                    query += ", ";
                }
            }
        }

        // Добавление таблицы (обязательное поле)
        if (!table_.empty()) {
            query += " FROM " + table_;
        }
        else {
            return ""; // Или можно бросить исключение
        }

        // Добавление условий WHERE
        if (!where_conditions_.empty()) {
            query += " WHERE ";
            auto it = where_conditions_.begin();

            query += it->first + "=" + it->second;
            ++it;

            for (; it != where_conditions_.end(); ++it) {
                query += " AND " + it->first + "=" + it->second;
            }
        }

        query += ";";
        return query;
    }
 private:
    std::vector<std::string> columns_;
    std::string table_;
    std::map<std::string, std::string> where_conditions_;
};
int main() {
    SqlSelectQueryBuilder builder;

    
    builder.AddWhere("name", "John")    // Добавляем условие 1
        .AddColumn("id")                // Добавляем колонку 1
        .AddFrom("users")               // Устанавливаем таблицу
        .AddColumn("name")              // Добавляем колонку 2  
        .AddWhere("age", "25")          // Добавляем условие 2
        .AddColumn("email")             // Добавляем колонку 3
        .AddWhere("name", "Johnny")     // ПЕРЕЗАПИСЫВАЕТ "John" на "Johnny"!
        .AddWhere("city", "NYC");       // Добавляем условие 3

    
    std::string query = builder.BuildQuery();
   
    std::cout << query << std::endl;

    return 0;
}