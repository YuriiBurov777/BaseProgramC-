#include "DLLR.h"

//создание транспорта и проверка на условие добавления в гонку 

void DinLR::Race::createTr(int value) {

    bool a{ true };
    auto n = reg.size();
    //std::cout << n << std::endl;

    // Проверяем на уже добавленный транспорт и nullptr.

    if (n != 0) {
        for (size_t i = 0; i < n; i++)
        {
            //std::cout << "1111" << reg[i]->ID << std::endl;
            if (reg[i] == nullptr)
            {
                std::cout << "Нет данных" << std::endl;
            }
            else if (reg[i]->ID == value)
            {
                resulAdd = reg[i]->getName() + " уже зарегистрирован";
                a = false;
                break;
            }

        }
    }

    if (a)
    {
        std::shared_ptr<Transport> Transp;

        switch (value)
        {
        case 1:
            // reg.push_back(std::make_shared<Boots>("Boots", 6, 10, 5, 60));
            Transp = std::make_shared<Boots>("Boots", 6, 10, 5, 60);
            break;
        case 2:
            //reg.push_back(std::make_shared<Broomstick>("Broomstick", 20));
            Transp = std::make_shared<Broomstick>("Broomstick", 20);
            break;
        case 3:
            //reg.push_back(std::make_shared<Camel>("Camel", 10, 5, 8, 30));
            Transp = std::make_shared<Camel>("Camel", 10, 5, 8, 30);
            break;
        case 4:
            // reg.push_back(std::make_shared<Kentavr>("Kent", 15, 2,8));
            Transp = std::make_shared<Kentavr>("Kent", 15, 2, 8);
            break;
        case 5:
            //reg.push_back(std::make_shared<Eigl>("Eigl", 8));
            Transp = std::make_shared<Eigl>("Eigl", 8);
            break;
        case 6:
            // reg.push_back(std::make_shared<CamelSpeed>("CamelSpeed", 40,5,6.5,8,10));
            Transp = std::make_shared<CamelSpeed>("CamelSpeed", 40, 5, 6.5, 8, 10);
            break;
        case 7:
            //reg.push_back(std::make_shared<AirCarpet>("AirCarpet", 10));
            Transp = std::make_shared<AirCarpet>("AirCarpet", 10);
            break;

        default:
            break;

        }

        // Только наземная гонка
        if (Transp->getTypeRace() == typeRace)
        {

            reg.push_back(Transp);
            resulAdd = Transp->getName() + " зарегистрирован!";
            countTr++;
        }
        //Только воздушная гонка
        else if (Transp->getTypeRace() == typeRace)
        {
            reg.push_back(Transp);
            resulAdd = Transp->getName() + " зарегистрирован!";
            countTr++;
        }
        //Смешанная гонка
        else if (typeRace == 3)
        {
            reg.push_back(Transp);
            resulAdd = Transp->getName() + " зарегистрирован";
            countTr++;
        }
        else { resulAdd = "Попытка зарегистрировать неподходящий транспорт"; }
    }
}

//Расчет времени 

void  DinLR::Race::startRace() {

    for (const auto& ptr : reg) {
        if (ptr) { // Проверка на nullptr
            ptr->calculateTime(_distanse);

        }
    }

}

//Сортировка результатов

void DinLR::Race::sortR() {

    std::sort(reg.begin(), reg.end(),
        [](const std::shared_ptr<Transport>& a, const std::shared_ptr<Transport>& b) {
            if (a && b) {
                return a->getDistance() < b->getDistance();
            }
        });
}

//Вывод результатов

void DinLR::Race::print() {

    int count{ 1 };

    std::cout << "Результат гонки: " << std::endl;
    for (const auto& ptr : reg) {
        if (ptr) { // Проверка на nullptr
            std::cout << count << ":  " + ptr->getName() + ". Time:  " << ptr->getDistance() << std::endl;
            count++;
        }
    }
    std::cout << std::endl;
    reg.clear();
    countTr = 0;
    resulAdd = "";
}

//Вывод типа гонки

void DinLR::Race::printTypeRace() const {

    if (typeRace == 1) {
        std::cout << "Гонка для наземного транспорта. Расстояние: " << _distanse << std::endl;
    }
    else if (typeRace == 2) {
        std::cout << "Гонка для воздушного транспорта. Расстояние: " << _distanse << std::endl;
    }
    else if (typeRace == 3) {
        std::cout << "Гонка для наземного и воздушного транспорта. Расстояние: " << _distanse << std::endl;
    }
}

//Вывод зарегистрированных тр ср

void DinLR::Race::printTransp() {

    std::string names;

    for (const auto& ptr : reg) {
        if (ptr) { // Проверка на nullptr
            names += ptr->getName() + "  ";

        }
    }

    std::cout << "Зарегистрированные транспортные стредства:  " + names << std::endl;
}

//Вывод дистанции

double  DinLR::Race::getDistance() const {
    return _distanse;
}

//Вывод количества зарегисттрированного тр

int DinLR::Race::getCount() const { return countTr; }

//Сообщение результата регистрации

std::string DinLR::Race::getresultAdd() { return resulAdd; }