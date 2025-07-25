
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

class adresse
{
public:
	adresse()
	{

	}
	adresse(std::string a_stadt, std::string a_strasse, std::string a_numHause, std::string a_numWohnung)
		:stadt{ a_stadt },
		strasse{ a_strasse },
		numHause{ a_numHause },
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
		return numHause;
	}
	std::string getNumWohnung()
	{
		return numWohnung;
	}

private:
	std::string stadt;
	std::string strasse;
	std::string numHause{};
	std::string numWohnung{};
};

// Сканирование количество значений массива
void scan(int& rows, std::string Text);

//Инициализауия массива
void initial_array(adresse* add_arey, int rows, std::string Text);


//Вывод массива в файл
void outputAdresse(adresse* adress, int row, std::string Text);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int row{};
	std::string TextScan{ "in.txt" };
	std::string TextPrint{ "out.txt" };
    scan(row,TextScan);
	adresse* adress{ new adresse[row] };
	
	std::cout << row << std::endl;
	initial_array(adress, row, TextScan);
	outputAdresse(adress, row, TextPrint);
	delete[] adress;
}

void scan(int& rows, std::string Text)
{
	std::ifstream ifile{ Text };

	if (ifile.is_open())
	{
		ifile >> rows;
	}
	ifile.close();
}

void initial_array(adresse* add_arey, int rows, std::string Text)
{
	
		int count{ 0 };
		std::string data1;
		std::string data2;
		std::string data3;
		std::string data4;

		std::ifstream ifile{ Text };
		if (ifile.is_open())
			ifile >> data1;
			while (!ifile.eof())
			{
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

void outputAdresse(adresse* adress, int row, std::string Text)
{

	std::ofstream ifile{Text};
	if (ifile.is_open())
	{
		ifile << row << std::endl;
		for (int i{ row-1}; (i >= 0); i--)
		{
				ifile << adress[i].getStadt()<<", ";
				ifile << adress[i].getStrasse() << ", ";
				ifile << adress[i].getNumHaus() << ", ";
				ifile << adress[i].getNumWohnung() << std::endl;
		}
	}
	ifile.close();
}
