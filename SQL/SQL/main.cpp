

#include <iostream>
#include <string>
#include <pqxx/pqxx>



class ClientManager {
private:
    pqxx::connection connectt;  // Одно подключение на весь класс

public:
   
    ClientManager(const std::string& conn_) : connectt(conn_) {

        if (!connectt.is_open()) {
            throw std::runtime_error("Couldn't connect to the database");
        }

        std::cout << "Connected to: " << connectt.dbname() << std::endl;
        std::cout << "\nTrying to create a table..." << std::endl;
        // Готовим шаблоны на частоиспользуемые запросы. Prepare использовать при высоконагруженных запросах
        //prepareQueries();
    }

    // Функция шаблонов на необходимые запросы
    void prepareQueries() {
        //Добавить клиента
        connectt.prepare("add_client",
            "INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3) RETURNING id");
        //Добавить номер телефона
        connectt.prepare("add_phone",
            "INSERT INTO client_phones (client_id, phone_number) VALUES ($1, $2)");
        // Удаление телефона
        connectt.prepare("delete_phone",
                "DELETE FROM client_phones WHERE client_id = $1 AND phone_number = $2");
        // Искать клиентов
        connectt.prepare("find_clients",
            "SELECT c.*, STRING_AGG(p.phone_number, ', ') as phones "
            "FROM clients c LEFT JOIN client_phones p ON c.id = p.client_id "
            "GROUP BY c.id ORDER BY c.id");
        // Поиск клиента по условию
        connectt.prepare("search_clients",
            "SELECT c.*, STRING_AGG(p.phone_number, ', ') as phones "
            "FROM clients c LEFT JOIN client_phones p ON c.id = p.client_id "
            "WHERE c.first_name ILIKE $1 OR c.last_name ILIKE $1 OR c.email ILIKE $1 "
            "GROUP BY c.id");
    }

    // Создание таблиц 
    void createTables() {
        //std::cout << "\nПробуем создать таблицу...111" << std::endl;
        pqxx::work txn(connectt);
       
        txn.exec(
            "CREATE TABLE IF NOT EXISTS clients ("
            "id SERIAL PRIMARY KEY,"
            "first_name VARCHAR(100) NOT NULL,"
            "last_name VARCHAR(100) NOT NULL,"
            "email VARCHAR(255) UNIQUE NOT NULL"
            ")"
        );

        txn.exec(
            "CREATE TABLE IF NOT EXISTS client_phones ("
            "id SERIAL PRIMARY KEY,"
            "client_id INTEGER NOT NULL REFERENCES clients(id) ON DELETE CASCADE,"
            "phone_number VARCHAR(20) NOT NULL,"
            "UNIQUE(client_id, phone_number)"
            ")"
        );

        txn.commit();
        std::cout << "Tables have been created" << std::endl;
    }

    // Добавить клиента (используем подготовленный запрос)
    int addClient(const std::string& first, const std::string& last,
        const std::string& email) {
        pqxx::work txn(connectt);

        try {
            // Используем шаблон. Если email уже существует БД вернет ошибку. Далее ловим ошибку и выводим на экран
            auto result = txn.exec_prepared("add_client", first, last, email);
            txn.commit();

            int id = result[0][0].as<int>();
            std::cout << "Added a client ID: " << id << std::endl;
            return id;

        }
        catch (const pqxx::unique_violation& e) {
            std::cout << "Error: the email already exists" << std::endl;
            return -1;
        }
    }

    // Добавить телефон (используем подготовленный запрос)
    void addPhone(int clientId, const std::string& phone) {
        pqxx::work txn(connectt);

        try {
            // Используем шаблон. Если телефон уже существует БД вернет ошибку. Далее ловим ошибку и выводим на экран
            txn.exec_prepared("add_phone", clientId, phone);
            txn.commit();
            std::cout << "Phone number added" << std::endl;

        }
        catch (const pqxx::unique_violation& e) {
            std::cout << "Error: the phone already exists" << std::endl;
        }
    }

