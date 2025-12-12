#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

// Определение классов объектов
class Publisher;
class Book;
class Shop;
class Stock;
class Sale;

// ORM-класс для Издателя
class Publisher {
public:
    std::string name;

    Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
    }
};

// ORM-класс для Книги
class Book {
public:
    std::string title;
    Wt::Dbo::ptr<Publisher> publisher;

    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, title, "title");
        Wt::Dbo::belongsTo(a, publisher, "publisher");
        Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "book");
    }
};

// ORM-класс для Магазина
class Shop {
public:
    std::string name;

    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "shop");
    }
};

// ORM-класс для Склада (Stock)
class Stock {
public:
    int count;
    Wt::Dbo::ptr<Book> book;
    Wt::Dbo::ptr<Shop> shop;

    Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> sales;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::belongsTo(a, book, "book");
        Wt::Dbo::belongsTo(a, shop, "shop");
        Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
    }
};

// ORM-класс для Продажи
class Sale {
public:
    int price;
    std::string date_sale;
    int count;
    Wt::Dbo::ptr<Stock> stock;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, price, "price");
        Wt::Dbo::field(a, date_sale, "date_sale");
        Wt::Dbo::field(a, count, "sale_count");
        Wt::Dbo::belongsTo(a, stock, "stock");
    }
};

class BookstoreDB {
private:
    std::unique_ptr<Wt::Dbo::backend::Postgres> connectt;
    std::unique_ptr<Wt::Dbo::Session> session;

public:
    // Подключеню к базе данных
    void connect(const std::string& connectionString) {
        connectt = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);
        session = std::make_unique<Wt::Dbo::Session>();
        session->setConnection(std::move(connectt));

