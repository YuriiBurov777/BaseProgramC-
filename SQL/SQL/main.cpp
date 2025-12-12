

#include <iostream>
#include <string>
#include <pqxx/pqxx>


// Добавил структуру
struct ClientInfo {
    int id;                             // поле для ID
    std::string first_name;             // поле для имени
    std::string last_name;              // поле для фамилии
    std::string email;                  // поле для email
    std::vector<std::string> phones;    // ВЕКТОР телефонов!
};

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

        //try {
            // Используем шаблон. Если email уже существует БД вернет ошибку. Далее ловим ошибку и выводим на экран
            auto result = txn.exec_prepared("add_client", first, last, email);
            txn.commit();

            int id = result[0][0].as<int>();
            std::cout << "Added a client ID: " << id << std::endl;
            return id;

        }
        //catch (const pqxx::unique_violation& e) {
        //    std::cout << "Error: the email already exists" << std::endl;
        //    return -1;
        //}
    //}

    // Добавить телефон (используем подготовленный запрос)
    void addPhone(int clientId, const std::string& phone) {
        pqxx::work txn(connectt);

        //try {
            // Используем шаблон. Если телефон уже существует БД вернет ошибку. Далее ловим ошибку и выводим на экран
            txn.exec_prepared("add_phone", clientId, phone);
            txn.commit();
            std::cout << "Phone number added" << std::endl;

       // }
        //catch (const pqxx::unique_violation& e) {
       //     std::cout << "Error: the phone already exists" << std::endl;
        //}
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
    //void searchClients(const std::string& query) {
    //    pqxx::work txn(connectt);

    //    std::string pattern = "%" + query + "%";

    //    // Используем подготовленный запрос
    //    auto result = txn.exec_prepared("search_clients", pattern);

    //    std::cout << "\n=== Search Results: '" << query << "' ===" << std::endl;
    //    for (auto row : result) {
    //        std::cout << "ID: " << row["id"].as<int>() << std::endl;
    //        std::cout << "Name: " << row["first_name"].as<std::string>() << " "
    //            << row["last_name"].as<std::string>() << std::endl;
    //        std::cout << "Email: " << row["email"].as<std::string>() << std::endl;

    //        if (!row["phones"].is_null()) {
    //            std::cout << "Phones: " << row["phones"].as<std::string>() << std::endl;
    //        }
    //        std::cout << "---" << std::endl;
    //    }
    //}

    // Поиск клиентов по условию (используем подготовленный запрос)
    std::vector<ClientInfo> searchClients(const std::string& query) {
        pqxx::work txn(connectt);
        std::string pattern = "%" + query + "%";
        auto result = txn.exec_prepared("search_clients", pattern);

        std::vector<ClientInfo> clients;

        for (auto row : result) {
            ClientInfo client;
            client.id = row["id"].as<int>();
            client.first_name = row["first_name"].as<std::string>();
            client.last_name = row["last_name"].as<std::string>();
            client.email = row["email"].as<std::string>();

            // Обрабатываю телефоны, если они есть
            if (!row["phones"].is_null()) {
                std::string phones_str = row["phones"].as<std::string>();

                // Разделил строку телефонов на вектор
                size_t start = 0;
                size_t end = phones_str.find(", ");

                while (end != std::string::npos) {
                    client.phones.push_back(phones_str.substr(start, end - start));
                    start = end + 2; 
                    end = phones_str.find(", ", start);
                }

                // Добавляю последний телефон
                if (start < phones_str.length()) {
                    client.phones.push_back(phones_str.substr(start));
                }
            }

            clients.push_back(client);
        }

        return clients;
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
        //try {
            pqxx::work txn(connectt);

            txn.exec_prepared("delete_phone", clientId, phoneNumber);
            txn.commit();

            std::cout << "The phone deletion operation has been completed" << std::endl;

       // }
       // catch (const std::exception& e) {
       //     std::cerr << "Error deleting the phone: " << e.what() << std::endl;
       // }
    }
    
};


int main() {

     try {
        // Подключение
        std::string conn_str = "dbname=SQLCxx user=postgres password='111' host=localhost";
        ClientManager manager(conn_str);

        // Основные операции
        manager.createTables();
        manager.prepareQueries();

        // Все исключения будут пойманы в main для возможной дальнейшей обработки. В каждом catсh можно дописать логику обработки ошибки

        int id1 = manager.addClient("Jon", "Meier", "Jon@gmail.com");
        int id2 = manager.addClient("Richard", "Schmidt", "Richard@gmail.com");

        manager.addPhone(id1, "+79161234567");
        manager.addPhone(id1, "+74951234567");

        manager.showClients();
        manager.deletePhone(1, "+79161234567");
        manager.showClients();

        // Поиск клиента
        std::vector<ClientInfo> results = manager.searchClients("Jon");

        std::cout << "\n=== Search Results ===" << std::endl;
        for (const auto& client : results) {
            std::cout << "ID: " << client.id << std::endl;
            std::cout << "Name: " << client.first_name << " " << client.last_name << std::endl;
            std::cout << "Email: " << client.email << std::endl;

            // Вывожу телефоны если есть
            if (!client.phones.empty()) {
                std::cout << "Phones: ";
                for (size_t i = 0; i < client.phones.size(); i++) {
                    std::cout << client.phones[i];
                    if (i < client.phones.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << "---" << std::endl;
        }
      
        manager.updateEmail(id1, "JonMeier@gmail.com");
        manager.showClients();
        manager.deleteClient(id2);
        manager.showClients();

        // Добавляю дубликат email - исключение будет перехвачено в main
        //manager.addClient("Jon", "Meier", "JonMeier@gmail.com");

    }
    catch (const pqxx::unique_violation& e) {

        std::cerr << "Database constraint violation: " << e.what() << std::endl;
        std::cerr << "This could be a duplicate email or phone number." << std::endl;
        return 1;
    }
    catch (const pqxx::foreign_key_violation& e) {
        std::cerr << "Foreign key violation: " << e.what() << std::endl;
        std::cerr << "Trying to reference a non-existent client." << std::endl;
        return 1;
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        std::cerr << "Query: " << e.query() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl; 
        std::cerr << "\nChecking:\n";
        std::cerr << "1. Is PostgreSQL running?\n";
        std::cerr << "2. Is there a database 'SQLCxx'?\n";
        std::cerr << "3. Password correctness\n";
        return 1;
    }

    std::cout << "\nPress Enter...";
    std::cin.get();
    return 0;
}


