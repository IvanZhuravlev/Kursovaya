#include <iostream>
#include <iomanip>     
#include <cstring>    
#include <string>

using namespace std;

char* NewDate() //там самая функция, в которой нету необходимости, т.к. её можно было реализовать в следующей, здесь просто создаём указатель на кучу из 128 символов, чтобы наверняка, там будет лежать дата
{
	char* DateNew = new char[128];
	cin >> DateNew;
	cout << "Дата создаётся" << endl;
	return DateNew;
}

void CreateDate(int &day, int &month, int &year) { //тут будем проверять дату, на вход ссылки на три целочисленные, ссылки, чтобы целочисленные переменные, которые задаются при вызове функции сохраняли именения, которые произойдут с ними в функции
	bool Trust = true;
	while (Trust)
	{
		char*  DateCr = NewDate();//записываю указатель возвращаемый в функции в этот указатель, при его инициализации
		int Length = strlen(DateCr);
		cout << "Дата проверяется" << endl << DateCr << endl;
		if ((Length == 10) || (Length == 8))//сначала проверяю на количество символов, у нас всего 4 типа формы, в каждой либо 10 либо 8 символов
		{
			bool Conform = true;//с помощбю этой переменной проверим все ли введенные символы соответсуют символам которые могут быть введены
			for (int i = 0; i < Length; i++)
				if (!(((DateCr[i] <= '9') && (DateCr[i] >= '0')) || (DateCr[i] == '.') || (DateCr[i] == '/')))//по весу символы от 0 до 9 идут подряд
				{
					Conform = false; //Так как мы проходим элементы внутри цикла, просто использовать continue не получится, поэтому используем переменную
				}
			if (Conform)
			{
				//определяюсь с тем какой знак используется в разделении символов у даты . или /
				bool leap = 0, validDate = 1;//первая переменная проверяет високосность, вторая корректность даты
				short  CntrP = 0;
				for (int i = 0; i < Length; i++)
				{
					if (DateCr[i] == '.' || DateCr[i] == '/')//считаем сколько разделительных символов у нас есть
					{
						CntrP++;
					}
				}
				if ((CntrP == 2) && (DateCr[2] == '.') && (DateCr[5] == '.'))//проверка на то, какие разделительные символы используются
				{
					sscanf(DateCr, "%d.%d.%d", &day, &month, &year);//тут и потом разбиваем строку на целочисленные куски
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
				if (!(year % 4))//условия для проверки того, существует ли такая дата
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
				if (validDate) //условие, если введена короткая запись, то последние два символа года преобразуются либо в 19ХХ либо в 20ХХ
				{
					if ((year < 20) && (Length == 8))
						year = year + 2000;
					if ((year < 100) && (Length == 8))
						year = year + 1900;
					delete[]DateCr; //вообще после вызова функции вроде само удалится
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

void OutDate(int day, int month, int year)//вывод даты, на вход три переменные, те, куда записывались куски строки в прошлой функции
{
	cout << "Дата в длинном формате:" << endl;
	if (day < 10)
		cout << "0" << day;//прибаляем 0 при выводе дней, далее вставка точки, прибавление нуля при выводе месяца меньшего 10 и вставка точки
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

void OutDateA(int day, int month, int year)//аналогично предыдущему
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

void BiggerDate(int days, int &day, int &month, int &year)//увеличение даты, на вход кроме самой даты с ссылками, ещё и количество дней, на которое увеличивается дата
{
	bool CorrectDate = false, leap = false;
	if (!(year % 4))
		leap = true;
	if (!(year % 100) && (year % 400))//тут по условиям всё похоже на вторую функцию
		leap = false;
	day = day + days;
	while (!CorrectDate) //после того как к переменной с днями прибавили количество дней на которое мы увелииваем, проходим и уменьшаем по соответсвующим месяцам
	{
		CorrectDate = true;
		if (month == 1 && day>31)//можно было и дать четыре условия, а не 12, но тогда бы цикл тикал чаще, а так за один цикл можно прибавить целый год
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
void LesserDate(int days, int &day, int &month, int &year)//уменьшение даты, это сложнее
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
		days = days + 32;//Так, потому что по другому хз как, типо day-days(то что нам нужно получить) = day+32-(days+32), поэтому сначала прибавляю, а потом, чтобы не было условий, использую функцию прибавки
	}					  // Вроде это работает
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
		{//это то о чём комменты в начале
			BiggerDate(32 - days, day, month, year);
		}
	}
}
void Difference(int day1, int month1, int year1, int day2, int month2, int year2)//Сравнение дат, и подчсчёт меньшего количество дней, тут просто дерево условий, на конце каждого циклы, где к меньшей дате прибавляется единичка пока она не поровняется с большей
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

void DayOfTheWeek(int day, int month, int year)//просто какая-то формула, нет смысла разбирать, выводим день недели и всё
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
void Menu()//Были сложноси с тем когда надо писать и стирать меню, поэтому сделал функцией, которую часто вызываю, наряду с system("cls")(надеюсь программу будут проверять на винде)
{
	cout << "Программа по работе с календарными числами" << endl << endl << "Введите номер операции с клавиатуры:" << endl;
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
		cout << "Программа по работе с календарными числами" << endl << endl << "Перед работой с основной частью программы необходимо ввести дату" << endl;
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
				cout << "Наберите новую дату:" << endl;
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
				cout << endl << "Введите ещё одну дату, для подсчёта дней между ней и текущей датой" << endl;
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
