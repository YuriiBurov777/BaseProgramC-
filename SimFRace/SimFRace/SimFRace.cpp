#include<iostream>
#include <map>
#include <functional>
#include<vector>
#include <algorithm>
#include <Windows.h>
#include <unordered_map>
#include "DLLR.h"
#include <cstdlib>
//#include"..\DinLibRace\DinLibRace.h"


static void printWielkommen() {
    std::cout << "Добро пожаловать в гоночный симулятор!" << std::endl;
    std::cout << "1. Гонка для наземного транспорта" << std::endl;
    std::cout << "2. Гонка для воздушного транспорта" << std::endl;
    std::cout << "3. Гонка для наземного и воздушного транспорта" << std::endl;
    std::cout << "Выбирите тип гонки:  ";
   
}

static void printDistanceR() {
    std::cout << "Укажите длинну дистанции( должна быть положительна ):  " << std::endl;
}

static void printRegistr() {
    std::cout << "Должно быть зарегистрированно не менее 2 транспортных средств" << std::endl;
    std::cout << "1. Зарегистрировать транспорт" << std::endl;
    std::cout << "Выберите действие: " << std::endl;
}

static void printselTransp() {
    std::cout << "1. Ботинки вездеходы " << std::endl;
    std::cout << "2. Метла" << std::endl;
    std::cout << "3. Верблюд" << std::endl;
    std::cout << "4. Кентавр" << std::endl;
    std::cout << "5. Орел" << std::endl;
    std::cout << "6. Верблюд_быстроход" << std::endl;
    std::cout << "7. Ковер_самолет" << std::endl;
    std::cout << "0. Закончить регистрацию" << std::endl;
    std::cout << "Выберите транспорт или 0 для окончания регистрации :";
}

static void printStReg() {
    std::cout << "1. Зарегистрировать транспорт" << std::endl;
    std::cout << "2. Начать гонку" << std::endl;
    std::cout << "Выберите действие :";

}

static void printNextRace() {
    std::cout << "1. Провести ещё одну гонку" << std::endl;
    std::cout << "2. Выйти" << std::endl;
    std::cout << "Выберите действие :";
    std::cout << std::endl;
}
template<typename T >
static T getNumberInRange(T min, T max) {
    T number{ 0 };
    do {
        std::cin >> number;

        if (number < min || number > max) {
            std::cout << "Ошибка! Число должно быть между " << min << " и " << max << std::endl;
            std::cout << "Повторите ввод :";
        }
    } while (number < min || number > max);

    return number;
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int countRace{ 0 };
    // Приветствие выбор типа гонки
    do
    {
        system("cls");
        printWielkommen();

        int typeR{ 0 };
        typeR = getNumberInRange(1, 3);



        //Установка дистанции
        system("cls");
        double typeDist{ 0 };

        printDistanceR();
        typeDist = getNumberInRange(0.1, 30000.0);

        DinLR::Race race(typeDist, typeR);




        // Переход к регистрации. Пред о 2 тр средствах
        system("cls");
        int registr{ 0 };
        printRegistr();
        registr = getNumberInRange(1, 1);


        do
        {
            


            do
            {
                //Сообщение о типе гонки расстоянии и регистрация тр

                system("cls");
                std::cout << race.getresultAdd() << std::endl;
                race.printTypeRace();
                race.printTransp();
                printselTransp();
                int sel;
                sel = getNumberInRange(0, 7);

                if (sel > 0) {
                    race.createTr(sel);
                }
                else if (sel == 0)
                {
                    break;
                }
            } while (true);



            //Проверка условий для гонки
            system("cls");
            race.printTypeRace();
            race.printTransp();
            int move;
            printStReg();
            move = getNumberInRange(1, 2);

            if ((race.getCount() > 1) && (move == 2)) { break; }
            else if (move == 1) { continue; }
            else {
                std::cout <<  std::endl;
                std::cout << " Участников меньше 2. Зарегистрируйте дополнительно участников" << std::endl; }
            Sleep(2000);
        } while (true);

        //Старт
        system("cls");
        race.startRace();
        race.sortR();

        int exitR{ 0 };

        race.print();
        printNextRace();
        std::cin >> exitR;

        if (exitR == 2) { break; }

    } while (true);
}

