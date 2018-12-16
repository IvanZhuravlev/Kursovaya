#include <iostream>
#include <iomanip>     
#include <cstring>    
#include <string>

using namespace std;

char* NewDate() //Cоздаём указатель на 128 символов, здесь будет лежать дата
{
	char* DateNew = new char[128];
	cin >> DateNew;
	cout << "Создание даты" << endl;//Создание даты
	return DateNew;
}

void CreateDate(int &day, int &month, int &year) { // Проверка даты
	bool Trust = true;
	while (Trust)
	{
		char*  DateCr = NewDate();// Записываем указатель возвращаемый в функции в этот указатель, при его инициализации
		int Length = strlen(DateCr);
		cout << "Проверка даты" << endl << DateCr << endl;//Проверка даты
		if ((Length == 10) || (Length == 8))// Проверяем на количество символов(либо 10, либо 8 символов)
		{
			bool Conform = true;// Проверяем введенные символы
			for (int i = 0; i < Length; i++)
				if (!(((DateCr[i] <= '9') && (DateCr[i] >= '0')) || (DateCr[i] == '.') || (DateCr[i] == '/')))//по весу символы от 0 до 9 идут подряд
				{
					Conform = false; // Мы проходим элементы внутри цикла, поэтому используем переменную
				}
			if (Conform)
			{
				// Определяемся с используемым знаком в разделении символов у даты . или /
				bool leap = 0, validDate = 1;// Первая переменная проверяет високосность, вторая корректность даты
				short  CntrP = 0;
				for (int i = 0; i < Length; i++)
				{
					if (DateCr[i] == '.' || DateCr[i] == '/')// Считаем сколько разделительных символов у нас есть
					{
						CntrP++;
					}
				}
				if ((CntrP == 2) && (DateCr[2] == '.') && (DateCr[5] == '.'))//проверка на используемые разделительные символы
				{
					sscanf(DateCr, "%d.%d.%d", &day, &month, &year);// Разбиваем строку на целочисленные куски
				}
				else if ((CntrP == 2) && (DateCr[2] == '/') && (DateCr[5] == '/'))
				{
					sscanf(DateCr, "%d/%d/%d", &day, &month, &year);
				}
				else
				{
					cout << "Ошибка в разделительных знаках, повторите ввод" << endl;
					continue;
				}
				if (!(year % 4))// Условия для проверки того, существует ли такая дата
					leap = true;
				if (!(year % 100) && (year % 400))
					leap = false;
				if (day < 1 || day > 31)
					validDate = false;
				if (month < 1 || month > 12)
					validDate = false;
				if (month == 2 && day > 29 && leap == true)
					validDate = false;
				if (month == 2 && day > 28 && leap == false)
					validDate = false;
				if (month == 4 || month == 6 || month == 9 || month == 11) {
					if (day > 30) {
						validDate = false;
					}
				}
				if (validDate) // Условие, если введена короткая запись, то последние два символа года преобразуются либо в 19ХХ либо в 20ХХ
				{
					if ((year < 20) && (Length == 8))
						year = year + 2000;
					if ((year < 100) && (Length == 8))
						year = year + 1900;
					delete[]DateCr;
					break;
				}
				else
				{
					cout << "Введена некорректная дата, повторите ввод" << endl;
					continue;
				}

			}
			else
			{
				cout << "Введены некорректные символы, повторите ввод" << endl;
				continue;
			}
		}
		else
		{
			cout << "Количество символов не соответсвуют форме ввода, повторите ввод" << endl;
			continue;
		}

	}

}

void OutDate(int day, int month, int year)// Вывод даты, на вход три переменные
{
	cout << "Дата в длинном формате:" << endl;
	if (day < 10)
		cout << "0" << day;
	else
		cout << day;
	cout << ".";
	if (month < 10)
		cout << "0" << month;
	else
		cout << month;
	cout << ".";
	cout << year << endl;
}

void OutDateA(int day, int month, int year)// Выше
{
	cout << "Дата в американском формате:" << endl;
	if (month < 10)
		cout << "0" << month;
	else
		cout << month;
	cout << ".";
	if (day < 10)
		cout << "0" << day;
	else
		cout << day;
	cout << ".";
	cout << year << endl;
}