        // Регистрация классов
        session->mapClass<Publisher>("publisher");
        session->mapClass<Book>("book");
        session->mapClass<Shop>("shop");
        session->mapClass<Stock>("stock");
        session->mapClass<Sale>("sale");
    }

    // Создание таблиц
    void createTables() {
        session->createTables();
        std::cout << "Таблицы успешно созданы!" << std::endl;
    }

    // Заполнение тестовыми данными
    void fillTestData() {
        Wt::Dbo::Transaction transaction(*session);

        // Создаем издателей
        auto publisher1 = session->addNew<Publisher>();
        publisher1.modify()->name = "Slide";

        auto publisher2 = session->addNew<Publisher>();
        publisher2.modify()->name = "MiVP";

        auto publisher3 = session->addNew<Publisher>();
        publisher3.modify()->name = "Rook";

        // Создаем магазины
        auto shop1 = session->addNew<Shop>();
        shop1.modify()->name = "Thought";

        auto shop2 = session->addNew<Shop>();
        shop2.modify()->name = "Chit-gorod";

        auto shop3 = session->addNew<Shop>();
        shop3.modify()->name = "The primer";

        // Создаем книги 
        auto book1 = session->addNew<Book>();
        book1.modify()->title = "The Master and Margarita";
        book1.modify()->publisher = publisher1;

        auto book2 = session->addNew<Book>();
        book2.modify()->title = "Crime and punishment";
        book2.modify()->publisher = publisher1;

        // Создаем книги
        auto book3 = session->addNew<Book>();
        book3.modify()->title = "War and Peace";
        book3.modify()->publisher = publisher2;

        auto book4 = session->addNew<Book>();
        book4.modify()->title = "A fly with a white head";
        book4.modify()->publisher = publisher2;

        // Создаем книги
        auto book5 = session->addNew<Book>();
        book5.modify()->title = "Modern C++";
        book5.modify()->publisher = publisher3;

        // Создаем записи на складах
        // Магазин 1 продает книги издателей 1 и 2
        auto stock1 = session->addNew<Stock>();
        stock1.modify()->book = book1;
        stock1.modify()->shop = shop1;
        stock1.modify()->count = 45;

        auto stock2 = session->addNew<Stock>();
        stock2.modify()->book = book3;
        stock2.modify()->shop = shop1;
        stock2.modify()->count = 31;

        // Магазин 2 продает книги издателей 2 и 3
        auto stock3 = session->addNew<Stock>();
        stock3.modify()->book = book4;
        stock3.modify()->shop = shop2;
        stock3.modify()->count = 27;

        auto stock4 = session->addNew<Stock>();
        stock4.modify()->book = book5;
        stock4.modify()->shop = shop2;
        stock4.modify()->count = 52;

        // Магазин 3 продает книги всех издателей
        auto stock5 = session->addNew<Stock>();
        stock5.modify()->book = book1;
        stock5.modify()->shop = shop3;
        stock5.modify()->count = 67;

        auto stock6 = session->addNew<Stock>();
        stock6.modify()->book = book3;
        stock6.modify()->shop = shop3;
        stock6.modify()->count = 55;

        auto stock7 = session->addNew<Stock>();
        stock7.modify()->book = book5;
        stock7.modify()->shop = shop3;
        stock7.modify()->count = 19;

        // Создаем продажи
        auto sale1 = session->addNew<Sale>();
        sale1.modify()->price = 500;
        sale1.modify()->date_sale = "2025-12-10";
        sale1.modify()->count = 2;
        sale1.modify()->stock = stock1;

        auto sale2 = session->addNew<Sale>();
        sale2.modify()->price = 450;
        sale2.modify()->date_sale = "2025-12-11";
        sale2.modify()->count = 1;
        sale2.modify()->stock = stock3;

        transaction.commit();
        std::cout << "Тестовые данные успешно добавлены!" << std::endl;
    }

    // Поиск магазинов по имени издателя
    void findShopsByPublisherName(std::string publisherName) {
        Wt::Dbo::Transaction transaction(*session);

        auto publishers = session->find<Publisher>()
            .where("name = ?").bind(publisherName)
            .resultList();

        if (publishers.empty()) {
            std::cout << "Издатель с именем '" << publisherName << "' не найден." << std::endl;
            return;
        }

        // Берем 
        // издателя из списка
        Wt::Dbo::ptr<Publisher> publisher = *publishers.begin();

        std::cout << "\n=== Информация об издателе ===" << std::endl;
        std::cout << "ID: " << publisher.id() << std::endl;
        std::cout << "Название: " << publisher->name << std::endl;
        std::cout << "Найдено издателей с таким именем: " << publishers.size() << std::endl;

        //Получаем имена магазинов 
   
        auto shopNames = session->query<std::string>(
            "SELECT DISTINCT s.name FROM shop s "
            "JOIN stock st ON s.id = st.shop_id "
            "JOIN book b ON st.book_id = b.id "
            "WHERE b.publisher_id = ?")  // ← Ожидает число
            .bind(publisher.id())  // ← Передаем число (ID)
            .resultList();

        std::cout << "\n=== Магазины, продающие книги этого издателя ===" << std::endl;

        if (shopNames.empty()) {
            std::cout << "Магазины не найдены." << std::endl;
        }
        else {
            int counter = 1;
            for (const std::string& name : shopNames) {
                std::cout << counter++ << ". " << name << std::endl;
            }
        }
    }

    // Поиск магазинов по ID издателя
    void findShopsByPublisherID(long long publisherId) {
        Wt::Dbo::Transaction transaction(*session);

        Wt::Dbo::ptr<Publisher> publisher = session->load<Publisher>(publisherId);

        if (!publisher) {
            std::cout << "Издатель с ID " << publisherId << " не найден." << std::endl;
            return;
        }

        std::cout << "\n=== Информация об издателе ===" << std::endl;
        std::cout << "ID: " << publisher.id() << std::endl;
        std::cout << "Название: " << publisher->name << std::endl;

        typedef Wt::Dbo::collection<Wt::Dbo::ptr<Shop>> ShopCollection;
        ShopCollection shops = session->query<Wt::Dbo::ptr<Shop>>(
            "SELECT DISTINCT s FROM shop s "
            "JOIN stock st ON s.id = st.shop_id "
            "JOIN book b ON st.book_id = b.id "
            "WHERE b.publisher_id = ?")
            .bind(publisherId);

        std::cout << "\n=== Магазины, продающие книги этого издателя ===" << std::endl;
        if (shops.size() == 0) {
            std::cout << "Магазины не найдены." << std::endl;
        }
        else {
            int counter = 1;
            for (const Wt::Dbo::ptr<Shop>& shop : shops) {
                std::cout << counter++ << ". " << shop->name << std::endl;
            }
        }
    }

    // Вывод списка всех издателей
    void listAllPublishers() {
        Wt::Dbo::Transaction transaction(*session);

        Wt::Dbo::collection<Wt::Dbo::ptr<Publisher>> publishers = session->find<Publisher>();

        std::cout << "\n=== Список всех издателей ===" << std::endl;
        int counter = 1;
        for (const Wt::Dbo::ptr<Publisher>& publisher : publishers) {
            std::cout << counter++ << ". ID: " << publisher.id()
                << ", Название: " << publisher->name << std::endl;
        }
    }
};

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        // Настройки подключения к PostgreSQL
        std::string connectionString = "host=localhost port=5432 dbname=books user=postgres password='Qsezsc11!'";

        BookstoreDB db;

        // Подключаемся к базе данных
        db.connect(connectionString);

        // Создаем таблицы
        db.createTables();

        // Заполняем тестовыми данными
        db.fillTestData();

        // Выводим список всех издателей
        db.listAllPublishers();

        // Ввод запроса от пользователя
        std::cout << "\n=== Поиск магазинов по издателю ===" << std::endl;
        std::cout << "Введите имя издателя или его ID (для поиска по ID добавьте префикс 'id:'): ";

        std::string input;
        std::getline(std::cin, input);

        if (input.find("id:") == 0) {
            // Поиск по ID
            std::string idStr = input.substr(3);
            try {
                long long publisherId = std::stoll(idStr);
                db.findShopsByPublisherID(publisherId);
            }
            catch (const std::exception& e) {
                std::cerr << "Некорректный ID: " << e.what() << std::endl;
            }
        }
        else {
            // Поиск по имени
            db.findShopsByPublisherName(input);
        }

    }
    catch (const Wt::Dbo::Exception& e) {
        std::cerr << "Ошибка Wt::Dbo: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка!" << std::endl;
        return 1;
    }

    return 0;
}