    // Показать всех клиентов (используем подготовленный запрос)
    void showClients() {
        pqxx::work txn(connectt);

        // Используем подготовленный запрос
        auto result = txn.exec_prepared("find_clients");

        std::cout << "\n=== All clients ===" << std::endl;
        for (auto row : result) {
            std::cout << "ID: " << row["id"].as<int>() << std::endl;
            std::cout << "Name: " << row["first_name"].as<std::string>() << " "
                << row["last_name"].as<std::string>() << std::endl;
            std::cout << "Email: " << row["email"].as<std::string>() << std::endl;

            if (!row["phones"].is_null()) {
                std::cout << "Phones: " << row["phones"].as<std::string>() << std::endl;
            }
            std::cout << "---" << std::endl;
        }
    }

    // Поиск клиентов по условию (используем подготовленный запрос)
    void searchClients(const std::string& query) {
        pqxx::work txn(connectt);

        std::string pattern = "%" + query + "%";

        // Используем подготовленный запрос
        auto result = txn.exec_prepared("search_clients", pattern);

        std::cout << "\n=== Search Results: '" << query << "' ===" << std::endl;
        for (auto row : result) {
            std::cout << "ID: " << row["id"].as<int>() << std::endl;
            std::cout << "Name: " << row["first_name"].as<std::string>() << " "
                << row["last_name"].as<std::string>() << std::endl;
            std::cout << "Email: " << row["email"].as<std::string>() << std::endl;

            if (!row["phones"].is_null()) {
                std::cout << "Phones: " << row["phones"].as<std::string>() << std::endl;
            }
            std::cout << "---" << std::endl;
        }
    }

    // 6. Удалить клиента использую param т.к. запрос будет производиться нечасто
    void deleteClient(int clientId) {
        pqxx::work txn(connectt);

        txn.exec_params("DELETE FROM clients WHERE id = $1", clientId);
        txn.commit();

        std::cout << "The client has been deleted" << std::endl;
    }

    // 7. Обновить email использую param т.к. запрос будет производиться нечасто
    void updateEmail(int clientId, const std::string& newEmail) {
        pqxx::work txn(connectt);

        txn.exec_params("UPDATE clients SET email = $1 WHERE id = $2",
            newEmail, clientId);
        txn.commit();

        std::cout << "Email updated" << std::endl;
    }

    // Удаление телефона
    void deletePhone(int clientId, const std::string& phoneNumber) {
        try {
            pqxx::work txn(connectt);

            txn.exec_prepared("delete_phone", clientId, phoneNumber);
            txn.commit();

            std::cout << "The phone deletion operation has been completed" << std::endl;

        }
        catch (const std::exception& e) {
            std::cerr << "Error deleting the phone: " << e.what() << std::endl;
        }
    }
    
};

// Простая главная функция
int main() {

    try {
        // Подключение
        std::string conn_str = "dbname=SQLCxx user=postgres password='111' host=localhost";
        ClientManager manager(conn_str);

        // Основные операции
        manager.createTables();

        // Готовим шаблоны на частоиспользуемые запросы. Prepare использовать при высоконагруженных запросах
        manager.prepareQueries();

        // Добавление клиентов с prepare
        int id1 = manager.addClient("Jon", "Meier", "Jon@gmail.com");
        int id2 = manager.addClient("Richard", "Schmidt", "Richard@gmail.com");

        if (id1 > 0) {
            manager.addPhone(id1, "+79161234567");
            manager.addPhone(id1, "+74951234567");
        }

        manager.showClients();

        // Удалить номер телефона
        manager.deletePhone(1, "+79161234567");

        // Поиск и отображение
        manager.showClients();
        manager.searchClients("Jon");

        // Разовые операции без prepare
        manager.updateEmail(id1, "JonMeier@gmail.com");

        manager.showClients();

        //Удаление
        manager.deleteClient(id2);  // раскомментируйте для удаления

        manager.showClients();

    }
    catch (const std::exception& e) {
        std::cerr << "Fault: " << e.what() << std::endl;
        std::cout << "Checking:\n";
        std::cout << "1. Is it running PostgreSQL\n";
        std::cout << "2. Is there a database 'SQLCxx'\n";
        std::cout << "3. Password correctness\n";
    }

    std::cout << "\nPress Enter...";
    std::cin.get();
    return 0;
}