void BiggerDate(int days, int &day, int &month, int &year)// Увеличение даты и количество дней, на которое увеличивается дата
{
	bool CorrectDate = false, leap = false;
	if (!(year % 4))
		leap = true;
	if (!(year % 100) && (year % 400))
		leap = false;
	day = day + days;
	while (!CorrectDate) 
	{
		CorrectDate = true;
		if (month == 1 && day>31)
		{
			day = day - 31;
			month++;
		}
		if (month == 2 && day > 29 && leap == true)
		{
			day = day - 29;
			month++;
		}
		if (month == 2 && day > 28 && leap == false)
		{
			day = day - 28;
			month++;
		}
		if (month == 3 && day>31)
		{
			day = day - 31;
			month++;
		}
		if ((month == 4) && (day>30))
		{
			day = day - 30;
			month++;
		}
		if (month == 5 && day>31)
		{
			day = day - 31;
			month++;
		}
		if (month == 6 && day>30)
		{
			day = day - 30;
			month++;
		}
		if (month == 7 && day>31)
		{
			day = day - 31;
			month++;
		}
		if (month == 8 && day>31)
		{
			day = day - 31;
			month++;
		}
		if (month == 9 && day>30)
		{
			day = day - 30;
			month++;
		}
		if (month == 10 && day>31)
		{
			day = day - 31;
			month++;
		}
		if (month == 11 && day>30)
		{
			day = day - 30;
			month++;
		}
		if (month == 12 && day>31)
		{
			day = day - 31;
			month++;
		}
		if (month > 12)
		{
			month = 1;
			year++;
			if (!(year % 4))
				leap = true;
			if (!(year % 100) && (year % 400))
				leap = false;
			CorrectDate = false;
		}
	}
}
void LesserDate(int days, int &day, int &month, int &year)// Уменьшение даты
{
	bool CorrectDate = false, leap = false;
	if (!(year % 4))
		leap = true;
	if (!(year % 100) && (year % 400))
		leap = false;
	if (day > days)
	{
		day = day - days;
		CorrectDate = true;
	}
	else
	{
		days = days + 32;
	}					 
	while (!CorrectDate)
	{
		CorrectDate = true;
		if (month == 12 && days>31)
		{
			days = days - 30;
			month--;
		}
		if (month == 11 && days>30)
		{
			days = days - 31;
			month--;
		}
		if (month == 10 && days>31)
		{
			days = days - 30;
			month--;
		}
		if (month == 9 && days>30)
		{
			days = days - 31;
			month--;
		}
		if (month == 8 && days>31)
		{
			days = days - 31;
			month--;
		}
		if (month == 7 && days>31)
		{
			days = days - 30;
			month--;
		}
		if (month == 6 && days>30)
		{
			days = days - 31;
			month--;
		}
		if (month == 5 && days>31)
		{
			days = days - 30;
			month--;
		}
		if ((month == 4) && (days>30))
		{
			days = days - 31;
			month--;
		}

		if (month == 3 && days > 29 && leap == true)
		{
			days = days - 29;
			month--;
		}
		if (month == 3 && days > 28 && leap == false)
		{
			days = days - 28;
			month--;
		}
		if (month == 2 && days>31)
		{
			days = days - 31;
			month--;
		}
		if (month == 1 && days>31)
		{
			days = days - 31;
			month--;
		}
		if (month == 0)
		{
			month = 12;
			year--;
			if (!(year % 4))
				leap = true;
			if (!(year % 100) && (year % 400))
				leap = false;
			CorrectDate = false;
		}
		else
		{
			BiggerDate(32 - days, day, month, year);
		}
	}
}
void Difference(int day1, int month1, int year1, int day2, int month2, int year2)
{
	int count = 0;
	if (year1 == year2)
	{
		if (month1 == month2)
		{
			if (day1 = day2)
			{
				cout << "Даты равны" << endl;
			}
			else if (day1 > day2)
			{
				cout << day1 - day2 << endl;
			}
			else
			{
				cout << day2 - day1 << endl;
			}
		}
		else if (month1 > month2)
		{
			while (!((month1 == month2) && (day1 == day2)))
			{
				BiggerDate(1, day2, month2, year2);
				count++;
			}
			cout << count << endl;
		}
		else
		{
			while (!((month1 == month2) && (day1 == day2)))
			{
				BiggerDate(1, day1, month1, year1);
				count++;
			}
			cout << count << endl;
		}
	}
	else if (year1 > year2)
	{
		while (!((year1 == year2) && (month1 == month2) && (day1 == day2)))
		{
			BiggerDate(1, day2, month2, year2);
			count++;
		}
		cout << count << endl;
	}
	else
	{
		while (!((year1 == year2) && (month1 == month2) && (day1 == day2)))
		{
			BiggerDate(1, day1, month1, year1);
			count++;
		}
		cout << count << endl;
	}
}

