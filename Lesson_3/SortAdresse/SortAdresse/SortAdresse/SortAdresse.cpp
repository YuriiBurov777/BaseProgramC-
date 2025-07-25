
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

//Класс город
class adresse
{
public:
	adresse()
	{
		std::string stadt="";
		std::string strasse="";
		std::string numHaus{};
		std::string numWohnung{};
	}
	adresse(std::string a_stadt, std::string a_strasse, std::string a_numHaus, std::string a_numWohnung)
		:stadt{ a_stadt },
		strasse{ a_strasse },
		numHaus{ a_numHaus },
		numWohnung{ a_numWohnung } {
	};
	std::string  getStadt()
	{
		return stadt;
	}
	std::string  getStrasse()
	{
		return strasse;
	}
	std::string  getNumHaus()
	{
		return numHaus;
	}
	std::string getNumWohnung()
	{
		return numWohnung;
	}

private:
	std::string stadt;
	std::string strasse;
	std::string numHaus{};
	std::string numWohnung{};
};

// Сканирование количество значений массива
void scan(int& rows, std::string Text);

//Инициализауия массива
void initial_array(adresse* add_arey, int rows, std::string Text);

//Сортировка адресов
void sortAdresee(adresse* adress, int size);

//Вывод массива в файл
void outputAdresse(adresse* adress, int row, std::string Text);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int row{};
	
	std::string TextScan{ "in.txt" };
	std::string TextPrint{ "out.txt" };
	
	scan(row, TextScan);
	adresse* adress{ new adresse[row] };

	initial_array(adress, row, TextScan);

	sortAdresee(adress, row);

	outputAdresse(adress, row, TextPrint);
	delete[] adress;
}

// Сканирование количество значений массива
void scan(int& rows, std::string Text)
{
	std::ifstream ifile{ Text };

	if (ifile.is_open())
	{
		ifile >> rows;
	}
	ifile.close();
}

//Инициализауия массива
void initial_array(adresse* add_arey, int rows, std::string Text)
{
	int count{ -1 };
	std::string data1;
	std::string data2;
	std::string data3;
	std::string data4;

	std::ifstream ifile{ Text };
	if (ifile.is_open())
	{
		while (!ifile.eof())
		{
			if (count == -1)    //Пропуск первой строчки (количество городов)
			{
				ifile >> data1;
				count += 1;
			}
			else               //Заполнение массива адресов
			{
				ifile >> data1;
				ifile >> data2;
				ifile >> data3;
				ifile >> data4;
				add_arey[count] = adresse(data1, data2, data3, data4);
				count += 1;
			}
		}
		ifile.close();
	}
}

//Сортировка адресов
void sortAdresee(adresse* adress, int size)
{
	adresse u;
	std::string A;
	std::string B;
	for (int e{ 0 }; e < size; e++)
	{
		for (int t{ size - 2 }; t >= 0; t--)
		{
			A = (adress[t].getStadt());
			B = (adress[t + 1].getStadt());
			if (A < B)
			{
				u = adress[t];
				adress[t] = adress[t + 1];
				adress[t + 1] = u;
			}
		}
	}
}

//Вывод массива в файл
void outputAdresse(adresse* adress, int row, std::string Text)
{

	std::ofstream ofile{ Text };
	if (ofile.is_open())
	{
		ofile << row << std::endl;
		for (int i{ row - 1 }; (i >= 0); i--)
		{
			ofile << adress[i].getStadt() << ", ";
			ofile << adress[i].getStrasse() << ", ";
			ofile << adress[i].getNumHaus() << ", ";
			ofile << adress[i].getNumWohnung() << std::endl;
		}
	}
	ofile.close();
}