void DayOfTheWeek(int day, int month, int year)// Выводим день недели
{
	int a = (14 - month) / 12;
	int y = year - a;
	int m = month + 12 * a - 2;
	int c = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
	switch (c)
	{
	case 0:cout << "Воскресенье" << endl;
		break;
	case 1:cout << "Понедельник" << endl;
		break;
	case 2:cout << "Вторник" << endl;
		break;
	case 3:cout << "Среда" << endl;
		break;
	case 4:cout << "Четверг" << endl;
		break;
	case 5:cout << "Пятница" << endl;
		break;
	case 6:cout << "Суббота" << endl;
		break;
	}
}
void Menu()
{
	cout << "Средства для работы с датами" << endl << endl << "Введите номер операции с клавиатуры:" << endl;
	cout << "1. Пересоздать дату" << endl << "2. Вывести дату в длинном формате" << endl << "3. Вывести дату в американском формате" << endl << "4. Увеличить дату на один день" << endl;
	cout << "5. Увеличить дату на указанное количество дней" << endl << "6. Уменьшить дату на один день" << endl << "7. Уменьшить дату на указанное количество дней" << endl;
	cout << "8. Вывести разницу между датами в днях" << endl << "9. Вывести какой день недели соответствует дате" << endl << "0. Выйти" << endl;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	bool let = true, mmm = true;
	int n, day, month, year, Day, Month, Year;
	char simbol;
	while (mmm)
	{
		cout << "Средства для работы с датами" << endl << endl << "Для функционирования приложения необходимо создать дату" << endl;
		cout << "1. Создать дату" << endl << "0. Выйти" << endl;
		cin >> simbol;
		system("cls");
		switch (simbol)
		{
		case'1':
			cout << "Введите дату в одном из форматов  дд.мм.гггг, дд/мм/гггг, дд.мм.гг, дд/мм/гг" << endl;
			CreateDate(day, month, year);
			mmm = false;
			break;
		case '0':
			exit(1);
			break;
		default:
			cout << "Вы ввели несуществующий пункт меню, повторите ввод" << endl;
			break;
		}
	}
	system("cls");
	Menu();
	while (1)
	{
		cin >> simbol;
		if ((simbol <= '9') && (simbol >= '0'))
		{

			switch (simbol)
			{
			case '1':
				system("cls");
				Menu();
				cout << "Введите новую дату:" << endl;
				CreateDate(day, month, year);
				system("cls");
				Menu();
				break;
			case '2':
				system("cls");
				Menu();
				OutDate(day, month, year);
				break;
			case '3':
				system("cls");
				Menu();
				OutDateA(day, month, year);
				break;
			case '4':
				system("cls");
				Menu();
				BiggerDate(1, day, month, year);
				break;
			case '5':
				system("cls");
				Menu();
				cout << endl << "Введите количество дней, на которое необходимо увеличить текущую дату" << endl;
				cin >> n;
				BiggerDate(n, day, month, year);
				system("cls");
				Menu();
				break;
			case '6':
				system("cls");
				Menu();
				LesserDate(1, day, month, year);
				break;
			case '7':
				system("cls");
				Menu();
				cout << endl << "Введите количество дней, а которое необходимо уменьшить текущую дату" << endl;
				cin >> n;
				LesserDate(n, day, month, year);
				system("cls");
				Menu();
				break;
			case '8':
				system("cls");
				Menu();
				cout << endl << "Введите вторую дату" << endl;
				CreateDate(Day, Month, Year);
				cout << endl << "Разница между датами:" << endl;
				Difference(day, month, year, Day, Month, Year);
				break;
			case '9':
				system("cls");
				Menu();
				cout << endl << "День недели:" << endl;
				DayOfTheWeek(day, month, year);
				break;
			case '0':
				exit(1);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}
